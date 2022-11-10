//
/** @file GWP2PClient+Record.h @brief 处理设备录制的分类 */
//  P2PSDK
//
//  Created by apple on 17/3/6.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import "GWP2PClient.h"

/**
 录像类型
 */
typedef enum GWP2PRecordType{
    GWP2PRecordTypeManual,/**< 手动 */
    GWP2PRecordTypeAlarm,/**< 报警时录像 */
    GWP2PRecordTypeSchedule,/**< 定时录像 */
}GWP2PRecordType;
/**
 云录像质量
 */
typedef enum GWP2PCloudRecordType{
    GWP2PRecordTypeQuilty = 0,/**< 质量优先 */
    GWP2PRecordTypeSmooth = 1,/**< 流畅优先 */
 
}GWP2PCloudRecordType;
/**
 卡录像质量
 */
typedef enum GWP2PCardRecordType{
    GWP2PCardRecordTypeUnsupport = 0,/**< 不支持设置 */
    GWP2PCardRecordTypeStandardDefinition = 1,/**< 标清 */
    GWP2PCardRecordTypeHighDefinition = 2,/**< 高清*/
}GWP2PCardRecordType;

/**
 录制声音开关状态
 */
typedef enum GWP2PRecordVolumeSwitchStatus{
    GWP2PRecordVolumeSwitchStatusUnsupport = 0,/**< 不支持设置 */
    GWP2PRecordVolumeSwitchStatusClose = 1,/**< 关闭*/
    GWP2PRecordVolumeSwitchStatusOpen = 2,/**< 开启 */
}GWP2PRecordVolumeSwitchStatus;
/**
 录像质量
 */
typedef enum GWP2PRecordDefinition {
    GWP2PRecordDefinitionTopSpeed, /**< 极速*/
    GWP2PRecordDefinitionFluent, /**< 流畅 */
    GWP2PRecordDefinitionStandardDefinition, /**< 标清 */
    GWP2PRecordDefinitionHighDefinition, /**< 高清 */
    GWP2PRecordDefinitionSuperDefinition, /**< 超清 */
}GWP2PRecordDefinition;


/**
 @brief 回放文件模型
 */
@interface GWPlaybackFileModel : NSObject

/* 文件时间的Component形式  */
@property (nonatomic, assign) NSInteger year; /**< 文件时间 年 */
@property (nonatomic, assign) NSInteger month; /**< 文件时间 月 */
@property (nonatomic, assign) NSInteger day; /**< 文件时间 日 */
@property (nonatomic, assign) NSInteger hour; /**< 文件时间 时 */
@property (nonatomic, assign) NSInteger minute; /**< 文件时间 分 */
@property (nonatomic, assign) NSInteger second; /**< 文件时间 秒 */
/* 文件时间的NSDate形式  */
@property (nonatomic, strong) NSDate *date; /**< 记录上面的时间 */
/* 文件时间的TimeInterval形式  */
@property (nonatomic, assign) NSInteger startTime;  /**< 开始时间 (秒)*/
@property (nonatomic, assign) NSInteger endTime;    /**< 结束时间 = startTime + duration (秒) */
@property (nonatomic, assign) NSInteger duration;   /**< 文件时长 若不支持, 则为-1 (秒)*/

@property (nonatomic, assign) NSInteger discID; /**< 文件在存储设备的标识 播放时用 */
@property (nonatomic, copy) NSString *cType; /**< 文件类型 一个字符 */

@property (nonatomic, assign) NSInteger month_yoosee; //yoosee专用

@end


/**
 @brief 处理设备录制的分类
 */
@interface GWP2PClient (Record)
#pragma mark - 录像设置
/**
 获取设备SD卡信息
 
 completionBlock返回：
 
 @"storage exist" (存储是否存在，一般为SD卡): BOOL类型
 
 @"storage count" (存储单元数量) ：NSNumber类型
 
 @"total storage" (总存储空间) ： NSNumber类型
 
 @"free storage" (可用空间) ： NSNumber类型
 
 @"unit" : 返回空间数据的单位 M（兆）
 
 @"SD Card ID" : SD卡ID，用于后面对SD卡操作，如格式化
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)getDeviceStorageInformationWithDeviceID:(NSString *)deviceID
                                devicePassword:(NSString *)devicePassword
                               completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备录像类型
 
 获取设备录像类型请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 
 @param recordType              录像类型
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceRecordType:(GWP2PRecordType)recordType
               withDeviceID:(NSString *)deviceID
             devicePassword:(NSString *)devicePassword
            completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备预录像开关状态
 
 获取设备预录像开关状态请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 
 @param prerecordOn             预录像是否打开
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDevicePrerecordState:(BOOL)prerecordOn
                   withDeviceID:(NSString *)deviceID
                 devicePassword:(NSString *)devicePassword
                completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备报警后的录像时间
 
 获取设备报警录像时间请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 
 @param alarmRecordTime         报警录像时间，单位：分 范围（1 ，2，3）
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceAlarmRecordTime:(NSUInteger)alarmRecordTime
                    withDeviceID:(NSString *)deviceID
                  devicePassword:(NSString *)devicePassword
                 completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备计划录像时间
 
 获取设备报警录像时间请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 
 @param fromHour                录像时间开始于几时 (24小时制)
 @param fromMinute              录像时间开始于几分
 @param toHour                  录像时间结束于几时 (24小时制)
 @param toMinute                录像时间结束于几分
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDevicePlanedRecordTimeWithFromHour:(NSUInteger)fromHour
                                   fromMinute:(NSUInteger)fromMinute
                                       toHour:(NSUInteger)toHour
                                     toMinute:(NSUInteger)toMinute
                                     deviceID:(NSString *)deviceID
                               devicePassword:(NSString *)devicePassword
                              completionBlock:(CompletionBlock)completionBlock;

/**
 设置手动录像开关状态:没有SD卡时，设置无效
 
 获取手动录像开关状态请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 
 @param manuallyRecordOn        手动录像是否打开
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceManuallyRecordState:(BOOL)manuallyRecordOn
                        withDeviceID:(NSString *)deviceID
                      devicePassword:(NSString *)devicePassword
                     completionBlock:(CompletionBlock)completionBlock;

/**
 格式化设备SD卡
 
 @param SDCardID                SD卡ID，获取SD卡信息时得到
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)formatDeviceSDCard:(NSUInteger)SDCardID
              withDeviceID:(NSString *)deviceID
            devicePassword:(NSString *)devicePassword
           completionBlock:(CompletionBlock)completionBlock;

/**
 获取录像质量
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)getDeviceRecordDefinitionWithDeviceID:(NSString *)deviceID
                               devicePassword:(NSString *)devicePassword
                              completionBlock:(CompletionBlock)completionBlock;

/**
 设置录像质量
 
 @param recordDefinition        枚举值
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceRecordDefinition:(GWP2PRecordDefinition)recordDefinition
                     withDeviceID:(NSString *)deviceID
                   devicePassword:(NSString *)devicePassword
                  completionBlock:(CompletionBlock)completionBlock;

#pragma mark - 设置云回放上传开关
/**
 设置云回放上传开关
 
 @param on        开关
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setVasSwitchOn:(BOOL)on
              deviceID:(NSString *)deviceID
        devicePassword:(NSString *)devicePassword
       completionBlock:(CompletionBlock)completionBlock;
#pragma mark - 获取回话文件
/**
 获取设备回放文件
 
 一次只能获取64个文件,如果给定的时间差大于64个文件,会分多次获取,一次返回多次获取文件,为保证每次数据都能正常返回,若无特殊要求,两次给定的时间差尽量小点
 
 completionBlock返回字典：
 
 @"files" 键对应一个 NSMutableArray<GWPlaybackFileModel *> *

 @param deviceID        设备ID
 @param devicePassword  设备密码
 @param startDate       获取的文件早于给定的时间,如果传nil,会默认为1970-1-1 00:00
 @param endDate         获取的文件晚于给定的时间,如果传nil,会默认为2050-1-1 00:00
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)getDevicePlaybackFilesWithDeviceID:(NSString *)deviceID
                            devicePassword:(NSString *)devicePassword
                                 startDate:(NSDate *)startDate
                                   endDate:(NSDate *)endDate
                           completionBlock:(CompletionBlock)completionBlock;
#pragma mark - 获取某一天的回放文件
/**
 获取设备回放文件
 
 一次只能获取64个文件,如果给定的时间差大于64个文件,会分多次获取,一次返回多次获取文件,为保证每次数据都能正常返回,若无特殊要求,两次给定的时间差尽量小点
 
 completionBlock返回字典：
 
 @"files" 键对应一个 NSMutableArray<GWPlaybackFileModel *> *
 
 @param deviceID        设备ID
 @param devicePassword  设备密码
 @param dayDate       当天日期，如果传空返回当天日期的回放列表
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)getDeviceOneDayPlaybackFilesOWithDeviceID:(NSString *)deviceID
                            devicePassword:(NSString *)devicePassword
                                 dayDate:(NSDate *)dayDate
                                  completionBlock:(CompletionBlock)completionBlock;
#pragma mark -  获取设备卡回放有有回放文件的列表

/**
 获取设备卡回放有没有云存储

 @param deviceID        设备ID
 @param devicePassword  设备密码
 @param endDate /从哪一天开始向前查找
 @param days /要查找多少天（包括endDate）
 @param completionBlock 与设备交互完成后的回调Block
 */
-(void)getDevcieRecodePlaybackDatesWithDeviceID:(NSString *)deviceID
                                 devicePassword:(NSString *)devicePassword
                                        enddate:(NSDate *)endDate
                                  andSearchDays:(NSInteger )days
                                completionBlock:(CompletionBlock)completionBlock;
#pragma mark -  设置设备云回放上传的质量
/**
 设置设备云回放上传的质量

 @param recordType 设置类型。质量优先与流畅优先
 @param deviceID        设备ID
 @param devicePassword  设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceCloudPlayBackQuality:(GWP2PCloudRecordType)recordType
                         WithDeviceID:(NSString *)deviceID
                       devicePassword:(NSString *)devicePassword
                      completionBlock:(CompletionBlock)completionBlock;


#pragma mark -  设置设备卡回放录像的质量
/**
 设置设备卡回放录像的质量

 @param recordType 设置类型。高清与标清
 @param deviceID        设备ID
 @param devicePassword  设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
 - (void)setDeviceCardPlayBackQuality:(GWP2PCardRecordType)recordType
                                 WithDeviceID:(NSString *)deviceID
                                 devicePassword:(NSString *)devicePassword
                      completionBlock:(CompletionBlock)completionBlock;

/**
 设置录像声音开关

 @param switchStatus 开关类型 0 不支持  1 开 2 关
 @param deviceID        设备ID
 @param devicePassword  设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceRecordVolumeSwitchStatus:(GWP2PRecordVolumeSwitchStatus)status
                                WithDeviceID:(NSString *)deviceID
                                devicePassword:(NSString *)devicePassword
                                completionBlock:(CompletionBlock)completionBlock;
@end


