//
//  WiledLinkAddViewController.m
//  GWP2PDemo
//
//  Created by yuguihua on 2019/6/28.
//  Copyright © 2019 gwell. All rights reserved.
//

#import "WiledLinkAddViewController.h"
#import "DeviceModel.h"
#import <GWP2P/GWP2P.h>
#import "LoginResult.h"

@interface WiledLinkAddViewController ()

@end

@implementation WiledLinkAddViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.title = @"有线添加";
    // Do any additional setup after loading the view.
}
- (void)viewDidAppear:(BOOL)animated
{
    [super viewDidAppear:animated];
    [self saveDevice];
}
-(void)saveDevice{
//tip 设备都必须复位也能w使用用线添加的  All devices must be reset and can be added using wires
    [MBProgressManager showLoading];
    if (!self.device.isInitPassword) { //设备没有初始化密码,设置密码,设置成功后添加保存
        [[GWP2PClient sharedClient] setDeviceInitialPassword:@"qwer1234" withDeviceID:self.device.deviceId completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
            NSLog(@"success:%i %@",success,dataDictionary);
            if (success) {
                DeviceModel *deviceModel = [[DeviceModel alloc] init];
                deviceModel.deviceID = self.device.deviceId;
                deviceModel.devicePassword = @"qwer1234";
                deviceModel.deviceType = self.device.deviceType;
                [DeviceModel saveDeviceModel:deviceModel];
                 [MBProgressManager hideAlert];
                [self.navigationController popToRootViewControllerAnimated:YES];
            }else{
                [MBProgressManager showBriefAlert:dataDictionary[@"description"]];
                [self.navigationController popViewControllerAnimated:YES];
            }
       
        }];
    } else { //设备已经初始化密码,可以让用户输入正确的密码验证通过后加到本地列表,这里直接使用123
        //之里的初始密码每个厂商出厂不一样，一般为123，可以自行改更密码,可以直接添加也可以更改密码成功后添加保存，这里是校验密码对了直接添加保存  [GWP2PClient sharedClient]setDeviceAdministratorPasswordWithOldPassword
       
        [[GWP2PClient sharedClient] getMultipleDeviceStatusWithDeviceID:self.device.deviceId password:@"123" completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
            NSLog(@"success:%i %@",success,dataDictionary);
            if (success) {
                DeviceModel *deviceModel = [[DeviceModel alloc] init];
                deviceModel.deviceID = self.device.deviceId;
                deviceModel.devicePassword = @"123";
                deviceModel.deviceType = self.device.deviceType;
                [DeviceModel saveDeviceModel:deviceModel];
                [MBProgressManager hideAlert]; 
                [self.navigationController popToRootViewControllerAnimated:YES];

            }else{
            [MBProgressManager showBriefAlert:dataDictionary[@"description"]];
            [self.navigationController popViewControllerAnimated:YES];
            }
        }];
    }

}
/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

@end
