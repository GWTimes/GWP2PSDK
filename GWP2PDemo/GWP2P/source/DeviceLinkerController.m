//
//  DeviceLinkerController.m
//  GWP2P
//
//  Created by apple on 17/5/24.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import "DeviceLinkerController.h"
#import "DeviceModel.h"
#import <GWP2P/GWP2P.h>
#import "LoginResult.h"

@interface DeviceLinkerController ()

@property (weak, nonatomic) IBOutlet UITextField *wifiSSIDTF;
@property (weak, nonatomic) IBOutlet UITextField *wifiPasswordTF;
@property (weak, nonatomic) IBOutlet UITextField *devicePasswordTF;

@property (copy, nonatomic) NSString *deviceID;

@property (assign, nonatomic) BOOL isDeviceLinkIn;
@end

@implementation DeviceLinkerController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    
//    self.wifiSSIDTF.text = @"GW_12M_2.4G";
//    self.wifiPasswordTF.text = @"29088360";
//    self.devicePasswordTF.text = @"qwe123";
    self.deviceID = @"9220533";
}

- (IBAction)apLink:(id)sender {
    if (!_wifiSSIDTF.text.length || !_devicePasswordTF.text.length) {
        [MBProgressManager showBriefAlert:@"WiFi名和初始密码不能为空"];
        return;
    }
    [self.view endEditing:YES];
    [MBProgressManager showWaitingWithTitle:@"AP配网中..."];
    //需要注意代码块会被回调许多次
    [GWP2PClient sharedClient].port = 25143;//要先调用这个接口因为第三方厂商有定制端口,无定制请注释
    [[GWP2PDeviceLinker shareInstance] p2pAPLinkDeviceWithWiFiSSID:_wifiSSIDTF.text wifiPassword:_wifiPasswordTF.text devicePassword:_devicePasswordTF.text deviceReceive:^(NSString *deviceId, BOOL isSupport) {
        NSLog(@"设备%@收到WiFi,isSupport:%d",deviceId,isSupport);
    } deviceLinkIn:^(NSDictionary *deviceDict) {
        [MBProgressManager hideAlert];
        [MBProgressManager showBriefAlert:@"AP配网成功"];
    }];
}

/**
 声波配网(智能联机)

 @param sender 控件
 */
- (IBAction)smartLink:(id)sender {
    if (!_wifiSSIDTF.text.length || !_devicePasswordTF.text.length) {
        [MBProgressManager showBriefAlert:@"WiFi名和初始密码不能为空"];
        return;
    }
    [self.view endEditing:YES];
    __weak typeof(self) weakSelf = self;
    [MBProgressManager showWaitingWithTitle:@"声波配网中..."];
    //需要注意deviceLinkIn会被回调很多次
    self.isDeviceLinkIn = NO;
    
    [[GWP2PDeviceLinker shareInstance] p2pSmartLinkDeviceWithWiFiSSID:_wifiSSIDTF.text password:_wifiPasswordTF.text useSimpleConfig:NO deviceLinkIn:^(NSDictionary *deviceDict) {
        NSLog(@"声波配网成功,返回数据:%@",deviceDict);
        if (weakSelf.isDeviceLinkIn) {
            return;
        }
        weakSelf.isDeviceLinkIn = YES;
        [MBProgressManager hideAlert];
        [MBProgressManager showBriefAlert:@"声波配网成功"];
        //如果智能联机,设备配网成功,就断开发送智能联机
        [[GWP2PDeviceLinker shareInstance] p2pStopSmartLink];
        
        NSString *deviceID = [deviceDict[@"deviceID"] stringValue];
#warning 配网成功后，调用P2P接口时传入deviceIP(设备在局域网中的IP地址最后一段)会走局域网与设备通信，基本上都能请求成功，如果直接穿入deviceID容易失败
        NSString *deviceIP = deviceDict[@"deviceIP"];
        if (![deviceDict[@"isInitPassword"] boolValue]) { //设备没有初始化密码,设置密码
            [[GWP2PClient sharedClient] setDeviceInitialPassword:weakSelf.devicePasswordTF.text withDeviceID:deviceIP completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
                NSLog(@"success:%i %@",success,dataDictionary);
                if (success) {
                    DeviceModel *deviceModel = [[DeviceModel alloc] init];
                    deviceModel.deviceID = deviceID;
                    deviceModel.devicePassword = weakSelf.devicePasswordTF.text;
                    deviceModel.deviceType = [dataDictionary[@"device type"] intValue];
                    deviceModel.deviceSubtype = [dataDictionary[@"device subtype"] intValue];
                    [DeviceModel saveDeviceModel:deviceModel];
                }
            }];
        } else { //设备已经初始化密码,可以让用户输入正确的密码验证通过后加到本地列表,这里直接使用123
            
            [[GWP2PClient sharedClient] getMultipleDeviceStatusWithDeviceID:deviceIP password:@"123" completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
                NSLog(@"success:%i %@",success,dataDictionary);
                if (success) {
                    DeviceModel *deviceModel = [[DeviceModel alloc] init];
                    deviceModel.deviceID = deviceID;
                    deviceModel.devicePassword = @"123";
                    deviceModel.deviceType = [dataDictionary[@"device type"] intValue];
                    deviceModel.deviceSubtype = [dataDictionary[@"device subtype"] intValue];
                    [DeviceModel saveDeviceModel:deviceModel];
                }
            }];
        }
    }];
}

- (void)dealloc {
    NSLog(@"%s",__func__);
    [[GWP2PDeviceLinker shareInstance] p2pStopSmartLink];
}

@end
