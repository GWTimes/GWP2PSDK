//
//  LoginResult.h
//  GWP2P
//
//  Created by apple on 17/6/13.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface LoginResult : NSObject

+ (void)setAccount:(NSString *)account;
+ (NSString *)getAccount;

+ (void)setP2PVerifyCode1:(NSString *)p2pVerifyCode1;
+ (NSString *)getP2PVerifyCode1;

+ (void)setP2PVerifyCode2:(NSString *)p2pVerifyCode2;
+ (NSString *)getP2PVerifyCode2;

+ (void)setSessionID1:(NSString *)sessionID1;
+ (NSString *)getSessionID1;

+ (void)setSessionID2:(NSString *)sessionID2;
+ (NSString *)getSessionID2;

@end
