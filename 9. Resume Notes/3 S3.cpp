------------------------------------------------------------------------------------------------------------------------------------------------
S3 Explanation:
------------------------------------------------------------------------------------------------------------------------------------------------

Upload Files:

1: Small Files:
    → FE sends file to backend 
    → Backend uploads files 

2: Large Files:
    → FE sends file data to backend 
    → Backend generate pre-signed URL 
    → FE uploads the file

------------------------------------------------------------------------------------------------------------------------------------------------

Pre-Signed URLs:
    → It is a normal HTTP URL which can perform operation like get or put or post on a specific object
    → Contains temporary access to S3

{
  "uploadUrl": "https://s3.amazonaws.com/....",
  "objectKey": "user-uploads/123/uuid_file.pdf"
}

------------------------------------------------------------------------------------------------------------------------------------------------

Testing:

→ We tested using temp AWS account with limited access like S3
→ Used postman to hit the api and check if file is uploaded or not
→ Test database If metadata is stored or not
→ Download using presigned url to check if download works

------------------------------------------------------------------------------------------------------------------------------------------------

S3 Client Configuration Class:

public class S3Config {

    @Bean
    public S3Client s3Client() {
        return S3Client.builder().region(Region.of(region)).build();
    }

    @Bean
    public S3Presigner s3Presigner() {
        return S3Presigner.builder().region(Region.of(region)).build();
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------
File Entity:

public class FileRecord {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private Long userId;
    private String objectKey;
    private String fileName;
    private String contentType;
    private String status; // PENDING, COMPLETED, FAILED
}

------------------------------------------------------------------------------------------------------------------------------------------------

Service:

public class FileService {

    private final FileRepository fileRepository;
    private final S3Client s3Client;
    private final S3Presigner s3Presigner;

    public UploadResponse getUploadUrl(String fileName, String contentType, Long userId) {

        String objectKey = "files/users/" + userId + "/" + UUID.randomUUID() + "/" + fileName;

        FileRecord fileRecord = FileRecord.builder()
                .userId(userId)
                .objectKey(objectKey)
                .fileName(fileName)
                .contentType(contentType)
                .status("PENDING")
                .build();
        fileRepository.save(fileRecord);

        String url = generateUploadUrl(objectKey, contentType);
        return new UploadResponse(fileRecord.getId(), url);
    }

    public UploadResponse getDownloadUrl(Long fileId, Long userId) {

        FileRecord file = fileRepository.findByIdAndUserId(fileId, userId).orElseThrow(() -> new RuntimeException("File not found"));

        if (!file.getStatus().equals("COMPLETED")) {
            throw new RuntimeException("File not available for download");
        }

        String url = generateDownloadUrl(file.getObjectKey());
        return new UploadResponse(file.getId(), url);
    }

    public void deleteFile(String key){

        DeleteObjectRequest deleteRequest = DeleteObjectRequest.builder().bucket(bucketName).key(key).build();
        s3Client.deleteObject(deleteRequest);

        fileRepository.findByS3Key(key).ifPresent(fileRepository::delete);
    }

    public void verifyFileOnS3(Long fileId, Long userId){

        FileRecord file = fileRepository.findByIdAndUserId(fileId, userId).orElseThrow(() -> new RuntimeException("File not found"));

        try {
            s3Client.headObject(HeadObjectRequest.builder()
                    .bucket(bucketName)
                    .key(file.getObjectKey())
                    .build());
        } catch (NoSuchKeyException e) {
            throw new RuntimeException("Upload not found in S3");
        }

        file.setStatus("COMPLETED");
        fileRepository.save(file);
    }

    private String generateDownloadUrl(String objectKey) {
        GetObjectRequest getRequest = GetObjectRequest.builder()
                .bucket(bucketName)
                .key(objectKey)
                .build();

        PresignedGetObjectRequest presignedRequest = s3Presigner.presignGetObject(
                GetObjectPresignRequest.builder()
                        .getObjectRequest(getRequest)
                        .signatureDuration(Duration.ofMinutes(10))
                        .build());

        return presignedRequest.url().toString()
    }

    private String generateUploadUrl(String objectKey, String contentType) {
        PutObjectRequest putRequest = PutObjectRequest.builder()
                .bucket(bucketName)
                .key(objectKey)
                .contentType(contentType)
                .build();

        PresignedPutObjectRequest presignedRequest =
                s3Presigner.presignPutObject(PutObjectPresignRequest.builder()
                        .putObjectRequest(putRequest)
                        .signatureDuration(Duration.ofMinutes(10))
                        .build());

        return presignedRequest.url().toString();
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

Controller:

@RestController
@RequestMapping("/files")
@RequiredArgsConstructor
public class FileController {

    private final FileService fileService;

    @PostMapping("/upload")
    public UploadResponse getUploadUrl(@RequestBody UploadRequest request, @RequestHeader("userId") Long userId) {
        return fileService.getUploadUrl(request.getFileName(), request.getContentType(), userId);
    }
    
    @GetMapping("/{fileId}/download")
    public UploadResponse getDownloadUrl(@PathVariable Long fileId, @RequestHeader("userId") Long userId) {
        return fileService.getDownloadUrl(fileId, userId);
    }

    @PostMapping("/{fileId}/complete")
    public void verifyFileOnS3(@PathVariable Long fileId, @RequestHeader("userId") Long userId) {
        fileService.verifyFileOnS3(fileId, userId);
    }

    @DeleteMapping("/delete/{key}")
    public ResponseEntity<String> deleteFile(@PathVariable String key) {
        s3Service.deleteFile(key);
        return ResponseEntity.ok("File deleted successfully: " + key);
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

Upload file from Backend:

public FileEntity uploadFile(MultipartFile file, Long userId) throws IOException {

    String objectKey = "files/users/" + userId + "/" + UUID.randomUUID() + "/" + file.getOriginalFilename();

    PutObjectRequest putRequest = PutObjectRequest.builder().bucket(bucketName).key(key).build();
    s3Client.putObject(putRequest, RequestBody.fromBytes(file.getBytes()));
}

------------------------------------------------------------------------------------------------------------------------------------------------

Interview questions for S3:

1. What is a pre-signed URL in AWS S3? Why do we use it?
    → Temporary URL for accessing private S3 objects.
    → Allows clients to download/upload without AWS credentials.
    → URL expires after a defined time.

------------------------------------------------------------------------------------------------------------------------------------------------

2. Difference between MultipartFile and File:
    → MultipartFile handles HTTP uploads from clients in Spring
    → File represents a local file on disk. 
    → In production, we usually stream MultipartFile directly to S3.

------------------------------------------------------------------------------------------------------------------------------------------------

4: Do you always need to convert MultipartFile to File:
    → No. 
    → Conversion is optional. 
    → Streaming InputStream directly to S3 is more efficient and avoids unnecessary disk I/O.

------------------------------------------------------------------------------------------------------------------------------------------------

5: How to handle large files in S3 upload/download?
    → For large files, I stream InputStream to S3 and use pre-signed URLs for downloads. 

------------------------------------------------------------------------------------------------------------------------------------------------

8: Explain streaming uploads/downloads
    → Streaming uploads and downloads use InputStreams to transfer data, preventing high memory usage and improving performance for large files.

------------------------------------------------------------------------------------------------------------------------------------------------

9: If user reports broken download link, what could be the problem?
    → The broken link could be due to URL expiration, incorrect S3 key, missing object, or permission issues. I would regenerate a fresh pre-signed URL for the user

------------------------------------------------------------------------------------------------------------------------------------------------

