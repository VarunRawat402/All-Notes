------------------------------------------------------------------------------------------------------------------------------------------------
S3 — File Upload & Download (AWS + Spring Boot):
------------------------------------------------------------------------------------------------------------------------------------------------

Upload Files:

1: Small Files:
    → FE sends the file directly to the backend.
    → BE uploads the file to S3 using S3Client.
    → Not good for large files

2: Large Files:
    → FE sends only metadata to the backend.
    → BE generates a pre-signed URL
    → FE uploads the file directly to S3
    → Avoids overloading the backend

------------------------------------------------------------------------------------------------------------------------------------------------

Pre-Signed URLs:
    → Its a normal HTTP URL
    → Its "signed" with temporary permission to perform a specific S3 action (GET or PUT) on a specific object.
    → Client needs zero AWS credentials — the permission is baked into the URL.
    → Expires after a set time like 10 minutes.

Example response from backend:
{
  "uploadUrl": "https://s3.amazonaws.com/....",
  "objectKey": "user-uploads/123/uuid_file.pdf"
}

------------------------------------------------------------------------------------------------------------------------------------------------
S3 CONFIGURATION (Spring Boot):
------------------------------------------------------------------------------------------------------------------------------------------------

public class S3Config {

    //To create S3Client for performing S3 operations
    @Bean    
    public S3Client s3Client() {
        return S3Client.builder().region(Region.of(region)).build();
    }

    //To generate pre-signed URLs for upload/download.
    @Bean   
    public S3Presigner s3Presigner() {
        return S3Presigner.builder().region(Region.of(region)).build();
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------
FILE ENTITY (Database Metadata):
------------------------------------------------------------------------------------------------------------------------------------------------

→ Stores meta-data of every file uploaded to S3.
→ Used for tracking and managing files in your application.
→ Status starts as PENDING when the pre-signed URL is issued.
→ Updated to COMPLETED only after frontend confirms upload via /complete endpoint.
→ This prevents phantom records where the URL was issued but upload never happened.

public class FileRecord {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;                                // Primary key

    private Long userId;                            // Owner of the file
    private String objectKey;                       // S3 path: files/users/{userId}/{UUID}/{fileName}
    private String fileName;                        // Original file name
    private String contentType;                     // e.g. "application/pdf"
    private String status;                          // PENDING → COMPLETED | FAILED
}

------------------------------------------------------------------------------------------------------------------------------------------------
SERVICE LAYER:
------------------------------------------------------------------------------------------------------------------------------------------------

getUploadUrl():
    → Create a unique S3 object key: files/users/{userId}/{UUID}/{fileName}
    → Saves FileRecord with status PENDING to the database.
    → Generates a pre-signed URL (valid 10 min).
    → Returns the fileId + URL to the frontend.

verifyFileOnS3()  
    → called by frontend after upload completes:
    → Used to confirm the file actually exists.
    → If found → updates status to COMPLETED in the database.
    → If not found → throws RuntimeException (NoSuchKeyException caught).

getDownloadUrl():
    → Fetches FileRecord by fileId + userId (ownership check).
    → Throws if status is not COMPLETED — prevents downloading incomplete uploads.
    → Generates and returns a pre-signed GET URL (valid 10 min).

deleteFile():
    → Sends DeleteObjectRequest to S3 via S3Client.
    → Deletes the FileRecord from the database to keep both in sync.

------------------------------------------------------------------------------------------------------------------------------------------------
Code:
------------------------------------------------------------------------------------------------------------------------------------------------

public class FileService {

    private final FileRepository fileRepository;
    private final S3Client s3Client;
    private final S3Presigner s3Presigner;

    // Save file metadata in DB and generate pre-signed URL for upload
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

    // Check if file is uploaded to S3 and generate pre-signed URL for download
    public UploadResponse getDownloadUrl(Long fileId, Long userId) {

        FileRecord file = fileRepository.findByIdAndUserId(fileId, userId).orElseThrow(() -> new RuntimeException("File not found"));

        if (!file.getStatus().equals("COMPLETED")) {
            throw new RuntimeException("File not available for download");
        }

        String url = generateDownloadUrl(file.getObjectKey());
        return new UploadResponse(file.getId(), url);
    }

    // Delete file from S3 and remove metadata from DB
    public void deleteFile(String key){

        DeleteObjectRequest deleteRequest = DeleteObjectRequest.builder().bucket(bucketName).key(key).build();
        s3Client.deleteObject(deleteRequest);

        fileRepository.findByS3Key(key).ifPresent(fileRepository::delete);
    }

    // Verify if the file exists on S3 after upload and update status to COMPLETED
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

    // Generate pre-signed URL for download
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

    // Generate pre-signed URL for upload
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
------------------------------------------------------------------------------------------------------------------------------------------------

@RestController
@RequestMapping("/files")
@RequiredArgsConstructor
public class FileController {

    private final FileService fileService;

    // 1. Frontend requests a pre-signed URL to upload
    @PostMapping("/upload")
    public UploadResponse getUploadUrl(@RequestBody UploadRequest request, @RequestHeader("userId") Long userId) {
        return fileService.getUploadUrl(request.getFileName(), request.getContentType(), userId);
    }
    
    // 2. Frontend calls this after upload is done — triggers verify + COMPLETED
    @GetMapping("/{fileId}/download")
    public UploadResponse getDownloadUrl(@PathVariable Long fileId, @RequestHeader("userId") Long userId) {
        return fileService.getDownloadUrl(fileId, userId);
    }

    // 3. Frontend requests a pre-signed URL to download
    @PostMapping("/{fileId}/complete")
    public void verifyFileOnS3(@PathVariable Long fileId, @RequestHeader("userId") Long userId) {
        fileService.verifyFileOnS3(fileId, userId);
    }

    // 4. Delete file from S3 + database
    @DeleteMapping("/delete/{key}")
    public ResponseEntity<String> deleteFile(@PathVariable String key) {
        s3Service.deleteFile(key);
        return ResponseEntity.ok("File deleted successfully: " + key);
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------

DIRECT BACKEND UPLOAD (Small Files):

public FileEntity uploadFile(MultipartFile file, Long userId) throws IOException {

    //Create unique S3 key
    String objectKey = "files/users/" + userId + "/" + UUID.randomUUID() + "/" + file.getOriginalFilename();

    //Create PutObjectRequest with bucket name and key
    PutObjectRequest putRequest = PutObjectRequest.builder().bucket(bucketName).key(key).build();

    // Upload the file to S3 using S3Client
    s3Client.putObject(putRequest, RequestBody.fromBytes(file.getBytes()));
}

Note: file.getBytes() loads entire file into memory.
    → For larger files, prefer RequestBody.fromInputStream(file.getInputStream(), file.getSize()).

------------------------------------------------------------------------------------------------------------------------------------------------

Interview questions for S3:

1. What is a pre-signed URL in AWS S3? Why do we use it?
    → Temporary URL with temporary permissions to perform a specific S3 action (GET or PUT) on a specific object.
    → Allows clients to download/upload without AWS credentials.
    → URL expires after a defined time.

------------------------------------------------------------------------------------------------------------------------------------------------

2. Difference between MultipartFile and File:
    → MultipartFile is Springs representation of a file coming in through an HTTP upload — its what you receive from a client request.
    → File represents an actual file sitting on disk
    → In production, we usually stream MultipartFile directly to S3.

------------------------------------------------------------------------------------------------------------------------------------------------

4: Do you always need to convert MultipartFile to File:
    → No. Its optional and usually wasteful.
    → Stream the InputStream directly using RequestBody.fromInputStream() — more efficient, avoids unnecessary disk I/O.

------------------------------------------------------------------------------------------------------------------------------------------------

5: How to handle large files in S3 upload/download?
    → Dont route file bytes through the backend at all.
    → Generate a pre-signed PUT URL and let the frontend upload directly to S3.
    → For very large files (5GB+), S3 Multipart Upload splits the file into chunks, uploads them in parallel, and assembles them on S3.

------------------------------------------------------------------------------------------------------------------------------------------------

8: Explain streaming uploads/downloads
    → Instead of loading the entire file into memory, streaming uses InputStream to transfer data chunk by chunk.
    → Prevents OutOfMemoryErrors, reduces backend memory pressure, and improves performance for large files.

------------------------------------------------------------------------------------------------------------------------------------------------

9: If user reports broken download link, what could be the problem?
    → Pre-signed URL expired (only valid for 10 minutes).
    → Incorrect objectKey stored in the database.
    → File was never actually uploaded — status never reached COMPLETED.
    → File was deleted from S3 but the DB record still exists.
    → Fix: call headObject to confirm the file exists on S3, then regenerate a fresh pre-signed URL.

------------------------------------------------------------------------------------------------------------------------------------------------

TESTING

→ Used a temporary AWS account with limited IAM permissions (S3 only).
→ Used Postman to hit each endpoint and verify correct responses.
→ Checked the database after upload to confirm metadata was stored.
→ Used the pre-signed GET URL to download and verify the file.
→ Tested /complete endpoint to confirm PENDING → COMPLETED status transition.

------------------------------------------------------------------------------------------------------------------------------------------------