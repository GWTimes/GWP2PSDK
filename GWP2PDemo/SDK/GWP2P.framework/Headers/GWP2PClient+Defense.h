//
/** @file GWP2PClient+Defense.h @brief 处理布撤防和预置位的分类 */
//  P2PSDK
//
//  Created by apple on 17/3/2.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import "GWP2PClient.h"

/**
 操作预置位方式
 */
typedef enum GWPresetPositionOperationType {
    GWPresetPositionOperationTypeTurnTo = 0,/**< 转向某预置位 */
    GWPresetPositionOperationTypeSet,/**< 在当前设备摄像头角度下增加给定索引的预置位，若给定索引设置过预置位，则覆盖原信息 */
    GWPresetPositionOperationTypeQuery,/**< 查看所有预置位信息 */
    GWPresetPositionOperationTypeDelete,/**< 删除某索引的预置位 */
} GWPresetPositionOperationType;


/**
 @brief 定时布防模型，一个 GWSheduleDefencesModel 对象对应一条定时布防数据
 */
@interface GWSheduleDefencesModel : NSObject

@property (nonatomic, assign) BOOL on;  /**< 此定时布防是否打开 */
@property (nonatomic, assign) NSUInteger index; /**< 此布防在设备的位置，一个设备最多五组布防 */
@property (nonatomic, assign) NSUInteger startTime_Hour;    /**< 开始于多少小时 */
@property (nonatomic, assign) NSUInteger startTime_Minute;  /**< 开始于多少分 */
@property (nonatomic, assign) NSUInteger endTime_Hour;      /**< 结束于多少小时 */
@property (nonatomic, assign) NSUInteger endTime_Minute;    /**< 结束于多少分 */
//每天的开关状态
@property (nonatomic, assign) BOOL mondayOn;    /**< 周一是否打开 */
@property (nonatomic, assign) BOOL tuesdayOn;   /**< 周二是否打开 */
@property (nonatomic, assign) BOOL wednesdayOn; /**< 周三是否打开 */
@property (nonatomic, assign) BOOL thursdayOn;  /**< 周四是否打开 */
@property (nonatomic, assign) BOOL fridayOn;    /**< 周五是否打开 */
@property (nonatomic, assign) BOOL saturdayOn;  /**< 周六是否打开 */
@property (nonatomic, assign) BOOL sundayOn;    /**< 周日是否打开 */

@end



/**
 @brief 处理布撤防和预置位的分类
 */
@interface GWP2PClient (Defense)

#pragma mark - 普通布撤防操作
/**
 设置设备布防状态
 
 普通布防只是布防与不布防的操作,定时布防有很多数据,参见 GWSheduleDefencesModel

 @param defenceStateOn    布防的开关状态
 @param deviceID        设备ID
 @param devicePassword  设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceDefenceState:(BOOL)defenceStateOn
                 withDeviceID:(NSString *)deviceID
               devicePassword:(NSString *)devicePassword
              completionBlock:(CompletionBlock)completionBlock;


#pragma mark - 定时布防操作
/**
 获取设备定时布撤防数据：返回的字典中 @"schedule defences" 键对应一个 包含 GWSheduleDefencesModel 的数组
 
 这个接口可判断设备是否支持定时布防,设置接口判断不了
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)getDeviceScheduleDefenceDataWithDeviceID:(NSString *)deviceID
                                 devicePassword:(NSString *)devicePassword
                                completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备定时布撤防：每一次设置都会覆盖原来的布防记录，且index自动从0开始排
 
 若接口调用不成功,请先调获取定时布防数据接口判断设备是否支持,如果设备不支持,只会返回连接失败
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceSheduleDefenceData:(NSArray<GWSheduleDefencesModel *> *)sheduleDefencesArray
                       withDeviceID:(NSString *)deviceID
                     devicePassword:(NSString *)devicePassword
                    completionBlock:(CompletionBlock)completionBlock;

#pragma mark 预置位操作
/**
 操作设备预置位
 
 功能介绍:摇头机转动位置，可以让用户设置几个特定的点,记住摇头机的位置(如门、窗或者其他位置)，设置好之后，发转向预置位指令，摇头机将转动到记住的位置
 
 获取时completionBlock返回信息 :
 
 @"preset position indexes" 键对应一个保存已有预置位索引值的数组 NSMutableArray<NSNumber *> *
 
 indexesArray传值：
 
 查看时indexesArray传nil或空数组。
 
 转向某预置位时传一个元素，传多个取第一个，传nil或空数组取索引值为0的预置位。
 
 添加预置位时传一个元素，一次只能添加一个预置位，传多个取第一个元素，传nil或空数组取索引值为0的预置位。
 
 删除时传一个或多个元素，一次能删除多个预置位。不能传空数组或nil
 
 @param operationType           GWPresetPositionOperationType枚举值
 @param indexesArray            保存预置位索引值的数组:索引值范围为0-4，一个设备最多5个预置位，索引值不能重复如@[@(0), @(3)]。
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)operateDevicePresetPositionWithOperationType:(GWPresetPositionOperationType)operationType
                            presetPositionIndexArray:(NSArray<NSNumber *> *)indexesArray
                                            deviceID:(NSString *)deviceID
                                      devicePassword:(NSString *)devicePassword
                                     completionBlock:(CompletionBlock)completionBlock;

@end
