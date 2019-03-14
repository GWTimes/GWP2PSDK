//
//  GWP2PClient+HXVision.h
//  GWP2P
//
//  Created by duxiaoyan on 2018/7/27.
//  Copyright © 2018年 apple. All rights reserved.
//

#import <GWP2P/GWP2P.h>

/**
 操作预置位方式
 */
typedef enum GWHXVisonPreseSubcmdType {
    GWHXVisonPreseSubcmdTypeAdd,//增加
    GWHXVisonPreseSubcmdTypeDelete,//删除
    GWHXVisonPreseSubcmdTypeGoTo,//转向
    GWHXVisonPreseSubcmdTypeGet,//获取
} GWHXVisonPreseSubcmdType;

@interface GWP2PClient (HXVision)

#pragma mark 汇讯视通预置位操作
/**
 操作设备预置位

 @param subcmdType              GWHXVisonPreseSubcmdType枚举值
 @param index                   预置位，add、goto传0-4；get传0；delete传bit0-bit4对应值，例如5个预置位都删除，传31
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)operateHXVisonDevicePresetWithSubCmdType:(GWHXVisonPreseSubcmdType)subcmdType
                                     presetIndex:(NSInteger)index
                                        deviceID:(NSString *)deviceID
                                  devicePassword:(NSString *)devicePassword
                                 completionBlock:(CompletionBlock)completionBlock;

@end
