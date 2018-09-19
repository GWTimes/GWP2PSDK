//
/** @file GWP2PClient+DeviceInfomation.h @brief 该文件为P2PClient获取和设置设备状态信息的分类 */
//  P2PSDK
//
//  Created by apple on 17/2/24.
//  Copyright © 2017年 gwell. All rights reserved.
//




#import "GWP2PClient.h"


/**
 设备网络连接类型
 */
typedef NS_ENUM(NSUInteger, GWDeviceNetworkType) {
    GWDeviceNetworkTypeWired,/**< 有线 */
    GWDeviceNetworkTypeWifi, /**< wifi */
};

/**
 设备的RTSP密码模式
 */
typedef NS_ENUM(NSUInteger, GWDeviceRTSPPasswordMode) {
    GWDeviceRTSPPasswordModeClosed = 0, /**< RTSP功能关闭 */
    GWDeviceRTSPPasswordModeOpenAndPasswordNeedless = 1, /**< RTSP功能打开,但不需要密码 */
    GWDeviceRTSPPasswordModeOpenAndPasswordNeeded = 2, /**< RTSP功能打开,并需要密码 */
    GWDeviceRTSPPasswordModeUnSetted = 3, /**< 设备支持RTSP功能,但没有设置过模式,设备初始化后会返回此值,如果设备返回此值,要调确认RTSP接口,再进行RTSP密码的设置,模式的修改等操作 */
    
    GWDeviceRTSPPasswordModeNOSuchFile = 4, /**< 设备支持RTSP功能,但没有支持文件,也要判断为不支持 */
    
    GWDeviceRTSPPasswordModeUnSurpurted = 999, /**< 设备不支持RTSP功能,设备模型初始化时附此值,方便后面判断 */
};



/**
 @brief 该分类可获取和设置设备各种状态信息
 */
@interface GWP2PClient (DeviceInfomation)

#pragma mark - 获取设备状态
/**
 获取多项设备状态：以下key返回结果里没有时表示设备不支持该功能
 
 completionBlock返回：
 
 @"defence state" （布防状态）: 类型：BOOL （YES 布防 , NO 撤防）
 
 @"buzzer state" （蜂鸣器蜂鸣时长）: 0 off , 1 2 3 min 蜂鸣时长 类型：NSNumber
 
 @"motion detect state"（移动侦测状态）:  类型：BOOL (NO off; YES on)
 
 @"record type" （录像类型） : manual; alarm; schedule  返回字典， record type 键对应 GWP2PRecordType 枚举
 
 @"manually record state" （手动录像开关） : 类型：BOOL (NO off; YES on)
 
 @"planed record time" （计划录像时间）:返回字典，对应的值为 NSNumber类型，保存开始时间的时分，结束时间的时分四个键值对（24小时制）
 
 @"video format" （视频格式） 返回字符串 : NTSC , PAL 返回字典：
 
 @"alarm record time" （报警录像时间）0 表示1分钟, 1 表示2分钟 2 表示3分钟
 
 @"net type" （网络类型） : 0 有线; 1 wifi;
 
 @"volume" （音量）: 0-9整数
 
 @"auto update" （自动升级）: NO off; YES on
 
 @"body infrared state" （人体红外状态） : NO off; YES on
 
 @"wired alarm input" （有线报警输入状态） : NO off; YES on
 
 @"wired alarm output" （有线报警输出状态） : NO off; YES on
 
 @"time zone" （时区） : @(0-24)
 
 @"password" （用户密码）
 
 @"image reverse state" （图像倒转状态）返回BOOL值 : @(NO) 非倒转; @(YES) 是倒转
 
 @"prerecord state" （预录像状态） : NO off YES on
 
 @"motion detect sensityvity" (移动侦测灵敏度) : 0-6 数值越大,灵敏度越高 -1表示返回数值有误
 
 @"lamp state" （灯光控制状态） : NO off YES on
 
 @"visitor password" （访客密码） : 由非0开头的数字组成
 
 @"focus zoom" （变焦 变倍） : 0 都没有; 1 只有变倍; 2 只有变焦; 3 变倍变焦都有
 
 @"AP Mode" （AP模式） : 0 不支持; 1 支持(mode!=ap); 2 支持(mode=ap)
 
 @"type" （设备主类型）： GWDeviceType 类型,（如IPC、NPC...） （设备返回的主类型不准）
 
 @"subtype" （设备子类型）： GWDeviceSubtype 类型,（如30只支持868；31支持868+情景模式；32支持868+情景模式+分享）
 
 @"preset position suppurted" （是否支持预置位）:  @(BOOL) NO 不支持; YES 支持
 
 @"RTSP password mode" (RTSP密码模式,此项有值说明支持RTSP模式,没有值说明设备不支持) @(GWDeviceRTSPPasswordMode)
 
 @"confirm RTSP password mode" (需不需要确认RTSP密码模式,需要时,调确认RTSP密码模式接口后才能正常配置RTSP密码)
 
 @"white light suppurted" (是否支持白光灯功能) @(BOOL)
 
 @"white light on" (白光灯灯关是否打开) @(BOOL)
 
 @"sound control suppurted" (是否支持声音控制功能) @(BOOL)
 
 @"white light brightness" (白光灯亮度) @(int)
 
 @"433 doorbell suppurted" (是否支持433门铃传感器) @(BOOL)
 
 @"object tracking" (物件追踪，字典里没有表示不支持) @(BOOL)
 
 @param deviceID                设备ID
 @param password                设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)getMultipleDeviceStatusWithDeviceID:(NSString *)deviceID
                                   password:(NSString *)password
                            completionBlock:(CompletionBlock)completionBlock;


/**
 获取设备信息
 
 completionBlock 返回字典对应的key:
 
 @"firmware version" 固件版本
 
 @"uBoot uersion" uBoot版本
 
 @"kernel version" 内核版本
 
 @"system version" 系统版本

 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)getDeviceInfomationWithDeviceID:(NSString *)deviceID
                         devicePassword:(NSString *)devicePassword
                        completionBlock:(CompletionBlock)completionBlock;

#pragma mark - 下载文件
/**
 从设备下载文件,下载结果在 GWP2PClientProtocol 的方法 client:didDownloadFile:withFilePath:deviceID: 中

 @param deviceID        设备ID
 @param devicePassword  设备密码
 @param remoteFilePath  远程文件路径,一般由设备返回
 @param localFilePath   下载后文件在本地的保存路径,文件在沙盒中的保存路径(包括文件名及文件扩展名),下载成功后文件直接保存在此路径

 @return 下载是否开始
 */
- (BOOL)downloadFileWithDeviceID:(NSString *)deviceID
                  devicePassword:(NSString *)devicePassword
                  remoteFilePath:(NSString *)remoteFilePath
                   localFilePath:(NSString *)localFilePath;

/**
 从设备下载报警时的截图, 下载结果在 GWP2PClientProtocol 的 client:didDownloadFile:withFilePath:deviceID:result: 方法中回调

 @param deviceID        设备ID
 @param devicePassword  设备密码
 @param pictureNumber   报警时截图的数量,设备推送报警时,会推送此数据
 @param toDownloadIndex 要下载的图片索引, <= (pictureNumber - 1)
 @param remoteFilePath  图片的路径,设备推送报警时,会推送此数据
 @param localFilePath   下载后图片在本地的保存路径,图片在沙盒中的保存路径(包括图片名及图片扩展名),下载成功后文件直接保存在此路径

 @return 下载是否开始
 */
- (BOOL)downloadAlarmPictureWithDeviceID:(NSString *)deviceID
                          devicePassword:(NSString *)devicePassword
                           pictureNumber:(NSUInteger)pictureNumber
                         toDownloadIndex:(NSUInteger)toDownloadIndex
                          remoteFilePath:(NSString *)remoteFilePath
                           localFilePath:(NSString *)localFilePath;

#pragma mark - 网络
/**
 获取设备搜索到的Wifi列表
 
 获取网络类型请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 
 completionBlock返回字典:
 
 @"wifi count" : wifi数目
 
 @"current wifi index" : 正在使用的wifi索引值 索引值从0开始
 
 @"wifi list" : wifi列表数组,数组内一个字典对应一个wifi的信息(wifi名,是否加密,wifi强度,加密类型) @[@{@"wifi name" : @"wifi名", @"has encrypted" : @(YES), @"wifi strength" : @"wifi强度"}, @"encrypted type" : @(0)];]
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)getDeviceWifiListWithDeviceID:(NSString *)deviceID
                       devicePassword:(NSString *)devicePassword
                      completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备网络连接类型，即在有线和wifi之间切换

 @param networkType     网络类型
 @param deviceID        设备ID
 @param devicePassword  设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceNetworkType:(GWDeviceNetworkType)networkType
                withDeviceID:(NSString *)deviceID
              devicePassword:(NSString *)devicePassword
             completionBlock:(CompletionBlock)completionBlock;

/**
 不再使用
 
 连网模式下设置设备当前Wifi，设置后设备会连接到设置的wifi,此接口只支持WPA加密的wifi
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param encrypted               wifi是否加密(可由获取到的wifi列表得到),传获取wifi列表字典中的@"has encrypted"对应的值
 @param wifiName                wifi名
 @param wifiPassword            wifi密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceWifiInNetworkModeWithDeviceID:(NSString *)deviceID
                                devicePassword:(NSString *)devicePassword
                            wifiHasBeEncrypted:(BOOL)encrypted
                                      wifiName:(NSString *)wifiName
                                  wifiPassword:(NSString *)wifiPassword
                               completionBlock:(CompletionBlock)completionBlock DEPRECATED_ATTRIBUTE;

/**
 连网模式下设置设备当前Wifi，设置后设备会连接到设置的wifi,新的接口,老的接口只支持WPA加密的wifi，此接口支持WEP加密和WPA加密的wifi
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param encryptedType           wifi加密类型(可由获取到的wifi列表得到),传获取wifi列表字典中的@"encrypted type"对应的值
 @param wifiName                wifi名
 @param wifiPassword            wifi密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceWifiInNetworkModeWithDeviceID:(NSString *)deviceID
                                devicePassword:(NSString *)devicePassword
                             wifiEncryptedType:(NSInteger)encryptedType
                                      wifiName:(NSString *)wifiName
                                  wifiPassword:(NSString *)wifiPassword
                               completionBlock:(CompletionBlock)completionBlock;


#pragma mark - 时间时区
/**
 获取设备时间 : 返回 年 月 日 时 分 的数值, 不是NSDate,避免时区出错
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)getDeviceTimeWithDeviceID:(NSString *)deviceID
                   devicePassword:(NSString *)devicePassword
                  completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备时间
 
 @param date                    要设置的时间
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceTime:(NSDate *)date
         withDeviceID:(NSString *)deviceID
       devicePassword:(NSString *)devicePassword
      completionBlock:(CompletionBlock)completionBlock;

/**
 设置设备时区
 
 获取时区请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 
 @param timeZone                要设置的时区,可设置如下数字:-11, -10, -9, -8, -7, -6, -5, -4, -3.5, -3, -2, -1, 0, 1, 2, 3, 3.5, 4, 4.5, 5, 5.5, 6, 6.5, 7, 8, 9, 9.5, 10, 11, 12
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceTimeZone:(float)timeZone
             withDeviceID:(NSString *)deviceID
           devicePassword:(NSString *)devicePassword
          completionBlock:(CompletionBlock)completionBlock;


#pragma mark - 安全
#pragma mark 密码
/**
 设置初始密码,重置设备后,设备没有密码(管理员)时调用,如果有密码,密码一般为123,具体请查看设备说明书
 
 必须保证手机与设备在同一局域网中,否则回调只会收到参数错误. 这一接口在发指令时一定要确保手机与设备在同一局域网中,指令将deviceID转成4位设备IP的最后一位,若不在同一局域网,获取不到设备IP,指令不会成功
 
 @param initialPassword         初始密码,必须为包含字母、数字、其它字符中两种的6~30位的字符串
 @param deviceID                设备ID,直接传设备ID,内部处理成IP地址,也可以传4位IP的最后一位数字
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceInitialPassword:(NSString *)initialPassword
                    withDeviceID:(NSString *)deviceID
                 completionBlock:(CompletionBlock)completionBlock;

/**
 设置管理员密码,设备已经有密码(管理员)时调用
 
 @param oldPassword             老的管理员密码,可能为简单的初始密码,如123
 @param newPassword             新的管理员密码,必须为包含字母、数字、其它字符中两种的6~30位的字符串,否则会返回参数错误
 @param deviceID                设备ID
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceAdministratorPasswordWithOldPassword:(NSString *)oldPassword
                                          newPassword:(NSString *)newPassword
                                             deviceID:(NSString *)deviceID
                                      completionBlock:(CompletionBlock)completionBlock;

/**
 设置访客密码,有管理员密码时调用
 
 @param newVisitorPassword      新的访客密码(必须为非零开头的小于等于9位的数字)
 @param administratorPassword   管理员密码
 @param deviceID                设备ID
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceVisitorPassword:(NSString *)newVisitorPassword
       withAdministratorPassword:(NSString *)administratorPassword
                        deviceID:(NSString *)deviceID
                 completionBlock:(CompletionBlock)completionBlock;

#pragma mark RTSP密码
/**
 设置RTSP密码
 
 不能获取密码

 @param rtspPassword 要设置的RTSP密码
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceRTSPPassword:(NSString *)rtspPassword
                 withDeviceID:(NSString *)deviceID
               devicePassword:(NSString *)devicePassword
              completionBlock:(CompletionBlock)completionBlock;

/**
 设置RTSP密码模式
 
 获取RTSP模式请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:

 @param rtspPasswordMode rtsp密码模式
 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)setDeviceRTSPPasswordMode:(GWDeviceRTSPPasswordMode)rtspPasswordMode
                     withDeviceID:(NSString *)deviceID
                   devicePassword:(NSString *)devicePassword
                  completionBlock:(CompletionBlock)completionBlock;

/**
 确认RTSP密码模式
 
 新设备或查询RTSP密码模式为 GWDeviceRTSPPasswordModeUnSetted == 3 时,需要向设备发此指令,告诉设备开启RTSP密码的配置功能,之后才能正常设置RTSP密码

 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)confirmDeviceRTSPPasswordModeWithDeviceID:(NSString *)deviceID
                                   devicePassword:(NSString *)devicePassword
                                  completionBlock:(CompletionBlock)completionBlock;

#pragma mark - 更新
/**
 设置自动更新状态
 
 如果获取不到设备的自动更新状态,表明设备不支持,调此方法是收不到回调数据,只会超时
 
 获取自动更新状态请调 getMultipledeviceStatusWithDeviceID:password:completionBlock:
 
 @param isAutoUpdate            是否自动更新
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)setDeviceAutoUpdateState:(BOOL)isAutoUpdate
                    withDeviceID:(NSString *)deviceID
                  devicePassword:(NSString *)devicePassword
                 completionBlock:(CompletionBlock)completionBlock;

/**
 检查设备是否可更新
 
 completionBlock返回字典对应的键值：
 
 @"current version" 当前固件版本
 
 @"update version" 待更新的版本
 
 @"can update"  （是否可更新）：对应值为 NSNumber 包装的 BOOL 类型
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)checkDeviceUpdateWithDeviceID:(NSString *)deviceID
                       devicePassword:(NSString *)devicePassword
                      completionBlock:(CompletionBlock)completionBlock;

/**
 执行设备更新
 
 执行更新后下载进度在 GWP2PClientProtocol 协议的 [GWP2PClientProtocol client:updateProgress:resultCode:ofDeviceID:]方法中进行监听
 
 completionBlock返回字典对应的键值：
 
 @"has begin update" （是否开始更新）：对应值为 NSNumber 包装的 BOOL 类型
 
 @"update progress" （更新进度）：对应值为 NSNumber 包装的 int 类型
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)performUpdateWithDeviceID:(NSString *)deviceID
                   devicePassword:(NSString *)devicePassword
                  completionBlock:(CompletionBlock)completionBlock;

/**
 取消设备更新（此命令收不到设备回调）
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)cancelUpdateWithDeviceID:(NSString *)deviceID
                  devicePassword:(NSString *)devicePassword
                 completionBlock:(CompletionBlock)completionBlock;

#pragma mark - 获取设备分辨率,IP地址,MAC(网卡)地址
/**
 获取设备分辨率,IP地址,MAC(网卡)地址
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)getDeviceResolutionAndIpAndMacAddressWithDeviceID:(NSString *)deviceID
                                           devicePassword:(NSString *)devicePassword
                                          completionBlock:(CompletionBlock)completionBlock;

#pragma mark - 获取用户及设备列表在线状态等信息
/**
 获取好友用户及设备列表在线状态等信息,此指令不能同时发两条,第二条要等第一条回调后再发,网络超时为25s
 
 completionBlock返回字典数据结构:
 
 @{ @"result" : @(NO),
    @"description" : @"success",
    @"操作描述" : @"获取好友用户及设备列表在线状态等信息",
    @"status" : @[  @{//一个字典对应一个设备或一个好友用户信息
                    @"deviceID" : @"设备ID或好友用户ID",
                    @"defence flag" : @(-1),//布防状态获取的时间标识,此值越大,表示获取的时间越晚,用于判断是否要刷新布防状态. -1表示不支持或设备不在线
                    @"defence state" : @(-1),//-1表示不支持或设备不在线
                    @"online state" : @(YES),//接口一定支持
                    @"subtype" : @(-1)//-1表示不支持或设备不在线
                    }
                ]
 }
 
 @param deviceIDsArray          设备ID数组,如果是用户(GWNet登陆的用户)ID,请在数字前加0,用于区分是设备ID还是用户ID
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)getDevicesOrUersStatusWithDeviceIDs:(NSArray<NSString *> *)deviceIDsArray
                      completionBlock:(CompletionBlock)completionBlock;

#pragma mark - NVR设备
/**
 获取设备NVR信息
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)getDeviceNVRInfomationWithDeviceID:(NSString *)deviceID
                            devicePassword:(NSString *)devicePassword
                           completionBlock:(CompletionBlock)completionBlock;

#pragma mark - 更新设备id
/**
 更新设备id
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
- (void)updateDeviceIdWithDeviceID:(NSString *)deviceID
                    devicePassword:(NSString *)devicePassword
                   completionBlock:(CompletionBlock)completionBlock;

#pragma mark - 获取当前全景相机的配置信息
/**
 获取当前全景相机的配置信息
 
 @param deviceID                设备ID
 @param devicePassword          设备密码
 @param completionBlock         与设备交互完成后的回调Block
 */
-(void)getFisheyeDeviceInfoWithDeviceId:(NSString*)deviceID
                         devicePassword:(NSString*)devicePassword
                        completionBlock:(CompletionBlock)completionBlock;

@end
