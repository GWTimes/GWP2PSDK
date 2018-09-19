//
//  GWP2PClient+WhiteLight.h
//  GWP2P
//
//  Created by USER on 2018/4/20.
//  Copyright © 2018年 apple. All rights reserved.
//

#import <GWP2P/GWP2P.h>



/**
 白光灯定时动作模型,每天到达这个时间,设备怎么执行白光灯的开关动作
 */
@interface GWWhiteLightScheduleModel : NSObject <NSCopying>

@property (nonatomic, assign) BOOL on;/**< 此时间点是开灯还是关灯 */

@property (nonatomic, assign) NSUInteger hour;/**< 时,取值 0-23 */
@property (nonatomic, assign) NSUInteger munite;/**< 分 取值 0-59 */

@property (nonatomic, assign) BOOL enable;/**< 此时间设置是否生效 */

@end


/**
 设备声控抓拍截图的图片模型
 */
@interface GWSoundControlPictureModel : NSObject

@property (nonatomic, assign) NSInteger year; /**< 图片生成时间 年 */
@property (nonatomic, assign) NSInteger month; /**< 图片生成时间 月 */
@property (nonatomic, assign) NSInteger day; /**< 图片生成时间 日 */
@property (nonatomic, assign) NSInteger hour; /**< 图片生成时间 时 */
@property (nonatomic, assign) NSInteger minute; /**< 图片生成时间 分 */
@property (nonatomic, assign) NSInteger second; /**< 图片生成时间 秒 */
@property (nonatomic, assign) NSInteger number; /**< 如果1秒内有多张抓图,这个值代表第几张,一般是0 */
@property (nonatomic, copy) NSString *type; /**< 字母"V" 区别于设备其它图片类型 */

@property (nonatomic, copy) NSString *path; /**< 图片在设备中的路径,调下载文件接口需要传入此路径 */

@end



@interface GWP2PClient (WhiteLight)

#pragma mark - 白光灯
/**
 设置白光灯开关状态
 
 所有时间只能一次修改,不能一次只改一个时间点
 
 获取开关状态及支不支持白光灯功能请调  getMultipledeviceStatusWithDeviceID:password:completionBlock:

 @param on 开关状态
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceWhiteLightState:(BOOL)on
                    withDeviceID:(NSString *)deviceID
                  devicePassword:(NSString *)devicePassword
                 completionBlock:(CompletionBlock)completionBlock;

/**
 获取白光灯定时动作设置
 
 设置和获取两条指令不能同时调,内部可能会把两条指令的回调搞混

 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)getDeviceWhiteLightSchedulesWithDeviceID:(NSString *)deviceID
                                  devicePassword:(NSString *)devicePassword
                                 completionBlock:(CompletionBlock)completionBlock;

/**
 设置白光灯定时动作,最多能设置6个时间
 
 设置和获取两条指令不能同时调,内部可能会把两条指令的回调搞混
 
 @param modelsArray 时间设置模型数组,多于6个时间会返回参数错误,数据模型里的时间数据不能重复
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceWhiteLightSchedules:(NSArray<GWWhiteLightScheduleModel *> *)modelsArray
                        withDeviceID:(NSString *)deviceID
                      devicePassword:(NSString *)devicePassword
                     completionBlock:(CompletionBlock)completionBlock;

#pragma mark - 声控
/**
 设置白光灯亮度,这个功能是在做声控时才加的,只有支持声控的设备才支持此功能
 
 获取亮度请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:

 @param brightnessPersent 亮度百分比,取值范围0-100,建议设置范围为10-100
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceWhiteLightBrightness:(NSUInteger)brightnessPersent
                         withDeviceID:(NSString *)deviceID
                       devicePassword:(NSString *)devicePassword
                      completionBlock:(CompletionBlock)completionBlock;

/**
 获取声控拍照截图
 
 返回数据格式:@{@"picktures" : @[ GWSoundControlPictureModel ]}

 @param fromDate 开始时间,如果传nil,会默认为1970-1-1 00:00:01
 @param toDate 结束时间,如果传nil,会默认为2050-1-1 00:00:01
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)getDeviceSoundControlPickturesFromDate:(NSDate *)fromDate
                                        toDate:(NSDate *)toDate
                                      deviceID:(NSString *)deviceID
                                devicePassword:(NSString *)devicePassword
                               completionBlock:(CompletionBlock)completionBlock;

/**
 获取声控状态
 
 目前设备支持 录像(record),拍照(capture),情景切换(work mode),灯光控制(lampligh) 4种声控状态
 
 返回数据包括4种声控是否单独打开,及声控总开关状态"sound control",总开关关闭后,其它4种声控都无效

 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)getDeviceSoundControlStateWithDeviceID:(NSString *)deviceID
                                devicePassword:(NSString *)devicePassword
                               completionBlock:(CompletionBlock)completionBlock;

/**
 设置声控总状态
 
 是否能让声音控制生效

 @param on 是否打开
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceSoundControlState:(BOOL)on
                      withDeviceID:(NSString *)deviceID
                    devicePassword:(NSString *)devicePassword
                   completionBlock:(CompletionBlock)completionBlock;

/**
 设置声控录像状态
 
 声音控制能否控制录像
 
 @param on 是否打开
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceSoundControlRecordState:(BOOL)on
                            withDeviceID:(NSString *)deviceID
                          devicePassword:(NSString *)devicePassword
                         completionBlock:(CompletionBlock)completionBlock;

/**
 设置声控拍照状态
 
 声音控制能否控制拍照
 
 @param on 是否打开
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceSoundControlCaptureState:(BOOL)on
                             withDeviceID:(NSString *)deviceID
                           devicePassword:(NSString *)devicePassword
                          completionBlock:(CompletionBlock)completionBlock;

/**
 设置声控情景切换状态
 
 声音控制能否切换情景状态
 
 @param on 是否打开
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceSoundControlWorkModeState:(BOOL)on
                      withDeviceID:(NSString *)deviceID
                    devicePassword:(NSString *)devicePassword
                   completionBlock:(CompletionBlock)completionBlock;

/**
 设置声控灯光控制状态
 
 声音控制能否控制灯光开关
 
 @param on 是否打开
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceSoundControlLamplighState:(BOOL)on
                      withDeviceID:(NSString *)deviceID
                    devicePassword:(NSString *)devicePassword
                   completionBlock:(CompletionBlock)completionBlock;

@end
