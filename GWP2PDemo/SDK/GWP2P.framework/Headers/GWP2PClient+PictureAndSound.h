//
/** @file GWP2PClient+PictureAndSound.h @brief 处理图像和声音的分类 */
//  P2PSDK
//
//  Created by apple on 17/2/28.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import "GWP2PClient.h"

/**
 视频制式枚举
 */
typedef enum GWP2PSetVideoFormat{
    GWP2PSetVideoFormatNTSC,
    GWP2PSetVideoFormatPAL
}GWP2PSetVideoFormat;


/**
 @brief 处理图像声音的分类
 */
@interface GWP2PClient (PictureAndSound)

/**
 设置设备视频制式: NTSC , PAL 两种
 
 获取视频制式请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 
 @param videoFormat             视频制式的枚举
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceVideoFormat:(GWP2PSetVideoFormat)videoFormat
                withDeviceID:(NSString *)deviceID
              devicePassword:(NSString *)devicePassword
             completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备音量
 
 获取音量请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 
 @param volume                  0-9的整数
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceVolume:(NSUInteger)volume
           withDeviceID:(NSString *)deviceID
         devicePassword:(NSString *)devicePassword
        completionBlock:(CompletionBlock)completionBlock;

/**
 设置图像倒转状态
 
 获取图像倒转状态请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 
 @param isImageReversed         图像是否倒转
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceImageReverseState:(BOOL)isImageReversed
                      withDeviceID:(NSString *)deviceID
                    devicePassword:(NSString *)devicePassword
                   completionBlock:(CompletionBlock)completionBlock;

/**
 获取设备指示灯状态
 
 返回 BOOL值, 指示灯是否打开
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)getDeviceIndicatorLightStatusWithDeviceID:(NSString *)deviceID
                                   devicePassword:(NSString *)devicePassword
                                  completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备指示灯状态
 
 @param on                      指示灯开头状态
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceIndicatorLightStatus:(BOOL)on
                         withDeviceID:(NSString *)deviceID
                       devicePassword:(NSString *)devicePassword
                      completionBlock:(CompletionBlock)completionBlock;

@end
