//
//  GWNetError.h
//  Yoosee
//
//  Created by zengyuying on 17/1/9.
//  Copyright © 2017年 Gwelltimes. All rights reserved.
//
#import <Foundation/Foundation.h>

//以下是根据新服务器网络接口错误码定义的宏,原为16进制的值,因为GWNet返回的是NSString,所以直接定义为字符串
/**
 +--反馈码--+---反馈码的描述----+
 50104006    在别处登录，被踢飞
 5010200A    UDP转发服务器握手失败
 50102009    连接tcp转发服务器成功，等待配对失败
 50102008    连接tcp转发服务器失败
 50102007    申请多路径传输，握手超时
 50102006    申请多路径传输超时
 50102005    局域网点对点连接失败
 50102004    发出呼叫，等待目标ID的地址信息超时
 50102003    传输数据中出现传输超时
 50102002    连接状态准备好，尝试传输数据超时
 40104006    在别处登录，被踢飞
 4010200A    UDP转发服务器握手失败
 40102009    连接tcp转发服务器成功，等待配对失败
 40102008    连接tcp转发服务器失败
 40102007    申请多路径传输，握手超时
 40102006    申请多路径传输超时
 40102005    局域网点对点连接失败
 40102004    发出呼叫，等待目标ID的地址信息超时
 40102003    传输数据中出现传输超时
 40102002    连接状态准备好，尝试传输数据超时
 30401003    Http库网络不通
 30401002    没有服务器可以连通
 30401001    JSON解析错误
 30104006    在别处登录，被踢飞
 30104005    等待p2p服务器响应超时
 30104004    List服务器响应超时
 30104003    解析List服务器响应包失败
 30104002    域名解析失败
 30104001    操作正在执行,没有错误,但是还没有链接到p2p服务器
 3010200F    APP和设备通过多个中继服务器握手都失败
 3010200E    发出呼叫，服务器收到并且处理，但是未收到mtp资源分配帧。需要排查设备是否收到calling，并且发起资源请求帧。
 3010200D    发出呼叫，通信层未收到ack。需排查APP网络是否正常或者p2p服务器是否正常工作
 3010200C    没有权限监控设备
 3010200A    UDP转发服务器握手失败
 30102009    连接tcp转发服务器成功，等待配对失败
 30102008    连接tcp转发服务器失败
 30102007    申请多路径传输，握手超时
 30102006    申请多路径传输超时
 30102005    局域网点对点连接失败
 30102004    发出呼叫，等待目标ID的地址信息超时
 30102003    传输数据中出现传输超时
 30102002    连接状态准备好，尝试传输数据超时
 20104006    在别处登录，被踢飞
 20104005    等待p2p服务器响应超时
 20104004    List服务器响应超时
 20104003    解析List服务器响应包失败
 20104002    域名解析失败
 20104001    操作正在执行,没有错误,但是还没有链接到p2p服务器
 2010200C    没有权限监控设备
 2010200A    UDP转发服务器握手失败
 20102009    连接tcp转发服务器成功，等待配对失败
 20102008    连接tcp转发服务器失败
 20102007    申请多路径传输，握手超时
 20102006    申请多路径传输超时
 20102005    局域网点对点连接失败
 20102004    发出呼叫，等待目标ID的地址信息超时
 20102003    传输数据中出现传输超时
 20102002    连接状态准备好，尝试传输数据超时
 2010100F    APP和设备通过多个中继服务器握手都失败
 2010100E    发出呼叫，服务器收到并且处理，但是未收到mtp资源分配帧。需要排查设备是否收到calling，并且发起资源请求帧
 2010100D    发出呼叫，服务器收到并且处理，但是未收到mtp资源分配帧。需要排查设备是否收到calling，并且发起资源请求帧发出呼叫，通信层未收到ack。需排查APP网络是否正常或者p2p服务器是否正常工作
 1090A003    Kafka发送失败
 1090A002    Kafka模块内部异常
 1090A001    Kafka模块初始化失败
 10909500    获取推流地址失败
 10908505    无视频记录
 10908501    直播创建失败
 10908404    直播停止
 10908201    直播播放次数
 10908200    直播消息
 10908103    指定时间段没有视频文件
 10908102    当前日期没有视频文件
 10908101    超出可下载时间范围
 10907101    手机号修改次数达到上限，具体参见用户协议
 10906401    无权限进入增值服务
 10906400    无效订单
 10906301    优惠劵已失效
 10906206    支付异常，请联系客服
 10906205    未知状态
 10906204    支付失败
 10906203    支付成功
 10906202    与第三方通信失败
 10906201    签名信息获取失败
 10906101    订单下单失败，请重试
 10905016    当前设备被绑定的次数已达到上限
 10905015    添加的历史设备数量已达到上限
 10905014    添加的当前设备数量已达到上限
 10905013    设备预配网信息校验失败
 10905012    设备预配网信息已存在
 10905011    设备被其他app绑定
 10905009    已是设备主人
 10905008    邀请码无效（不存在或超时）
 10905007    创建邀请码失败
 10905006    主人权限不能被分享
 10905005    必须是主人权限才能操作
 10905004    此设备已被他人锁定及绑定主人信息
 10905003    此设备已被锁定，正在绑定主人信息
 10905002    此设备还没有有主人
 10905001    此设备已有主人
 10903013    没有权限
 10903012    文件上传异常
 10903011    输入参数错误
 10903010    数据已存在
 10903009    操作失败
 10903008    未登录或登陆超时
 10903007    登陆信息异常
 10903006    数据库操作异常
 10903005    导入文件有误
 10903004    查询结果为空
 10903003    该ID的记录不存在
 10903002    系统异常
 10903001    没有回放权限
 10902076    密码已被初始化过，无法再初始化
 10902075    国家码数据格式不正确
 10902074    验证码为空
 10902073    验证码不存在
 10902072    注册失败
 10902027    输入手机号格式错误
 10902026    获取手机验证码已到达上限
 10902025    获取手机验证码太频繁
 10902025    获取手机验证码太频繁
 10902024    发送手机验证码失败
 10902023    发送验证邮件失败
 10902022    为了你的帐号安全，请输入邮箱地址
 10902021    邮箱已被使用
 10902020    手机号已被使用
 10902018    同一IP登录密码错误次数超过限制
 10902017    你的IP已被限制访问
 10902016    登录密码错误次数达到上限，请X分钟后再试
 10902015    登录太频繁，请X分钟后再试
 10902014    重置密码链接无效
 10902013    帐号不可用_不可用的原因在error中返回帐号状态编号
 10902012    会话ID不正确
 10902011    用户不存在
 10902010    手机验证码超时
 1090200E    设备列表已是最新的，无需重新加载
 1090200D    添加/上传设备列表时ID重复
 1090200C    请重新从服务器加载设备/好友列表
 1090200B    设备ID或好友不在列表中
 1090200A    设备ID或好友已在列表中
 10902009    手机验证码不正确
 10902008    系统分配账号失败
 10902007    请在手机号前输入国码
 10902006    获取绑定的用户信息失败
 10902005    绑定的用户密码错误
 10902004    绑定的用户不存在
 10902003    用户密码错误
 10902002    第三方账号不存在
 10902001    第三方账号已存在
 10901500    系统异常
 109013E9    请换用其他服务器接口
 10901090    protobuf序列化失败
 10901080    权限不足
 10901073    调用当前接口太频繁
 10901072    您的IP调用接口太频繁，已被限制访问
 10901071    服务器不支持此项服务
 10901070    访问受限制
 10901062    设备或用户的校验秘钥（R1R2）错误
 10901061    这里的内容动态生成，APP直接显示此内容
 10901060    系统正在维护，请稍后再试
 10901053    APP客户号(内置主版本号)错误
 10901052    APP信息不存在
 10901051    此APP已被冻结
 10901050    APP信息(AppID、AppToken、包名等)不正确
 10901040    系统配置错误
 10901030    发现非法字符
 10901027    参数超出范围
 10901026    用户ID必须以0开头
 10901025    参数错误
 10901024    密码数据格式不符合要求
 10901023    邮箱地址数据格式不符合要求
 10901022    手机号数据格式不符合要求
 10901021    输入数据格式错误
 10901020    缺少输入参数
 10901012    文件操作失败
 10901011    文件不存在
 10901010    文件打开失败
 10901005    数据库内部数据异常
 10901004    数据库操作异常
 10901003    数据库记录集为空
 10901001    数据库连接失败
 */
typedef NSString *GWNetErrCode NS_STRING_ENUM;

//常见错误
FOUNDATION_EXPORT GWNetErrCode const SUCCESS;                                 //成功
FOUNDATION_EXPORT GWNetErrCode const UNKNOWN;                                 //未知
FOUNDATION_EXPORT GWNetErrCode const KEY_LOGIN_NEED_PASSWORD;                 //一键登录 注册需要设置密码
FOUNDATION_EXPORT GWNetErrCode const KEY_LOGIN_OPERATOR_PHONE_ERROR;          //一键登录 获取运营商的手机号失败
FOUNDATION_EXPORT GWNetErrCode const SHOW_SERVER_MESSAGE_1;                   //app直接显示服务器返回的错误字符串
FOUNDATION_EXPORT GWNetErrCode const SHOW_SERVER_MESSAGE_2;                   //app直接显示服务器返回的错误字符串
FOUNDATION_EXPORT GWNetErrCode const SYSTEM_MAINTENANCE_ERROR;                //系统正在维护，请稍后再试
FOUNDATION_EXPORT GWNetErrCode const PASSWORD_HAS_BEEN_INITED_ERROR;          //密码已被初始化过，无法再初始化
FOUNDATION_EXPORT GWNetErrCode const COUNTRY_CODE_FORMAT_ERROR;               //国家码数据格式不正确
FOUNDATION_EXPORT GWNetErrCode const REGIEST_FAILED;                          //注册失败
FOUNDATION_EXPORT GWNetErrCode const GET_PHONE_CODE_REACH_CEILING;            //获取手机验证码已到达上限
FOUNDATION_EXPORT GWNetErrCode const GET_PHONE_CODE_TOO_TIMES;                //获取手机验证码太频繁
FOUNDATION_EXPORT GWNetErrCode const SEND_VERIFY_CODE_FAILED;                 //发送手机验证码失败
FOUNDATION_EXPORT GWNetErrCode const SEND_VERIFY_EMAIL_FAILED;                //发送验证邮件失败
FOUNDATION_EXPORT GWNetErrCode const EMAIL_USED;                              //邮箱已被使用
FOUNDATION_EXPORT GWNetErrCode const PHONE_USED;                              //手机号已被使用
FOUNDATION_EXPORT GWNetErrCode const ACCOUNT_DISABLED;                        //帐号不可用_不可用的原因在error中返回帐号状态编号
FOUNDATION_EXPORT GWNetErrCode const SESSION_ID_ERROR;                        //会话ID不正确
FOUNDATION_EXPORT GWNetErrCode const ACCOUNT_NOT_EXIST;                       //用户不存在
FOUNDATION_EXPORT GWNetErrCode const PHONE_CODE_TIMEOUT;                      //手机验证码超时
FOUNDATION_EXPORT GWNetErrCode const PHONE_CODE_ERROR;                        //手机验证码不正确
FOUNDATION_EXPORT GWNetErrCode const LACK_COUNTRY_CODE;                       //请在手机号前输入国码
FOUNDATION_EXPORT GWNetErrCode const BIND_ACCOUNT_PASSWORD_ERROR;             //绑定的用户密码错误
FOUNDATION_EXPORT GWNetErrCode const BIND_ACCOUNT_NOT_EXIST;                  //绑定的用户不存在
FOUNDATION_EXPORT GWNetErrCode const ACCOUNT_PASSWORD_ERROR;                  //用户密码错误
FOUNDATION_EXPORT GWNetErrCode const THIRD_ACCOUNT_NOT_EXIST;                 //第三方账号不存在
FOUNDATION_EXPORT GWNetErrCode const THIRD_ACCOUNT_EXIST;                     //第三方账号已存在
FOUNDATION_EXPORT GWNetErrCode const SERVICE_NOT_SUPPORT;                     //服务器不支持此项服务
FOUNDATION_EXPORT GWNetErrCode const PASSWORD_FORMAT_ERROR;                   //密码数据格式不符合要求
FOUNDATION_EXPORT GWNetErrCode const EMAIL_FORMAT_ERROR;                      //邮箱地址数据格式不符合要求
FOUNDATION_EXPORT GWNetErrCode const PHONE_FORMAT_ERROR;                      //手机号数据格式不符合要求
FOUNDATION_EXPORT GWNetErrCode const LACK_PARAMETER_ERROR;                    //缺少输入参数
FOUNDATION_EXPORT GWNetErrCode const GET_EMAIL_CODE_TOO_OFTEN;                //获取邮件太频繁
FOUNDATION_EXPORT GWNetErrCode const GET_EMAIL_CODE_COUNT_LIMIT;              //邮件验证码超时
FOUNDATION_EXPORT GWNetErrCode const EMAIL_CODE_ERROR;                        //邮件验证码不正确
FOUNDATION_EXPORT GWNetErrCode const EMAIL_CODE_TIMEOUT;                      //邮件验证码超时

//同步设备列表相关
FOUNDATION_EXPORT GWNetErrCode const ADD_DEVICE_ALREADY_EXIST;                //设备已存在，不能重复添加
FOUNDATION_EXPORT GWNetErrCode const MODIFY_DEVICE_NOT_EXIST;                 //设备信息不存在
FOUNDATION_EXPORT GWNetErrCode const MODIFY_DEVICE_SERVER_NEWER;              //服务器上的记录比客户端的新，客户端需要重新加载
FOUNDATION_EXPORT GWNetErrCode const DEVICE_ID_REPEATED;                      //设备ID重复
FOUNDATION_EXPORT GWNetErrCode const LOAD_DEVICE_ALREADY_LAST;                //您的设备列表已经是最新的，不需要从服务器拉取了

//设备分享
FOUNDATION_EXPORT GWNetErrCode const SHARING_DEVICE_HAS_NO_OWNER;             //此设备还没有主人
FOUNDATION_EXPORT GWNetErrCode const SHARING_DEVICE_HAS_OWNER;                //此设备已有主人
FOUNDATION_EXPORT GWNetErrCode const SHARING_DEVICE_IS_BEING_BINDING;         //此设备已被锁定，正在绑定主人信息
FOUNDATION_EXPORT GWNetErrCode const SHARING_DEVICE_HAS_BEEN_LOCKED;            //此设备已被他人锁定及绑定主人信息
FOUNDATION_EXPORT GWNetErrCode const SHARING_INSUFFICIONT_USER_PERMISSIONS;   //必须是主人权限才能操作
FOUNDATION_EXPORT GWNetErrCode const SHARING_CREATE_INVATE_CODE_FAIL;         //创建邀请码失败
FOUNDATION_EXPORT GWNetErrCode const SHARING_INVATE_CODE_INVANIDATE;          //邀请码无效（不存在或超时）
FOUNDATION_EXPORT GWNetErrCode const SHARING_IS_OWNER;                        //已经是主人
FOUNDATION_EXPORT GWNetErrCode const SHARING_IS_VISITOR;                      //已经是访客
FOUNDATION_EXPORT GWNetErrCode const PARAMETER_ERROR;                         //参数错误
FOUNDATION_EXPORT GWNetErrCode const PARAMETER_SHARECANCEL;                   //分享已被主人取消

//设备数量限制
FOUNDATION_EXPORT GWNetErrCode const ADD_DEVICE_COUNT_LIMIT;                  //添加的当前设备数量已达到上限
FOUNDATION_EXPORT GWNetErrCode const ADD_PAST_DEVICE_COUNT_LIMIT;             //添加的历史设备数量已达到上限
FOUNDATION_EXPORT GWNetErrCode const DEVICE_BINDED_COUNT_LIMIT;               //当前设备被绑定的次数已达到上限

//权限管理
FOUNDATION_EXPORT GWNetErrCode const VISITOR_HAS_DELETE_DEVICE;               //配置权限时访客已删除该设备

////其他
//FOUNDATION_EXPORT GWNetErrCode const VERIFICATION_CODE_EMPTY;                 //验证码为空
//FOUNDATION_EXPORT GWNetErrCode const VERIFICATION_CODE_NOT_EXIST;             //验证码不存在
//FOUNDATION_EXPORT GWNetErrCode const INPUT_EMAIL_ADDRESS_PLEASE;              //为了你的帐号安全，请输入邮箱地址
//FOUNDATION_EXPORT GWNetErrCode const RESET_PASSWORD_LINK_INVALID;             //重置密码链接无效
//FOUNDATION_EXPORT GWNetErrCode const ASSIGN_ACCOUNT_FAILED;                   //系统分配账号失败
//FOUNDATION_EXPORT GWNetErrCode const GET_BINDING_USER_INFO_FAILED;            //获取绑定的用户信息失败
//FOUNDATION_EXPORT GWNetErrCode const SWAP_ANOTHER_SERVER_INTERFACE;           //请换用其他服务器接口
//FOUNDATION_EXPORT GWNetErrCode const ACCESS_RESTRICTED;                       //访问受限制
//FOUNDATION_EXPORT GWNetErrCode const APP_VERSION_ERROR;                       //APP客户号(内置主版本号)错误
//FOUNDATION_EXPORT GWNetErrCode const APP_INFO_NOT_EXIST;                      //APP信息不存在
//FOUNDATION_EXPORT GWNetErrCode const APP_HAS_BEEN_FROZEN;                     //此APP已被冻结
//FOUNDATION_EXPORT GWNetErrCode const APP_INFO_ERROR;                          //APP信息(AppID、AppToken、包名等)不正确
//FOUNDATION_EXPORT GWNetErrCode const SYS_CFG_ERROR;                           //系统配置错误
//FOUNDATION_EXPORT GWNetErrCode const SWAP_ANOTHER_SERVER_INTERFACE_2;         //请换用其他服务器接口
//FOUNDATION_EXPORT GWNetErrCode const ILLEGAL_CHARACTERS_FOUND;                //发现非法字符
//FOUNDATION_EXPORT GWNetErrCode const PARAMETER_OUT_OF_RANGE;                  //参数超出范围
//FOUNDATION_EXPORT GWNetErrCode const USER_ID_NOT_PREFIX_0;                    //用户ID必须以0开头
//FOUNDATION_EXPORT GWNetErrCode const DATA_FORMAT_ERROR;                       //输入数据格式错误
//FOUNDATION_EXPORT GWNetErrCode const FILE_OPERATION_FAILED;                   //文件操作失败
//FOUNDATION_EXPORT GWNetErrCode const FILE_NOT_EXIST;                          //文件不存在
//FOUNDATION_EXPORT GWNetErrCode const FILE_OPEN_FAILED;                        //文件打开失败
//FOUNDATION_EXPORT GWNetErrCode const DB_OPERATION_ABNORMAL;                   //数据库操作异常
//FOUNDATION_EXPORT GWNetErrCode const DB_RECORDSET_EMPTY;                      //数据库记录集为空
//FOUNDATION_EXPORT GWNetErrCode const DB_OPERATION_FAILED;                     //数据库操作失败
//FOUNDATION_EXPORT GWNetErrCode const DB_CONNECTION_FAILED;                    //数据库连接失败


