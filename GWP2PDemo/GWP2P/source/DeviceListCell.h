//
//  DeviceListCell.h
//  GWP2P
//
//  Created by apple on 17/5/23.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "DeviceModel.h"
@class DeviceListCell;
@protocol DeviceListCellDelegate <NSObject>
- (void)deviceListCell:(DeviceListCell *)cell pushVC:(NSString *)vcName isStoryboard:(BOOL)isStoryboard;

@end

@interface DeviceListCell : UITableViewCell

@property (nonatomic, weak) id<DeviceListCellDelegate> delegate;
@property (nonatomic, strong) DeviceModel *deviceModel;
@end

