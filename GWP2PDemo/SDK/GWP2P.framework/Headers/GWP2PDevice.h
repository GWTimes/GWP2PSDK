//
/** @file GWP2PDevice.h @brief 设备模型和相关枚举 */
//  P2PSDK
//
//  Created by zengyuying on 17/3/31.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import <Foundation/Foundation.h>

/**
 设备类型,设备的一些功能要根据设备类型来判断
 
 目前设备返回的类型不准确,做功能判断时都用设备子类型 GWP2PDeviceIPCSubtype
 */
typedef NS_ENUM(NSUInteger, GWP2PDeviceType) {
    GWP2PDeviceTypeUnknown = 0,
    GWP2PDeviceTypeNPC = 2,
    GWP2PDeviceTypeDoorbell = 5,
    GWP2PDeviceTypeIPC = 7,
    GWP2PDeviceTypeNVR = 11,
};


/**
 IPC设备(DeviceType=7)的设备子类型,目前只有IPC有子类型
 */
typedef NS_ENUM(NSUInteger, GWP2PDeviceIPCSubtype) {
    GWP2PDeviceIPCSubtypeNormal = 0,        //摇头机,全功能
    GWP2PDeviceIPCSubtypeSimple,            //卡片机, 不带马达
    GWP2PDeviceIPCSubtype38X38,             //38板，不带马达，不带人体红外，不带回音消除
    GWP2PDeviceIPCSubtypeDoorbell,          //门铃，不带马达，带语音优化
    GWP2PDeviceIPCSubtypeCostdown,          //costdown版的摇头机，不带人体红外，不带外部无线传感器. 不带回音消除
    GWP2PDeviceIPCSubtype38Module,

    GWP2PDeviceIPCSubtypeNvrPtz = 6,        //预留
    GWP2PDeviceIPCSubtypeNvrNoPtz,          //预留
    GWP2PDeviceIPCSubtypeSmarthome868,      //支持 868 + 情景模式
    GWP2PDeviceIPCSubtypeRsv4,              //预留 9
    
    GWP2PDeviceIPCSubtype130wNormal,        //130w,摇头机,全功能
    GWP2PDeviceIPCSubtype130wSimple = 11,   //130w,卡片机, 不带马达
    GWP2PDeviceIPCSubtype130w38X38,         //130w,38板，不带马达，不带人体红外，不带回音消除
    GWP2PDeviceIPCSubtype130wDoorbell,      //130w,门铃，不带马达，带语音优化
    GWP2PDeviceIPCSubtype130wCostdown,      //130w,costdown版的摇头机，不带人体红外，不带外部无线传感器. 不带回音消除
    GWP2PDeviceIPCSubtype130w38Module,
    
    GWP2PDeviceIPCSubtype130wNvrPtz = 16,   //预留
    GWP2PDeviceIPCSubtype130wNvrNoPtz,      //预留
    GWP2PDeviceIPCSubtype130WSmarthome868,  //支持 868 + 情景模式
    GWP2PDeviceIPCSubtype130wRsv4,          //预留 19
    
    GWP2PDeviceIPCSubtype200wNormal,        //200w,摇头机,全功能
    GWP2PDeviceIPCSubtype200wSimple = 21,   //200w,卡片机, 不带马达
    GWP2PDeviceIPCSubtype200w38X38,         //200w,38板，不带马达，不带人体红外，不带回音消除
    GWP2PDeviceIPCSubtype200wDoorbell,      //200w,门铃，不带马达，带语音优化
    GWP2PDeviceIPCSubtype200wCostdown,      //200w,costdown版的摇头机，不带人体红外，不带外部无线传感器. 不带回音消除
    GWP2PDeviceIPCSubtype200w38Module,
    
    GWP2PDeviceIPCSubtype200wNvrPtz = 26,   //预留
    GWP2PDeviceIPCSubtype200wNvrNoPtz,      //预留
    GWP2PDeviceIPCSubtype200WSmarthome868,  //支持 868 + 情景模式
    GWP2PDeviceIPCSubtype200wRsv4,          //预留 29
    
    GWP2PDeviceIPCSubtype868,               //只支持 868
    GWP2PDeviceIPCSubtypeSmarthome = 31,    //支持 868 + 情景模式
    GWP2PDeviceIPCSubtypeSmarthomeShare,    //支持 868 + 情景模式 + 分享, 这种设备很少
    GWP2PDeviceIPCSubtypeSC1135Fisheye360D, //360全景
    GWP2PDeviceIPCSubtypeSC1135Fisheye180D, //180全景
    GWP2PDeviceIPCSubtypeSC3035Fisheye360D, //360全景
    GWP2PDeviceIPCSubtypeSC3035Fisheye180D = 36, //180全景
    
};


/**
 鱼眼设备分类,渲染使用,不要修改
 */
typedef NS_ENUM(NSUInteger, GWP2PFisheyeType) {
    GWP2PFisheyeType360 = 0,    //360鱼眼
    GWP2PFisheyeType180 = 1,    //180鱼眼
    GWP2PFisheyeTypeUnkown = 999,
};


/**
 360鱼眼设备视频显示的形状
 */
typedef NS_ENUM(NSUInteger, GWP2PFisheyeShapeType) {
    GWP2PFisheyeShapeTypeCircle = 0,        //圆形      360鱼眼使用
    GWP2PFisheyeShapeType180HalfSphere,     //180°半球  180鱼眼使用
    GWP2PFisheyeShapeTypeCylider,           //圆柱      360鱼眼使用
    GWP2PFisheyeShapeTypeBowle,             //碗状      360鱼眼使用
    GWP2PFisheyeShapeTypeFourSplit          //四分屏     360鱼眼使用
};


/**
 设备视频比例
 */
typedef NS_ENUM(NSUInteger, GWP2PDeviceVideoRatio) {
    GWP2PDeviceVideoRatio16X9 = 0, //大部分设备为默认的16:9
    GWP2PDeviceVideoRatio4X3,      //130w的设备4:3
    GWP2PDeviceVideoRatio1X1,      //360全景1:1
};


/**
 @brief 设备模型,提供一些基础的可能用到的设备属性和设备判断方法,开发时要用到的其它设备数据此模型没有时,可在此模型的基础上新建子类
 */
@interface GWP2PDevice : NSObject

/** 设备ID */
@property (nonatomic, copy) NSString *deviceID;

/** 设备昵称 */
@property (nonatomic, copy) NSString *deviceName;

/** 设备密码 */
@property (nonatomic, copy) NSString *devicePassword;

/** 设备类型 */
@property (nonatomic, assign) GWP2PDeviceType deviceType;

/** 设备子类型 */
@property (nonatomic, assign) GWP2PDeviceIPCSubtype deviceSubtype;

/**
 是否鱼眼设备
 */
+ (BOOL)isFisheyeDevice:(GWP2PDeviceIPCSubtype)deviceSubtype;


/**
 获取鱼眼类型 180or360
 
 @param deviceSubtype 设备子类型
 @return 鱼眼类型枚举值
 */
+ (GWP2PFisheyeType)getFisheyeTypeWithSubtype:(GWP2PDeviceIPCSubtype)deviceSubtype;

/**
 根据IPC子类型获取视频比例
 
 @param deviceSubtype 设备子类型
 @return 视频比例枚举值
 */
+ (GWP2PDeviceVideoRatio)getVideoRatioWithSubtype:(GWP2PDeviceIPCSubtype)deviceSubtype;


@end
