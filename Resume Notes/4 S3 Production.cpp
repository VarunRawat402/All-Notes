------------------------------------------------------------------------------------------------------------------------------------------------
S3 Production Code:
------------------------------------------------------------------------------------------------------------------------------------------------

S3 Client Configuration Class:

@Configuration
public class S3Config {

    @Value("${aws.accessKeyId}")
    private String accessKey;

    @Value("${aws.secretKey}")
    private String secretKey;

    @Value("${aws.region}")
    private String region;

    @Bean
    public S3Client s3Client() {
        validateProperties();
        AwsBasicCredentials credentials = AwsBasicCredentials.create(accessKey, secretKey);
        return S3Client.builder()
                       .region(Region.of(region))
                       .credentialsProvider(StaticCredentialsProvider.create(credentials))
                       .build();
    }

    @Bean
    public S3Presigner s3Presigner() {
        validateProperties();
        AwsBasicCredentials credentials = AwsBasicCredentials.create(accessKey, secretKey);
        return S3Presigner.builder()
                          .region(Region.of(region))
                          .credentialsProvider(StaticCredentialsProvider.create(credentials))
                          .build();
    }

    private void validateProperties() {
        if (accessKey == null || accessKey.isEmpty()) {
            throw new IllegalArgumentException("AWS accessKey must not be null or empty");
        }
        if (secret == null || secret.isEmpty()) {
            throw new IllegalArgumentException("AWS secret must not be null or empty");
        }
        if (region == null || region.isEmpty()) {
            throw new IllegalArgumentException("AWS region must not be null or empty");
        }
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

Database Entity to Map the file, user and S3 Key:

@Entity
@Table(name = "files")
public class FileEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private String originalFileName;
    private String s3Key;
    private String uploadedBy; // optional: track user
    private LocalDateTime uploadedAt = LocalDateTime.now();
}

------------------------------------------------------------------------------------------------------------------------------------------------

Repository:

@Repository
public interface FileRepository extends JpaRepository<FileEntity, Long> {
    Optional<FileEntity> findByOriginalFileNameAndUploadedBy(String originalFileName, String uploadedBy);
}

------------------------------------------------------------------------------------------------------------------------------------------------

S3 Service:

@Service
public class S3Service {

    private final S3Client s3Client;
    private final S3Presigner presigner;
    private final FileRepository fileRepository;

    @Value("${aws.s3.bucket}")
    private String bucketName;

    public S3Service(S3Client s3Client, S3Presigner presigner, FileRepository fileRepository) {
        this.s3Client = s3Client;
        this.presigner = presigner;
        this.fileRepository = fileRepository;
    }

    // Upload file and save mapping in DB
    public FileEntity uploadFile(MultipartFile file, String uploadedBy) throws IOException {
        String key = UUID.randomUUID() + "-" + file.getOriginalFilename();

        PutObjectRequest putRequest = PutObjectRequest.builder()
                                                      .bucket(bucketName)
                                                      .key(key)
                                                      .acl(ObjectCannedACL.PRIVATE)
                                                      .build();

        s3Client.putObject(putRequest, RequestBody.fromBytes(file.getBytes()));

        FileEntity entity = new FileEntity();
        entity.setOriginalFileName(file.getOriginalFilename());
        entity.setS3Key(key);
        entity.setUploadedBy(uploadedBy);

        return fileRepository.save(entity);
    }

    // Generate pre-signed URL for download
    public String generatePresignedUrl(String s3Key, Duration expiry) {
        GetObjectRequest getObjectRequest = GetObjectRequest.builder()
                                                            .bucket(bucketName)
                                                            .key(s3Key)
                                                            .build();

        GetObjectPresignRequest presignRequest = GetObjectPresignRequest.builder()
                                                                       .signatureDuration(expiry)
                                                                       .getObjectRequest(getObjectRequest)
                                                                       .build();

        return presigner.presignGetObject(presignRequest).url().toString();
    }

    @GetMapping("/list")
    public ResponseEntity<List<Map<String, Object>>> listFiles(@RequestParam(required = false) String user) {
        List<FileEntity> files = s3Service.listAllFiles(user);

        List<Map<String, Object>> response = files.stream().map(file -> {
            Map<String, Object> map = new HashMap<>();
            map.put("id", file.getId());
            map.put("fileName", file.getOriginalFileName());
            map.put("uploadedBy", file.getUploadedBy());
            map.put("uploadedAt", file.getUploadedAt());
            // Generate pre-signed URL for download
            String url = s3Service.generatePresignedUrl(file.getS3Key(), Duration.ofMinutes(5));
            map.put("downloadUrl", url);
            return map;
        }).collect(Collectors.toList());

        return ResponseEntity.ok(response);
    }

    @DeleteMapping("/delete/{key}")
    public ResponseEntity<String> deleteFile(@PathVariable String key) {
        s3Service.deleteFile(key);
        return ResponseEntity.ok("File deleted successfully: " + key);
    }

    private File convertMultiPartFileToFile(MultipartFile file) {
        File convertedFile = new File(file.getOriginalFilename());
        try (FileOutputStream fos = new FileOutputStream(convertedFile)) {
            fos.write(file.getBytes());
        } catch (IOException e) {
            log.error("Error converting multipartFile to file", e);
        }
        return convertedFile;
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

S3 Controller:
@RestController
@RequestMapping("/api/files")
public class S3Controller {

    private final S3Service s3Service;
    private final FileRepository fileRepository;

    public S3Controller(S3Service s3Service, FileRepository fileRepository) {
        this.s3Service = s3Service;
        this.fileRepository = fileRepository;
    }

    // Upload file and return download URL
    @PostMapping("/upload")
    public ResponseEntity<Map<String, String>> uploadFile(@RequestParam("file") MultipartFile file,
                                                          @RequestParam("user") String user) throws IOException {
        FileEntity entity = s3Service.uploadFile(file, user);
        String url = s3Service.generatePresignedUrl(entity.getS3Key(), Duration.ofMinutes(5));

        Map<String, String> response = new HashMap<>();
        response.put("fileName", entity.getOriginalFileName());
        response.put("key", entity.getS3Key());
        response.put("url", url);

        return ResponseEntity.ok(response);
    }

    // Get download URL for existing file
    @GetMapping("/download-url")
    public ResponseEntity<Map<String, String>> getDownloadUrl(@RequestParam String fileName,
                                                              @RequestParam String user) {
        FileEntity entity = fileRepository.findByOriginalFileNameAndUploadedBy(fileName, user)
                                          .orElseThrow(() -> new RuntimeException("File not found"));

        String url = s3Service.generatePresignedUrl(entity.getS3Key(), Duration.ofMinutes(5));
        return ResponseEntity.ok(Collections.singletonMap("url", url));
    }

    public List<FileEntity> listAllFiles(String uploadedBy) {
        // Option 1: Fetch from DB (recommended)
        return fileRepository.findAll()
                             .stream()
                             .filter(f -> uploadedBy == null || f.getUploadedBy().equals(uploadedBy))
                             .collect(Collectors.toList());


    public void deleteFile(String key) {
        // Delete from S3
        DeleteObjectRequest deleteRequest = DeleteObjectRequest.builder()
                                                               .bucket(bucketName)
                                                               .key(key)
                                                               .build();
        s3Client.deleteObject(deleteRequest);

        // Delete from DB
        fileRepository.findByS3Key(key).ifPresent(fileRepository::delete);
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

Interview questions for S3:

1. What is a pre-signed URL in AWS S3? Why do we use it?
    Temporary URL for accessing private S3 objects.
    Allows clients to download/upload without AWS credentials.
    URL expires after a defined time.

------------------------------------------------------------------------------------------------------------------------------------------------

2. Difference between MultipartFile and File:
MultipartFile handles HTTP uploads from clients in Spring, while File represents a local file on disk. In production, we usually stream MultipartFile directly to S3.

------------------------------------------------------------------------------------------------------------------------------------------------

3. How to upload a file to S3 in Spring Boot?
Spring receives MultipartFile.
Upload using AWS SDK, streaming InputStream or temporary File.
Use unique key for storage.
"In Spring Boot, I take the uploaded MultipartFile, generate a unique key, and upload it to S3 using AWS SDK. Streaming InputStream directly to S3 is preferred in production."

------------------------------------------------------------------------------------------------------------------------------------------------

4: Do you always need to convert MultipartFile to File:
No. Conversion is optional. Streaming InputStream directly to S3 is more efficient and avoids unnecessary disk I/O.

------------------------------------------------------------------------------------------------------------------------------------------------

5: How to handle large files in S3 upload/download?
For large files, I stream InputStream to S3 and use pre-signed URLs for downloads. For very large uploads, S3’s multipart upload feature is used to handle chunked transfers.

------------------------------------------------------------------------------------------------------------------------------------------------

6: How to delete a file in S3 while keeping DB consistent?
I delete the object from S3 using its key and then remove the corresponding DB record. This ensures both storage and metadata remain consistent

------------------------------------------------------------------------------------------------------------------------------------------------

7: How to list all files uploaded by a user? Fetch from S3 or DB?
I fetch the list of files from the database, optionally filtered by user. This is more efficient than listing directly from S3, especially for large buckets

------------------------------------------------------------------------------------------------------------------------------------------------

8: Explain streaming uploads/downloads
Streaming uploads and downloads use InputStreams to transfer data, preventing high memory usage and improving performance for large files.

------------------------------------------------------------------------------------------------------------------------------------------------

9: If user reports broken download link, what could be the problem?
The broken link could be due to URL expiration, incorrect S3 key, missing object, or permission issues. I would regenerate a fresh pre-signed URL for the user

------------------------------------------------------------------------------------------------------------------------------------------------



