//
//  DeviceListController.m
//  GWP2P
//
//  Created by apple on 17/5/23.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import "DeviceListController.h"
#import "DeviceListCell.h"
#import <GWP2P/GWP2P.h>
#import "DeviceModel.h"
#import "LanDevicesController.h"
#import "LoginResult.h"

@interface DeviceListController () <UITableViewDelegate, UITableViewDataSource, DeviceListCellDelegate, UIAlertViewDelegate> {
    NSTimer *_p2pConnectStatusTimer;
}

@property (nonatomic, weak) IBOutlet UITableView *tableView;
@end

@implementation DeviceListController

- (void)didEnterBackgroundNotification:(NSNotification *)notification {
    NSLog(@"didEnterBackgroundNotification");
    [[GWP2PClient sharedClient] disconnect];
}

- (void)willEnterForegroundNotification:(NSNotification *)notification {
    NSLog(@"willEnterForegroundNotification");
    [[GWP2PClient sharedClient] connectWithAccount:[LoginResult getAccount] codeStr1:[LoginResult getP2PVerifyCode1] codeStr2:[LoginResult getP2PVerifyCode2] sessionID1:[LoginResult getSessionID1] sessionID2:[LoginResult getSessionID2] customerIDs:nil];
}

- (void)connectStatus {
    NSLog(@"p2p连接状态:%ld", (long)[GWP2PClient sharedClient].linkStatus);
}

- (void)viewDidLoad {
    [super viewDidLoad];
    self.navigationController.view.backgroundColor = [UIColor whiteColor];
    
    //为解决手机放置一段时间后,sdk没有响应的问题,手机进入后台时,先断开p2p,回到前台时再重新连接
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(didEnterBackgroundNotification:) name:UIApplicationDidEnterBackgroundNotification object:nil];
    [[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(willEnterForegroundNotification:) name:UIApplicationWillEnterForegroundNotification object:nil];
    
    _p2pConnectStatusTimer = [NSTimer scheduledTimerWithTimeInterval:10 target:self selector:@selector(connectStatus) userInfo:nil repeats:YES];
}

- (void)viewDidAppear:(BOOL)animated {
    [super viewDidAppear:animated];
    [self.tableView reloadData];
}

#pragma mark - 按钮事件
- (IBAction)setDeviceLinker:(id)sender {
    UIViewController *deviceLinkerVC= [[UIStoryboard storyboardWithName:@"DeviceLinker" bundle:nil] instantiateInitialViewController];
    [self.navigationController pushViewController:deviceLinkerVC animated:YES];
}

- (IBAction)getLanDevices:(id)sender {
    LanDevicesController *lanDevicesVC = [[LanDevicesController alloc] init];
    lanDevicesVC.hidesBottomBarWhenPushed = YES;
    [self.navigationController pushViewController:lanDevicesVC animated:YES];
}

- (IBAction)addDevice:(id)sender {
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"添加已联网设备" message:nil delegate:self cancelButtonTitle:@"取消" otherButtonTitles:@"添加",@"强制添加", nil];
    alertView.alertViewStyle = UIAlertViewStyleLoginAndPasswordInput;
    UITextField *textField1 = [alertView textFieldAtIndex:0];
    textField1.placeholder = @"设备ID";
    UITextField *textField2 = [alertView textFieldAtIndex:1];
    textField2.placeholder = @"密码";
    [alertView show];
}

#pragma mark - AlertView代理
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    NSString *deviceID = [alertView textFieldAtIndex:0].text;
    NSString *devicePassword = [alertView textFieldAtIndex:1].text;
    DeviceModel *deviceModel = [[DeviceModel alloc] init];
    deviceModel.deviceID = deviceID;
    deviceModel.devicePassword = devicePassword;
    __weak typeof(self) weakSelf = self;
    
    if (buttonIndex == 1) {//在线验证后添加
        //alertView的消失会导致MBProgressHUD一起消失,所以要添加到tabBarController.view
        [MBProgressManager showWaitingWithTitle:@"获取设备状态..." inView:self.tabBarController.view];
        [[GWP2PClient sharedClient] getMultipleDeviceStatusWithDeviceID:deviceID password:devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
            [MBProgressManager hideAlert];
            NSNumber *errorValue = dataDictionary[GWP2PMessageErrorValue];
            if (success ||
                errorValue.integerValue == P2PClientMessageErrorNoRight) {
                deviceModel.deviceType = [dataDictionary[@"device type"] intValue];
                deviceModel.deviceSubtype = [dataDictionary[@"device subtype"] intValue];
                [DeviceModel saveDeviceModel:deviceModel];
                [weakSelf.tableView reloadData];
            } else {
                [MBProgressManager showBriefAlert:@"添加失败" inView:self.tabBarController.view];
            }
        }];
    } else if (buttonIndex == 2) {//不验证直接添加
        [DeviceModel saveDeviceModel:deviceModel];
        [weakSelf.tableView reloadData];
        //再在后台尝试获取
        [[GWP2PClient sharedClient] getMultipleDeviceStatusWithDeviceID:deviceID password:devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
            if (success) {
                deviceModel.deviceType = [dataDictionary[@"device type"] intValue];
                deviceModel.deviceSubtype = [dataDictionary[@"device subtype"] intValue];
                [DeviceModel saveDeviceModel:deviceModel];
                [weakSelf.tableView reloadData];
            }
        }];
    }
}

#pragma mark - 设备列表代理
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    return [DeviceModel deviceModels].count;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    DeviceListCell *cell = [tableView dequeueReusableCellWithIdentifier:@"DeviceList"];
    if (!cell) {
        cell = [[NSBundle mainBundle] loadNibNamed:@"DeviceListCell" owner:nil options:nil].firstObject;
    }
    cell.deviceModel = [DeviceModel deviceModels][indexPath.row];
    cell.delegate = self;
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    return tableView.frame.size.width * 9 / 16 + 44 + 10;
}

- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath {
    return YES;
}

- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath {
    DeviceModel *deviceModel = [DeviceModel deviceModels][indexPath.row];
    [DeviceModel removeDeviceModel:deviceModel];
    [tableView reloadData];
}

#pragma mark - 设备列表cell按钮点击代理 DeviceListCellDelegate
- (void)deviceListCell:(DeviceListCell *)cell pushVC:(NSString *)vcName isStoryboard:(BOOL)isStoryboard {
    UIViewController *vc;
    if (isStoryboard) {
        vc = [[UIStoryboard storyboardWithName:vcName bundle:nil] instantiateInitialViewController];
    } else {
        vc = [[NSClassFromString(vcName) alloc] init];
    }
    if ([vc respondsToSelector:@selector(deviceModel)]) {
        [vc setValue:cell.deviceModel forKey:@"deviceModel"];
    }
    vc.hidesBottomBarWhenPushed = YES;
    [self.navigationController pushViewController:vc animated:YES];
}

@end
