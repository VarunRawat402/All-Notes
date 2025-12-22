------------------------------------------------------------------------------------------------------------------------------------------------
S3 Explanation:
------------------------------------------------------------------------------------------------------------------------------------------------

Upload Files:

Backend uploads are mainly for small files. 
For larger files, we use pre-signed S3 URLs to avoid loading large files through the service and to improve scalability.

------------------------------------------------------------------------------------------------------------------------------------------------

Approach 1 — Backend uploads to S3 (simple + controlled):
Used when files are small or medium sized (< 5MB).

Flow:
Client sends file to backend API (multipart/form-data)
Backend:
    Validates file type/size
    Generates S3 object key (folder + UUID)
    Uploads to S3 using AWS SDK
    Backend saves metadata in DB
    Backend returns success response

The upload API accepts multipart files, validates size and type, generates a unique object key, and uploads the file to S3 using the AWS SDK. 
We store file metadata like object key, bucket name, and owner in the database.

MetaData:
id, user_id, bucket_name, object_key, original_file_name, content_type, file_size, created_at

------------------------------------------------------------------------------------------------------------------------------------------------

Approach 2 — Pre-signed URLs (most common in real production):

Backend does not handle large files
Reduces server load
Faster uploads/downloads

Flow:
Client calls backend
Backend:
    Authenticates user
    Generates pre-signed PUT URL (valid for 5-15 minutes)
    Stores expected object key in DB
Client uploads file directly to S3
Client notifies backend upload is complete (optional)


------------------------------------------------------------------------------------------------------------------------------------------------

Note:
In production we never store access keys in code. The application uses IAM roles, and AWS SDK automatically picks up credentials

------------------------------------------------------------------------------------------------------------------------------------------------

Error Handling:
    File size exceeded
    Unsupported content type
    S3 upload failure
    Expired pre-signed URL
    Unauthorized access

------------------------------------------------------------------------------------------------------------------------------------------------

Pre-Signed URLs:
It is a normal HTTP URL which can perform operation like get or put or post on a specific object
Contains temporary aws signature

Flow:

Front-end gets the url from backend:
{
  "uploadUrl": "https://s3.amazonaws.com/....",
  "objectKey": "user-uploads/123/uuid_file.pdf"
}

It directly calls S3 like this:
Method: PUT
URL: pre-signed URL
Body: raw file bytes
Headers:
    Content-Type (must match what backend used)

------------------------------------------------------------------------------------------------------------------------------------------------
Success Upload:
------------------------------------------------------------------------------------------------------------------------------------------------

Approach A — Client confirms upload (most common):

Flow
Client uploads file to S3 using pre-signed URL
    If upload succeeds (HTTP 200):
    POST /files/{id}/complete

Backend:
    Verifies file exists in S3 (HEAD object)
    Updates status → COMPLETED

------------------------------------------------------------------------------------------------------------------------------------------------

Approach B — Backend async verification (also used)

Scheduled job checks:
    PENDING records older than X minutes
    Uses HEAD Object call to S3
    If object exists → COMPLETED
    If expired → FAILED

------------------------------------------------------------------------------------------------------------------------------------------------

What happens if upload fails:
    If upload fails, the record stays in PENDING state

------------------------------------------------------------------------------------------------------------------------------------------------

Flow:

Small files:

Frontend -> Backend -> Upload Files -> SUCCESS -> DB(COMPLETED)
Frontend -> (fail) -> Throws Exception -> Handled

Large Files:
For this mechanism client must send the confirmation back to backend:

Frontend → Backend → DB(PENDING) → pre-signed URL → Frontend
Frontend → S3 → Backend verify → DB(COMPLETED)
Frontend → (fail) → DB(PENDING/FAILED) → Cleaned up after some time

------------------------------------------------------------------------------------------------------------------------------------------------

Testing:

What we did is basically tested it with Temp aws account with limited access like  s3 get and put roles
Used postman to hit the api and check in temps3 if file is uploaded 
Test database for metadata is stored or not
Download using presigned url to check if download works

------------------------------------------------------------------------------------------------------------------------------------------------

IAM Role:
Iam role is configured through machine in EC2 and use AWS SDK 	

------------------------------------------------------------------------------------------------------------------------------------------------

AWS SDK:
It is a library provided amazon web services software development kit
It is used to interact with aws services without calling aws api directly

It means isntead of calling s3 apis directlt we uses s3Client.PutObectRequest and s3Client.getObjectRequest

------------------------------------------------------------------------------------------------------------------------------------------------

ENV Variables:
we dont hardcode things like accessRequest, maxRetryCount, bucketName
accessRequest are automatically injected using IAM Role, attach IAM role to the machine
and @Value(${}) are used to get the env values and inject them in properties file
env can be passed in when created config files in k8s or set in ECS set env 

------------------------------------------------------------------------------------------------------------------------------------------------

FLOW:
We created multiple api to upload
1: First Normal upload -> creates file name + gets presigned url to upload + returns URL + saves and marks the filEntity as pending
2: Completed API -> gets the fileEntity and marks it as completed from pending
3: Retry -> if retry gets the fileEntity if completed -< Throw error, If pending or failed + marks as pending again + generate new presign url and returns it
4: if retry reaches max retry count throw error 

------------------------------------------------------------------------------------------------------------------------------------------------

Code:

Application file:
aws.region=ap-south-1
aws.s3.bucket=${S3_BUCKET_NAME}
file.upload.max-retry=${MAX_RETRY_COUNT:3}

Fetch from k8s config files

------------------------------------------------------------------------------------------------------------------------------------------------

File Entity:

@Entity
@Data
@Builder
@AllArgsConstructor
@NoArgsConstructor
public class FileRecord {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private Long userId;
    private String objectKey;
    private String fileName;
    private String contentType;
    private String status; // PENDING, COMPLETED, FAILED

    private LocalDateTime createdAt;
    private LocalDateTime updatedAt;

    @PrePersist
    protected void onCreate() {
        createdAt = LocalDateTime.now();
        updatedAt = createdAt;
    }

    @PreUpdate
    protected void onUpdate() {
        updatedAt = LocalDateTime.now();
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------
DTOS:

@Data
public class UploadRequest {
    private String fileName;
    private String contentType;
}

@Data
@AllArgsConstructor
public class UploadResponse {
    private Long fileId;
    private String preSignedUrl;
}

------------------------------------------------------------------------------------------------------------------------------------------------
Service:

@Service
@RequiredArgsConstructor
public class FileService {

    private final FileRepository fileRepository;
    private final S3Client s3Client;
    private final S3Presigner s3Presigner;

    @Value("${aws.s3.bucket}")
    private String bucketName;

    public UploadResponse createUpload(String fileName, String contentType, Long userId) {
        String objectKey = userId + "/" + UUID.randomUUID() + "_" + fileName;

        FileRecord fileRecord = FileRecord.builder()
                .userId(userId)
                .objectKey(objectKey)
                .fileName(fileName)
                .contentType(contentType)
                .status("PENDING")
                .build();
        fileRepository.save(fileRecord);

        String url = generatePreSignedUrl(objectKey, contentType);
        return new UploadResponse(fileRecord.getId(), url);
    }

    public void completeUpload(Long fileId, Long userId) {
        FileRecord file = fileRepository.findByIdAndUserId(fileId, userId)
                .orElseThrow(() -> new RuntimeException("File not found"));

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

    public UploadResponse downloadFile(Long fileId, Long userId) {
        FileRecord file = fileRepository.findByIdAndUserId(fileId, userId)
                .orElseThrow(() -> new RuntimeException("File not found"));

        if (!file.getStatus().equals("COMPLETED")) {
            throw new RuntimeException("File not available for download");
        }

        GetObjectRequest getRequest = GetObjectRequest.builder()
                .bucket(bucketName)
                .key(file.getObjectKey())
                .build();

        PresignedGetObjectRequest presignedRequest = s3Presigner.presignGetObject(
                GetObjectPresignRequest.builder()
                        .getObjectRequest(getRequest)
                        .signatureDuration(Duration.ofMinutes(10))
                        .build()
        );

        return new UploadResponse(file.getId(), presignedRequest.url().toString());
    }

    private String generatePreSignedUrl(String objectKey, String contentType) {
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

    @PostMapping
    public UploadResponse createUpload(@RequestBody UploadRequest request,
                                       @RequestHeader("userId") Long userId) {
        return fileService.createUpload(request.getFileName(), request.getContentType(), userId);
    }

    @PostMapping("/{fileId}/complete")
    public void completeUpload(@PathVariable Long fileId,
                               @RequestHeader("userId") Long userId) {
        fileService.completeUpload(fileId, userId);
    }
    
    @GetMapping("/{fileId}/download")
    public UploadResponse downloadFile(@PathVariable Long fileId,
                                       @RequestHeader("userId") Long userId) {
        return fileService.downloadFile(fileId, userId);
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------