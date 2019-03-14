//
/** @file GWP2PLanDevice.h @brief 局域网设备模型 */
//  UDPSocket
//
//  Created by apple on 17/5/2.
//  Copyright © 2017年 apple. All rights reserved.
//
//  局域网搜索的返回的设备信息

#import <Foundation/Foundation.h>
#import "GWP2PDevice.h"
/**
 @brief 局域网设备模型
 */
@interface GWP2PLanDevice : NSObject

/** 设备ID */
@property (nonatomic, copy) NSString *deviceId;

/** 设备类型 */
@property (nonatomic, assign) GWP2PDeviceType deviceType;

/** 设备IP地址 */
@property (nonatomic, copy) NSString *ipAddress;

/** 搜索到的时间 */
@property (nonatomic, assign) NSTimeInterval lanTimeInterval;

/** 是否设置过密码 */
@property (nonatomic, assign) BOOL isInitPassword;

/** 是否支持RTSP */
@property (nonatomic, assign) NSInteger isSupportRtsp;

/** 客户ID */
@property (nonatomic, assign) NSInteger customID;

/** MAC地址12个字母 */
@property (nonatomic, copy) NSString *macAddress;

/** 设备加密功能选项 */
@property (nonatomic, assign) uint64_t deviceFuciton;

@end
