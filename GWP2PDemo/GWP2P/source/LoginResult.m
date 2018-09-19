//
//  LoginResult.m
//  GWP2P
//
//  Created by apple on 17/6/13.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import "LoginResult.h"

static NSString *loginAccount = nil;

static NSString *_p2pVerifyCode1 = nil;
static NSString *_p2pVerifyCode2 = nil;
static NSString *_sessionID1 = nil;
static NSString *_sessionID2 = nil;

@implementation LoginResult

+ (void)setAccount:(NSString *)account {
    NSLog(@"登陆账号为:%@", account);
    loginAccount = account;
}

+ (NSString *)getAccount {
    return loginAccount;
}

+ (void)setP2PVerifyCode1:(NSString *)p2pVerifyCode1 {
    NSLog(@"认证码1:%@", p2pVerifyCode1);
    _p2pVerifyCode1 = p2pVerifyCode1;
}

+ (NSString *)getP2PVerifyCode1 {
    return _p2pVerifyCode1;
}

+ (void)setP2PVerifyCode2:(NSString *)p2pVerifyCode2 {
    NSLog(@"认证码2:%@", p2pVerifyCode2);
    _p2pVerifyCode2 = p2pVerifyCode2;
}

+ (NSString *)getP2PVerifyCode2 {
    return _p2pVerifyCode2;
}

+ (void)setSessionID1:(NSString *)sessionID1 {
    NSLog(@"sessionID1:%@", sessionID1);
    _sessionID1 = sessionID1;
}

+ (NSString *)getSessionID1 {
    return _sessionID1;
}

+ (void)setSessionID2:(NSString *)sessionID2 {
    NSLog(@"sessionID2:%@", sessionID2);
    _sessionID2 = sessionID2;
}

+ (NSString *)getSessionID2 {
    return _sessionID2;
}

@end
