//
//  LanDevicesController.m
//  GWP2P
//
//  Created by apple on 17/5/24.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import "LanDevicesController.h"
#import <GWP2P/GWP2P.h>

@interface LanDevicesController ()

///列表数组
@property(nonatomic,strong)NSMutableArray<GWP2PLanDevice *> *listsArr;

@end

@implementation LanDevicesController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.title = @"局域网设备";
    
    //手动刷新按钮
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithBarButtonSystemItem:UIBarButtonSystemItemRefresh target:self action:@selector(refreshLanDeviceList)];
    
    self.listsArr = [NSMutableArray array];
    
    [self getLists];
    
}

#pragma mark 获取设备列表
-(void)getLists {

    //dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        GWP2PDeviceLinker *linker = [GWP2PDeviceLinker shareInstance];
          [linker refreshLanDevices];
        self.listsArr = linker.lanDevices;
        
        NSLog(@"%@",linker.lanDevices);
    //});
    
}


/**
 手动刷新
 */
- (void)refreshLanDeviceList {
    [[GWP2PDeviceLinker shareInstance] refreshLanDevices];
    [MBProgressManager showLoading];
    dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(2.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
        [MBProgressManager hideAlert];
        [self.tableView reloadData];
    });
}

#pragma mark 数据源方法
-(NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {

    return self.listsArr.count;

}

-(UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {

    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"lanDevice"];
    if (!cell) {
        
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"lanDevice"];
        
    }

    GWP2PLanDevice *device = self.listsArr[indexPath.row];
//    cell.backgroundColor = [UIColor blueColor];
    //时间戳转为标准时间格式
    NSTimeInterval time = device.lanTimeInterval;
    NSDate *date = [NSDate dateWithTimeIntervalSince1970:time];
    NSDateFormatter *dateFormatter = [[NSDateFormatter alloc]init];
    [dateFormatter setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
    NSString *timeStr= [dateFormatter stringFromDate:date];
    cell.textLabel.text =[NSString stringWithFormat:@"ID:%@,  更新时间:%@\nIP:%@,  类型:%@\n是否初始化密码:%zd,  是否支持Rtsp:%zd,",device.deviceId,timeStr,device.ipAddress,[self getTypeFromEnum:device.deviceType],device.isInitPassword,device.isSupportRtsp];
    
    cell.textLabel.numberOfLines = 0;
    cell.textLabel.font = [UIFont systemFontOfSize:14];
    return cell;
}

-(CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section {

    return 0.1;

}


-(CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {


    return 80;

}

//-(CGFloat)tableView:(UITableView *)tableView estimatedHeightForRowAtIndexPath:(NSIndexPath *)indexPath {
//
//    return 60;
//    
//}

-(BOOL)tableView:(UITableView *)tableView shouldHighlightRowAtIndexPath:(NSIndexPath *)indexPath {

    return NO;

}


#pragma mark 根据设备类型的枚举转换成对应字符串
-(NSString *)getTypeFromEnum:(GWP2PDeviceType)type {
    
    NSString *result;
    switch (type) {
        case 2:
            result = @"NPC";
            break;
        case 5:
            result = @"Doorbell";
            break;
        case 7:
            result = @"IPC";
            break;
        case 11:
            result = @"NVR";
            break;
        default:
            result = @"unKnow";
            break;
    }
    
    return result;
}


@end
