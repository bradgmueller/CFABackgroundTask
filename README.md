# CFABackgroundTask
A simpler way to manage Background Tasks on iOS

Background tasks should be simpler - this category makes creating and ending background tasks quick & easy, and manages safely invalidating the task for you.

## Usage

To start a background task, call `[UIApplication cfa_backgroundTask]`, or optionally `[UIApplication cfa_backgroundTaskWithExpiration:]` to include a block to execute upon expiration.

To end the task, simply call `invalidate` on the object, which will end the task if it hadn't already ended.

Notes - 
 - Hold a reference of the task to ensure it continues - it will automatically end if deallocated.
 - If the task expires, it will automatically end itself to prevent the app from being terminated.

## Example 

### Typical code for a background task:
```
    // Create the background task
    __block UIBackgroundTaskIdentifier bgTask;
    bgTask = [[UIApplication sharedApplication]
              beginBackgroundTaskWithName:nil
              expirationHandler:^{
                  
	          // End the task so the OS doesn’t kill the app
                  if (bgTask != UIBackgroundTaskInvalid)
                  {
                      [[UIApplication sharedApplication] endBackgroundTask:bgTask];
                      bgTask = UIBackgroundTaskInvalid;
                  }
              }];
    
    /* 
        ... Code permitted to execute in background …
    */
    
    // End the task
    if (bgTask != UIBackgroundTaskInvalid)
    {
        [[UIApplication sharedApplication] endBackgroundTask:bgTask];
        bgTask = UIBackgroundTaskInvalid;
    }
```

### With `CFABackgroundTask`, this is simplified to:

```
    // Create the background task
    CFABackgroundTask *task = [UIApplication cfa_backgroundTask];
    
    /* 
        ... Code permitted to execute in background …
    */
    
    // End the task
    [task invalidate];
```

### Test it out

In `[AppDelegate applicationDidEnterBackground:]`, setup some code to fire on delay, and see how it behaves with/without the task. *NOTE: Run on a real device - simulator doesn't always suspend apps in background*
```
    // Start the background task
    CFABackgroundTask *task = [UIApplication cfa_backgroundTask];
    
    // Wait 5 seconds….
    float delayInSeconds = 5.0;
    dispatch_time_t delayTimer = dispatch_time(DISPATCH_TIME_NOW, delayInSeconds * NSEC_PER_SEC);
    dispatch_after(delayTimer, dispatch_get_main_queue(), ^(void){
        
        NSLog(@"Application state: %ld", [[UIApplication sharedApplication] applicationState]);
        NSLog(@"Background Time Remaining: %0.1f", [[UIApplication sharedApplication] backgroundTimeRemaining]);
        
        // End the task 
        [task invalidate];
    });
```
