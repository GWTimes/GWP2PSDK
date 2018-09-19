//
//  GWNet.h
//  GWNet
//
//  Created by apple on 16/11/1.
//  Copyright © 2016年 YHQ. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonDigest.h>
#import "GWNetError.h"

#ifndef GWNetSingleton
#define GWNetSingleton [GWNet shareInstance]
#endif


/**
 接口回调block

 @param success 仅代表网络请求是否成功,不代表相应的操作结果,具体的要从errorCode判断
 @param errorCode 错误码, 0 代表没有错误,其它每个数字字符串代表确定的错误原因
 @param errorString 描述具体的错误原因
 @param json 具体的返回数据
 */
typedef void(^GWNetCompletionBlock)(BOOL success, NSString *errorCode, NSString *errorString, NSDictionary *json);

//调接口时会话ID错误发出的通知,会话ID超时/错误时所有接口无法调用,应该让用户重新登录获取新的Session。每个接口处理过于麻烦,所以增加通知。
extern NSString * const kGWNetSessionIdErrorNotification;


@interface GWNet : NSObject

@property (nonatomic, assign) BOOL connectWithHttps;/**< 以https的方式连接我们的服务器.默认为NO,用http的方式连接 */

@property(nonatomic,assign)NSInteger theTag;//这个相当于Tag
@property(nonatomic,copy)NSString* theTagString;//这个相当于String类型的Tag

#pragma mark - 获取单例
/**获取单例,注意,本程序并不是全单例,而是半单例,本程序并没有重写alloc方法,所以alloc出来的依然是独立的地址*/
+(instancetype)shareInstance;//获取单例

#pragma mark - 设置为输出日志
-(void)stOutputLog:(BOOL)outputLog;

#pragma mark - 必需设置的参数,如果不设置这些参数,会导致SDK传递的信息不正确
/**
 中文简体  中文繁体 英文 日语 韩语 德语 俄语
 zh-Hans zh-Hant en  ja  ko   de  ru ,其它语言请自行查询
 */
@property(nonatomic,copy)NSString* theAppLanguage;//设置SDK的语言,如果服务器支持的话,服务器会返回相应的语言,默认为iOS系统语言
@property(nonatomic,copy)NSString* theAppVersion;//APP的版本,类似于 2.3.4.7 这样的版本号,默认为 0.0.0.0
@property(nonatomic,copy)NSString* theAppName;//App名称,请尽可能提供相应的名称
@property(nonatomic,copy)NSString* theAppId;//APPID要与技威公司联系申请,否则SDK不能正常使用
@property(nonatomic,copy)NSString* theAppToken;//AppToken要与技威公司联系申请,否则SDK不能正常使用

/**
 服务器列表,自建服务器时才需要设置
 
 默认:
 
 @[@"api1.cloudlinks.cn",//中国大陆第一台
 
 @"api2.cloudlinks.cn",//中国大陆第二台
 
 @"api3.cloud-links.net",//外国第一台
 
 @"api4.cloud-links.net"];//外国第二台
 */
@property(nonatomic,copy)NSArray<NSString*>* serverList;

#pragma mark - 账号基础接口
#pragma mark 登录
/**
 登录
 
 回调数据:
 
 "error_code" 返回码（0：成功，其他值代表失败）
 
 "UserID"       用户ID
 
 P2PVerifyCode  p2p校验码1
 
 P2PVerifyCode2 p2p校验码2
 
 Email          用户邮箱地址
 
 NickName       用户昵称
 
 CountryCode    手机号国际代码
 
 PhoneNO        手机号
 
 ImageID        头像ID（0：系统默认头像）
 
 SessionID      会话ID（调用其他接口时用到

 @param name 1 手机号码(手机号登录可以用不带国码，也可以用 国码-手机号码（如（国码中的+号也可以省略）：86-13800008888 或 +86-13800008888）登录,但是，如果用户信息表中如果存在两个手机号相同而国码不相同时必需用“国码-手机号码”. 2 邮箱 3 ID号(如:10000|0x80000000 = -2147473648, -2147473648&0x7fffffff = 10000,01000是显示给用户的ID号,传给服务器可以为-2147473648也可以为01000)
 @param pwd 密码,需要32位的md5加密处理,如果提供明文密码,内部会自动加密
 @param token 苹果设备Token,用来远程推送,可空,空时则无法推送
 @param completion 请求完成回调
 */
-(void)loginWithUserName:(NSString*)name//可以为手机,如 +86-15200002222,或者邮箱地址,或者ID号,例如-2147473648
            withPassword:(NSString*)pwd//密码,需要32位的md5加密处理,如果提供明文密码,内部会自动加密
          withAppleToken:(NSString*)token//苹果设备Token,用来远程推送,可空,空时则无法推送
              completion:(GWNetCompletionBlock)completion;//请求完成回调

#pragma mark 第三方登录
/**
 第三方登录
 
 调用接口时,先判断是哪个平台登录,platformType参数1表示微信,4表示Facebook,5表示LINE,客户使用此接口时还可使用2表示匿名登录3表示混合登录
 
 匿名登录是通过取设备的特征信息生成UID(User Identification), unionID参数可传设备的UDID, user,pwd可不传,option每次传"3"即可
 
 混合登录是用第三方平台已有系统账号作为特征信息之一生成UID,第三方可以是微信,facebook,line等, unionID参数正常传, user,pwd可不传,option每次传"3"即可
 
 option传"1"时表示正常的登录,第一次登录时,账号还没有生成,此时不能传"1", 先传"2"或"3",传"2"表示绑定再有的Yoosee账号,此时user,pwd参数不能为空,传"3"时,服务器会自动生成一个Yoosee账号,生成账号后再调用初始化密码接口后,即可正常使用此账号

 @param platformType 平台,1表示微信 2表示匿名登录 3表示混合登录 4表示Facebook 5表示LINE,此参数不可空
 @param unionID 第三方平台验证后传回的唯一标识符,如果是匿名登录,提供设备的唯一标识即可,不可空,若是我司下游客户自己的账号,可用我司分配的AppVersion前两位和客户公司自己的账号拼成一个在我司平台唯一的账号,如 0046CustomAccount
 @param user Yoosee用户名,第三方平台登录后,绑定账号时要传,其它情况下可不传.可为手机,如+86-15200002222,或邮箱,或ID号,如010000,
 @param pwd Yoosee账号密码,第三方平台登录后,绑定账号时要传,其它情况下可不传
 @param token 苹果设备Token,用来远程推送,可空,空时则无法推送
 @param option 1 仅登录 2绑定老用户并登录 3登录,若不存在则自动注册
 @param storeID 商城ID,需要商城版功能时必须上传,可空,不懂的话留空即可
 @param nickName 昵称,此参数传入微信,line等授权后的昵称作为账号默认的昵称
 @param completion 回调
 */
-(void)thirdLoginWithPlatformType:(NSString*)platformType//平台,1.微信 2.匿名登录 3 混合登录 4.Facebook 5.LINE,此参数不可空
                      withUnionID:(NSString*)unionID//第三方平台的唯一标识符,如果是匿名登录,提供设备的唯一标识即可,不可空
                         withUser:(NSString*)user//用户名,可为手机,如+86-15200002222,或邮箱,或ID号,如010000,绑定账号时不可空
                     withPassword:(NSString*)pwd//密码,需要32位的md5加密处理,如果提供明文密码,内部会自动加密,绑定账号时不可空
                   withAppleToken:(NSString*)token//苹果设备Token,用来远程推送,可空,空时则无法推送
                       withOption:(NSString*)option//1仅登录 2绑定老用户并登录 3登录,若不存在则自动注册
                      withStoreID:(NSString*)storeID//商城ID,需要商城版功能时必须上传,可空,不懂的话留空即可
                         nickName:(NSString*)nickName//此参数传入微信,line等授权后的昵称作为账号默认的昵称
                       completion:(GWNetCompletionBlock)completion;//请求完成回调

/**
 第三方登陆后,初始化密码
 
 第三方登陆后,会自动生成一个Yoosee账号,但未生成密码,调用此接口配置密码
 
 @param password 密码
 @param userId yoosee用户Id
 @param sessionId 会话Id
 @param completion 回调
 */
- (void)thirdLoginInitPassword:(NSString *)password
                    withUserId:(NSString *)userId
                     sessionId:(NSString *)sessionId
                    completion:(GWNetCompletionBlock)completion;

#pragma mark 退出登录
/**
 退出登录

 @param userId 用户ID,数据从登录时返回的json里获取
 @param sessionId 会话ID,数据从登录时返回的json里获取
 @param completion 回调
 */
-(void)unLoginWithUserId:(NSString*)userId//这个应该从登录时返回的json里获取
           withSessionId:(NSString*)sessionId//这个应该从登录时返回的json里获取
              completion:(GWNetCompletionBlock)completion;//请求完成回调

#pragma mark 邮箱注册
-(void)regEmailWithEmail:(NSString*)name //邮箱地址
                 withPwd:(NSString*)pwd //密码,需要32位的md5加密处理,如果提供明文密码,内部会自动加密
               withRePwd:(NSString*)rePwd//再次密码,两次的密码应当一致
              completion:(GWNetCompletionBlock)completion;//请求完成回调

#pragma mark 获取支持手机注册的国家编码
/**
 获取支持手机注册的国家编码列表
 
 国家编码之间由’|’分隔，例如：86|44|233

 @param completion 回调
 */
- (void)getContryCodesSupportedTelephoneRegisterWithCompletion:(GWNetCompletionBlock)completion;

#pragma mark 手机号注册
/**
 手机号注册

 @param num 手机号
 @param cCode 国码,中国为 86,不要写成+86
 @param pwd 密码,需要32位的md5加密处理,如果提供明文密码,内部会自动加密
 @param rePwd 再次密码
 @param smsCode 短信验证码
 @param completion 回调
 */
-(void)regPhoneWithNum:(NSString*)num//手机号
       withCountryCode:(NSString*)cCode//国码,中国为 86,不要写成+86
          withPassword:(NSString*)pwd//密码,需要32位的md5加密处理,如果提供明文密码,内部会自动加密
             withRePwd:(NSString*)rePwd//再次密码
           withSmsCode:(NSString*)smsCode//短信验证码
            completion:(GWNetCompletionBlock)completion;//请求完成回调

#pragma mark 发验证码
/**
 发验证码,注册时用,手机找回的时候不要用这个方法.此接口针对同一手机号及客户端IP有严格的调用限制策略。前端调用接口时服务器返回“0（发送验证码成功）”、“27或10902025（获取手机验证码太频繁）”后，客户端必须限定用户在120秒内不能再调用此接口。

 @param code 国码
 @param num 手机号
 @param completion 回调
 */
-(void)sendSmsWithCountryCode:(NSString*)code//国码
                 withPhoneNum:(NSString*)num//手机号
                   completion:(GWNetCompletionBlock)completion;//请求完成回调

#pragma mark 验证验证码
/**
 验证验证码是否输入正确,手机注册时用,手机找回的时候不要用这个方法

 @param code 国码
 @param num 手机号
 @param vCode 短信验证码
 @param completion 回调
 */
-(void)checkSmsWithCountryCode:(NSString*)code//国码
                  withPhoneNum:(NSString*)num//手机号
                withVerifyCode:(NSString*)vCode//短信验证码
    completion:(GWNetCompletionBlock)completion;//请求完成回调

#pragma mark  通过邮箱找回
/**
 通过邮箱找回密码,会向这个邮箱发一封找回的邮件,按照操作能重置密码

 @param email 邮箱
 @param completion 回调
 */
-(void)findFromEmailWithEmail:(NSString*)email//会向这个邮箱发一封找回的邮件,仅此而已
                   completion:(GWNetCompletionBlock)completion;//请求完成回调

#pragma mark 通过手机找回来重置密码必需严格按顺序按照下面3步执行,过程中会用到2个不同的vKey,都是由服务器返回
#pragma mark 1.手机找回
/**
 手机找回,服务器会自动向手机发验证码,不需要调用上面发验证码的方法

 @param countryCode 国码,中国为 86,不要写成+86
 @param num 手机号
 @param completion 回调
 */
-(void)findFromPhoneWithCountryCode:(NSString*)countryCode//国码,中国为 86,不要写成+86
                       withPhoneNum:(NSString*)num//手机号
                         completion:(GWNetCompletionBlock)completion;//请求完成回调

#pragma mark 2.验证手机找回
/**
 验证手机找回,用这个方法来验证刚才通过找回的验证码是否正确

 @param theId 从手机找回返回的json里获取
 @param vKey 从手机找回返回的json里获取
 @param cCode 国码
 @param num 手机号
 @param smsCode 短信验证码
 @param completion 回调
 */
-(void)checkFindFromPhoneWithID:(NSString*)theId//这个应该从返回的json里获取
                       withVkey:(NSString*)vKey//这个应该从返回的json里获取
                withCountryCode:(NSString*)cCode//国码
                   withPhoneNum:(NSString*)num//手机号
                    withSmsCode:(NSString*)smsCode//短信验证码
                     completion:(GWNetCompletionBlock)completion;//请求完成回调

#pragma mark 3.通过手机重置密码
/**
 通过手机重置密码

 @param theId 从手机找回返回的json里获取
 @param vkey 从手机找回返回的json里获取
 @param pwd 密码,需要32位的md5加密处理,如果提供明文密码,内部会自动加密
 @param rePwd 确认密码
 @param completion 回调
 */
-(void)reSetPasswordWithId:(NSString*)theId//这个应该从返回的json里获取
                  withVkey:(NSString*)vkey//这个应该从返回的json里获取
                withNewPwd:(NSString*)pwd//密码,需要32位的md5加密处理,如果提供明文密码,内部会自动加密
                 withRePwd:(NSString*)rePwd//再次密码
                completion:(GWNetCompletionBlock)completion;//请求完成回调

#pragma mark 检查账号是否存在
/**
 检查要注册的账号是否存在

 @param account 账号,邮箱或者手机
 @param completion 回调
 */
-(void)checkAccountIsExistWithAccount:(NSString*)account//账号可以是邮箱或者手机
                           completion:(GWNetCompletionBlock)completion;//请求完成回调

#pragma mark 获取账户信息
/**
 获取账户信息
 
 返回数据:
 
 Email          绑定的邮箱
 
 CountryCode    绑定的国码
 
 PhoneNO        绑定的手机号码

 @param userID 用户ID
 @param sessionID 会话ID
 @param completion 回调
 */
-(void)gtUserInfoWithUserID:(NSString*)userID//这个应该从登录时返回的json里获取
              withSessionID:(NSString*)sessionID//这个应该从登录时返回的json里获取
                 completion:(GWNetCompletionBlock)completion;//请求完成回调

#pragma mark 设置账户安全信息
/**
 设置账户安全信息,用于绑定邮箱和手机号

 @param userID 用户ID
 @param sessionID 会话ID
 @param email 邮箱,此参数当bFlag传"2"或者"0"时有效,为空则解除绑定邮箱
 @param cCode 国码,此参数当bFlag传"1"或者"0"时有效,为空则解除绑定手机
 @param phone 手机号,此参数当bFlag传"1"或者"0"时有效,为空则解除绑定手机,绑定的手机应该是未被注册过的手机
 @param Pwd 密码,绑定邮箱或者手机需要验证密码,需要32位的md5加密处理,如果提供明文密码,内部会自动加密
 @param bFlag //绑定标志(0:同时绑定手机和邮箱 1:仅绑定手机 2:仅绑定邮箱) 不可空
 @param sms 验证码,绑定手机的时候需要提供手机验证码,先调发验证码接口
 @param completion 回调
 */
-(void)stUserInfoWithUserID:(NSString*)userID//这个应该从登录时返回的json里获取
              withSessionID:(NSString*)sessionID//这个应该从登录时返回的json里获取
                  withEmail:(NSString*)email//绑定邮箱,此参数当bFlag=2或者0时有效,为空则解除绑定邮箱
            withCountryCode:(NSString*)cCode//国码,此参数当bFlag=1或者0时有效,为空则解除绑定手机
               withPhoneNum:(NSString*)phone//手机号,此参数当bFlag=1或者0时有效,为空则解除绑定手机,绑定的手机应该是未被注册过的手机
                withUserPwd:(NSString*)Pwd//绑定邮箱或者手机需要验证密码,需要32位的md5加密处理,如果提供明文密码,内部会自动加密
               withBindFlag:(NSString*)bFlag//绑定标志(0:同时绑定手机和邮箱 1:仅绑定手机 2:仅绑定邮箱) 不可空
                    withSms:(NSString*)sms//当绑定手机的时候需要提供手机验证码,可以调发验证码的接口就行了
                 completion:(GWNetCompletionBlock)completion;//请求完成回调

#pragma mark 修改用户账号密码
/**
 修改用户账号密码

 @param userID 用户iD
 @param sessionID 会话ID
 @param oldPwd 账号的原密码,需要32位的md5加密处理,如果提供明文密码,内部会自动加密
 @param pwd 账号的新密码,需要32位的md5加密处理,如果提供明文密码,内部会自动加密
 @param rePwd 确认新密码
 @param completion 回调
 */
-(void)changeUserPasswordWithUserID:(NSString*)userID//用户iD
                      withSessionID:(NSString*)sessionID//会话ID
                         withOldPwd:(NSString*)oldPwd//账号的原密码,需要32位的md5加密处理,如果提供明文密码,内部会自动加密
                            withPwd:(NSString*)pwd//账号的新密码,需要32位的md5加密处理,如果提供明文密码,内部会自动加密
                          withRePwd:(NSString*)rePwd//两次确认的新密码,需要32位的md5加密处理,如果提供明文密码,内部会自动加密
                         completion:(GWNetCompletionBlock)completion;//请求完成回调

#pragma mark - 设备同步接口
#pragma mark 设备同步-增加设备
/**
 增加设备

 @param userID 用户ID
 @param sessionID 会话ID
 @param modifyTime 客户端本地修改时的UTC时间戳
 @param deviceID 设备ID
 @param devicePwd 设备加密后的密码
 @param remarkName 设备昵称
 @param permission 权限(初始为0，表示不支持权限配置)
 @param completion 回调
 */
-(void)addDeviceWithUserID:(NSString*)userID//用户ID
                 sessionID:(NSString*)sessionID//会话ID
                modifyTime:(NSString*)modifyTime//客户端本地修改时的UTC时间戳
                  deviceID:(NSString*)deviceID//设备ID
                 devicePwd:(NSString*)devicePwd//设备加密后的密码
                remarkName:(NSString*)remarkName//设备昵称
                permission:(NSInteger)permission//权限（初始为0，表示不支持权限配置)
                completion:(GWNetCompletionBlock)completion;

#pragma mark 设备同步-删除设备
/**
 删除设备,服务器不会真删除,只把状态标识变为0,下次拉取数据时设备还会返回
 
 主人请不要调此接口,调解绑接口,会同时删除设备

 @param userID 用户ID
 @param sessionID 会话ID
 @param modifyTime 客户端本地修改时的UTC时间戳,只能是整数
 @param deviceID 设备ID
 @param completion 回调
 */
-(void)deleteDeviceWithUserID:(NSString*)userID//用户ID
                    sessionID:(NSString*)sessionID//会话ID
                   modifyTime:(NSString*)modifyTime//客户端本地修改时的UTC时间戳
                     deviceID:(NSString*)deviceID//设备ID
                   completion:(GWNetCompletionBlock)completion;

#pragma mark 设备同步-修改设备
/**
 修改设备,修改一台设备信息

 @param userID 用户ID
 @param sessionID 会话ID
 @param modifyTime 客户端本地修改时的UTC时间戳
 @param deviceID 设备ID
 @param devicePwd 设备加密后的密码
 @param remarkName 设备昵称
 @param permission 权限,不可通过此接口更改设备权限
 @param completion 回调
 */
-(void)modifyDeviceWithUserID:(NSString*)userID//用户ID
                    sessionID:(NSString*)sessionID//会话ID
                   modifyTime:(NSString*)modifyTime//客户端本地修改时的UTC时间戳
                     deviceID:(NSString*)deviceID//设备ID
                     devicePwd:(NSString*)devicePwd//设备加密后的密码
                   remarkName:(NSString*)remarkName//设备昵称
                   permission:(NSInteger)permission
                   completion:(GWNetCompletionBlock)completion;

#pragma mark 设备同步-批量更新设备
/**
 设备同步-批量更新设备
 
 参数 DeviceInfo 格式说明（两台设备信息之间用英式','分隔，各个信息字段用英式'|'分隔）,如
 
 "操作选项1|修改时间1|设备信息版本号1|分组ID1|设备ID1|权限1|秘钥1|备注名1,操作选项2|修改时间2|设备信息版本号2|分组ID2|设备ID2|权限2|秘钥2|备注名2"
 
 操作选项取值：1（添加）、2（删除）、3（修改）,最大包含200台设备信息。

 @param userID 用户ID
 @param sessionID 会话ID
 @param deviceInfo 设备信息,要更改的设备信息,按上面说明的格式填写
 @param completion 回调
 */
-(void)upgradeDevicesWithUserID:(NSString*)userID//用户ID
                    sessionID:(NSString*)sessionID//会话ID
                     deviceInfo:(NSString*)deviceInfo//设备信息
                     completion:(GWNetCompletionBlock)completion;

#pragma mark 设备同步-拉取设备信息
/**
 设备同步-拉取设备信息
 
 回调数据说明:
 
 DeviceInfo格式,和批量更新不完全一致（两台设备信息之间用英式','分隔，各个信息字段用英式'|'分隔）,如:
 
 "修改时间1|设备信息版本号1|分组ID1|设备ID1|权限1|秘钥1|备注名1|状态1,修改时间2|设备信息版本号2|分组ID2|设备ID2|权限2|秘钥2|备注名2|状态2"
 
 这里的“状态”取值：0（已标记为删除【实际上不会真正删除数据】，APP不要显示）、1（正常）。

 @param userID 用户ID
 @param sessionID 会话ID
 @param preDeviceID 上次拉取时获取到的最后一个设备ID（第一次拉取填0
 @param requestCount 请求拉取的设备数量（每次最大200个）
 @param upgradeFlag 本地缓存的列表最后更新标志,传"0"即可
 @param upgCheckList 要获取哪些设备有固件更新,格式为"设备ID1|设备ID2"
 @param completion 回调
 */
-(void)loadDevicesWithUserID:(NSString*)userID//用户ID
                   sessionID:(NSString*)sessionID//会话ID
                 preDeviceID:(NSString*)preDeviceID//上次拉取时获取到的最后一个设备ID（第一次拉取填0）
                requestCount:(NSUInteger)requestCount//请求拉取的设备数量（每次最大200个）
                 upgradeFlag:(NSString*)upgradeFlag//本地缓存的列表最后更新标志
                upgCheckList:(NSString*)upgCheckList
                  completion:(GWNetCompletionBlock)completion;

#pragma mark - 分享接口
#pragma mark 锁定设备
/**
 锁定设备绑定主人的功能
 
 锁定后其它用户不能再对此设备进行绑定主人操作
 
 同时此接口可查询设备是否已经被绑定了
 
 主人绑定设备有好几个步骤,每个步骤失败后,都会导致整个绑定过程失败,先调此接口查询服务器能不能绑定设备,同时,此接口会返回上一次同一个主人账号设置过的访客密码,第二次重复绑定时,可使用此密码,保证先前的访客还能使用此设备。

 @param deviceID   设备ID
 @param userID     用户ID
 @param sessionID  登陆会话ID
 @param completion 绑定完成后的block
 */
- (void)lockBindingDevice:(NSString *)deviceID
               withUserID:(NSString *)userID
                sessionID:(NSString *)sessionID
               completion:(GWNetCompletionBlock)completion;

#pragma mark 绑定主人
/**
 绑定主人

 关于权限的定义，Permission是8字节整型，总共有64个bit，从低位到高位分配如下：
 
 Bit0: 表示是否启用权限管理功能
 
 Bit1: 表示是否是设备的主人(主人不受其他权限位的影响；不是主人才需要根据权限位的定义处理)
 
 Bit2：表示是否有基本权限(看视频、截屏、录制本地视频、查看当前流量，调整画质[分辨率])
 
 Bit3：表示是否有摇头权限
 
 Bit4：表示是否有语音（含对讲）权限；
 
 Bit5：表示是否有回放（包含云回放）权限
 
 Bit6：表示是否有布撤防权限；
 
 Bit7：表示是否有开锁（支持锁的设备才显示开锁权限设置）权限；
 
 Bit8：表示是否有接收设备消息（报警、门铃、呼叫等）推送权限；
 
 Bit9: 表示是否开启接收设备消息（当Bit8为1，此位才有效）；

 @param deviceID          设备ID
 @param userID            用户(主人)ID
 @param sessionID         登陆会话ID
 @param modifyTime        绑定时时间戳
 @param deviceInfoVersion 设备信息版本号(现在传 0，后续可使用不同版本号对应不同的加密方式等)
 @param groupID           分组ID(现在传 0，表示不支持设备分组)
 @param permission        权限(必须是开启权限功能且是主人,按权限值计算)
 @param secretKey         设备加密后的密码(主人密码)
 @param guestKey          设备加密后的访客密码
 @param remarkName        设备备注名称
 @param keyID             由DeviceID+Rkey组成(其中DeviceID、RKey需要加密)
 @param customID          客户ID,从配网后的数据获取,获取不到传0
 @param macAddr           设备网卡地址,从配网后的数据获取,获取不到传空
 @param completion        绑定完成后的block
 */
- (void)bindDevice:(NSString *)deviceID
        withUserID:(NSString *)userID
         sessionID:(NSString *)sessionID
        modifyTime:(NSString *)modifyTime
 deviceInfoVersion:(NSString *)deviceInfoVersion
           groupID:(NSString *)groupID
        permission:(NSInteger)permission
         secretKey:(NSString *)secretKey
          guestKey:(NSString *)guestKey
        remarkName:(NSString *)remarkName
             keyID:(UInt64)keyID
          customID:(int)customID
           macAddr:(NSString *)macAddr
        completion:(GWNetCompletionBlock)completion;

#pragma mark 获取邀请码
/**
 获取邀请码,此接口已经不用,改用获取邀请链接
 
 @param deviceID   设备ID
 @param userID     用户(主人)ID
 @param sessionID  登陆会话ID
 @param permission 权限(必须是开启权限功能且是主人)
 @param completion 绑定完成后的block
 */
- (void)getInviteCodeWithUserID:(NSString *)userID
                      sessionID:(NSString *)sessionID
                       deviceID:(NSString *)deviceID
                     permission:(NSInteger)permission
                     completion:(GWNetCompletionBlock)completion;

#pragma mark 获取邀请链接
/**
 获取邀请链接
 
 返回ShareLink:分享链接(包含链接作用类型、邀请码、分享者的昵称、分享者APP的版本号、设备ID)。链接作用类型=1 代表是分享功能的链接

 @param userID 用户(主人)ID
 @param sessionID 登陆会话ID
 @param deviceID 设备ID
 @param permission 权限(必须是开启权限功能且是访客,传1即可)
 @param guestID 访客ID(二维码或链接分享时传空)
 @param guestRemark 访客备注名(二维码或链接分享时传空)
 @param appendMsg 留言(二维码或链接分享时传空)
 @param completion 回调
 */
- (void)getShareLinkWithUserID:(NSString *)userID
                     sessionID:(NSString *)sessionID
                      deviceID:(NSString *)deviceID
                    permission:(NSInteger)permission
                       guestID:(NSString *)guestID
                   guestRemark:(NSString *)guestRemark
                     appendMsg:(NSString *)appendMsg
                    completion:(GWNetCompletionBlock)completion;

#pragma mark 获取访客列表
/**
 获取访客列表
 
 @param userID     用户(主人)ID
 @param sessionID  登陆会话ID
 @param deviceID   设备ID
 @param completion 绑定完成后的block
 */
- (void)getGuestListWithUserID:(NSString *)userID
                     sessionID:(NSString *)sessionID
                      deviceID:(NSString *)deviceID
                    completion:(GWNetCompletionBlock)completion;

#pragma mark 删除访客
/**
 主人删除访客
 
 @param userID     用户(主人)ID
 @param sessionID  登陆会话ID
 @param deviceID   设备ID
 @param guestID    访客ID
 @param completion 绑定完成后的block
 */
- (void)deleteGuestWithUserID:(NSString *)userID
                    sessionID:(NSString *)sessionID
                     deviceID:(NSString *)deviceID
                      guestID:(NSString *)guestID
                   completion:(GWNetCompletionBlock)completion;

#pragma mark 删除主人信息（解绑）
/**
 删除主人信息（解绑）
 
 解绑后服务器会直接删除设备,不用再调删除设备接口
 
 @param userID     用户(主人)ID
 @param sessionID  登陆会话ID
 @param deviceID   设备ID
 @param completion 绑定完成后的block
 */
- (void)deleteOwnerWithUserID:(NSString *)userID
                    sessionID:(NSString *)sessionID
                     deviceID:(NSString *)deviceID
                   completion:(GWNetCompletionBlock)completion;

#pragma mark 获取设备密码
/**
 获取设备密码
 
 @param userID     用户(主人)ID
 @param sessionID  登陆会话ID
 @param deviceID   设备ID
 @param completion 绑定完成后的block
 */
- (void)getSharedDevicePasswordWithUserID:(NSString *)userID
                                sessionID:(NSString *)sessionID
                                 deviceID:(NSString *)deviceID
                               completion:(GWNetCompletionBlock)completion;

#pragma mark 获取被分享的设备信息(访客添加被分享的设备)
/**
 通过邀请码获取被分享的设备信息(访客添加被分享的设备)
 
 @param userID     用户(访客)ID
 @param sessionID  登陆会话ID
 @param inviteCode 邀请码(设备主人分享得到,二维码或文本)
 @param completion 绑定完成后的block
 */
- (void)getSharedDeviceInfomationWithUserID:(NSString *)userID
                                  sessionID:(NSString *)sessionID
                                 inviteCode:(NSString *)inviteCode
                                 completion:(GWNetCompletionBlock)completion;


#pragma mark 设置访客权限
/**
 主人设置访客权限

 @param userID 用户ID
 @param sessionID 会话ID
 @param deviceID 设备ID
 @param guestID 访客ID
 @param permission 权限值
 @param completion 回调
 */
- (void)modifyGuestPermissionWithUserID:(NSString *)userID
                              sessionID:(NSString *)sessionID
                               deviceID:(NSString *)deviceID
                                guestID:(NSString *)guestID
                             permission:(NSString *)permission
                             completion:(GWNetCompletionBlock)completion;

#pragma mark 主人分享时查询访客信息
/**
 主人分享时查询访客信息

 @param userID 主人ID
 @param sessionID 会话ID
 @param deviceID 设备ID
 @param guestAccount 要分享的访客ID
 @param completion 回调
 */
- (void)getGuestInfoWithUserID:(NSString *)userID
                     sessionID:(NSString *)sessionID
                      deviceID:(NSString *)deviceID
                  guestAccount:(NSString *)guestAccount
                    completion:(GWNetCompletionBlock)completion;

#pragma mark 主人修改访客备注
/**
 主人修改访客备注

 @param userID 主人ID
 @param sessionID 会话ID
 @param deviceID 设备ID
 @param guestID 访客ID
 @param remarkName 修改后的备注名
 @param completion 回调
 */
- (void)modifyGuestRemarknameWithUserID:(NSString *)userID
                              sessionID:(NSString *)sessionID
                               deviceID:(NSString *)deviceID
                                guestID:(NSString *)guestID
                             remarkName:(NSString *)remarkName
                             completion:(GWNetCompletionBlock)completion;

#pragma mark 修改用户昵称
/**
 修改用户昵称

 @param userID 用户ID
 @param sessionID 会话ID
 @param nickName 昵称
 @param completion 回调
 */
- (void)modifyNicknameWithUserID:(NSString *)userID
                       sessionID:(NSString *)sessionID
                        nickName:(NSString *)nickName
                      completion:(GWNetCompletionBlock)completion;

#pragma mark 主人/访客解除接收推送
/**
 主人/访客解除接收报警推送

 @param userID 用户ID
 @param sessionID 会话ID
 @param deviceID 设备ID
 @param completion 回调
 */
- (void)cancelReceivePushWithUserID:(NSString *)userID
                          sessionID:(NSString *)sessionID
                           deviceID:(NSString *)deviceID
                         completion:(GWNetCompletionBlock)completion;


#pragma mark - 自定义服务器地址请求
/**
 自定义链接请求,适用于单独的Web API或者测试
 
 @param urlStr     请求链接
 @param paras      除了公共参数之外的参数
 @param completion 回调
 */
- (void)requestWithURLString:(NSString *)urlStr parameters:(NSDictionary *)paras completion:(GWNetCompletionBlock)completion;

@end
