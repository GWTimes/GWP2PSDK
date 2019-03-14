//
//  GWP2PPlayerDefine.h
//  GWP2P
//
//  Created by WangShunXing on 2019/3/5.
//  Copyright © 2019 apple. All rights reserved.
//

#ifndef GWP2PPlayerDefine_h
#define GWP2PPlayerDefine_h

/**
 * 呼叫设备回调的参数字典的key常量声明
 */
extern NSString * const kP2PCallingIsSameDomainKey; //与对方是否在同个局域网
extern NSString * const kP2PCallAcceptIsVideo960PKey; //对方视频是否960P
extern NSString * const kP2PCallAcceptIsVideoWidescreenKey; //对方视频是否宽屏(16:9)
extern NSString * const kP2PCallAcceptVideoScaleKey; //视频画面边缘切边比例，NSNumber(float)，范围0~1
extern NSString * const kP2PCallAcceptVideoCenterKey; //视频画面中心点, NSValue(CGPoint)，范围(0,0)~(1,1)

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
//0x2010200A        UDP转发服务器握手失败
//0x20102009        连接tcp转发服务器成功，等待配对失败
//0x20102008        连接tcp转发服务器失败
//0x20102007        申请多路径传输，握手超时
//0x20102006        申请多路径传输超时
//0x20102005        局域网点对点连接失败
//0x20102004        发出呼叫，等待目标ID的地址信息超时
//0x20102003        传输数据中出现传输超时
//0x20102002        连接状态准备好，尝试传输数据超时

/**
 全景模式
 
 - PM_NONE: 黑屏,切换此模式无效
 - PM_HALF_SPHERE: 半球
 - PM_CYLINDER: 圆柱
 - PM_SCROLL: 画卷
 - PM_FOUR_SCREEN: 四画面
 - PM_MIX: 混合
 - PM_WIDE_ANGLE: 广角
 - PM_QUAD: 四边形,适用于普通监控
 */
typedef NS_ENUM(NSUInteger, PanoMode) {
    PM_NONE,
    PM_HALF_SPHERE,
    PM_CYLINDER,
    PM_SCROLL,
    PM_FOUR_SCREEN,
    PM_MIX,
    PM_WIDE_ANGLE,
    PM_QUAD
};

/**
 录制过程中的事件
 */
typedef NS_ENUM(NSUInteger, MP4RecordEvent) {
    MP4RecordEventStart,                /**< 等到视频流关键帧，开始录像 */
    MP4RecordEventStop,                 /**< 停止录像 */
    MP4RecordEventRatioChanged,         /**< 切换了视频分辨率，停止录像 */
};

/**
 定义录制过程中的事件回调代码块
 */
typedef void(^MP4RecordEventHandler)(MP4RecordEvent stopEvent);

/**
 控制镜头转向
 */
typedef NS_ENUM(NSUInteger, GWP2PPTZDirection) {
    GWP2PPTZDirectionLeft = 0,  //左
    GWP2PPTZDirectionRight,     //右
    GWP2PPTZDirectionUp,        //上
    GWP2PPTZDirectionDown,      //下
};


/**
 视频清晰度
 */
typedef NS_ENUM(NSUInteger, GWP2PPTZDefinition) {
    GWP2PPTZDefinitionLD = 0,   //流畅,NPC:320*240 IPC:320*180
    GWP2PPTZDefinitionSD,       //标清,NPC:640*480 IPC:640*360
    GWP2PPTZDefinitionHD,       //高清,NPC:None    IPC:1280*720
};


/**
 播放控制回调
 */
typedef NS_ENUM(NSUInteger, GWP2PPlaybackControl) {
    GWP2PPlaybackControlPlay,               //播放
    GWP2PPlaybackControlPause,              //暂停
    GWP2PPlaybackControlStop,               //停止
    GWP2PPlaybackControlFileEnd,            //文件播放完毕
    GWP2PPlaybackControlFastForward,        //快进
    GWP2PPlaybackControlFastForwardCancel,  //取消快进
    GWP2PPlaybackControlNextFile,           //切换文件播放
    GWP2PPlaybackControlSeekTime,           //指定时间播放
};

/**
 汇讯视通控制镜头
 */
typedef NS_ENUM(NSUInteger, GWP2PHXVisonDirection) {
    GWP2PHXVisonDirectionLeft = 0,  //左
    GWP2PHXVisonDirectionRight,     //右
    GWP2PHXVisonDirectionUp,        //上
    GWP2PHXVisonDirectionDown,      //下
    GWP2PHXVisonDirectionShort,     //缩小
    GWP2PHXVisonDirectionLong,      //放大
    GWP2PHXVisonDirectionStop,      //停止
};

/**
 汇讯视通3D手势
 */
typedef NS_ENUM(NSUInteger, GWP2PHXVison3DGestureZoomType)
{
    GWP2PHXVison3DGestureZoomTele = 0,  //3D放大
    GWP2PHXVison3DGestureZoomWide,      //3D缩小
    GWP2PHXVison3DGestureZoomLocate,    //3D定位移动
};

#endif /* GWP2PPlayerDefine_h */
