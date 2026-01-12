------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Logging
------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Centralized Logging Systems:
    Logs from all services are aggregated to a central system.
    Helps in debugging, monitoring, and auditing.
    ELK Stack: Elasticsearch (store & search), Logstash (process), Kibana (visualize)
    EFK Stack: Elasticsearch, Fluentd, Kibana (commonly used with Kubernetes)

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

1. Elasticsearch:
    Distributed search engine.
    Stores logs as JSON documents (indexed).
    Provides fast querying, filtering, aggregation, and full-text search.
    Scales horizontally.

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

ERROR   : Request failed, needs immediate attention (exceptions, DB failures).
WARN    : Unexpected behavior but request can continue (timeouts, retries).
INFO    : Normal application flow (service start, user actions).
DEBUG   : Detailed debugging info (enabled in lower environments).
TRACE   : Very fine-grained logs (method-level, rarely enabled in prod).

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Log Format:
    Plain text: Easy to read but hard to parse.
    JSON: Key-value based, easy to query, filter, and aggregate.

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
    Kibana (ELK/EFK)    → search by requestId, customerId, error level, or time range.
    CloudWatch          → use filters and logs insights queries.
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

In production, logs are centralized using ELK or CloudWatch. 
Each service writes structured JSON logs containing timestamp, log level, service name, environment, and trace/request ID.
When a customer creation fails, I first obtain the request or trace ID, search it in the logging system, identify the service where the error occurred, 
analyze the error message and stack trace, correlate logs across services using the same trace ID, 
and determine the root cause—whether it is a validation issue, database constraint failure, or an external service timeout.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------
Describe a difficult bug you solved:

My task was to investigate why the search was failing for certain inputs and fix it so that all valid data would be returned correctly. 
The tricky part was that the issue only happened for some scenarios — it wasnt a complete failure, which made it harder to pinpoint

Action / How I Solved It:
I started by checking the logs and monitoring the queries sent to the database. The search queries themselves were being generated correctly and returned the expected results when tested manually.
Then I noticed a pattern: searches that included leading or trailing blank spaces in the search term were returning no results. 
The underlying problem was that while the database had the correct data, the search term provided by the user was not trimmed before being passed to the Spring Data JPA Specification.
As a result, the query was looking for exact matches with extra spaces, which did not exist in the database.
To fix this, I updated the search logic to trim any leading or trailing spaces from the input search term before executing the database query. 
I also added unit tests to cover scenarios with extra spaces, ensuring this wouldnt happen again.

Result / Outcome:
After the fix, the search functionality returned results correctly, even when the users input had extra spaces. This improved the user experience, reduced support tickets related to missing search results, and ensured the search feature was reliable for all scenarios.

------------------------------------------------------------------------------------------------------------------------------------------------------------------------

A production issue you handled:

For old users there are so many transactions for that user so fetching all transactions is taking too long and timing out
So we implemented pagination for fetching transactions, so only a few transactions are fetched at a time and sorted by date 
User gets to see recent transactions first and can load more if needed and they are all are returned in latest order

------------------------------------------------------------------------------------------------------------------------------------------------------------------------