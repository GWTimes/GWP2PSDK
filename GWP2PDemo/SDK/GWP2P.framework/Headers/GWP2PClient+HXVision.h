//
//  GWP2PClient+HXVision.h
//  GWP2P
//
//  Created by duxiaoyan on 2018/7/27.
//  Copyright © 2018年 apple. All rights reserved.
//

#import <GWP2P/GWP2P.h>
#import <Foundation/Foundation.h>
#import "GWP2PPlayerDefine.h"
#import <UIKit/UIKit.h>

/**
 操作预置位方式
 */
typedef enum  GWHXVisionPresetSubCmdType {
    GWHXVisionPresetSubCmdTypeAdd,//增加
    GWHXVisionPresetSubCmdTypeDelete,//删除
    GWHXVisionPresetSubCmdTypeGoTo,//转向
    GWHXVisionPresetSubCmdTypeGet,//获取
} GWHXVisionPresetSubCmdType;

@interface GWP2PClient (HXVision)

#pragma mark 汇讯视通预置位操作
/**
 操作设备预置位

 @param subCmdType              GWHXVisionPresetSubCmdType枚举值
 @param index                   预置位，add、goto传0-4；get传0；delete传bit0-bit4对应值，例如5个预置位都删除，传31
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)operateHXVisionDevicePresetWithSubCmdType:(GWHXVisionPresetSubCmdType)subCmdType
                                      presetIndex:(NSInteger)index
                                         deviceID:(NSString *)deviceID
                                   devicePassword:(NSString *)devicePassword
                                  completionBlock:(CompletionBlock)completionBlock;


-(void)hxVision3DGestureCommand:(GWP2PHXVision3DGestureZoomType)zoomType
                   withDeviceID:(NSString *)deviceID
                 devicePassword:(NSString *)devicePassword
                          point:(CGPoint)point
                           size:(CGSize)size
                   andChannelId:(int)channelId;

- (void)sendHXCommandTypeAndOption:(GWP2PHXVisionDirection)direction andChannelId:(int)channelId;

@end
