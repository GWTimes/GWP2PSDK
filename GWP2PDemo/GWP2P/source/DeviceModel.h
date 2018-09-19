//
//  DeviceModel.h
//  GWP2P
//
//  Created by zengyuying on 17/5/24.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import <GWP2P/GWP2P.h>


/**
 设备类型
 */
typedef NS_ENUM(NSUInteger, GWDeviceSharingType) {
    GWDeviceSharingTypeNoShared, /**< 不是分享设备 */
    GWDeviceSharingTypeMastor, /**< 主人 */
    GWDeviceSharingTypeVisitor, /**< 访客 */
};


@interface DeviceModel : GWP2PDevice <NSCoding>

@property (assign) GWDeviceSharingType deviceSharingType; /**< 设备的分享类型 */

+ (NSArray<DeviceModel *> *)deviceModels;

/**
 这里是为了简便,客户最好用数据库处理

 @param deviceModel 模型
 */
+ (void)saveDeviceModel:(DeviceModel *)deviceModel;
+ (void)removeDeviceModel:(DeviceModel *)deviceModel;

@end
