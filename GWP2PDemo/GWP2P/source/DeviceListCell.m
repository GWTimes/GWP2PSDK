//
//  DeviceListCell.m
//  GWP2P
//
//  Created by apple on 17/5/23.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import "DeviceListCell.h"

@interface DeviceListCell () <UIAlertViewDelegate>
@property (weak, nonatomic) IBOutlet UILabel *deviceInfoLabel;
@property (weak, nonatomic) IBOutlet UIButton *sharingButton;

@end

@implementation DeviceListCell

- (void)setDeviceModel:(DeviceModel *)deviceModel {
    _deviceModel = deviceModel;
    
    if (deviceModel.deviceSharingType == GWDeviceSharingTypeNoShared) {
        self.sharingButton.hidden = YES;
    } else if (deviceModel.deviceSharingType == GWDeviceSharingTypeMastor) {
        self.sharingButton.hidden = NO;
        [self.sharingButton setTitle:@"主人" forState:UIControlStateNormal];
    } else if (deviceModel.deviceSharingType == GWDeviceSharingTypeVisitor) {
        self.sharingButton.hidden = NO;
        [self.sharingButton setTitle:@"访客" forState:UIControlStateNormal];
    }
    self.deviceInfoLabel.text = [NSString stringWithFormat:@"ID:%@ PW:%@ Type:%lu SubType:%lu",deviceModel.deviceID, deviceModel.devicePassword, (unsigned long)deviceModel.deviceType, (unsigned long)deviceModel.deviceSubtype];
}

- (IBAction)monitor:(id)sender {
    if ([self.delegate respondsToSelector:@selector(deviceListCell:pushVC:isStoryboard:)]) {
        [self.delegate deviceListCell:self pushVC:@"Monitor" isStoryboard:YES];
    }
}

- (IBAction)playback:(id)sender {
    if ([self.delegate respondsToSelector:@selector(deviceListCell:pushVC:isStoryboard:)]) {
        [self.delegate deviceListCell:self pushVC:@"PlaybackListsController" isStoryboard:NO];
    }
}

- (IBAction)setting:(id)sender {
    if ([self.delegate respondsToSelector:@selector(deviceListCell:pushVC:isStoryboard:)]) {
        [self.delegate deviceListCell:self pushVC:@"Setting" isStoryboard:YES];
    }
}

- (IBAction)changePassword:(id)sender {
    UIAlertView *alertView = [[UIAlertView alloc] initWithTitle:@"修改本地密码" message:nil delegate:self cancelButtonTitle:@"取消" otherButtonTitles:@"修改", nil];
    alertView.alertViewStyle = UIAlertViewStylePlainTextInput;
    UITextField *textField1 = [alertView textFieldAtIndex:0];
    textField1.placeholder = @"输入新密码";
    [alertView show];
}

#pragma mark - AlertViewDelegate
- (void)alertView:(UIAlertView *)alertView clickedButtonAtIndex:(NSInteger)buttonIndex {
    if (buttonIndex == 1) {
        NSString *password = [alertView textFieldAtIndex:0].text;
        _deviceModel.devicePassword = password;
        [DeviceModel saveDeviceModel:_deviceModel];
        [self setDeviceModel:_deviceModel];
    }
}

@end
