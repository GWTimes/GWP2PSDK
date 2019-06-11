//
/** @file GWP2PDefine.h @brief 定义的各种类型枚举,错误类型,密码强弱,操作类型,报警类型等 */
//  P2PSDK
//
//  Created by apple on 17/2/28.
//  Copyright © 2017年 gwell. All rights reserved.
//

#ifndef GWP2PDefine_h
#define GWP2PDefine_h


@class GWP2PClient;

/**
 给设备发消息后的回调block,block都没有在主线程调用,操作UI时,请注意回到主线程
 
 关于返回结果中设备ID的说明:如果手机和设备处理同一局域网,会直接通过局域网发消息给设备,这时发消息传递的设备ID不是实际的设备ID号,而是设备在局域网中IPV4地址的4位数字的最后一位,其值小于等于255,设备消息返回后,block字典中的"device ID"字段返回的也是中IPV4地址的4位数字的最后一位,而不是设备ID
 
 @abstract 由用户自己定义,实现与设备交互后的操作
 @param client                GWP2PClient单例,调用此指针,避免循环引用
 @param success               是否与设备通信成功(不代表设备指令成功)
 @param dataDictionary        返回数据,与设备通信成功后返回所请求的数据,不成功会返回失败原因，具体指令是否成功会保存在此字典的GWP2PMessageResult键对应的 NSNumber包装的BOOL值中：YES表示成功，可以取具体数据或操作设备成功；NO表示失败，GWP2PMessageDescription键对应的值中会描述具体原因.若有特殊要求,可取 GWP2PMessageErrorValue 键对应的NSNumber 包装的 P2PClientMessageError 枚举值,查看具体错误原因
 */
typedef void (^CompletionBlock)(GWP2PClient *client, BOOL success, NSDictionary<NSString *, id> *dataDictionary);

//CompletionBlock返回字典中对应的常量字符串
static NSString *const GWP2PMessageDeviceNotSurported = @"device not surported";/**< 设备不支持 */
static NSString *const GWP2PMessageDescription = @"description";/**< 具体的描述 */
static NSString *const GWP2PMessageResult = @"result";/**< 结果 对应NSNumber包装的BOOL类型 */
static NSString *const GWP2PMessageFailure = @"failure"; /**< 失败 */
static NSString *const GWP2PMessageSuccess = @"success"; /**< 成功 */
static NSString *const GWP2PMessageErrorValue = @"error value"; /**< NSNumber 包装的 P2PClientMessageError 枚举值 */


/**
 发送设备指令后返回的错误类型
 */
typedef NS_ENUM(NSUInteger, P2PClientMessageError) {
    P2PClientMessageErrorNone,              /**< 没有错误 */
    P2PClientMessageErrorPasswordFail,      /**< 密码错误 */
    P2PClientMessageErrorTimeOut,           /**< 超时 */
    P2PClientMessageErrorIOSPushError,      /**< ios内部错误 */
    P2PClientMessageErrorNoRight,           /**< 没有权限 */
    P2PClientMessageErrorSendFailed = 5,        /**< 因缓存不够发送失败 */
    P2PClientMessageErrorDeviceOffline = 6,     /**< 设备离线 */
    
    P2PClientMessageErrorMessageIsSending = 9996,  /**< 当前请求正在进行 */
    P2PClientMessageErrorParameterError = 9997,    /**< 传递参数错误 */
    P2PClientMessageErrorOtherError = 9998, /**< 其它错误,返回结果一般会描述错误原因 */
    P2PClientMessageErrorUnKnow = 9999      /**< 未知错误,返回结果一般不会描述错误原因 */
};

typedef NS_ENUM(NSUInteger, P2PLinkStatus) {
    P2PLinkStatusOK = 0,                /**< 连接成功 */
    P2PLinkStatusLinking,               /**< 连接操作正在进行还没成功 */
    P2PLinkStatusDNSParseFailed,        /**< DNS解析错误 */
    P2PLinkStatusCheckListServerFailed, /**< 列表服务器没有响应 */
    P2PLinkStatusGetServerListTimeOut,  /**< 获取服务器列表超时 */
    P2PLinkStatusWaitHeartbeatFailed,   /**< 等待P2P服务器心跳失败 */
    P2PLinkStatusLoginAnother,          /**< 在其他设备登录了 */
    P2PLinkStatusUnknown                /**< 未知 */
};



/**
 管理员密码强度,设置密码时不能为弱密码
 */
typedef NS_ENUM(NSUInteger, P2PAdministratorPasswordStrength) {
    P2PAdministratorPasswordStrengthInValidate, /**< 无效 */
    P2PAdministratorPasswordStrengthWeak,       /**< 弱 */
    P2PAdministratorPasswordStrengthMiddle,     /**< 中 */
    P2PAdministratorPasswordStrengthStrong,     /**< 强 */
};


/**  
 设备操作类型 
 */
typedef NS_ENUM(NSUInteger, P2POperationType) {
    P2POperationTypeInsert, /**< 增加 */
    P2POperationTypeDelete, /**< 删除 */
    P2POperationTypeUpdate, /**< 修改 */
};

/**
 设备报警类型
 */
typedef NS_ENUM(NSUInteger, GWSensorAlarmType) {
    GWSensorAlarmTypeNone,
    GWSensorAlarmTypeExternal = 1,          /**< 1 外部报警 */
    GWSensorAlarmTypeMotionDetect,          /**< 2 移动侦测 */
    GWSensorAlarmTypeForce,                 /**< 3 紧急 */
    GWSensorAlarmTypeDebug,                 /**< 4 调试 */
    GWSensorAlarmTypeLine = 5,              /**< 5 有线 */
    GWSensorAlarmTypeVOL,                   /**< 6 低电压 */
    GWSensorAlarmTypePIR,                   /**< 7 人体红外 */
    GWSensorAlarmTypeDefence,               /**< 8 布防 */
    GWSensorAlarmTypeCancelDefence,         /**< 9 撤防 */
    GWSensorAlarmTypeBatteryLowVoltage = 10,/**< 10 电池低电 */
    GWSensorAlarmTypeParameterUpdateToServer,/**< 11 参数上传服务器 */
    GWSensorAlarmTypeTemperatureHumidity,   /**< 12 温湿度 */
    GWSensorAlarmTypeDoorbellPush,          /**< 13 门铃推送 */
    GWSensorAlarmTypeForceFromKeypress,     /**< 14 按键触发报警(UI 显示紧急报警) */
    GWSensorAlarmTypeRecordFail = 15,       /**< 15 录像失败 */
    GWSensorAlarmTypeEmailTooOften,         /**< 16 邮箱发送过于频繁 */
    GWSensorAlarmTypeUARTInput,             /**< 17 串口输入报警 */
    GWSensorAlarmTypeProberFire,            /**< 18 防火报警 */
    GWSensorAlarmTypeProberGas,             /**< 19 煤气泄漏 */
    GWSensorAlarmTypeProberSteal,           /**< 20 防盗报警 */
    GWSensorAlarmTypeProberAround = 21,     /**< 21 周界报警 */
    GWSensorAlarmTypeProberForce,           /**< 22 */
    GWSensorAlarmTypeProber120,             /**< 23 医疗求救 */
    GWSensorAlarmTypeProberPreventDisconnect,/**< 24 防拆报警 */
    GWSensorAlarmTypeProberCommunicationTiming,/**< 25 定时通讯 */
    GWSensorAlarmTypeProberLowPower = 26,    /**< 26 低电报警 */
    GWSensorAlarmTypeProberLowPowerRecovery,/**< 27 低电恢复报警 */
    GWSensorAlarmTypeProberPowerOn,         /**< 28 开机报警 */
    GWSensorAlarmTypeProberPowerOff,        /**< 29 关机报警 */
    GWSensorAlarmTypeProberDefence,         /**< 30 布防 */
    GWSensorAlarmTypeProberCancelDefence = 31,/**< 31 撤防 */
    GWSensorAlarmTypeProberEXT,             /**< 32 门磁报警 */
    GWSensorAlarmTypeSound,                 /**< 33 声音报警 */
    GWSensorAlarmTypePIR1,                  /**< 34 */
    GWSensorAlarmTypeRecordAlert,           /**< 35 录像 */
    GWSensorAlarmTypeExternalAttact = 36,   /**< 36 外部攻击 */
    GWSensorAlarmTypeSensorAlarm,           /**< 37 传感器报警 */
    GWSensorAlarmTypeForceSOS,              /**< 38 sos */
    GWSensorAlarmTypeKeepSilent,            /**< 39 silent */
    GWSensorAlarmTypeSmoke,                 /**< 40 smoke */
    GWSensorAlarmTypeGas = 41,              /**< 41 gas */
    GWSensorAlarmTypeDoorMagnet,            /**< 42 door magnet */
    GWSensorAlarmTypeTemprature,            /**< 43 temprature */
    GWSensorAlarmTypeHumidity,              /**< 44 humidity */
    GWSensorAlarmTypePIRAlarm,              /**< 45 pir */
    GWSensorAlarmTypeUARTRecord = 46,       /**< 46 UART RECORD */
    GWSensorAlarmTypeEmergencyCall,         /**< 47 紧急呼叫 */
    GWSensorAlarmTypeMAX,
};

/** 测试用，请勿读写 */
//extern void *gwdebug;
extern void (*gwdebug)(NSInteger level, NSString *file, NSString *func, NSInteger line, NSString *msg);

#endif /* GWP2PDefine_h */
