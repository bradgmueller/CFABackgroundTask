//
//  UIApplication+CFABackgroundTask.h
//

#import <UIKit/UIKit.h>

/**
 An object to retain a UIBackgroundTaskIdentifier and be responsible for safely invalidating it upon expiration
 */
@interface CFABackgroundTask : NSObject

/** A unique identifier for the background task */
@property (nonatomic, readonly) NSString *identifier;

/** Returns whether or not the background task is still active, or has been invalidated */
@property (nonatomic, readonly) BOOL isActive;

- (instancetype)init __attribute__((unavailable("Use the UIApplication category methods")));

/** Invalidates the background task if it has not already been invalidated */
- (void)invalidate;

@end

@interface UIApplication (CFABackgroundTask)

/** Create and begin a new background task */
+ (CFABackgroundTask *)cfa_backgroundTask;

/** Create and begin a new background task, with an optional block to run upon the tasks expiration */
+ (CFABackgroundTask *)cfa_backgroundTaskWithExpiration:(void(^)())expiration;

@end
