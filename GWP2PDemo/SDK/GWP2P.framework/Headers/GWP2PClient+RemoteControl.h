//
//  GWP2PClient+RemoteControl.h
//  GWP2P
//
//  Created by JonorZhang on 2019/8/29.
//  Copyright © 2019 apple. All rights reserved.
//

#import <GWP2P/GWP2P.h>

NS_ASSUME_NONNULL_BEGIN

@interface GWP2PClient (RemoteControl)

/**
 多sensor支持。[15:8]支持sensor数量, [7:0]当前选择的sensor索引(注意：索引值是从1开始的，没有用0)
 
 @param index 当前选择的sensor索引(注意：索引值是从1开始的，没有用0)
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setMultiSensorIdx:(UInt16)index
               deviceID:(NSString *)deviceID
         devicePassword:(NSString *)devicePassword
        completionBlock:(CompletionBlock)completionBlock;


/**
 手动红外灯控制
 
 @param on 红外灯状态,1开；0关
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setIRLEDLightOn:(BOOL)on
               deviceID:(NSString *)deviceID
         devicePassword:(NSString *)devicePassword
        completionBlock:(CompletionBlock)completionBlock;

/**
 手动重启设备
 
 @param on 是否重启,1开；0关
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setRemoteReboot:(BOOL)on
               deviceID:(NSString *)deviceID
         devicePassword:(NSString *)devicePassword
        completionBlock:(CompletionBlock)completionBlock ;
@end

NS_ASSUME_NONNULL_END
