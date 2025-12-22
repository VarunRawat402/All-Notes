------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Logging
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Centralized Logging Systems:
    Logs from all services are aggregated to a central system.
    ELK Stack: Elasticsearch (store), Logstash (process), Kibana (view)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

1. Elasticsearch:
Distributed search engine.
Stores logs as JSON documents.
Provides fast querying, filtering, and aggregation.

Log Example:
{
  "@timestamp": "2025-12-21T04:10:00Z",
  "level": "ERROR",
  "service": "user-service",
  "traceId": "ab123",
  "message": "User creation failed",
  "exception": "DuplicateKeyException"
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

2. Logstash:
Log processing and transformation pipeline.
Collects logs → parses → enriches → sends to Elasticsearch.
Logs come in different formats (JSON, plain text).
Adds metadata (service name, environment, host).

Application → Logstash → Elasticsearch

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

3. Kibana:
Visualization and log analysis UI.
Used by developers, support, and SRE teams.
Search logs (traceId: ab123)
Filter by time, service, log level
Create dashboards (error rate, latency)
Set alerts (via Elastic rules)

Example:
All errors in user-service:
service:"user-service" AND level:"ERROR"

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Log Levels:

ERROR: Something failed that needs attention.
WARN: Unexpected behavior but not critical.
INFO: Normal application flow (user actions, service calls).
DEBUG: Detailed info for troubleshooting (only enabled in dev or when debugging).
TRACE: Very fine-grained info (rarely used in production due to volume).

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Log Format:
    Plain text: Easy to read but hard to parse.
    JSON: Structured, easy to query in ELK/CloudWatch.

Example:

    {
    "timestamp": "2025-12-20T15:00:00Z",
    "level": "ERROR",
    "service": "user-service",
    "message": "Failed to fetch user",
    "userId": 12345,
    "traceId": "abcd-1234"
    }

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

How logs are written in application:

@Slf4j
@Service
public class UserService {

    public void createUser(User user) {
        log.info("Creating user {}", user.getEmail());

        try {
            // business logic
        } catch (Exception e) {
            log.error("User creation failed", e);
            throw e;
        }
    }
}

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
How to Check issue:
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Step 1: Identify the context:

Get the identifiers:
    Customer ID, request ID, or timestamp.
    Helps you search logs without scanning everything.
    Know the service where the issue might occur:
    E.g., user-service, transaction-service, notification-service.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Step 2: Search logs

Use the centralized logging UI:
    Kibana (ELK/EFK) → search by requestId, customerId, error level, or time range.
    CloudWatch → use filters and logs insights queries.
    Look at ERROR or WARN logs first.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Step 3: Correlate logs

If microservices are involved:
get the traceId of the request and search in other services to get the error
Helps find which service failed.

Check for:
Exceptions
Validation errors
Timeout / network errors
Database errors

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Step 4: Check metrics & monitoring (optional)
Check dashboards (Prometheus/Grafana, CloudWatch metrics):
Error rate spike
Latency
Request volume
Sometimes logs alone arent enough — metrics help locate the problem.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

In production, logs are centralized using ELK/CloudWatch. Each service writes structured logs with timestamps, log level, and request/customer ID. 
When a customer creation fails, I first get the request or customer ID, search it in the logs to see which service failed, 
check error messages and stack traces, correlate logs across services using trace IDs, 
and then identify the root cause — whether its a validation error, DB issue, or external service failure.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------