//
//  AppDelegate.m
//  GWP2P
//
//  Created by zengyuying on 17/5/22.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import "AppDelegate.h"
#import <GWP2P/GWP2P.h>

@interface AppDelegate ()

@end

@implementation AppDelegate


- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
    // Override point for customization after application launch.
    return YES;
}


- (void)applicationWillResignActive:(UIApplication *)application {
    // Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
    // Use this method to pause ongoing tasks, disable timers, and invalidate graphics rendering callbacks. Games should use this method to pause the game.
}


- (void)applicationDidEnterBackground:(UIApplication *)application {
    
//    UIApplication *app = [UIApplication sharedApplication];
//    UIBackgroundTaskIdentifier taskID = 0;
//    taskID = [app beginBackgroundTaskWithExpirationHandler:^{
//        [[GWP2PClient sharedClient] disconnect];
//        [app endBackgroundTask:taskID];
//    }];
//
//    if (taskID == UIBackgroundTaskInvalid) {
//        [[GWP2PClient sharedClient] disconnect];
//        NSLog(@"Failed to start background task!");
//        return;
//    }

}


- (void)applicationWillEnterForeground:(UIApplication *)application {
    // Called as part of the transition from the background to the active state; here you can undo many of the changes made on entering the background.
}


- (void)applicationDidBecomeActive:(UIApplication *)application {
    // Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
}


- (void)applicationWillTerminate:(UIApplication *)application {
    // Called when the application is about to terminate. Save data if appropriate. See also applicationDidEnterBackground:.
}


@end
