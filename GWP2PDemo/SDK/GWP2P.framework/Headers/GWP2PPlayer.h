//
/** @file GWP2PPlayer.h @brief 播放器基类与其协议 */
//  P2PSDK
//
//  Created by zengyuying on 17/3/8.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "GWP2PCallDefine.h"

@class GWP2PPlayer;


/**
 正在呼叫设备
 
 @param parameters 目前只有一个参数. kP2PCallingIsSameDomainKey:设备与手机是否在同个局域网
 */
typedef void (^P2PCallingBlock)(NSDictionary *parameters);


/**
 设备接受了呼叫请求,回调相关参数
 
 @param parameters kP2PCallAcceptIsVideo960PKey:视频是否960P
                   kP2PCallAcceptIsVideoWidescreenKey:是否是否宽屏(16:9)
 */
typedef void (^P2PAcceptBlock)(NSDictionary *parameters);


/**
 设备拒绝了呼叫,回调错误详情

 @param error     错误枚举,详见枚举中的注释
 @param errorCode 错误码,连接超时时会返回这个错误,详细说明连接超时的原因,详见错误枚举下方的说明
 */
typedef void (^P2PRejectBlock)(GWP2PCallError error, NSString *errorCode);


/**
 连接上设备并准备就绪,开始显示画面
 */
typedef void (^P2PReadyBlock)();


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
- (void)p2pPlayer:(GWP2PPlayer *)player recieveGestureRecognizer:(UIGestureRecognizer *)gesture;

@end



/**
 @brief 播放器基类
 */
@interface GWP2PPlayer : NSObject

/** 播放View */
@property (nonatomic, readonly) UIView *view;

/** scrollView是view的子view (usePano=YES时无效)*/
@property (nonatomic, weak, readonly) UIScrollView *scrollView;

/** 是否正在播放 */
@property (nonatomic, assign, readonly) BOOL isPlaying;

/** 静音 */
@property (nonatomic, assign, getter=isMute) BOOL mute;

/** 手势开关 默认开启 (usePano=YES时无效)*/
@property (nonatomic, assign) BOOL enableGesture;

/** 代理 */
@property (nonatomic, weak) id <GWP2PPlayerProtocol> delegate;

/** 是否使用新全景模式(半球,圆柱,画卷,四分,混合,广角)播放 */
@property (nonatomic, assign, readonly) BOOL usePano;

/** 当前全景视频pts,转化成时间戳(秒)=pts/(1000*1000) */
@property (nonatomic, assign, readonly) uint64_t panoPTS;

/**
 构造方法

 @param usePano 是否使用新全景进行播放。目前所有情况都使用新全景库播放，此接口现在等价于默认的init方法。
 @return 实例
 */
- (instancetype)initWithUsingPano:(BOOL)usePano;


/**
 停止监控/视频/回放
 */
- (void)p2pStop;


/**
 截图
 @param completionBlock 回调
 */
- (void)p2pScreenshot:(ScreenshotCompletionBlock)completionBlock;

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
 设置全景模式
 */
@property (nonatomic, assign) PanoMode showMode;


/**
 获取全景视图控制器,用于将PanoController添加到当前UIViewController
 */
@property (nonatomic, strong, readonly) UIViewController *panoViewController;

/**
 设置切边参数

 @param x 切边中心点x
 @param y 切边中心点y
 @param ratio 边缘切边比例
 */
- (void)setCutParam:(float)x y:(float)y ratio:(float)ratio;


@end