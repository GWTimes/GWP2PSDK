//
/** @file GWP2PVideoPlayer.h @brief 监控和视频通话的播放器 */
//  P2PSDK
//
//  Created by zengyuying on 17/4/7.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import "GWP2PPlayer.h"
#import "GWP2PPlayerDefine.h"
#import "GWP2PDevice.h"

@class GWP2PVideoPlayer;

/**
 NPC设备主动呼叫的通知
 参数有设备ID和是否在同个局域网
 userInfo:@{@"deviceId":deviceId,kP2PCallingIsSameDomainKey:@(BOOL)}
 */
extern NSString * const kGWP2PDeviceIsCallingNotification;

/**
 NPC设备主动拒绝的通知

 */
extern NSString * const kGWP2PDeviceIsRejectNotification;

/**
 @brief GWP2PVideoPlayerProtocol协议包含监控时的设备状态信息的回调,按需要选择性实现
 */
@protocol GWP2PVideoPlayerProtocol <GWP2PPlayerProtocol>

@optional

/**
 观看人数变化回调
 触发场景:
 1.呼叫设备后开始监控时
 2.观看人数变化时(其他监控者加入或者断开)
 3.高清-标清,高清-流畅,两种情况的分辨率互相切换时(标清-流畅切换不触发)
 
 @param currentNumber 当前观看人数
 */
- (void)p2pVideoPlayer:(GWP2PVideoPlayer *)player numberOfAudiencesChange:(NSUInteger)currentNumber;

/**
 监控网速发生改变，每秒回调一次

 @param player 播放器
 @param speed 网速
 */
- (void)p2pVideoPlayer:(GWP2PVideoPlayer *)player networkSpeedChanged:(NSInteger)speed;

/**
 远程录像(SD卡录像)状态发送改变

 @param parameters 参数 @"isRemoteRecording":@(BOOL),是否正在录像
                       @"hasSDCard":@(BOOL),是否有SD卡
                       @"isRecordFalse":@(BOOL),是否录制失败,可能SD卡损坏
 */
- (void)p2pVideoPlayer:(GWP2PVideoPlayer *)player remoteSDCardRecordStateChange:(NSDictionary *)parameters;

/**
 布防状态发生改变

 @param isDefenceOn 改变后的布防状态. YES:布防状态,NO:撤防状态
 */
- (void)p2pVideoPlayer:(GWP2PVideoPlayer *)player defenceStateChange:(BOOL)isDefenceOn;


@end


/**
 @brief 监控和视频通话的播放器,继承自GWP2PPlayer
 */
@interface GWP2PVideoPlayer : GWP2PPlayer

/** 代理 */
@property (nonatomic, weak) id <GWP2PVideoPlayerProtocol> delegate;

/** 手势操作水平翻转 */
@property (nonatomic, assign) BOOL isFlipHorizontal;

/** 手势操作垂直翻转 */
@property (nonatomic, assign) BOOL isFlipVertical;


/**
 呼叫一个设备,进行监控
 
 @param deviceId      设备ID
 @param password      设备密码
 @param definition    默认清晰度
 @param callingBlock  正在呼叫回调,详见block定义注释
 @param acceptBlock   接收呼叫回调,详见block定义注释
 @param rejectBlock   拒绝连接回调,详见block定义注释
 @param readyBlock    连接就绪回调,详见block定义注释
 @param playingBlock   开始显示回调,详见block定义注释
 */
- (void)p2pCallDeviceWithDeviceId:(NSString *)deviceId
                         password:(NSString *)password
                       definition:(GWP2PPTZDefinition)definition
                          calling:(P2PCallingBlock)callingBlock
                           accept:(P2PAcceptBlock)acceptBlock
                           reject:(P2PRejectBlock)rejectBlock
                            ready:(P2PReadyBlock)readyBlock
                          playing:(P2PPlayingBlock)playingBlock
                         allowLAN:(BOOL)allowLAN;

/**
 呼叫一个NPC设备,进行视频对讲,目前只有NPC一种设备存在对讲视频对讲功能,所以不需要设备类型等参数

 @param deviceId 设备ID
 @param password 设备密码
 @param callingBlock  正在呼叫回调,详见block定义注释
 @param acceptBlock   接收呼叫回调,详见block定义注释
 @param rejectBlock   拒绝连接回调,详见block定义注释
 @param readyBlock    连接就绪回调,详见block定义注释
 @param playingBlock   开始显示回调,详见block定义注释
 */
- (void)p2pCallNPCDeviceWithDeviceId:(NSString *)deviceId
                            password:(NSString *)password
                             calling:(P2PCallingBlock)callingBlock
                              accept:(P2PAcceptBlock)acceptBlock
                              reject:(P2PRejectBlock)rejectBlock
                               ready:(P2PReadyBlock)readyBlock
                             playing:(P2PPlayingBlock)playingBlock;


/**
 接受当前的设备呼叫请求

 @param acceptBlock 接收呼叫回调,详见block定义注释
 @param rejectBlock 拒绝连接回调,详见block定义注释
 @param readyBlock  连接就绪回调,详见block定义注释
 @param playingBlock   开始显示回调,详见block定义注释
 */
- (void)p2pAcceptCallingWithChannelid:(int)channelId
                             deviceid:(NSString*)deviceid
                               accept:(P2PAcceptBlock)acceptBlock
                            reject:(P2PRejectBlock)rejectBlock
                             ready:(P2PReadyBlock)readyBlock
                              playing:(P2PPlayingBlock)playingBlock;

/**
 控制摇头机镜头转向

 @param direction 转动方向枚举
 */
 - (void)p2pTurnDirection:(GWP2PPTZDirection)direction;

/**
 设置视频清晰度

 @param definition 清晰度枚举
 */
- (void)p2pSetDefinition:(GWP2PPTZDefinition)definition;

/**
 控制汇讯视通镜头转向
 
 @param  direction 镜头转动方向
 */
- (void)p2pHXVsionTurnDirection:(GWP2PHXVisionDirection)direction;

/**
 汇讯视通3D手势
 
 @param zoomType 3D手势类型
 @param point 手势坐标
 @param size  手势大小,当定位移动时，宽高必须传0
 */
- (void)p2pHXVsionOperate3DGesture:(GWP2PHXVision3DGestureZoomType)zoomType point:(CGPoint)point size:(CGSize)size;

/**
 开始摄像
 
 @param view 显示画面视图
 */
- (void)startCameraWithAddView:(UIView *)view;

/**
 停止摄像
 */
- (void)stopCamera;

/**
 切换摄像镜头
 */
- (void)switchCamera;


@end
