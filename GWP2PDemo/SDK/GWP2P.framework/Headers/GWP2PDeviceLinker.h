//
/** @file GWP2PDeviceLinker.h @brief 设备配网的类和协议 */
//  GWP2PDeviceLinker
//
//  Created by apple on 17/5/2.
//  Copyright © 2017年 apple. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GWP2PLanDevice.h"

extern NSString * const DUPLICATE_DEVICE_ID_NOTIFICATION;

@class GWP2PDeviceLinker;

/**
 设备通过任何方式联网成功后，会通过这个Block进行回调设备信息。目前配网并不是100%可靠，主要是因为设备联网成功后是通过广播消息的形式在局域网发送消息通知APP端的，如果有多台设备在同一个局域网同时联网，会有干扰。
 
 1、设备是通过局域网广播的方式通知APP联网成功的，所以手机所在网络需要与设备配置网络处于同一个局域网，才能收到消息。
 2、由于iOS平台没有权限控制WiFi，通过设备的AP模式联网时，如果在配网成功后，手机没有自动连接到给设备配置的WiFi，是收不到配网成功消息的，此时建议在UI上添加一个按钮，让用户在听到设备“连接成功”的提示音后进行点击，点击后将设备添加到本地列表。
 3、设备联网成功后，会在20秒内发送多次消息。
 */
typedef void (^DeviceLinkInBlock)(NSDictionary *deviceDict);


/**
 AP配网时，设备在收到WiFi及密码信息后，在断开AP热点去联网前，会回调相关信息
 
 @param deviceId  设备ID
 @param isSupport 是否支持AP模式联网
 */
typedef void (^DeviceReceiveBlock)(NSString *deviceId, BOOL isSupport);


/**
 @brief 设备配网回调协议
 */
@protocol GWPP2PDeviceLinkerProtocol <NSObject>

/**
 局域网里面有设备联网成功后，都会回调此方法。

 @param deviceDict 设备信息
 */
- (void)p2pDeviceLinker:(GWP2PDeviceLinker *)linker deviceLinkSuccess:(NSDictionary *)deviceDict;

@end

/**
 @brief 设备配网的类
 */
@interface GWP2PDeviceLinker : NSObject

/** 协议 */
@property (nonatomic, weak) id <GWPP2PDeviceLinkerProtocol> delegate;

/** 局域网设备列表 */
@property (nonatomic, strong) NSMutableArray <GWP2PLanDevice *> *lanDevices;

/** 智能联机是否发送声波 默认YES */
@property (nonatomic, assign) BOOL smarkLinkSoundEnable;

/// UDP SOCKET 是否停止接受数据
@property (nonatomic, assign) BOOL udpSocketStopWorking;

/**
 单例初始化
 */
+ (instancetype)shareInstance;

/// 开始监听局域网设备 Socker
- (void)startScanLanDeviceSocket;
/// 停止监听局域网设备 Socker
- (void)stopScanLanDevicesSocket;

/**
强制刷新局域网设备,删除设备
 */
- (void)forceScanLanDevices;

/**
 刷新局域网设备
 */
- (void)refreshScanLanDevices;

/**
 智能联机，内部会同时发送声波、空中发包、SimpleConfig数据
 
 此接口停用，请调 [GWP2PDeviceLinker p2pSmartLinkDeviceWithWiFiSSID:password:useSimpleConfig:deviceLinkIn:]
 
 一定要将手机连接上设备要连接的wifi,才能收到DeviceLinkInBlock连接成功的回调
 
 @param ssid              设备需要连接的WiFi SSID
 @param password          设备需要连接的WiFi 密码
 @param deviceLinkInBlock 设备连接到网络的回调,会回调多次,调接口时需要处理一下
 */
- (void)p2pSmartLinkDeviceWithWiFiSSID:(NSString *)ssid
                              password:(NSString *)password
                          useSoundWave:(BOOL)useSoundWave
                          deviceLinkIn:(DeviceLinkInBlock)deviceLinkInBlock;



/**
 智能联机，内部会同时发送声波及用另一种方式发送数据（空中发包或SimpleConfig）
 
 调此接口后一定要调 [GWP2PDeviceLinker p2pStopSmartLink 方法停止发送声波，空中发包，及SimpleConfig数据
 
 一定要将手机连接上设备要连接的wifi,才能收到DeviceLinkInBlock连接成功的回调
 
 @param ssid              设备需要连接的WiFi SSID,手机一定要连到此wifi才能收到回调，目前设备只支持2.4Gwifi
 @param password          设备需要连接的WiFi 密码
 @param useSimpleConfig   是否用SimpleConfig方式进行配网，传YES采用SimpleConfig和声波发wifi数据，传NO采用声波和空中发包发wifi数据
 @param deviceLinkInBlock 设备连接到网络的回调,会回调多次,调接口时需要处理一下
 */
- (void)p2pSmartLinkDeviceWithWiFiSSID:(NSString *)ssid
                              password:(NSString *)password
                       useSimpleConfig:(BOOL)useSimpleConfig
                          deviceLinkIn:(DeviceLinkInBlock)deviceLinkInBlock;

/**
 停止智能联机，请在设备联网成功后手动调用停止
 */
- (void)p2pStopSmartLink;



/**
 AP配网。在连接到支持AP配网的设备的热点(GW_AP_XXXXXX)后,调用此方法给设备发送WiFi帐号及密码,以及要给设备初始化的管理密码
 
 @param ssid                wifi名称
 @param wifiPassword        wifi密码
 @param devicePassword      设备密码
 @param deviceReceiveBlock  设备收到WiFi信息的回调,准备断开AP热点去连接WiFi。
 @param deviceLinkInBlock   设备连接到网络的回调
 */
- (void)p2pAPLinkDeviceWithWiFiSSID:(NSString *)ssid
                       wifiPassword:(NSString *)wifiPassword
                     devicePassword:(NSString *)devicePassword
                      deviceReceive:(DeviceReceiveBlock)deviceReceiveBlock
                       deviceLinkIn:(DeviceLinkInBlock)deviceLinkInBlock;

/**
 停止AP配网。如果配网中途停止，调此方法停止发送数据，正常配网成功不需要调此方法
 */
- (void)p2pStopAPLink;
/**
 获取设备IP
 
 若设备与手机在同一局域网中,则返回设备局域网IP,用于手机与设备的局域网通信,否则返回 0
 
 @param deviceID 设备ID
 
 @return 设备IP地址
 */
+ (NSInteger)getDeviceIPByID:(NSString *)deviceID;
@end
