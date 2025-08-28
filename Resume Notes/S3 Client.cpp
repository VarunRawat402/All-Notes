------------------------------------------------------------------------------------------------------------------------------------------------
S3 : AWS Simple Storage service
------------------------------------------------------------------------------------------------------------------------------------------------

Can store big files
Control authorized access with IAM policies
Store files as objects Each object contains : Data, MetaData ( Contenttype, Size , Key( Unique key u create by UUID + filename )
Can Upload and download data using restAPI

------------------------------------------------------------------------------------------------------------------------------------------------

Steps :

1: Bean Configuration
Create S3Client using S3Client Builder to setup the configurations like region and credentials

2: UploadFile Function:

//Takes Multipart file 
//Creates Filename which is unique using UUID Random
//Use PutObjectRequest to create the request to upload to S3
//Create it using bucket name and file key and content type
//Use S3 Client and putObject to upload the file into the S3
//It returns the file key save it in the DB

public String uploadFile(MultipartFile file) throws IOException {
    // Create a unique key (file name)
    String fileKey = UUID.randomUUID() + "_" + file.getOriginalFilename();

    PutObjectRequest putObjectRequest = PutObjectRequest.builder()
            .bucket(bucketName)
            .key(fileKey)
            .contentType(file.getContentType())
            .build();

    PutObjectResponse response = s3Client.putObject(
            putObjectRequest,
            software.amazon.awssdk.core.sync.RequestBody.fromBytes(file.getBytes())
    );

    return fileKey; // You can save this key into DB
}

3: Download File:

//We have bucket name we can pass in this function

public byte[] downloadFile(String bucketName, String key) {
        try {
            GetObjectRequest getObjectRequest = GetObjectRequest.builder()
                    .bucket(bucketName)
                    .key(key)
                    .build();

            ResponseBytes<GetObjectResponse> objectBytes = s3Client.getObjectAsBytes(getObjectRequest);
            return objectBytes.asByteArray();
        } catch (S3Exception e) {
            throw new RuntimeException("Failed to download file: " + e.awsErrorDetails().errorMessage(), e);
        }
    }


------------------------------------------------------------------------------------------------------------------------------------------------

Upload:

Create a S3 Client

Takes MultiPart file
Create key using UUID_filename
Create putRequest using bucketname, key, contentType
Use putResponse to upload the file in S3
returns file key and store in DB

------------------------------------------------------------------------------------------------------------------------------------------------

Download:
Take key
Create getRequest with bucketname, key
Use s3 Client to download the file and return it as ByteArray
Extract the file name by splitting _ 
and then return the file and file

------------------------------------------------------------------------------------------------------------------------------------------------