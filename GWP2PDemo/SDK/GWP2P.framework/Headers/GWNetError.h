//
//  GWNetError.h
//  Yoosee
//
//  Created by zengyuying on 17/1/9.
//  Copyright © 2017年 Gwelltimes. All rights reserved.
//

//以下是根据新服务器网络接口错误码定义的宏,原为16进制的值,因为GWNet返回的是NSString,所以直接定义为字符串


#define GWNET_RET_OPERATION_SUCCESS @"0"  //成功

#define GWNET_RET_SHOW_SERVER_MESSAGE_1  @"10001"  //app直接显示服务器返回的错误字符串
#define GWNET_RET_SHOW_SERVER_MESSAGE_2  @"10901061"  //app直接显示服务器返回的错误字符串
#define GWNET_RET_SYSTEM_MAINTENANCE_ERROR  @"10901060"  //系统正在维护，请稍后再试
#define GWNET_RET_PASSWORD_HAS_BEEN_INITED_ERROR  @"10902076"  //密码已被初始化过，无法再初始化
#define GWNET_RET_COUNTRY_CODE_FORMAT_ERROR @"10902075"  //国家码数据格式不正确
#define GWNET_RET_REGIEST_FAILED @"10902072"  //注册失败
#define GWNET_RET_GET_PHONE_CODE_REACH_CEILING @"10902026"  //获取手机验证码已到达上限
#define GWNET_RET_GET_PHONE_CODE_TOO_TIMES @"10902025"  //获取手机验证码太频繁
#define GWNET_RET_SEND_VERIFY_CODE_FAILED @"10902024"  //发送手机验证码失败
#define GWNET_RET_SEND_VERIFY_EMAIL_FAILED @"10902023"  //发送验证邮件失败
#define GWNET_RET_EMAIL_USED @"10902021"  //邮箱已被使用
#define GWNET_RET_PHONE_USED @"10902020"  //手机号已被使用
#define GWNET_RET_ACCOUNT_DISABLED @"10902013"  //帐号不可用_不可用的原因在error中返回帐号状态编号
#define GWNET_RET_SESSION_ID_ERROR @"10902012"  //会话ID不正确
#define GWNET_RET_ACCOUNT_NOT_EXIST @"10902011"  //用户不存在
#define GWNET_RET_PHONE_CODE_TIMEOUT @"10902010"  //手机验证码超时
#define GWNET_RET_PHONE_CODE_ERROR @"10902009"  //手机验证码不正确
#define GWNET_RET_LACK_COUNTRY_CODE @"10902007"  //请在手机号前输入国码
#define GWNET_RET_BIND_ACCOUNT_PASSWORD_ERROR @"10902005"  //绑定的用户密码错误
#define GWNET_RET_BIND_ACCOUNT_NOT_EXIST @"10902004"  //绑定的用户不存在
#define GWNET_RET_ACCOUNT_PASSWORD_ERROR @"10902003"  //用户密码错误
#define GWNET_RET_THIRD_ACCOUNT_NOT_EXIST @"10902002"  //第三方账号不存在
#define GWNET_RET_THIRD_ACCOUNT_EXIST @"10902001"  //第三方账号已存在
#define GWNET_RET_SERVICE_NOT_SUPPORT @"10901071"  //服务器不支持此项服务
#define GWNET_RET_PASSWORD_FORMAT_ERROR @"10901024"  //密码数据格式不符合要求
#define GWNET_RET_EMAIL_FORMAT_ERROR @"10901023"  //邮箱地址数据格式不符合要求
#define GWNET_RET_PHONE_FORMAT_ERROR @"10901022"  //手机号数据格式不符合要求
#define GWNET_RET_LACK_PARAMETER_ERROR @"10901020"  //缺少输入参数
#define GWNET_RET_GET_EMAIL_CODE_TOO_OFTEN @"10902027"  //获取邮件太频繁
#define GWNET_RET_GET_EMAIL_CODE_COUNT_LIMIT @"10902028" //邮件验证码超时
#define GWNET_RET_EMAIL_CODE_ERROR @"10902029"  //邮件验证码不正确
#define GWNET_RET_EMAIL_CODE_TIMEOUT @"10902030"  //邮件验证码超时

//同步设备列表相关
#define GWNET_RET_ADD_DEVICE_ALREADY_EXIST @"1090200A"	//设备已存在，不能重复添加
#define GWNET_RET_MODIFY_DEVICE_NOT_EXIST @"1090200B"	//设备信息不存在
#define GWNET_RET_MODIFY_DEVICE_SERVER_NEWER @"1090200C"	//服务器上的记录比客户端的新，客户端需要重新加载
#define GWNET_RET_DEVICE_ID_REPEATED @"1090200D"	//设备ID重复
#define GWNET_RET_LOAD_DEVICE_ALREADY_LAST @"1090200E"	//您的设备列表已经是最新的，不需要从服务器拉取了

//设备分享
#define GWNET_RET_SHARING_DEVICE_HAS_NO_OWNER @"10905002"	//此设备还没有主人
#define GWNET_RET_SHARING_DEVICE_HAS_OWNER @"10905001"	//此设备已有主人
#define GWNET_RET_SHARING_DEVICE_HAS_BE_LOCKED_AND_IS_BEENING_BINDED @"10905003"	//此设备已被锁定，正在绑定主人信息
#define GWNET_RET_SHARING_DEVICE_HAS_BE_LOCKED @"10905004"	//此设备已被他人锁定及绑定主人信息
#define GWNET_RET_SHARING_INSUFFICIONT_USER_PERMISSIONS @"10905005" //必须是主人权限才能操作
#define GWNET_RET_SHARING_CREATE_INVATE_CODE_FAIL @"10905007" //创建邀请码失败
#define GWNET_RET_SHARING_INVATE_CODE_INVANIDATE @"10905008" //邀请码无效（不存在或超时）
#define GWNET_RET_SHARING_IS_OWNER @"10905009" //已经是主人
#define GWNET_RET_SHARING_IS_VISITOR @"10905010" //已经是访客
#define GWNET_RET_PARAMETER_ERROR @"10901025"  //参数错误

//设备数量限制
#define GWNET_RET_ADD_DEVICE_COUNT_LIMIT @"10905014" //添加的当前设备数量已达到上限
#define GWNET_RET_ADD_PAST_DEVICE_COUNT_LIMIT @"10905014" //添加的历史设备数量已达到上限
#define GWNET_RET_DEVICE_BINDED_COUNT_LIMIT @"10905014" //当前设备被绑定的次数已达到上限

//权限管理
#define GWNET_RET_VISITOR_HAS_DELETE_DEVICE @"10905017" //配置权限时访客已删除该设备


//以下错误码在客户端暂时没用到,有需要时再进行定义

//需要用到再定义 #define  @"10902074"  //验证码为空
//需要用到再定义 #define  @"10902073"  //验证码不存在
//需要用到再定义 #define  @"10902022"  //为了你的帐号安全，请输入邮箱地址
//需要用到再定义 #define  @"10902014"  //重置密码链接无效
//需要用到再定义 #define  @"10902008"  //系统分配账号失败
//需要用到再定义 #define  @"10902006"  //获取绑定的用户信息失败
//需要用到再定义 #define  @"109013E9"  //请换用其他服务器接口
//需要用到再定义 #define  @"10901070"  //访问受限制
//需要用到再定义 #define  @"10901061"  //这里的内容动态生成，APP直接显示此内容
//需要用到再定义 #define  @"10901053"  //APP客户号(内置主版本号)错误
//需要用到再定义 #define  @"10901052"  //APP信息不存在
//需要用到再定义 #define  @"10901051"  //此APP已被冻结
//需要用到再定义 #define  @"10901050"  //APP信息(AppID、AppToken、包名等)不正确
//需要用到再定义 #define  @"10901040"  //系统配置错误
//需要用到再定义 #define  @"1090103E"  //请换用其他服务器接口
//需要用到再定义 #define  @"10901030"  //发现非法字符
//需要用到再定义 #define  @"10901027"  //参数超出范围
//需要用到再定义 #define  @"10901026"  //用户ID必须以0开头
//需要用到再定义 #define  @"10901021"  //输入数据格式错误
//需要用到再定义 #define  @"10901012"  //文件操作失败
//需要用到再定义 #define  @"10901011"  //文件不存在
//需要用到再定义 #define  @"10901010"  //文件打开失败
//需要用到再定义 #define  @"10901004"  //数据库操作异常
//需要用到再定义 #define  @"10901003"  //数据库记录集为空
//需要用到再定义 #define  @"10901002"  //数据库操作失败
//需要用到再定义 #define  @"10901001"  //数据库连接失败
