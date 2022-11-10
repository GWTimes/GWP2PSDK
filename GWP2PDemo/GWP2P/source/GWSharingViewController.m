//
//  GWSharingViewController.m
//  GWP2P
//
//  Created by USER on 2018/4/19.
//  Copyright © 2018年 gwell. All rights reserved.
//

#import "GWSharingViewController.h"
#import "DeviceModel.h"
#import <GWP2P/GWP2P.h>
#import "LoginResult.h"
#import "GWSharingFlowchartViewController.h"



@interface GWSharingViewController ()

@property (copy, nonatomic) NSString *deviceID;
@property (nonatomic, assign) BOOL isDeviceLinkIn;

@end


@implementation GWSharingViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.title = @"分享";
    
    self.navigationItem.rightBarButtonItem = [[UIBarButtonItem alloc] initWithTitle:@"流程图" style:UIBarButtonItemStylePlain target:self action:@selector(showSharingFlowchart)];
    
    self.deviceID = @"5252037";
}

- (void)showSharingFlowchart {
    GWSharingFlowchartViewController *sharingFlowchartViewController = [[GWSharingFlowchartViewController alloc] init];
    [self.navigationController pushViewController:sharingFlowchartViewController animated:YES];
}

#pragma mark - 主人操作

/**
 智能联机后绑定主人
 
 @param sender 控件
 */
- (IBAction)smartLink:(id)sender {
    [self.view endEditing:YES];
    
#warning 请修改成对应的数据
    NSString *wifiSSID = @"IPC_YunWei_Group";
    NSString *wifiPassword = @"29088360";
    __block NSString *mastorPassword = @"qwe123"; //主人密码,客户根据自己的设计处理
    __block NSString *visitorPassword = @"1234"; //访客密码,客户根据自己的设计处理
    
    __weak typeof(self) weakSelf = self;
    [MBProgressManager showWaitingWithTitle:@"声波配网中..."];
    //需要注意deviceLinkIn会被回调很多次
    self.isDeviceLinkIn = NO;
    
    //分享设备使用流程,共有以下几个步骤,UI上不写示范代码,客户根据自己公司的app设计去实现
    //要使用分享的功能,需要技威服务器后台支持,请联系商务配置服务器
    //一主人操作
    //1 配网,这一步可以是智能连机,也可以是ap配网,步骤是一致的,这里只以智能连机来说明,ap配网时会设置主人密码,第2步与第3步合并
    [[GWP2PDeviceLinker shareInstance] p2pSmartLinkDeviceWithWiFiSSID:wifiSSID password:wifiPassword useSimpleConfig:NO deviceLinkIn:^(NSDictionary *deviceDict) {
        if (weakSelf.isDeviceLinkIn) {//会回调多次,用一个变量拦截,只处理一次
            NSLog(@"已经处理过");
            return;
        }
        
        NSLog(@"声波配网成功,返回数据:%@ %@", [NSThread currentThread], deviceDict);
        weakSelf.isDeviceLinkIn = YES;
        [MBProgressManager hideAlert];
        [MBProgressManager showBriefAlert:@"声波配网成功"];
        //如果智能联机,设备配网成功,就断开发送智能联机
        [[GWP2PDeviceLinker shareInstance] p2pStopSmartLink];
        
        __block NSString *deviceID = [deviceDict[@"deviceID"] stringValue];
        self.deviceID = deviceID;
#warning 配网成功后，调用P2P接口时传入deviceIP(设备在局域网中的IP地址最后一段)会走局域网与设备通信，基本上都能请求成功，如果直接穿入deviceID容易失败
        __block NSString *deviceIP = deviceDict[@"deviceIP"];
        __block NSNumber *customID = deviceDict[@"customID"];
        __block NSString *macAddr = deviceDict[@"macAddr"];
        
        sleep(3);//这里是为了解决设备刚连上网,马上给设备发指令,成功率低的问题,客户可以做个漂亮的UI
        //2 先锁定设备,确认设备能绑定主人,避免后面的工作白做
        [GWNetSingleton lockBindingDevice:self.deviceID withUserID:[LoginResult getAccount] sessionID:[LoginResult getSessionID1] completion:^(BOOL success, NSString *errorCode, NSString *errorString, NSDictionary *json) {
            NSLog(@"");
            if ([errorCode isEqualToString:SUCCESS]) {
                
                if (![deviceDict[@"isInitPassword"] boolValue]) {
                    //3 设置主人密码 没有初始化密码
                    [[GWP2PClient sharedClient] setDeviceInitialPassword:mastorPassword withDeviceID:deviceIP completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
                        
                        //后续的步骤与下面的一致
                    }];
                } else {
                    
                    //3 设置主人密码 有密码时,设备默认密码一般都是 123, 新的密码由客户自己处理
                    [[GWP2PClient sharedClient] setDeviceAdministratorPasswordWithOldPassword:@"123" newPassword:mastorPassword deviceID:deviceIP completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
                        NSNumber *result = dataDictionary[GWP2PMessageResult];//消息结果要以这个数据
                        if (success && result.boolValue) {
                            NSLog(@"设置主人密码成功");
                            //4 设置访客密码
                            [[GWP2PClient sharedClient] setDeviceVisitorPassword:visitorPassword withAdministratorPassword:mastorPassword deviceID:deviceIP completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
                                NSNumber *result1 = dataDictionary[GWP2PMessageResult];//消息结果要以这个数据
                                if (success && result1.boolValue) {
                                    NSLog(@"设置访客密码成功");
                                    //5 绑定主人
                                    NSString *time = [NSString stringWithFormat:@"%0.f", [[NSDate date] timeIntervalSince1970]];
                                    NSString *account = [LoginResult getAccount];
                                    NSString *sessionID = [LoginResult getSessionID1];
                                    UInt64 keyID = [MD5Manager getSecretDeviceIdWithDeviceId:deviceID];
                                    
                                    char buffer1[300] = {0};
                                    [MD5Manager PasswordEncrypt:(char *)[mastorPassword cStringUsingEncoding:NSUTF8StringEncoding] UserID:(char*)[account cStringUsingEncoding:NSUTF8StringEncoding] Dst:buffer1 Len:300];
                                    NSString *secretKey = [NSString stringWithUTF8String:buffer1];
                                    
                                    char buffer2[300] = {0};
                                    [MD5Manager PasswordEncrypt:(char *)[visitorPassword cStringUsingEncoding:NSUTF8StringEncoding] UserID:(char*)[account cStringUsingEncoding:NSUTF8StringEncoding] Dst:buffer2 Len:300];
                                    NSString *guestKey = [NSString stringWithUTF8String:buffer2];
                                    
                                    NSLog(@"参数 deviceID:%@ account:%@ sessionID:%@ time:%@ secretKey:%@ guestKey:%@ keyID:%llu customID:%@ macAddr:%@", deviceID, account, sessionID, time, secretKey, guestKey, keyID, customID, macAddr);
                                    //5 绑定设备
                                    [GWNetSingleton bindDevice:deviceID withUserID:account sessionID:sessionID modifyTime:time deviceInfoVersion:@"0" groupID:@"0" permission:3 secretKey:@"0" guestKey:guestKey remarkName:@"填个名字" keyID:keyID customID:customID.intValue macAddr:macAddr isSupport:NO completion:^(BOOL success, NSString *errorCode, NSString *errorString, NSDictionary *json) {
                                        if ([errorCode isEqualToString:SUCCESS]) {
                                            NSLog(@"绑定成功");
                                            //获取设备必要信息,这一步非必需,为了保证添加的设备有准确信息,最好执行
                                            [[GWP2PClient sharedClient] getMultipleDeviceStatusWithDeviceID:deviceIP password:mastorPassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
                                                NSLog(@"success:%i %@",success,dataDictionary);
                                                //服务器已经认为绑定了,这里不管成功还是失败,都要加入设备列表
                                                DeviceModel *deviceModel = [[DeviceModel alloc] init];
                                                deviceModel.deviceID = deviceID;
                                                deviceModel.devicePassword = mastorPassword;
                                                deviceModel.deviceSharingType = GWDeviceSharingTypeMastor;
                                                if (success && dataDictionary[GWP2PMessageResult]) {
                                                    deviceModel.deviceType = [dataDictionary[@"device type"] intValue];
                                                    deviceModel.deviceSubtype = [dataDictionary[@"device subtype"] intValue];
                                                } else {
                                                    
                                                }
                                                [DeviceModel saveDeviceModel:deviceModel];
                                            }];
                                        } else {
                                            //出错处理
                                            NSLog(@"绑定主人第五步,绑定出错 %@", errorString);
                                        }
                                    }];
                                } else {
                                    //出错处理
                                    NSLog(@"绑定主人第四步,设访客密码出错 %@", dataDictionary);
                                }
                            }];
                        } else {
                            //出错处理
                            NSLog(@"绑定主人第三步,设主人密码出错 %@", dataDictionary);
                        }
                    }];
                }
            } else {
                //错误处理
                NSLog(@"绑定主人第二步,锁定设备出错");
            }
        }];
    }];
}

static NSString *inviteCode = nil;

/**
 获取分享链接
 
 @param sender 控件
 */
- (IBAction)getShareLink:(id)sender {
    //获取邀请码, 这一步是主人账号获取,获取后通过一定的途径(如二维码,纯文本)分享给访客账号
    NSString *account = [LoginResult getAccount];
    NSString *sessionID = [LoginResult getSessionID1];
    [GWNetSingleton getShareLinkWithUserID:account sessionID:sessionID deviceID:self.deviceID permission:1 guestID:@"" guestRemark:@"" appendMsg:@""  masterNickName:@"ss" deviceNickName:@"12" completion:^(BOOL success, NSString *errorCode, NSString *errorString, NSDictionary *json) {
        NSLog(@"获取分享邀请码 errorCode:%@ errorString:%@ %@", errorCode, errorString, json);
        if ([errorCode isEqualToString:SUCCESS]) {
            NSString *inviteLink = [NSString stringWithFormat:@"%@", json[@"ShareLink"]];//邀请链接,也可以直接分享给访客,访客拿到后解析出邀请码
            NSArray<NSString *> *array = [inviteLink componentsSeparatedByString:@"&"];
            [array enumerateObjectsUsingBlock:^(NSString * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
                if ([obj containsString:@"InviteCode="]) {
                    NSArray<NSString *> *inviteCodeArray = [obj componentsSeparatedByString:@"="];
                    inviteCode = inviteCodeArray.lastObject;//邀请码
                    *stop = YES;
                }
            }];
        } else {
            
        }
    }];
}

//删除访客
- (IBAction)deleteVisitor:(id)sender {
    NSString *account = [LoginResult getAccount];
    NSString *sessionID = [LoginResult getSessionID1];
    //先获取访客
    [GWNetSingleton getGuestListWithUserID:account sessionID:sessionID deviceID:self.deviceID completion:^(BOOL success, NSString *errorCode, NSString *errorString, NSDictionary *json) {
        NSLog(@"成功:%d 返回码:%@ 错误描述:%@ 数据:%@", success, errorCode, errorString, json);
        if ([errorCode isEqualToString:SUCCESS]) {
            NSInteger didShareCount = [NSString stringWithFormat:@"%@", json[@"GuestCount"]].integerValue;//总共的访客数量
            NSInteger canShareMaxCount = [NSString stringWithFormat:@"%@", json[@"GuestMax"]].intValue;//最多能分享给多少个访客
            NSLog(@"有 %ld 个访客, 最多可添加 %ld 个访客", (long)didShareCount, (long)canShareMaxCount);
            if (didShareCount > 0) {
                NSArray<NSDictionary *> *guestListArray = json[@"GuestList"];
                if (guestListArray.count > 0) {
                    NSDictionary *guestDictionary = guestListArray[0];
                    
                    NSString *guestID = guestDictionary[@"GuestID"];
                    //删除第一个访客,具体要删除哪个,用户自己处理,这里只是演示代码
                    [GWNetSingleton deleteGuestWithUserID:account sessionID:sessionID deviceID:self.deviceID guestID:guestID completion:^(BOOL success, NSString *errorCode, NSString *errorString, NSDictionary *json) {
                        NSLog(@"成功:%d 返回码:%@ 错误描述:%@ 数据:%@", success, errorCode, errorString, json);
                        if ([errorCode isEqualToString:SUCCESS]) {
                            [MBProgressManager showBriefAlert:@"删除成功"];
                        } else {
                            [MBProgressManager showBriefAlert:@"删除失败"];
                        }
                    }];
                }
            } else {
                [MBProgressManager showBriefAlert:@"没有访客"];
            }
        } else {
            [MBProgressManager showBriefAlert:@"获取访客出错"];
        }
    }];
}

//解绑,解绑后不需要再调同步删除的接口
- (IBAction)unbind:(id)sender {
    NSString *account = [LoginResult getAccount];
    NSString *sessionID = [LoginResult getSessionID1];
    [GWNetSingleton deleteOwnerWithUserID:account sessionID:sessionID deviceID:self.deviceID packageOption:NO completion:^(BOOL success, NSString *errorCode, NSString *errorString, NSDictionary *json) {
        NSLog(@" errorCode:%@ errorString:%@ %@", errorCode, errorString, json);
        if ([errorCode isEqualToString:SUCCESS]) {
            [MBProgressManager showBriefAlert:@"解绑成功"];
            //删除数据库
            [[DeviceModel deviceModels] enumerateObjectsUsingBlock:^(DeviceModel * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
                if (obj.deviceID.integerValue == self.deviceID.integerValue) {
                    [DeviceModel removeDeviceModel:obj];
                    *stop = YES;
                }
            }];
        } else {
            [MBProgressManager showBriefAlert:@"解绑失败"];
        }
    }];
}

#pragma mark - 访客操作
//访客通过邀请码添加设备
- (IBAction)visitorAddDevice:(id)sender {
    NSString *account = [LoginResult getAccount];
    NSString *sessionID = [LoginResult getSessionID1];
    //这里添加不进,只是演示代码,要调接口成功,不能与主人用同一个账号,用户测试时也可把账号改一下
    //访客通过一定的途径(如二维码,纯文本),获取到邀请码后,从服务器获取设备访客密码,添加设备
    NSString *modifyTimeString = [NSString stringWithFormat:@"%0.f", [[NSDate date] timeIntervalSince1970]];
    [GWNetSingleton getSharedDeviceInformationWithUserID:account sessionID:sessionID inviteCode:inviteCode modifyTime:modifyTimeString completion:^(BOOL success, NSString *errorCode, NSString *errorString, NSDictionary *json) {
        NSLog(@" errorCode:%@ errorString:%@ %@", errorCode, errorString, json);
        if ([errorCode isEqualToString:SUCCESS]) {
            NSString *guestKey = [NSString stringWithFormat:@"%@", json[@"GuestKey"]];
            char pwdBuff[300] = {0};
            [MD5Manager PassswrodDecrypt:(char *)[guestKey UTF8String] UserID:(char *)[[LoginResult getAccount] UTF8String] Dst:(char *)&pwdBuff Len:300];
            NSString *password = [NSString stringWithUTF8String:pwdBuff];
            NSLog(@"服务器密码:%@ 解析出来的密码:%@", guestKey, password);
            [[GWP2PClient sharedClient] getMultipleDeviceStatusWithDeviceID:self.deviceID password:password completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
                
                
                DeviceModel *deviceModel = [[DeviceModel alloc] init];
                deviceModel.deviceID = self.deviceID;
                deviceModel.devicePassword = password;
                deviceModel.deviceSharingType = GWDeviceSharingTypeVisitor;
                if (success && dataDictionary[GWP2PMessageResult]) {
                    deviceModel.deviceType = [dataDictionary[@"device type"] intValue];
                    deviceModel.deviceSubtype = [dataDictionary[@"device subtype"] intValue];
                } else {
                    
                }
                [DeviceModel saveDeviceModel:deviceModel];
            }];
        } else {
            
        }
    }];
}

//访客自己删除设备调同步设备接口的删除设备就行
- (IBAction)visitorDeleteDevice:(id)sender {
    NSString *account = [LoginResult getAccount];
    NSString *sessionID = [LoginResult getSessionID1];
    NSString *time = [NSString stringWithFormat:@"%.0f", [[NSDate date] timeIntervalSince1970]];
    [GWNetSingleton deleteDeviceWithUserID:account sessionID:sessionID modifyTime:time deviceID:self.deviceID completion:^(BOOL success, NSString *errorCode, NSString *errorString, NSDictionary *json) {
        NSLog(@"成功:%d 返回码:%@ 错误描述:%@ 数据:%@", success, errorCode, errorString, json);
        if ([errorCode isEqualToString:SUCCESS]) {
            [MBProgressManager showBriefAlert:@"删除成功"];
            //删除数据库
            [[DeviceModel deviceModels] enumerateObjectsUsingBlock:^(DeviceModel * _Nonnull obj, NSUInteger idx, BOOL * _Nonnull stop) {
                if (obj.deviceID.integerValue == self.deviceID.integerValue) {
                    [DeviceModel removeDeviceModel:obj];
                    *stop = YES;
                }
            }];
        } else {
            [MBProgressManager showBriefAlert:@"删除失败"];
        }
    }];
}

@end
