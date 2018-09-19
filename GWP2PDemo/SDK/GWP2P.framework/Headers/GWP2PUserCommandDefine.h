//
/** @file GWP2PUserCommandDefine.h @brief 控制镜头转向,视频清晰度,播放控制等相关的枚举 */
//  P2PSDK
//
//  Created by zengyuying on 17/4/7.
//  Copyright © 2017年 gwell. All rights reserved.
//

#ifndef GWP2PUserCommandDefine_h
#define GWP2PUserCommandDefine_h


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


#endif /* GWP2PUserCommandDefine_h */
