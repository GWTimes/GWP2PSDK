//
/** @file GWMP4Recorder.h @brief 通用的音视频录制到手机功能,基类,录制监控视频用其子类 */
//  GWP2P
//
//  Created by USER on 2017/11/7.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, AudioType) {
    AudioTypePCM,
    AudioTypeAMR,
};

typedef NS_ENUM(NSUInteger, MP4RecordEvent) {
    MP4RecordEventStart,                /**< 初始化成功，开始录像 */
    MP4RecordEventStop,                 /**< 停止录像 */
    MP4RecordEventEncoderInitFailed,    /**< 初始化失败 */
    MP4RecordEventRatioChanged,         /**< 切换了视频分辨率，停止录像 */
};

typedef void(^MP4RecordEventHandler)(MP4RecordEvent stopEvent);

/**
 @brief 实现了通用的录制MP4到手机功能,作为基类,要录制P2P获取的音视频要用其子类GWP2PMP4Recorder
 */
@interface GWMP4Recorder : NSObject

@property (nonatomic, assign, readonly) NSUInteger videoWidth;    /**< 当前视频宽度 */
@property (nonatomic, assign, readonly) NSUInteger videoHeight;   /**< 当前视频高度 */
@property (nonatomic, assign, readonly) BOOL isRecording;   /**< 是否正在录制 */
@property (nonatomic, copy, readonly) NSString *savePath;   /**< 视频保存路径 */


/**
 开始录制视频
 @param savePath 视频保存路径

 */
- (void)startRecordWithSavePath:(NSString *)savePath;

/**
 开始录制视频
 
 @param savePath 视频保存路径
 @param eventHandler 录制开始、异常等事件回调
 */
- (void)startRecordWithSavePath:(NSString *)savePath eventHandler:(MP4RecordEventHandler)eventHandler;


/**
 停止录制视频
 */
- (void)stopRecord;


/**
 停止录制视频
 这个方法可以选择是否同时将视频保存到系统相册，注意这里是复制，将占用双倍存储空间。
 @param saveAlbum 是否同时将视频保存到系统相册
 */
- (void)stopRecordAndSaveToPhotosAlbum:(BOOL)saveAlbum;



/**
 设置视频宽高，设置了宽高才会开始录制

 @param dwVideoWidth 视频宽度
 @param dwVideoHeight 视频高度
 */
- (void)setVideoWidth:(NSUInteger)dwVideoWidth VideoHeight:(NSUInteger)dwVideoHeight;


/**
 接收需要录制的音视频数据

 @param audioType 音频格式
 @param pAudioData 音频数据
 @param dwAudioLen 音频长度
 @param dwFrames 帧率
 @param u64APTS 音频pts
 @param pVideoData 视频数据
 @param dwVideoLen 视频长度
 @param u64VPTS 视频pts
 */
- (void)receiveAVDataWithAudioType:(AudioType)audioType
                         audioData:(uint8_t*)pAudioData
                       audioLength:(NSUInteger)dwAudioLen
                            frames:(NSUInteger)dwFrames
                          audioPTS:(uint64_t)u64APTS
                         videoData:(uint8_t*)pVideoData
                       videoLength:(NSUInteger)dwVideoLen
                          videoPTS:(uint64_t)u64VPTS;


@end
