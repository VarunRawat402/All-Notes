------------------------------------------------------------------------------------------------------------------------------------------------------------
AWS LAMBDA:
------------------------------------------------------------------------------------------------------------------------------------------------------------

→ lets you run code when triggered
→ In EC2 Instance, Application runs all the time even if nothing is getting processed
→ In Lambda, Code runs only when request comes or processing happening otherwise stops

Features & Limitations:
    1: Serverless → Runs your code without creating any server
    2: Pay only for the execution time
    3: Auto scales instantly
    4: Timeout limit is 15 minutes → if request takes longer than that, it will not be processed
    5: Memory up to 10 GB
    6: Code size up to 250 MB

Event Triggers:
    1: HTTP Request → API Gateway → Lambda
    2: File Upload → S3 → Lambda
    3: Database Change → DynamoDB → Lambda
    4: Schedule → CloudWatch Events → Lambda
    5: Message → SQS → Lambda

------------------------------------------------------------------------------------------------------------------------------------------------------------

How Lambda works:

1: You create a lambda function
    → Create a java code / class in IDE
    → Create jar file of that specific code
    → Upload it on AWS Lambda

2: Add a trigger
    → Create a trigger to run the lambda
    → Attach the trigger to lambda

------------------------------------------------------------------------------------------------------------------------------------------------------------

LifeCycle:
    Trigger → Lambda Container starts → Runs your code → Returns result → Container may stay warm for reuse

------------------------------------------------------------------------------------------------------------------------------------------------------------

SpringBoot Application Invoking Lambda:

1: Create AWS Lambda client
2: Create invokeRequest
3: Use invoke method and pass invoke request to run the lambda

@Service
public class ReportService {
    
    @Autowired
    private AWSLambda lambdaClient;
    
    public void generateReportAsync(ReportRequest request) {
        // Async report generation
        InvokeRequest invokeRequest = new InvokeRequest()
            .withFunctionName("report-generator-lambda")
            .withPayload(JsonUtils.toJsonString(request));
        
        lambdaClient.invoke(invokeRequest);
        // Returns immediately, Lambda runs in background
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------------------

Example of Thumbnail Generator on Lambda:

Lambda Code:

public class ThumbnailGenerator implements RequestHandler<S3Event, String> {
    public String handleRequest(S3Event event, Context context) {
        // Get uploaded file from S3 event
        String bucket = event.getRecords().get(0).getS3().getBucket().getName();
        String key = event.getRecords().get(0).getS3().getObject().getKey();
        
        // Download image, create thumbnail, upload back
        // Runs only when image uploaded
        // Spring Boot doesn't wait for this - async!
        
        return "Thumbnail created";
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------------------

Real Use Cases of Lambda:

Use Case 1: User Registration:
    Spring Boot: Handles registration form
    Lambda: Sends welcome email (triggered by DB insert)

Use Case 2: File Processing:
    Spring Boot: Accepts file upload
    Lambda: Converts PDF to images (triggered by S3 upload)

Use Case 3: Scheduled Tasks:
    Spring Boot: Main application
    Lambda: Daily report generation (triggered by CloudWatch schedule)

------------------------------------------------------------------------------------------------------------------------------------------------------------