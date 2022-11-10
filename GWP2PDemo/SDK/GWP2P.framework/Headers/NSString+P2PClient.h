//
//  NSString+P2PClient.h
//  Test
//
//  Created by apple on 17/1/18.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GWP2PDefine.h"

@interface NSString (P2PClient)

/**
 @abstract 是不是纯数字
 */
- (BOOL)isValidateNumber;

/**
 @abstract 是不是登陆技威服务器后返回的有效的认证码
 */
- (BOOL)isValidateP2PVerifyCode;

/**
 获取管理员密码强度
 @return 管理员密码强度
 */
- (P2PAdministratorPasswordStrength)administratorPasswordStrength;

/**
 16进制字符串转为10进制

 @return 十进制的
 */
- (unsigned char)charToInt;

@end
