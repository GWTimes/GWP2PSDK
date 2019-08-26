//
/** @file GWP2PClient+Alarm.h @brief 处理设备报警的分类 */
//  P2PSDK
//
//  Created by apple on 17/3/2.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import "GWP2PClient.h"

/**
 邮箱加密方式
 */
typedef enum GWP2PAlarmEmailEncryptType {
    GWP2PAlarmEmailEncryptTypeNone, /**< 不加密 */
    GWP2PAlarmEmailEncryptTypeSSL,  /**< SSL加密 */
    GWP2PAlarmEmailEncryptTypeTLS,  /**< TLS加密 */
}GWP2PAlarmEmailEncryptType;

/**
 解除报警推送账号的操作类型
 */
typedef enum GWUnbindAlarmAccountOperationType {
    GWUnbindAlarmAccountOperationTypeUnbindAlarmAccount = 0,/**< 解除设备报警推送账号(当前登陆服务器的) */
    GWUnbindAlarmAccountOperationTypeStopDoorBellPush = 1,/**< 停止门铃推送至当前账号(当前登陆服务器的) */
}GWUnbindAlarmAccountOperationType;


/**
 @brief 处理设备报警的分类
 */
@interface GWP2PClient (Alarm)

#pragma mark - 设备报警设置
/**
 设置设备移动侦测状态
 
 获取设备移动侦测状态请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 
 @param motionDetetionOn        移动侦测是否打开
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceMotionDetetionState:(BOOL)motionDetetionOn
                        withDeviceID:(NSString *)deviceID
                      devicePassword:(NSString *)devicePassword
                     completionBlock:(CompletionBlock)completionBlock;
/**
 设置设备移动侦测灵敏度
 
 获取设备移动侦测灵敏度请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 
 @param motionDetetionSensitivity   移动侦测灵敏度:0-6,数值越大,灵敏度越高
 @param deviceID                    设备ID
 @param devicePassword              设备密码
 @param completionBlock             与设备交互完成后的回调Block
 */
- (void)setDeviceMotionDetetionSensitivity:(NSUInteger)motionDetetionSensitivity
                              withDeviceID:(NSString *)deviceID
                            devicePassword:(NSString *)devicePassword
                           completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备物件追踪状态
 
 获取设备物件追踪状态请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 
 @param objectTrackingOn        物件追踪是否打开
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceObjectTrackingState:(BOOL)objectTrackingOn
                        withDeviceID:(NSString *)deviceID
                      devicePassword:(NSString *)devicePassword
                     completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备蜂鸣器状态
 
 获取设备蜂鸣器状态请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 
 @param buzzTime                蜂鸣时长,单位为分,可设数字有:0(关闭), 1, 2, 3
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceBuzzerState:(NSUInteger)buzzTime
                withDeviceID:(NSString *)deviceID
              devicePassword:(NSString *)devicePassword
             completionBlock:(CompletionBlock)completionBlock;


/**
 设置设备报警声开关状态
 获取设备报警声开关状态请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 @param alarmOn 开关状0关，1开
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceSpecialAlarmState:(NSUInteger)alarmOn
                      withDeviceID:(NSString *)deviceID
                    devicePassword:(NSString *)devicePassword
                   completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备报警白光灯状态
 获取设备备报警白光灯状态请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 @param alarmOn 开关状0关，1开
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceWhiteAlarmLightState:(NSUInteger)alarmOn
                         withDeviceID:(NSString *)deviceID
                       devicePassword:(NSString *)devicePassword
                      completionBlock:(CompletionBlock)completionBlock;

/**
 设置AI实验室人形侦测开关状态
 获取AI实验室人形侦测开关状态请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 @param detectionOn 开关状0关，1开
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceAIHumanoidDetectionState:(BOOL)detectionOn
                            withDeviceID:(NSString *)deviceID
                          devicePassword:(NSString *)devicePassword
                         completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备红蓝灯开关状态
 获取设备红蓝灯开关状态请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 @param alarmOn 开关状0关，1开
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceRedBluelAlarmLightState:(NSUInteger)alarmOn
                            withDeviceID:(NSString *)deviceID
                          devicePassword:(NSString *)devicePassword
                         completionBlock:(CompletionBlock)completionBlock;
/**
 设置设备人体红外开关状态
 
 获取设备人体红外开关状态请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 
 如果获取不到设备人体红外开关状态,调用些方法无效
 
 @param humanInfraredOn         人体红外是否打开
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceHumanInfraredState:(BOOL)humanInfraredOn
                       withDeviceID:(NSString *)deviceID
                     devicePassword:(NSString *)devicePassword
                    completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备有线报警输入开关状态
 
 获取设备蜂有线报警输入开关状态请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 
 如果获取不到设备有线报警输入开关状态,调用些方法无效
 
 @param wiredAlarmInputOn       有线报警输入是否打开
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceWiredAlarmInputState:(BOOL)wiredAlarmInputOn
                         withDeviceID:(NSString *)deviceID
                       devicePassword:(NSString *)devicePassword
                      completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备有线报警输出开关状态
 
 获取设备蜂有线报警输出开关状态请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 
 如果获取不到设备有线报警输出开关状态,调用些方法无效
 
 @param wiredAlarmOutputOn       有线报警输出是否打开
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceWiredAlarmOutputState:(BOOL)wiredAlarmOutputOn
                          withDeviceID:(NSString *)deviceID
                        devicePassword:(NSString *)devicePassword
                       completionBlock:(CompletionBlock)completionBlock;

/**
 获取设备报警时推送的绑定账号
 
 completionBlock返回字典:
 
 @"account count"               绑定账号的个数
 
 @"account maxCount"            设备最大可绑定账号的个数
 
 @"accounts"                    绑定的账号,类型为 NSArray<NSString *> *
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)getDeviceBindedAlarmAccountWithDeviceID:(NSString *)deviceID
                                 devicePassword:(NSString *)devicePassword
                                completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备报警时推送的绑定账号
 @param accounts                要绑定的账号数组(多个账号),参数为字符串,绑定成功后覆盖原来的数据。账号为登陆技威web服务器后返回的经过 & 0x7fffffff 位处理的数字账号，在yoosee上显示的以0开头的账号
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceBindedAlarmAccounts:(NSArray<NSString *> *)accounts
                        withDeviceID:(NSString *)deviceID
                      devicePassword:(NSString *)devicePassword
                     completionBlock:(CompletionBlock)completionBlock;

/**
 获取设备报警邮箱
 
 completionBlock字典返回:
 
 @"email"              绑定的邮箱，类型：NSString
 
 @"email is verified"  邮箱是否验证，类型：BOOL YES表示未验证,NO表示已验证
 
 @"surport SMTP"       设备是否支持SMTP邮箱，类型：BOOL
 
 @"password is right"  SMTP邮箱密码是否正确，类型：BOOL
 
 @"SMTP server"        SMTP服务器，类型：NSString
 
 @"SMTP port"          SMTP端口，类型：NSNumber
 
 @"SMTP user"          SMTP用户，类型：NSString
 
 @"SMTP password"      SMTP密码，类型：NSString
 
 @"encrypt type"       加密类型，类型：GWP2PAlarmEmailEncryptType
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)getDeviceAlarmEmailWithDeviceID:(NSString *)deviceID
                         devicePassword:(NSString *)devicePassword
                        completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备报警邮箱,设置后返回的数据不准确,再调获取接口获取邮箱数据
 
 老设备,不支持SMTP,是否支持SMTP在获取报警邮箱时得到,则用技威服务器的邮箱发送邮件至设置邮箱
 
 新设备,支持SMTP,报警时,若完整地设置邮箱(SMTP及密码都通过验证),用设置的邮箱发送邮件至设置的邮箱自己
 
 一些常用的邮箱SMTP服务器与端口号:
 
 腾讯: smtp.qq.com 465
 
 yahoo: smtp.mail.yahoo.com 465
 
 google: 173.194.193.108 465, 173.194.67.108 465, smtp.gmail.com 465
 
 189: smtp.189.cn 465
 
 hotEmail: smtp.live.com 465
 
 网易: smtp.163.com 25
 
 新浪: smtp.sina.com.cn 465
 
 completionBlock返回：获取后的邮箱密码等数据可能不准确,可参考的是邮箱是否验证成功,SMTP邮箱密码是否正确
 
 @"success"            BOOL类型，操作是否成功
 
 @"email"              绑定的邮箱，类型：NSString
 
 @"email is verified"  邮箱是否验证，类型：NSNumber 1表示未验证,0表示已验证,这个与其它逻辑相反,要注意
 
 @"surport SMTP"       设备是否支持SMTP邮箱，类型：NSNumber @(BOOL)
 
 @"password is right"  SMTP邮箱密码是否正确，类型：NSNumber @(BOOL)
 
 @param alarmEmail      报警邮箱地址, 解绑时要传 @"0",否则解绑不成功
 @param deviceID        设备ID
 @param devicePassword  设备密码
 @param isSupportSMTP   设备是否支持SMTP邮箱:获取报警邮箱时可获取此参数;若设备支持,必须传入SMTP的服务器、端口、用户名、用户密码才能绑定邮箱，此参数也必须为YES
 @param SMTPServer      SMTP服务器
 @param SMTPPort        SMTP服务器端口
 @param SMTPUser        SMTP用户名:设备报警时用来发送邮件
 @param SMTPPassword    SMTP密码 或者 SMTP授权码
 @param encryptType     加密类型
 @param emailTile       邮件主题:设备报警时发送邮件的标题
 @param emailContent    邮件内容:设备报警时发送邮件的内容
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceAlarmEmail:(NSString *)alarmEmail
               withDeviceID:(NSString *)deviceID
             devicePassword:(NSString *)devicePassword
              isSupportSMTP:(BOOL)isSupportSMTP
                 SMTPServer:(NSString *)SMTPServer
                   SMTPPort:(NSUInteger)SMTPPort
                   SMTPUser:(NSString *)SMTPUser
               SMTPPassword:(NSString *)SMTPPassword
                encryptType:(GWP2PAlarmEmailEncryptType)encryptType
                 emailTitle:(NSString *)emailTile
               emailContent:(NSString *)emailContent
            completionBlock:(CompletionBlock)completionBlock;

#pragma mark - 设备报警后操作
/**
 设备报警时,关闭蜂鸣器
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)closeBuzzerWhenDeviceIsAlarmingWithDeviceID:(NSString *)deviceID
                                     devicePassword:(NSString *)devicePassword
                                    completionBlock:(CompletionBlock)completionBlock;

/**
 设备报警时解除关联的当前报警账号
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param operationType           操作类型,有
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)unbindDeviceCurrentAlarmAccountWithDeviceID:(NSString *)deviceID
                                     devicePassword:(NSString *)devicePassword
                                      operationType:(GWUnbindAlarmAccountOperationType)operationType
                                    completionBlock:(CompletionBlock)completionBlock;

@end
