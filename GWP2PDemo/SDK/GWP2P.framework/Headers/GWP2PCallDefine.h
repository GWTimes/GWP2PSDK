//
/** @file GWP2PCallDefine.h @brief 设备呼叫相关的枚举 */
//  P2PSDK
//
//  Created by zengyuying on 17/3/21.
//  Copyright © 2017年 gwell. All rights reserved.
//

#ifndef GWP2PCallDefine_h
#define GWP2PCallDefine_h

/**
 * 呼叫设备回调的参数字典的key常量声明
 */
extern NSString * const kP2PCallingIsSameDomainKey; //与对方是否在同个局域网
extern NSString * const kP2PCallAcceptIsVideo960PKey; //对方视频是否960P
extern NSString * const kP2PCallAcceptIsVideoWidescreenKey; //对方视频是否宽屏(16:9)

typedef NS_ENUM(NSUInteger, GWP2PCallWay) {//呼叫方式
    GWP2PCallWayInitiative = 0, //主动呼叫设备
    GWP2PCallWayPassive,        //被动呼叫,指NPC设备呼叫APP(通过用户ID)
};

typedef NS_ENUM(NSUInteger, GWP2PCallType) {//呼叫类型(主动呼叫设备时)
    GWP2PCallTypeMonitor = 0,   //监控
    GWP2PCallTypeVideo,         //视频通话(NPC设备)
    GWP2PCallTypePlayback,      //回放
};

typedef NS_ENUM(NSUInteger, GWP2PCallStatus) { //呼叫状态
    GWP2PCallStatusNone = 0,    //默认
    GWP2PCallStatusCalling,     //呼叫中
    GWP2PCallStatusRejected,    //呼叫被对方拒绝
    GWP2PCallStatusAccepted,    //呼叫被对方接受
    GWP2PCallStatusReady,       //连接准备就绪
};

typedef NS_ENUM(NSUInteger, GWP2PPlaybackState) { //回放状态
    GWP2PPlaybackStateNone,        //默认
    GWP2PPlaybackStatePause,       //暂停
    GWP2PPlaybackStatePlaying,     //正常播放中
    GWP2PPlaybackStateFastForward, //快进中
    GWP2PPlaybackStateStop         //停止
};


/**
 呼叫失败的错误枚举
 */
typedef NS_ENUM(NSUInteger, GWP2PCallError) {
    GWP2PCallErrorNone = 0,        //0无原因
    GWP2PCallErrorDesidNotEnable,  //1对方的ID 被禁用
    GWP2PCallErrorDesidOverDate,   //2对方的ID 过期了
    GWP2PCallErrorDesidNotAcitve,  //3对方的ID 尚未激活
    GWP2PCallErrorDesidOffline,    //4对方离线
    GWP2PCallErrorDesidBusy,       //5对方忙线中
    GWP2PCallErrorDesidPowerDown,  //6对方已关机
    GWP2PCallErrorNoHelper,        //7没有找到协助人
    GWP2PCallErrorHangUp,          //8对方已经挂断
    GWP2PCallErrorTimeout,         //9连接超时
    GWP2PCallErrorInterError,      //10内部错误
    GWP2PCallErrorRingTimeout,     //11无人接听
    GWP2PCallErrorPwdWrong,        //12密码错误(在远程监控时用到密码，在视频通话是不需要)
    GWP2PCallErrorConnFail,
    GWP2PCallErrorNotSupport,
};

/**
 CallErrorCode 呼叫失败(连接超时)还会返回具体错误的16进制errorCode
 由服务器定义,更多可在http://gwellserver2:8008/进行查询
 */
//0x2010200A		UDP转发服务器握手失败
//0x20102009		连接tcp转发服务器成功，等待配对失败
//0x20102008		连接tcp转发服务器失败
//0x20102007		申请多路径传输，握手超时
//0x20102006		申请多路径传输超时
//0x20102005		局域网点对点连接失败
//0x20102004		发出呼叫，等待目标ID的地址信息超时
//0x20102003		传输数据中出现传输超时
//0x20102002		连接状态准备好，尝试传输数据超时



#endif /* GWP2PCallDefine_h */
