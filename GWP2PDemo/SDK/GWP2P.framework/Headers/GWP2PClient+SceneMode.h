//
/** @file GWP2PClient+SceneMode.h @brief 处理情景模式的分类 */
//  P2PSDK
//
//  Created by apple on 17/3/6.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import "GWP2PClient.h"


/**
 情景模式
 */
typedef NS_ENUM(NSUInteger, GWP2PSceneMode) {
    GWP2PSceneModeAtHome = 1,/**< 在家 */
    GWP2PSceneModeGoOut,     /**< 外出 */
    GWP2PSceneModeSleep,     /**< 睡眠 */
};


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
 防护模式
 */
typedef NS_ENUM(NSInteger, GWProtectionPlanMode) {
    GWProtectionPlanModeNotSurpport, /**< 设备不支持 */
    GWProtectionPlanModeOut = 1,    /**< 外出 值和固件保持一致 */
    GWProtectionPlanModeAtHome, /**< 在家 */
};

/**
 防护计划模型
 */
@interface GWProtectionPlanModel : NSObject<NSCopying>

@property (nonatomic, assign) BOOL enable;  /**< 是否生效 */
@property (nonatomic, assign) GWProtectionPlanMode mode;  /**< 防护模式 */
@property (nonatomic, assign) NSUInteger hour;  /**< 时间：时 */
@property (nonatomic, assign) NSUInteger minute;  /**< 时间：分 */

@end

/**
 各传感器的防护设置状态
 */
typedef NS_ENUM(uint8_t, GWProtectionSettingState) {
    GWProtectionSettingStateNotSurpport, /**< 设备不支持 */
    GWProtectionSettingStateOn = 1,    /**< 状态开 */
    GWProtectionSettingStateOff, /**< 状态关 */
};
/**
 各传感器的防护设置状态
 */
typedef NS_ENUM(uint8_t, GWProtectionSettingBodyState) {
    GWProtectionSettingBodyStateNotSurpport = 0, /**< 设备不支持 */
    GWProtectionSettingBodyStateOn = 3,    /**< 状态开 */
    GWProtectionSettingBodyStateOnlyBodyOff =7, /**< 状态关 */
 
};


/**
 防护设置模型
 */
@interface GWProtectionSettingModel : NSObject


@property (nonatomic, assign) GWProtectionPlanMode protectionMode;

@property (nonatomic, assign) GWProtectionSettingState motionDetectState; /**< 移动侦测 */
@property (nonatomic, assign) NSInteger alarmSensitivity;/**< 报警灵敏度，同之前的移动侦测灵敏度 0-6表示灵敏度值，7表示不支持 */
@property (nonatomic, assign) GWProtectionSettingState objectTrackingState; /**< 物件追踪 */
@property (nonatomic, assign) GWProtectionSettingState humanBodyInfraredState; /**< 人体红外 */
@property (nonatomic, assign) GWProtectionSettingState externalAlarmInputState; /**< 外部报警输入 */
@property (nonatomic, assign) GWProtectionSettingState externalAlarmOutputState; /**< 外部报警输出 */
@property (nonatomic, assign) GWProtectionSettingState externalSensorState; /**< 外部传感器 */
@property (nonatomic, assign) GWProtectionSettingBodyState body_detect; /**< 人体侦测 &1 bit 0 表示不支持  1 支持    &4 bit 3 0表示仅人形   1表示物件跟人形都支持  人形侦测 0不支持 3打开 7关闭*/ 

@end



/**
 @brief 处理情景模式的分类
 */
@interface GWP2PClient (SceneMode)

/**
 设置设备的情景模式，仅868情景模式设备支持

 @param mode 情景模式，1,表示在家
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceSceneMode:(GWP2PSceneMode)mode
              withDeviceID:(NSString *)deviceID
            devicePassword:(NSString *)devicePassword
           completionBlock:(CompletionBlock)completionBlock;

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


//设置优化由于和之前的情景模式比较相似，因此放到这个分类里面

/**
 获取设备的防护计划
 
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)getDeviceProtectionPlansWithDeviceID:(NSString *)deviceID
                              devicePassword:(NSString *)devicePassword
                             completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备的防护计划
 
 @param protectionPlansArray 防护计划数组
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceProtectionPlans:(NSArray<GWProtectionPlanModel *> *)protectionPlansArray
                    withDeviceID:(NSString *)deviceID
                  devicePassword:(NSString *)devicePassword
                 completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备的防护计划模式
 
 @param protectionPlanMode 防护计划模式
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceProtectionPlanMode:(GWProtectionPlanMode)protectionPlanMode
                       withDeviceID:(NSString *)deviceID
                     devicePassword:(NSString *)devicePassword
                    completionBlock:(CompletionBlock)completionBlock;

/**
 获取设备对应模式的防护设置
 
 completionBlock返回数据 @“protection setting” 对应一个类 GWProtectionSettingModel
 
 @param protectionMode 防护模式
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)getDeviceProtectionSettingsWithProtectionMode:(GWProtectionPlanMode)protectionMode
                                             deviceID:(NSString *)deviceID
                                       devicePassword:(NSString *)devicePassword
                                      completionBlock:(CompletionBlock)completionBlock;

/**
 设置防护模式
 
 @param protectionSetting 设置项类，如果获取时设备不支持那一项，设置时也请传不支持
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceProtectionSettings:(GWProtectionSettingModel *)protectionSetting
                           deviceID:(NSString *)deviceID
                     devicePassword:(NSString *)devicePassword
                    completionBlock:(CompletionBlock)completionBlock;

/**
 设置报警推送间隔
 
 @param timeinterval 报警推送间隔，可设的值有 10 60 300 600 1800，单位为秒
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceAlarmTimeinterval:(NSInteger)timeinterval
                      withDeviceID:(NSString *)deviceID
                    devicePassword:(NSString *)devicePassword
                   completionBlock:(CompletionBlock)completionBlock;


@end
