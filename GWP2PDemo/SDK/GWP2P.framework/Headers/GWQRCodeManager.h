//
//  GWQRCodeManager.h
//  Yoosee
//
//  Created by HuangZhen on 2018/5/28.
//  Copyright © 2018年 Gwelltimes. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

/**
 扫码结果回调

 @param scanResult 原始字符串
 @param deviceID 设备ID
 @param qrNetCfgAvailable 设备是否支持扫码配网
 */
typedef void(^GWQRCodeScanCallback)(NSString * _Nullable scanResult, NSString * _Nullable deviceID, BOOL qrNetCfgAvailable);

@interface GWQRCodeManager : NSObject

/**
 初始化二维码扫码
 需要手动调用startScan开启扫码
 @param preView 视频显示区域
 @param cropRect 识别区域，值为CGRectZero时全屏识别
 @param callback 识别完成回调
 @return GWQRCodeManager实例
 */
- (instancetype)initWithPreView:(UIView*)preView cropRect:(CGRect)cropRect callback:(GWQRCodeScanCallback)callback;

/**
 初始化并开启二维码扫码

 @param preView 视频显示区域
 @param cropRect 识别区域，值为CGRectZero时全屏识别
 @param callback 识别完成回调
 @return GWQRCodeManager实例
 */
+ (instancetype)startScanWithPreView:(UIView*)preView cropRect:(CGRect)cropRect callback:(GWQRCodeScanCallback)callback;


/**
 闪光灯模式
 */
@property (nonatomic, assign) AVCaptureTorchMode torchMode;


/**
 开始扫码
 */
- (void)startScan;


/**
 停止扫码
 */
- (void)stopScan;


/**
 生成二维码

 @param wifiName Wi-Fi名称
 @param wifiPwd Wi-Fi密码
 @param userID 有看头ID
 @param size 二维码尺寸

 @return 二维码图片, 失败时为nil
 */
+ (nullable UIImage *)createQRCodeWithWifiName:(NSString *)wifiName wifiPwd:(NSString *)wifiPwd userID:(NSString *)userID qrSize:(CGSize)size;

/**
 生成二维码
 
 @param wifiName Wi-Fi名称
 @param wifiPwd Wi-Fi密码
 @param userID 有看头ID
 @param languageCode 语言代码用来设备进行配网语音提示
 //英文    1   中文(简体/繁体)    2泰语    3越南语    4德语    5韩语    6 法语    7葡萄牙语(巴西)    8意大利    9俄语    10日语    11西班牙语    12波兰语    13土耳其语    14波斯语    15印尼语    16马来语    17捷克    18斯洛伐克语    19荷兰语    20
 @param size 二维码尺寸
 
 @return 二维码图片, 失败时为nil
 */
+ (nullable UIImage *)createQRCodeWithWifiName:(NSString *)wifiName wifiPwd:(NSString *)wifiPwd userID:(NSString *)userID languageCode:(NSString *)languageCode qrSize:(CGSize)size;
/**
 生成二维码

 @param qrString 要生成二维码的字符串
 @param size 二维码尺寸
 @return 二维码图片, 失败时为nil
 */
+ (nullable UIImage *)createQRCodeWithString:(NSString *)qrString qrSize:(CGSize)size;
/**
 识别二维码
 
 @param 二维码图片 image
 @return 二维码NSString, 二维码的字符串
 */
+(NSString*)getQRCodeStringWithImage:(UIImage*)image;

@end

NS_ASSUME_NONNULL_END
