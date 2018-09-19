//
//  PlaybackController.h
//  GWP2P
//
//  Created by apple on 17/5/24.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <GWP2P/GWP2P.h>
#import "DeviceModel.h"

@interface PlaybackController : UIViewController

///设备录像列表
@property(nonatomic,strong)NSMutableArray *fillModelArr;

///当前设备的信息模型
@property(nonatomic,strong)DeviceModel *deviceModel;

///当前模型位置
@property(nonatomic,assign)NSInteger currentIndex;

@end
