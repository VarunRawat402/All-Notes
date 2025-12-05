--------------------------------------------------------------------------------------------------------------------------------------------
S3 Notes:
https://chat.deepseek.com/share/uq0g9zd4v7guje34st
--------------------------------------------------------------------------------------------------------------------------------------------

PutObjectRequest:
    It is a request object that holds all the details needed to upload something to S3.

putObject():

It is the actual S3 client method that performs the upload.

It is overloaded function:
    putObject(String bucket, String key, File file)
    putObject(String bucket, String key, InputStream stream, ObjectMetadata metadata)
    putObject(PutObjectRequest request)

So, putObject() is the function that sends the upload request to AWS.It is the actual S3 client method that performs the upload.

Key: 
It is the file name you create to upload to S3
It has to be unique
Example:
    String fileName = System.currentTimeMillis() + "_" + file.getOriginalFilename();
    String fileKey = UUID.randomUUID() + "_" + file.getOriginalFilename();


S3 Configuration:

@Configuration
public class S3Config {

    private static final Logger log = LoggerFactory.getLogger(S3Config.class);

    @Value("${cloud.aws.credentials.access-key}")
    private String accessKey;

    @Value("${cloud.aws.credentials.secret-key}")
    private String accessSecret;

    @Value("${cloud.aws.region.static}")
    private String region;

    @Bean
    public AmazonS3 s3Client() {

        validateProperties();
        AWSCredentials awsCredentials = new BasicAWSCredentials(accessKey, secret);

        // Logging the creation of AmazonS3 bean
        log.info("Creating AmazonS3 client with region: {}", region);

        return AmazonS3ClientBuilder.standard()
                .withRegion(region)
                .withCredentials(new AWSStaticCredentialsProvider(awsCredentials))
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

Controller:

@RestController
@RequestMapping("/file")
public class S3Contoller {

    @Autowired
    private S3Service s3Service;

    @PostMapping("/upload")
    public ResponseEntity<String> uploadFile(@RequestParam(value = "file") MultipartFile file) {
        return new ResponseEntity<>(service.uploadFile(file), HttpStatus.OK);
    }

    @GetMapping("/download/{fileName}")
    public ResponseEntity<ByteArrayResource> downloadFile(@PathVariable String fileName) {
        byte[] data = service.downloadFile(fileName);
        ByteArrayResource resource = new ByteArrayResource(data);
        return ResponseEntity
                .ok()
                .contentLength(data.length)
                .header("Content-type", "application/octet-stream")
                .header("Content-disposition", "attachment; filename=\"" + fileName + "\"")
                .body(resource);
    }

    @DeleteMapping("/delete/{fileName}")
    public ResponseEntity<String> deleteFile(@PathVariable String fileName) {
        return new ResponseEntity<>(service.deleteFile(fileName), HttpStatus.OK);
    }
}

public interface FileServiceImpl {

    String saveFile(MultipartFile file);

    byte[] downloadFile(String filename);

    String deleteFile(String filename);

    List<String> listAllFiles();
}


Service Class:

@Service
public class S3Service implements FileServiceImpl {

    @Value("${aws.bucketName}")
    private String bucketName;

    private final AmazonS3 s3Client;

    public S3Service(AmazonS3 s3Client) {
        this.s3Client = s3Client;
    }

    @Override
    public String saveFile(MultipartFile file) {
        String originalFilename = file.getOriginalFilename();
        int count = 0;
        int maxTries = 3;
        while (true) {
            try {
                File file1 = convertMultiPartToFile(file);
                PutObjectResult putObjectResult = s3.putObject(bucketName, originalFilename, file1);
                return putObjectResult.getContentMd5();
            } catch (IOException e) {
                if (++count == maxTries)
                    throw new RuntimeException(e);
            }
        }

    }

    @Override
    public byte[] downloadFile(String filename) {
        S3Object object = s3.getObject(bucketName, filename);
        S3ObjectInputStream objectContent = object.getObjectContent();
        try {
            return IOUtils.toByteArray(objectContent);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }

    }

    @Override
    public String deleteFile(String filename) {

        s3.deleteObject(bucketName, filename);
        return "File deleted";
    }

    @Override
    public List<String> listAllFiles() {

        ListObjectsV2Result listObjectsV2Result = s3.listObjectsV2(bucketName);
        return listObjectsV2Result.getObjectSummaries().stream().map(S3ObjectSummary::getKey)
                .collect(Collectors.toList());

    }

    private File convertMultiPartToFile(MultipartFile file) throws IOException {
        File convFile = new File(file.getOriginalFilename());
        FileOutputStream fos = new FileOutputStream(convFile);
        fos.write(file.getBytes());
        fos.close();
        return convFile;
    }
}

@Service
@Slf4j
public class StorageService {

    @Value("${application.bucket.name}")
    private String bucketName;

    @Autowired
    private AmazonS3 s3Client;

    public String uploadFile(MultipartFile file) {
        File fileObj = convertMultiPartFileToFile(file);
        String fileName = System.currentTimeMillis() + "_" + file.getOriginalFilename();
        s3Client.putObject(new PutObjectRequest(bucketName, fileName, fileObj));
        fileObj.delete();
        return "File uploaded : " + fileName;
    }


    public byte[] downloadFile(String fileName) {
        S3Object s3Object = s3Client.getObject(bucketName, fileName);
        S3ObjectInputStream inputStream = s3Object.getObjectContent();
        try {
            byte[] content = IOUtils.toByteArray(inputStream);
            return content;
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }


    public String deleteFile(String fileName) {
        s3Client.deleteObject(bucketName, fileName);
        return fileName + " removed ...";
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