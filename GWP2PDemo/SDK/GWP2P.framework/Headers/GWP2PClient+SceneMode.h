//
/** @file GWP2PClient+SceneMode.h @brief 处理情景模式的分类 */
//  P2PSDK
//
//  Created by apple on 17/3/6.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import "GWP2PClient.h"

typedef enum GWP2PSceneMode {
    GWP2PSceneModeAtHome = 1,//在家
    GWP2PSceneModeGoOut,     //外出
    GWP2PSceneModeSleep,     //睡眠
} GWP2PSceneMode;


/**
 @brief 情景模式，一个 GWSceneModeModel 对象对应一条情景模（定时组、防防护计划）式数据
 */
@interface GWSceneModeModel : NSObject

@property (nonatomic, assign) BOOL on;  /**< 此情景模式是否打开 */
@property (nonatomic, assign) NSUInteger index; /**< 此情景模式在设备的位置, 一个设备最多6个 index为0-5 */
@property (nonatomic, assign) NSUInteger startTime_Hour;    /**< 开始于多少小时 */
@property (nonatomic, assign) NSUInteger startTime_Minute;  /**< 开始于多少分 */
@property (nonatomic, assign) GWP2PSceneMode workMode;  /**< 工作模式 */

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
 @brief 处理情景模式的分类
 */
@interface GWP2PClient (SceneMode)

/**
 获取设备所有情景模式
 
 completionBlock返回字典
 
 @"device scene models" 键对应一个数组 NSArray<GWSceneModeModel *> *
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)getDeviceSceneModelsWithDeviceID:(NSString *)deviceID
                          devicePassword:(NSString *)devicePassword
                         completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备一个情景模式(定时组、防护计划)
 
 非情景模式设备不要调用该指令，虽然可能会成功。发送命令给设备后，设备就会自动在指定的时间开启相应的模式
 
 @param aSceneModeModel         一个情景模式的模型
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setADeviceSceneModel:(GWSceneModeModel *)aSceneModeModel
                withDeviceID:(NSString *)deviceID
              devicePassword:(NSString *)devicePassword
             completionBlock:(CompletionBlock)completionBlock;

/**
 删除设备一个情景模式(定时组、防护计划)
 
 非情景模式设备不要调用该指令，虽然可能会成功。
 
 @param aSceneModeIndex         一个情景模式的索引值
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)removeADeviceSceneModelAtIndex:(NSUInteger)aSceneModeIndex
                          withDeviceID:(NSString *)deviceID
                        devicePassword:(NSString *)devicePassword
                       completionBlock:(CompletionBlock)completionBlock;

@end
