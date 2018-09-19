//
//  GWSimpleConfigManager.h
//  GWP2P
//
//  Created by HuangZhen on 2018/6/26.
//  Copyright © 2018年 apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface GWSimpleConfigManager : NSObject

/**
 以SimpleConfig的方式进行配网

 @param wifiName wifi名
 @param wifiPassword wifi密码
 */
+ (void)startWithWifiName:(NSString *)wifiName wifiPassword:(NSString *)wifiPassword;


+ (void)stop;

@end
