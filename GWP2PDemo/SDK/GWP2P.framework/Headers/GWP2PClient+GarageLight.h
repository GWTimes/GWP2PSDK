//
//  GWP2PClient+GarageLight.h
//  GWP2P
//
//  Created by duxiaoyan on 2018/6/26.
//  Copyright © 2018年 apple. All rights reserved.
//

#import <GWP2P/GWP2P.h>

@interface GWP2PClient (GarageLight)

/**
 获取车库灯状态
 
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)getGarageLightStatusWithDeviceID:(NSString *)deviceID
                          devicePassword:(NSString *)devicePassword
                         completionBlock:(CompletionBlock)completionBlock;

/**
 设置车库灯手动开关白光灯
 
 @param on 车库灯手动开关白光灯,1开；0关
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setGarageLightWhiteLightOn:(BOOL)on
                          deviceID:(NSString *)deviceID
                    devicePassword:(NSString *)devicePassword
                   completionBlock:(CompletionBlock)completionBlock;

/**
 设置车库灯白光灯控制模式
 
 @param mode 车库灯白光灯控制模式,0—关闭；1—晚上开灯；2—晚上+PIR触发开灯；3—PIR开灯
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setGarageLightWhiteLightMode:(NSInteger)mode
                            deviceID:(NSString *)deviceID
                      devicePassword:(NSString *)devicePassword
                     completionBlock:(CompletionBlock)completionBlock;

/**
 设置车库灯驱逐按钮
 
 @param on 驱逐按钮开关,1开；0关
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setGarageLightExpelOn:(BOOL)on
                     DeviceID:(NSString *)deviceID
               devicePassword:(NSString *)devicePassword
              completionBlock:(CompletionBlock)completionBlock;


/**
 设置车库灯项目PIR触发亮灯时间
 
 @param lightUpTime 车库灯项目PIR触发亮灯时间
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setGarageLightPirLightUpTime:(NSUInteger)lightUpTime
                            deviceID:(NSString *)deviceID
                      devicePassword:(NSString *)devicePassword
                     completionBlock:(CompletionBlock)completionBlock;

@end
