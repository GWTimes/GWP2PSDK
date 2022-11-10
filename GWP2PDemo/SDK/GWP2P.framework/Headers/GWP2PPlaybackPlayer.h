//
/** @file GWP2PPlaybackPlayer.h @brief 回放播放器 */
//  P2PSDK
//
//  Created by zengyuying on 17/3/31.
//  Copyright © 2017年 gwell. All rights reserved.
//
//

#import "GWP2PPlayer.h"
#import "GWP2PDevice.h"
#import "GWP2PClient+Record.h"

/**
 @brief 回放播放器,继承自GWP2PPlayer
 */
@interface GWP2PPlaybackPlayer : GWP2PPlayer

/** 当前播放的文件 */
@property (nonatomic, readonly) GWPlaybackFileModel *playbackFile;
/** 当前播放的文件的时间 */
@property (nonatomic, assign) uint64_t startTime;

/** 当前播放的时间,单位:微秒μs,可监听此时间变化更新播放进度条*/
@property (nonatomic, readonly) uint64_t currentTime;

/** 当前文件总时长,单位:微秒μs,开始播放时设备端会返回这个时间,正常情况下与playbackFile中的time是一样的,建议使用这个totalTime*/
@property (nonatomic, readonly) uint64_t totalTime;

/** 回放的状态 */
@property (nonatomic, readonly) GWP2PPlaybackState playbackState;

/** 播放倍速 */
@property (nonatomic, assign) GWPlaybackSpeed speed;

/**
 播放设备远程录像文件,原理和监控设备是一样的,需要先呼叫连接设备
 
 @param deviceId      设备ID
 @param password      设备密码
 @param playbackFile  回放文件对象,由GWP2PClient+Record中的获取回放文件列表方法获取
 @param callingBlock  正在呼叫回调,详见block定义注释
 @param acceptBlock   接收呼叫回调,详见block定义注释
 @param rejectBlock   拒绝连接回调,详见block定义注释
 @param readyBlock    连接就绪回调,详见block定义注释
 @param playingBlock   开始显示回调,详见block定义注释
 */
- (void)p2pCallPlaybackFileWithDeviceId:(NSString *)deviceId
                               password:(NSString *)password
                           playbackFile:(GWPlaybackFileModel *)playbackFile
                                calling:(P2PCallingBlock)callingBlock
                                 accept:(P2PAcceptBlock)acceptBlock
                                 reject:(P2PRejectBlock)rejectBlock
                                  ready:(P2PReadyBlock)readyBlock
                                playing:(P2PPlayingBlock)playingBlock;
/**
 播放设备远程录像文件,原理和监控设备是一样的,需要呼叫连接设备
 
 @param deviceId      设备ID
 @param password      设备密码
 @param playbackFile  回放文件对象,由GWP2PClient+Record中的获取回放文件列表方法获取
 @param callingBlock  正在呼叫回调,详见block定义注释
 @param acceptBlock   接收呼叫回调,详见block定义注释
 @param rejectBlock   拒绝连接回调,详见block定义注释
 @param readyBlock    连接就绪回调,详见block定义注释
 @param playingBlock   开始显示回调,详见block定义注释
 */
- (void)p2pCallPlaybackFileWithDeviceId:(NSString *)deviceId
                               password:(NSString *)password
                                filepts:(unsigned int)pts
                           playbackFile:(GWPlaybackFileModel *)playbackFile
                                calling:(P2PCallingBlock)callingBlock
                                 accept:(P2PAcceptBlock)acceptBlock
                                 reject:(P2PRejectBlock)rejectBlock
                                  ready:(P2PReadyBlock)readyBlock
                                playing:(P2PPlayingBlock)playingBlock;
/**
 播放远程录像文件,如果已经连接上设备,调用此方法即可快速切换回放文件

 @param playbackFile 回放文件对象
 */
- (void)p2pPlayPlaybackFile:(GWPlaybackFileModel *)playbackFile;
/**
 播放远程录像文件,如果已经连接上设备,调用此方法即可快速切换回放文件
 
 @param playbackFile 回放文件对象 ,指定播放时间
 */
- (void)p2pPlayPlaybackFile:(GWPlaybackFileModel *)playbackFile andPts:(NSUInteger)pts ;

/**
 暂停或者继续播放
 */
- (void)p2pPauseOrResume;

/**
 暂停
 */
- (void)p2pPause;
/**
 播放
 */
- (void)p2pPlay;
/**
 快进或者取消快进
 */
- (void)p2pFastForwardOrCancel;


/**
 指定播放时间

 @param seekTime 播放时间(单位是微秒,如要跳到第45秒,传入45*1000*1000)
 */
- (void)p2pSeekToTime:(uint64_t)seekTime;




@end
