//
/** @file GWP2PClient.h @brief P2P客户端及其协议,连接与断连P2P服务器,获取连接状态,获取AP模式ID等 */
//  P2PSDK
//
//  Created by apple on 16/12/9.
//  Copyright © 2016年 gwell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GWP2PDefine.h"


@class GWP2PClient;

#pragma mark - GWP2PClientProtocol
/**
 @brief P2P客户端协议,包含接收设备报警和文件下载等回调
 */
@protocol GWP2PClientProtocol <NSObject>

@optional
/**
 接收到设备报警推送(包括门铃响铃推送的一种,而且是设备常用的一种):
 
 alarmDictionary字典各键对应的信息
 
 @"alarm type" : 报警类型 GWSensorAlarmType 枚举值
 
 @"can delete binded push ID" : 是否支持删除绑定的推送ID，即能否解除当前账号的报警推送
 
 @"sensor name" : 传感器名字
 
 报警图片,由于情景模式设备与其它的设备图片存储方式不一样,因此可能返回@"scene mode device picture"与@"common device picture"两个键中的一个或两个,如果返回两个,要先判断设备类型,再用对应的图片路径去获取图片才能获取到
 
 @"scene mode device picture" : 情景模式设备报警图片, 对应一个字典
 
 @"common device picture" : 普通设备报警图片, 对应一个字典
 
 图片对应的字典@{@"path" : 图片在设备的路径，用来下载图片, @"picture number" : @"报警时,设备截图数量"}
 
 @param client          GWP2PClient类
 @param alarmDictionary 保存报警信息的字典
 */
- (void)client:(GWP2PClient *)client receavedDeviceAlarm:(NSDictionary<NSString *, id> *)alarmDictionary;

/**
 串口透传接收到门铃的响铃推送,门铃响铃有两种方式推送到手机端:
 
 一是通过报警推送, 其报警类型@"alarm type"的值为 GWSensorAlarmTypeDoorbellPush , 即 13,
 
 二是通过串口透传,此方法接收到的报警信息就是通过串口透传推送的,
 
 ringingDictionary字典各键对应的信息:
 
 @"device ID" : @"设备id";
 
 @"cmd" : @"串口透传命令";

 @param client              GWP2PClient类
 @param ringingDictionary   保存响铃信息的字典
 */
- (void)client:(GWP2PClient *)client receavedDoorbellRingingBySerialTransmission:(NSDictionary<NSString *, id> *)ringingDictionary;

/**
 下载文件回调

 @param client   GWP2PClient 类
 @param filePath 若下载成功,此路径为本地存储路径,若下载失败,此路径为远程路径或nil
 @param deviceID 设备ID
 @param success  是否下载成功
 @param resultDictionary 保存下载失败原因的字典
 */
- (void)client:(GWP2PClient *)client didDownloadFile:(BOOL)success withFilePath:(NSString *)filePath deviceID:(NSString *)deviceID result:(NSDictionary<NSString *, NSString *> *)resultDictionary;

/**
 更新进度
 
 给设备发送更新命令后，设备开始更新，此方法会不停的调用，返回更新进度百分比,此方法在主线程运行，方便UI处理
 
 @param client  GWP2PClient 类
 @param persent 更新到百分之多少
 @param resultCode NSNumber对应更新结果：1更新中 65更新完成
 @param deviceID 设备ID
 */
- (void)client:(GWP2PClient *)client updateProgress:(NSInteger)persent resultCode:(NSNumber *)resultCode ofDeviceID:(NSString *)deviceID;

/**
 收到串口透传的数据
 
 @param client GWP2PClient 类
 @param data   串口透传回来的二进制数据,最大为248个字节
 */
- (void)client:(GWP2PClient *)client receavedSerialTransmissionData:(NSDictionary *)data;


/**
 P2P库接收到通知，包括 设备升级、系统消息、权限通知等
 
 @param client GWP2PClient 类
 @param noti 通知数据字典
 
    "PermissionMessage"
    "AppNeedUpdate"
    "SystemMessage"
 */
- (void)client:(GWP2PClient *)client didReceivedNotification:(NSDictionary *)userInfo;

@end




#pragma mark - GWP2PClient类
/**
 @brief 控制设备的类,用单例,连接与断连P2P服务器,获取连接状态,获取AP模式ID等
 */
@interface GWP2PClient : NSObject

/**
 收到设备不支持的回调
 
 由于给设备发指令,收到设备回复时,是以指令类型去判断是哪条消息,而有的指令设备不支持这一数据覆盖了指令类型,所以设备不支持对应不到具体指令,只能单独传出来
 */
@property (nonatomic, copy) void (^deviceNotSupportBlock)(GWP2PClient *client, NSString *deviceID);

@property (nonatomic, assign) P2PLinkStatus linkStatus; /**< p2p连接状态 */

@property (nonatomic, weak) id<GWP2PClientProtocol> delegate;/**< GWP2PClient的代理，一些设备事件的通知对象 */

@property (nonatomic, assign) BOOL isAPMode;/**< 是不是AP模式。此属性只保存上次与路由器交互后的数据，调 getDeviceIDInAPMode 方法会重新与路由器交互更新APMode状态，每次app进入前台时会更新APMode状态 */
@property (nonatomic, assign) NSInteger port;/**< 广播端口 */

@property (nonatomic, copy) NSString *serverList; /**< P2P服务器列表，自建服务器需要设置此属性，格式"|p2p1.cloudlinks.cn|p2p2.cloudlinks.cn|p2p3.cloud-links.net" */

#pragma mark 获取单例
/**
 *  获取单例
 */
+ (instancetype)sharedClient;


#pragma mark 连接服务器
/**
 @method
 @abstract 连接服务器
 @discussion 程序启动时首先要连接服务器，才能与设备通信。如果只需支持某一公司的设备，那么请向技威的技术支持咨询获取你们的客户ID
 @param account 用户账号,不是注册时的邮箱,手机号,是登陆或注册时返回的值取后31位:[json[@"UserID"] intValue] & 0x7fffffff
 @param codeStr1 用户账号登陆成功后返回的 P2PVerifyCode1 , 为固定值
 @param codeStr2 用户账号登陆成功后返回的 P2PVerifyCode2 , 为固定值
 @param sessionID1 用户账号登陆成功后返回的 sessionId1 , 每次登陆返回值不固定
 @param sessionID2 用户账号登陆成功后返回的 sessionId2 , 每次登陆返回值不固定
 @param customerIDsArray 技威客户公司id数组，传nil表示支持所有技威方案的设备。数组内传了几个公司的ID，连接后就支持对应公司的设备。最多支持10个。传入的ID值不正确时，支持不了设备，都传0时与传nil效果一样。要了解具体客户ID，请联系技威客服。
 @result 返回值代表是否连接成功
 */
- (BOOL)connectWithAccount:(NSString *)account
                  codeStr1:(NSString *)codeStr1
                  codeStr2:(NSString *)codeStr2
                sessionID1:(NSString *)sessionID1
                sessionID2:(NSString *)sessionID2
               customerIDs:(NSArray <NSNumber *> *)customerIDsArray;

/**
 @method
 @abstract 连接服务器(为支持P2P通知消息增加三个参数）
 @discussion 程序启动时首先要连接服务器，才能与设备通信。如果只需支持某一公司的设备，那么请向技威的技术支持咨询获取你们的客户ID
 @param account 用户账号,不是注册时的邮箱,手机号,是登陆或注册时返回的值取后31位:[json[@"UserID"] intValue] & 0x7fffffff
 @param codeStr1 用户账号登陆成功后返回的 P2PVerifyCode1 , 为固定值
 @param codeStr2 用户账号登陆成功后返回的 P2PVerifyCode2 , 为固定值
 @param sessionID1 用户账号登陆成功后返回的 sessionId1 , 每次登陆返回值不固定
 @param sessionID2 用户账号登陆成功后返回的 sessionId2 , 每次登陆返回值不固定
 @param customerIDsArray 技威客户公司id数组，传nil表示支持所有技威方案的设备。数组内传了几个公司的ID，连接后就支持对应公司的设备。最多支持10个。传入的ID值不正确时，支持不了设备，都传0时与传nil效果一样。要了解具体客户ID，请联系技威客服。
 @param appVersion 向技威申请得到的AppVersion(格式如00.46.03.03)
 @param messageLanguage P2P通知消息语言，请传nil，设置无效，目前根据系统语言判定。
 @param lastSystemMessageID 最后一个系统消息ID
 @param lastAuthorityMessageID 权限系统消息ID，配网时传密码也会走这个消息

 @result 返回值代表是否连接成功
 */
- (BOOL)connectWithAccount:(NSString *)account
                  codeStr1:(NSString *)codeStr1
                  codeStr2:(NSString *)codeStr2
                sessionID1:(NSString *)sessionID1
                sessionID2:(NSString *)sessionID2
               customerIDs:(NSArray <NSNumber *> *)customerIDsArray
                appVersion:(NSString *)appVersion
           messageLanguage:(NSString *)messageLanguage
       lastSystemMessageID:(NSString *)lastSystemMessageID
    lastAuthorityMessageID:(NSString *)lastAuthorityMessageID;


/**
 @abstract 断开连接
 */
- (void)disconnect;

/**
 AP模式下获取设备ID，只有当设备为AP模式且手机连接到设备的wifi时才能成功获取并更新设备的APMode状态
 
 @return 设备ID。返回值不为0时可确定设备处于AP模式；返回值为0时可能为AP，也可能是手机未连接到设备wifi
 */
- (NSUInteger)getDeviceIDInAPMode;

#pragma mark - 发送二进制数据给设备
/**
 直接向设备发送原始数据,本接口是为满足一些客户定制的需求,一般用户不需要直接使用此接口,具体的数据格式根据功能来定,请咨询技威客服
 
 在 GWP2PClient 的分类中各接口都是把各个功能的数据封装好后,进行调用.为了满足一些客户的特殊要求,公开这条接口,让客户自己去封装数据,回调的数据也是 NSData 类型,定制功能使用此接口时,用户需要自己将数据封装成 NSData 类型,然后传入此接口参数data中,封装时一定要注意字节对齐.
 
 如果是 GWP2PClient 分类中有的指令,调这条接口直接发二进制数据是收不到回调数据的
 
 此接口发送后不能连续发这个条指令,必需要上一条数据返回时才能发下一条指令

 @param deviceID 设备ID
 @param devicePassword 设备密码
 @param data 要发送的数据,数据结构是由技威定义的结构体,封装成NSData时一定要注意字节对齐
 @param completionBlock 与设备交互完成后的回调Block
 */
- (void)sendBinaryDataToDevice:(NSString *)deviceID
            withDevicePassword:(NSString *)devicePassword
                          data:(NSData *)data
               completionBlock:(CompletionBlock)completionBlock;

@end
