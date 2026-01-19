-------------------------------------------------------------------------------------------------------------------------------
CompletableFuture:
-------------------------------------------------------------------------------------------------------------------------------

CompletableFuture is a Java class for asynchronous programming:
    Run tasks without blocking threads
    Chain multiple async operations
    Combine results of multiple async tasks
    Handle errors cleanly
    Introduced in Java 8.

-------------------------------------------------------------------------------------------------------------------------------

Old async approach (Future):

Future<User> future = threadPool.submit(() -> getUser());
User user = future.get();                   // BLOCKING ❌

-------------------------------------------------------------------------------------------------------------------------------

1: runAsync():
Returns CompletableFuture<Void>
no return value
Used for fire-and-forget

Code:
CompletableFuture.runAsync(() -> {
    sendEmail();
});

-------------------------------------------------------------------------------------------------------------------------------

2: supplyAsync():
returns a value

Code:
CompletableFuture<User> future =
    CompletableFuture.supplyAsync(() -> getUser());

-------------------------------------------------------------------------------------------------------------------------------
Chaining operations:
-------------------------------------------------------------------------------------------------------------------------------

1: thenApply():
transform result like a map
Runs in same thread

CompletableFuture<UserDto> future =
    CompletableFuture.supplyAsync(() -> getUser())
        .thenApply(user -> convertToDto(user));

-------------------------------------------------------------------------------------------------------------------------------

2: thenApplyAsync():
async transformation
Runs in another thread

.thenApplyAsync(user -> convertToDto(user))

-------------------------------------------------------------------------------------------------------------------------------

3: thenAccept():
consume result (no return)
Access to result

.thenAccept(user -> log.info(user.getName()));

-------------------------------------------------------------------------------------------------------------------------------

4: thenRun():
run something after completion
No access to result

.thenRun(() -> log.info("Done"));

-------------------------------------------------------------------------------------------------------------------------------

5: thenCombine():
combine two futures
CompletableFuture<User> userFuture = getUserAsync();
CompletableFuture<Wallet> walletFuture = getWalletAsync();

CompletableFuture<UserProfile> profile =
    userFuture.thenCombine(walletFuture,
        (user, wallet) -> new UserProfile(user, wallet));

Used when:
Tasks are independent
Need both results

-------------------------------------------------------------------------------------------------------------------------------\
Exception handling
-------------------------------------------------------------------------------------------------------------------------------

2: exceptionally():
fallback

future.exceptionally(ex -> {
    log.error(ex.getMessage());
    return defaultUser;
});

-------------------------------------------------------------------------------------------------------------------------------

2: handle():
success or failure

future.handle((result, ex) -> {
    if (ex != null) return defaultUser;
    return result;
});

-------------------------------------------------------------------------------------------------------------------------------

3: whenComplete():
side-effect only

future.whenComplete((res, ex) -> {
    log.info("Completed");
});

-------------------------------------------------------------------------------------------------------------------------------

Kafka Code:

AddCallBack():

kafkaTemplate.send(topic, key, message)
    .addCallback(
        result -> handleSuccess(result),
        ex -> handleError(ex)
    );


CompletableFuture:

CompletableFuture<SendResult<String, String>> future = kafkaTemplate.send(topic, key, message);
future.thenAccept(result -> handleSuccess(result))
      .exceptionally(ex -> {
          handleError(ex);
          return null;
      });

-------------------------------------------------------------------------------------------------------------------------------
