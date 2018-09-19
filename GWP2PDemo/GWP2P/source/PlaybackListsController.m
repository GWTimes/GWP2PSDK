//
//  PlaybackListsController.m
//  GWP2P
//
//  Created by apple on 17/5/26.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import "PlaybackListsController.h"
#import "DeviceModel.h"
#import <GWP2P/GWP2P.h>
#import "PlaybackController.h"

@interface PlaybackListsController ()

@property(nonatomic,strong)NSMutableArray *listsArr;

///当前设备的信息模型
@property(nonatomic,strong)DeviceModel *deviceModel;

@end

@implementation PlaybackListsController

- (void)viewDidLoad {
    [super viewDidLoad];

    self.title = @"回放列表";
    self.listsArr = [NSMutableArray array];
    
    [self getLists];

}

#pragma mark -获取设备回放列表
-(void)getLists {

    [MBProgressManager showWaitingWithTitle:@"正在获取列表"];
    __weak typeof (self)weakSelf = self;
    GWP2PClient *click = [GWP2PClient sharedClient];
    [click getDevicePlaybackFilesWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword startDate:nil endDate:nil completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        
        NSLog(@"获取回放文件结果:%@", dataDictionary);
        [MBProgressManager hideAlert];
        NSString *result = dataDictionary[@"result"];
        if ([result floatValue] == 1) {
            
            NSArray *tempArr = [NSMutableArray arrayWithArray:dataDictionary[@"files"]];
            
            [weakSelf.listsArr addObjectsFromArray:tempArr];
            
            NSLog(@"%zd",self.listsArr.count);
            
            dispatch_async(dispatch_get_main_queue(), ^{
               
               [weakSelf.tableView reloadData];
            });
            
        }else {
            
           dispatch_async(dispatch_get_main_queue(), ^{
              
               [MBProgressManager showBriefAlert:@"获取列表失败"];
               
               dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(3 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                   
                  [weakSelf.navigationController popViewControllerAnimated:YES];
               });
               
           });
            
            
        }
        
    }];

}


#pragma mark - Table view data source
- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView {

    return 1;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {

    return self.listsArr.count;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"PlaybackLists"];
    if (!cell) {
        
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"PlaybackLists"];
    }
    
    cell.textLabel.font = [UIFont systemFontOfSize:14];
    GWPlaybackFileModel *fillModel = self.listsArr[indexPath.row];
    
    cell.textLabel.text = [NSString stringWithFormat:@"%zd-%zd-%zd_%zd:%zd:%zd_%@(%zd)",fillModel.year,fillModel.month,fillModel.day,fillModel.hour,fillModel.minute,fillModel.second,fillModel.cType,fillModel.time];
    return cell;
}

-(CGFloat)tableView:(UITableView *)tableView heightForFooterInSection:(NSInteger)section {

    return 0.1;

}

-(void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {

    PlaybackController *playBackVC = [[UIStoryboard storyboardWithName:@"Playback" bundle:nil] instantiateInitialViewController];

    playBackVC.fillModelArr = self.listsArr;
    playBackVC.deviceModel = self.deviceModel;
    playBackVC.currentIndex = indexPath.row;
    [self.navigationController pushViewController:playBackVC animated:YES];
}

@end
