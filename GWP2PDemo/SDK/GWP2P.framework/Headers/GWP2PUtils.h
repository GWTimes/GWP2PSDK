//
//  GWP2PUtils.h
//  P2PSDK
//
//  Created by apple on 17/4/1.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import <Foundation/Foundation.h>


//密码头,处理密码时用
#define PASSWORD_HEAD @"passwordhead"



@interface GWP2PUtils : NSObject

/*
 关于密码的说明:
 第一阶段:添加设备、修改密码，要求: 非空、非0开头、<10位、纯数字
 设置设备初始密码、修改设备密码 同上
 数据库直接保存
 
 第二阶段:添加设备、修改密码，         要求:非空、非0开头、<=30位
 设置设备初始密码、修改设备密码 要求:非空、非0开头、<=30位， 非弱密码
 数据库保存:若是10位以下非0开头的纯数字密码,直接保存;否则，加密，头部加'0'保存。
 
 第三阶段:添加设备、修改密码，        只允许输入:非空、<=30位、的密码
 设置设备初始密码、修改设备密码        只允许输入:非空、<=30位、的密码
 数据库保存:PASSWORD_HEAD+原文保存。
 */
+ (unsigned int)getTreatedPassword:(NSString *)sPassword;

+ (NSString *)getMobileIPAddress;

+ (NSString*)currentWifiSSID;

/**
 获取设备IP
 
 若设备与手机在同一局域网中,则返回设备局域网IP,用于手机与设备的局域网通信,否则返回 0

 @param deviceID 设备ID

 @return 设备IP地址
 */
+ (NSInteger)getDeviceIPByID:(NSString *)deviceID;

/**
 获取局域网中的设备ID

 @param deviceIP 设备IP地址的最后一位
 @return 设备ID
 */
/// 坑，这写的啥玩意，完全不靠谱 2019-05-29
+ (NSString *)getDeviceIDByIP:(NSInteger)deviceIP;

/**
 获取ap模式下局域网中的设备IP
 */
+ (unsigned int)getDeviceIPInAPMode;

/**
 获取ap模式下局域网中的设备ID
 */
+ (unsigned int)getDeviceIDInAPMode;

@end
