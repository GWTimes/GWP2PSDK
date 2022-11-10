//
/** @file GWP2PPlayer.h @brief 播放器基类与其协议 */
//  P2PSDK
//
//  Created by zengyuying on 17/3/8.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "GWP2PPlayerDefine.h"

@class GWP2PPlayer;


/**
 正在呼叫设备
 
 @param parameters 目前只有一个参数. kP2PCallingIsSameDomainKey:设备与手机是否在同个局域网
 */
typedef void (^P2PCallingBlock)(NSDictionary *parameters);


/**
 设备接受了呼叫请求,回调相关参数
 
 @param parameters kP2PCallingIsSameDomainKey; //与对方是否在同个局域网
                   kP2PCallAcceptIsVideo960PKey; //对方视频是否960P
                   kP2PCallAcceptIsVideoWidescreenKey; //对方视频是否宽屏(16:9)
                   kP2PCallAcceptVideoScaleKey; //视频画面边缘切边比例，NSNumber(float)，范围0~1
                   kP2PCallAcceptVideoCenterKey; //视频画面中心点, NSValue(CGPoint)，范围(0,0)~(1,1)
 */
typedef void (^P2PAcceptBlock)(NSDictionary *parameters);


/**
 设备拒绝了呼叫,回调错误详情

 @param error     错误枚举,详见枚举中的注释
 @param errorCode 错误码,连接超时时会返回这个错误,详细说明连接超时的原因,详见错误枚举下方的说明
 */
typedef void (^P2PRejectBlock)(GWP2PCallError error, NSString *errorCode);


/**
 连接上设备并准备就绪
 */
typedef void (^P2PReadyBlock)(void);

/**
 开始显示画面
 */
typedef void (^P2PPlayingBlock)(void);

/**
 截图完成回调

 @param screenshot UIImage格式截图
 @param timeInterval 截图时间戳,注意仅对鱼眼设备有效,转换成时间格式使用时区[NSTimeZone timeZoneForSecondsFromGMT:0]
 */
typedef void (^ScreenshotCompletionBlock)(UIImage *screenshot, NSTimeInterval timeInterval);

/**
 @brief 播放器基类的协议
 */
@protocol GWP2PPlayerProtocol <NSObject>


/**
 player内部对view添加了手势,每次手势触发时回调
 普通设备:swipe(上下左右)
 鱼眼设备:tap(单击\双击),pan,pinch

 @param gesture 手势
 */
- (BOOL)p2pPlayer:(GWP2PPlayer *)player shouldHandlerSwipeGesture:(UIGestureRecognizer *)gesture;


/**
 更新时间戳和视频尺寸
 
 @param player 播放器对象
 @param pts 显示时间戳(Presentation Time Stamp)
 @param size 视频尺寸
 
 */
- (void)p2pPlayer:(GWP2PPlayer *)player didUpdatePTS:(NSTimeInterval)pts size:(CGSize)size;

@end



/**
 @brief 播放器基类
 */
@interface GWP2PPlayer : NSObject

/** 播放器ViewController */
@property (nonatomic, readonly) UIViewController *viewController;

/** 是否正在播放, 从call开始就为YES，播放中断置为NO */
@property (nonatomic, assign, readonly) BOOL isPlaying;

/** 设备Id */
@property (nonatomic, copy) NSString *deviceId;

/** 音视频传输的通道 */
@property (nonatomic, assign) int channelID;

/** 麦克风 */
@property (nonatomic, assign) BOOL micEnable;

/** 静音, 当`silent=YES`时`mute=YES` */
@property (nonatomic, assign, getter=isMute) BOOL mute;

/** 手势开关 默认开启 (usePano=YES时无效)*/
@property (nonatomic, assign) BOOL enableGesture;

/** 代理 */
@property (nonatomic, weak) id <GWP2PPlayerProtocol> delegate;

/** 是否使用新全景模式(半球,圆柱,画卷,四分,混合,广角)播放 */
@property (nonatomic, assign, readonly) BOOL usePano;

/** 当前全景视频pts,转化成时间戳(秒)=pts/(1000*1000) */
@property (nonatomic, assign, readonly) uint64_t panoPTS;
/** 刷新*/
@property (nonatomic, assign) BOOL panoPause;
/** 清晰度 */
@property (nonatomic, assign) GWP2PPTZDefinition definition;
 /**
 构造方法

 @param usePano 是否使用新全景进行播放。目前所有情况都使用新全景库播放，此接口现在等价于默认的init方法。
 @return 实例
 */
- (instancetype)initWithUsingPano:(BOOL)usePano;

/**
 停止监控/视频/回放
 */
- (BOOL)getAudioStatus;
- (void)startAudioPlay;
/**
 停止监控/视频/回放
 */
- (void)p2pStop;
/**
 主动停止监控/视频/回放
 */
- (void)p2pSelfStop;


/**
 停止监控/视频/回放
 */
- (void)p2pStop:(int)channelId;
/**
 截图
 @param completionBlock 回调
 */
- (void)p2pScreenshot:(ScreenshotCompletionBlock)completionBlock;

/**
 开始录制视频，当播放器销毁、视频监控中断、切换分辨率时，都会自动停止录制并保存视频
 
 @param savePath 视频保存路径
 @param eventHandler 录制开始、异常等事件回调
 @param saveAlbum 是否将录制的视频保存到系统相册，将会占用应用沙盒和系统相册两份空间
 */
- (void)startRecordWithSavePath:(NSString *)savePath saveToPhotosAlbum:(BOOL)saveAlbum eventHandler:(MP4RecordEventHandler)eventHandler;

/**
 停止录制视频并保存视频
 */
- (void)stopRecord;

/**
 设置全景模式
 */
@property (nonatomic, assign)  PanoMode showMode;


/**
 设置全景切边参数，主要是中心点偏移、边缘剪切

 @param x 切边中心点x,范围0~1
 @param y 切边中心点y,范围0~1
 @param ratio 边缘切边比例,范围0~1
 */
- (void)setCutParam:(float)x y:(float)y ratio:(float)ratio;
/**
 设置开启关闭自动巡航
 */
- (void)setWideAngleAuto:(BOOL)isAuto ;
/*
 是否支持人形框，默认支持
 */
- (void)setShowHumanTack:(BOOL)isEnable;
/*
设置人形框的缩放因数，l默认为1
*/
- (void)setShowHumanTackZoom:(float)zoom;
@end
