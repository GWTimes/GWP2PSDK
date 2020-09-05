//
//  SettingController.m
//  GWP2P
//
//  Created by apple on 17/5/24.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import "SettingController.h"
#import "DeviceModel.h"
#import "LoginResult.h"
#import <GWP2P/GWNet.h>
@interface SettingExample : NSObject

@property (nonatomic, copy) NSString *title;

@property (nonatomic, assign) SEL selector;

@end

@implementation SettingExample

+ (instancetype)exampleWithTitle:(NSString *)title sel:(SEL)selector {
    SettingExample *example = [[self class] new];
    example.title = title;
    example.selector = selector;
    return example;
}
@end



@interface SettingController () <UITableViewDelegate, UITableViewDataSource, GWP2PClientProtocol>

@property (nonatomic, weak) IBOutlet UITableView *categoryTableView;

@property (nonatomic, weak) IBOutlet UITableView *exampleTableView;

@property (weak, nonatomic) IBOutlet UITextView *logTextView;

@property (nonatomic, copy) NSArray <NSDictionary *> *examples;

@property (nonatomic, strong) NSDateFormatter *formatter;

@property (nonatomic, assign) NSInteger sdCardID; /**< sd卡ID */

@end

@implementation SettingController

- (void)awakeFromNib {
    [super awakeFromNib];

}

- (void)viewDidLoad {
    [super viewDidLoad];
    
    [self initExamples];
    
    self.automaticallyAdjustsScrollViewInsets = NO;
    self.navigationItem.title = [NSString stringWithFormat:@"设备ID:%@",self.deviceModel.deviceID];
    
    self.categoryTableView.delegate = self;
    self.categoryTableView.dataSource = self;
    self.exampleTableView.delegate = self;
    self.exampleTableView.dataSource = self;
    [self.categoryTableView selectRowAtIndexPath:[NSIndexPath indexPathForRow:0 inSection:0] animated:NO scrollPosition:UITableViewScrollPositionNone];
    
    self.categoryTableView.tableFooterView = [UIView new];
    self.exampleTableView.tableFooterView = [UIView new];
    
    //监控报警,门铃响铃,下载文件回调等
    [GWP2PClient sharedClient].delegate = self;;
}

- (void)viewWillAppear:(BOOL)animated {
    [super viewWillAppear:animated];
    self.tabBarController.tabBar.hidden = YES;
}

#pragma mark - GWP2PClientProtocol
- (void)client:(GWP2PClient *)client receavedDeviceAlarm:(NSDictionary<NSString *,id> *)alarmDictionary {
    [self outputLog:alarmDictionary success:YES];
    NSLog(@"报警信息:%@", alarmDictionary);
    NSDictionary *pictureDic = alarmDictionary[@"scene mode device picture"];//情景模式设备
    //如果贵公司的设备不是情景模式的设备,请用下面代码获取保存图片信息字典
    //pictureDic = alarmDictionary[@"common device picture"];
    NSNumber *pictureNumber = pictureDic[@"picture number"];
    NSUInteger pictureCount = pictureNumber.unsignedIntegerValue;
    NSUInteger toDownloadIndex = 0;
    NSString *documentPath = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0];
    NSString *localPath = [NSString stringWithFormat:@"%@/%.0f.png", documentPath, [NSDate date].timeIntervalSince1970];
    NSLog(@"下载图片 硬件路径:%@ 手机路径:%@", pictureDic[@"path"], localPath);
    [client downloadAlarmPictureWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword pictureNumber:pictureCount toDownloadIndex:toDownloadIndex remoteFilePath:pictureDic[@"path"] localFilePath:localPath];
      [self outputLog:alarmDictionary success:YES];
}

- (void)client:(GWP2PClient *)client receavedDoorbellRingingBySerialTransmission:(NSDictionary<NSString *,id> *)ringingDictionary {
    NSLog(@"门铃设备通过串口透传推送响铃:%@", ringingDictionary);
      [self outputLog:ringingDictionary success:YES];
}

- (void)client:(GWP2PClient *)client didDownloadFile:(BOOL)success withFilePath:(NSString *)filePath deviceID:(NSString *)deviceID result:(NSDictionary<NSString *,NSString *> *)resultDictionary {
    [self outputLog:resultDictionary success:success];
    
    if (success) {
        dispatch_async(dispatch_get_main_queue(), ^{
            //NSBundle *bundle = [NSBundle mainBundle];
            NSFileManager *fileManager = [NSFileManager defaultManager];
            if([fileManager fileExistsAtPath:filePath]) {
                NSData *data = [[NSData alloc] initWithContentsOfFile:filePath];
                UIImage *image = [UIImage imageWithData:data];
                NSLog(@"拿到图片%@", image);
                /*
                UIImageView *imageView = [[UIImageView alloc] initWithImage:image];
                imageView.frame = self.tableView.frame;
                imageView.backgroundColor = [UIColor yellowColor];
                [self.view addSubview:imageView];
                dispatch_after(dispatch_time(DISPATCH_TIME_NOW, 10 * NSEC_PER_SEC), dispatch_get_main_queue(), ^{
                    [imageView removeFromSuperview];
                });*/
            }
        });
    }
}

/**
 更新进度

 @param client  GWP2PClient 类
 @param persent 进度百分比
 */
- (void)client:(GWP2PClient *)client updateProgress:(NSInteger)persent {
    [self outputLog:@{@"更新进度" : [NSString stringWithFormat:@"%ld%%", (long)persent]} success:YES];
}

/**
 收到串口透传的数据

 @param client GWP2PClient 类
 @param data   串口透传数据
 */
- (void)client:(GWP2PClient *)client receavedSerialTransmissionData:(NSDictionary *)data {
    NSString *string = @"收到串口透传数据:";
    [self outputLog:[string stringByAppendingString:data.description] success:YES];
}

#pragma mark - 设备控制指令
- (void)initExamples {
    self.examples = @[
                      @{@"category":@"设备信息",
                        @"example":
                            @[[SettingExample exampleWithTitle:@"获取设备状态信息" sel:@selector(getMulDevicesStatusExample)],
                              [SettingExample exampleWithTitle:@"获取设备版本信息" sel:@selector(getDeviceVersionExample)],
                              [SettingExample exampleWithTitle:@"初始化设备密码" sel:@selector(initDevicePasswordExample)],
                              [SettingExample exampleWithTitle:@"设置管理员密码" sel:@selector(setDeviceAdministratorPasswordExample)],
                                [SettingExample exampleWithTitle:@"设置访客密码" sel:@selector(setDeviceVisitorPasswordExample)],
                              [SettingExample exampleWithTitle:@"设置设备时间" sel:@selector(setDeviceTimeExample)],
                              [SettingExample exampleWithTitle:@"获取设备时间" sel:@selector(getDeviceTimeExample)],
                              [SettingExample exampleWithTitle:@"设置设备时区" sel:@selector(setDeviceTimeZoneExample)],
                              [SettingExample exampleWithTitle:@"设置设备连网类型" sel:@selector(setDeviceNetworkTypeExample)],
                              [SettingExample exampleWithTitle:@"执行设备更新" sel:@selector(performUpdateExample)],
                              [SettingExample exampleWithTitle:@"取消设备更新" sel:@selector(cancelUpdateExample)],
                              [SettingExample exampleWithTitle:@"设置RTSP密码模式" sel:@selector(setRTSPPasswordModeExample)],
                              [SettingExample exampleWithTitle:@"设置RTSP密码" sel:@selector(setRTSPPasswordExample)],
                              [SettingExample exampleWithTitle:@"确认RTSP密码模式" sel:@selector(confirmRTSPPasswordModeExample)],
                              [SettingExample exampleWithTitle:@"获取设备分辨率,IP地址,MAC(网卡)地址" sel:@selector(getDeviceResolutionAndIpAndMacAddressExample)],
                            [SettingExample exampleWithTitle:@"获取IP地址,网关地址，子网地址,DNS地址" sel:@selector(getDeviceDnsAndIpAndSubNetAndGateWayExample)],
                            [SettingExample exampleWithTitle:@"设置IP地址,网关地址，子网地址,DNS地址" sel:@selector(setDeviceDnsAndIpAndSubNetAndGateWayExample)],
                              [SettingExample exampleWithTitle:@"获取设备NVR信息" sel:@selector(getDeviceNVRInifomationExample)],
                              [SettingExample exampleWithTitle:@"设置设备Wifi信息" sel:@selector(setWifiExample)],
                            [SettingExample exampleWithTitle:@"获取设备Wifi信息" sel:@selector(getWifiExample)],
                              ],
                        
                    
                        },
                      
                      @{@"category":@"在线状态",
                        @"example":
                            @[
                                [SettingExample exampleWithTitle:@"获取多个用户或设备在线状态等" sel:@selector(getDevicesStatusExample)],
                                ],
                        },
                      
                      @{@"category":@"报警",
                        @"example":
                            @[
                                [SettingExample exampleWithTitle:@"打开接收报警" sel:@selector(operateAcceptAlarmMessageCellButton)],
                                [SettingExample exampleWithTitle:@"设置报警邮箱" sel:@selector(setDeviceAlarmEmailExample)],
                                [SettingExample exampleWithTitle:@"获取报警邮箱" sel:@selector(getDeviceAlarmEmailExample)],
                                [SettingExample exampleWithTitle:@"打开移动侦测" sel:@selector(setMotionDetectExample)],
                                [SettingExample exampleWithTitle:@"移动侦测灵敏度" sel:@selector(setMotionDetectSensityvityExample)],
                                [SettingExample exampleWithTitle:@"设置报警账号" sel:@selector(setDeviceAlarmAccountExample)],
                                [SettingExample exampleWithTitle:@"获取报警账号" sel:@selector(getDeviceAlarmAccountExample)],
                                [SettingExample exampleWithTitle:@"解除报警账号" sel:@selector(unbindDeviceCurrentAlarmAccountExample)],

                                

                                ],
                        },
                      
                      @{@"category":@"AP模式",
                        @"example":
                            @[
                                [SettingExample exampleWithTitle:@"AP模式下设置设备wifi密码" sel:@selector(setDeviceWifiPasswordInAPModeExample)],
                                [SettingExample exampleWithTitle:@"AP配网单机模式切换到普通单机模式" sel:@selector(setDeviceFromConfigNetworkAPModeToNormalAPModeExample)],
                                ],
                        },
                      
                      @{@"category":@"定时布防",
                        @"example":
                            @[
                                [SettingExample exampleWithTitle:@"普通布撤防" sel:@selector(defenceOperationExample)],
                                [SettingExample exampleWithTitle:@"获取设备定时布撤防数据" sel:@selector(getDeviceSheduleDefenceDataExample)],
                                [SettingExample exampleWithTitle:@"转向某预置位" sel:@selector(operateDevicePresetPositionExample)],
                                [SettingExample exampleWithTitle:@"添加某预置位" sel:@selector(addDevicePresetPositionExample)],
                            ],
                        },
                      
                      @{@"category":@"画面与声音",
                        @"example":
                            @[
                                [SettingExample exampleWithTitle:@"设置设备视频制式" sel:@selector(setDeviceRecordTypeExample)],
                                [SettingExample exampleWithTitle:@"设置设备色彩模式" sel:@selector(setDeviceColorModeExample)],
                            ],
                        },
                      
                      @{@"category":@"录像",
                        @"example":
                            @[
                                [SettingExample exampleWithTitle:@"设置设备录像类型" sel:@selector(setDeviceVideoFormatExample)],
                                [SettingExample exampleWithTitle:@"获取回话文件" sel:@selector(getDevicePlaybackFilesExample)],
                                [SettingExample exampleWithTitle:@"获取录像质量" sel:@selector(getRecordDefinitionExample)],
                                [SettingExample exampleWithTitle:@"设置录像质量" sel:@selector(setRecordDefinitionExample)],
                                [SettingExample exampleWithTitle:@"设置手动录像开关" sel:@selector(setDeviceManuallyRecordStateExample)],
                                [SettingExample exampleWithTitle:@"获取SD卡信息" sel:@selector(getDeviceStorageInfomationExample)],
                                [SettingExample exampleWithTitle:@"格式化SD卡" sel:@selector(formatDeviceSDCardExample)],
                            ],
                        },
                      
                      @{@"category":@"情景模式",
                        @"example":
                            @[
                                [SettingExample exampleWithTitle:@"获取设备所有情景模式" sel:@selector(getDeviceSceneModelsExample)],
                                ],
                        },
                      
                      @{@"category":@"传感器",
                        @"example":
                            @[
                                [SettingExample exampleWithTitle:@"获取普通设备传感器" sel:@selector(getDeviceConnectedSensorsExample)],
                                [SettingExample exampleWithTitle:@"获取情景模式设备传感器" sel:@selector(sceneModeDeviceGetSensorsInfomationExample)],
                                [SettingExample exampleWithTitle:@"门铃开锁" sel:@selector(doorbellDeviceUnlockExample)],
                                [SettingExample exampleWithTitle:@"普通设备添加传感器" sel:@selector(addASensorExample)],
                                [SettingExample exampleWithTitle:@"普通删除添加传感器" sel:@selector(deleteASensorExample)],
                                [SettingExample exampleWithTitle:@"发送串口透传数据" sel:@selector(sendSerialTransmissionDataExample)],
                                ],
                        },
                      
                      @{@"category":@"客户定制功能",
                        @"example":
                            @[
                                [SettingExample exampleWithTitle:@"获取报警消息" sel:@selector(sendBinaryDataExample)],
                                ],
                        },
                      
                      @{@"category":@"下载文件",
                        @"example":
                            @[
                                [SettingExample exampleWithTitle:@"下载图片" sel:@selector(downloadPictureExample)],
                                ],
                        },
                      
                      @{@"category":@"白光灯声控",
                        @"example":
                            @[
                                [SettingExample exampleWithTitle:@"设置白光灯开关状态" sel:@selector(setDeviceWhiteLightStateExample)],
                                [SettingExample exampleWithTitle:@"获取白光灯定时动作设置" sel:@selector(getDeviceWhiteLightSchedulesExample)],
                                [SettingExample exampleWithTitle:@"设置白光灯定时动作" sel:@selector(setDeviceWhiteLightSchedulesExample)],
                                [SettingExample exampleWithTitle:@"设置白光灯亮度" sel:@selector(setDeviceWhiteLightBrightnessExample)],
                                [SettingExample exampleWithTitle:@"获取声控图片" sel:@selector(getDeviceSoundControlPickturesExample)],
                                [SettingExample exampleWithTitle:@"获取声控状态" sel:@selector(getDeviceSoundControlStateExample)],
                                [SettingExample exampleWithTitle:@"设置声控情景切换状态" sel:@selector(setDeviceSoundControlWorkModeStateExample)],
                                [SettingExample exampleWithTitle:@"设置灯光控制状态" sel:@selector(setDeviceSoundControlLamplighStateExample)],
                                [SettingExample exampleWithTitle:@"设置声控拍照状态" sel:@selector(setDeviceSoundControlCaptureStateExample)],
                                [SettingExample exampleWithTitle:@"设置声控录像状态" sel:@selector(setDeviceSoundControlStateRecordExample)],
                                [SettingExample exampleWithTitle:@"设置声控状态" sel:@selector(setDeviceSoundControlStateExample)],
                                ],
                        },
                      @{@"category":@"变倍变焦",
                        @"example":
                            @[
                                [SettingExample exampleWithTitle:@"获取变倍变焦" sel:@selector(getAutoZoom)],
                                [SettingExample exampleWithTitle:@"设置变倍变焦" sel:@selector(setAutoZoom)],

                                ],
                        },
                      @{@"category":@"SDK P2P信息",
                        @"example":
                            @[
                                [SettingExample exampleWithTitle:@"获取SDK P2P版本信息" sel:@selector(getSDKVersion)],
                               
                                
                                ],
                        },
                      ];
}

#pragma mark 请求例子

/**
 获取设备NVR信息
 */
- (void)getDeviceNVRInifomationExample {
    [[GWP2PClient sharedClient] getDeviceNVRInfomationWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}


#pragma mark - 强制绑定，上传设备关系链设备,这样3.0的设备才能收到在线推送
- (void)bindDevice {
    //5 绑定设备
    NSString *myAccountID = [LoginResult getAccount];
    NSString *modifyTimeString = [NSString stringWithFormat:@"%0.f", [[NSDate date] timeIntervalSince1970]];
    UInt64 secretDeviceId = [MD5Manager getSecretDeviceIdWithDeviceId:self.deviceModel.deviceID];

    [GWNetSingleton bindDevice:self.deviceModel.deviceID withUserID:myAccountID sessionID:[LoginResult getSessionID1] modifyTime:modifyTimeString deviceInfoVersion:@"0" groupID:@"0" permission:271 secretKey:@"0" guestKey:self.deviceModel.devicePassword remarkName:@"填个名字" keyID:secretDeviceId customID:0 macAddr:@"0" isSupport:NO completion:^(BOOL success, NSString *errorCode, NSString *errorString, NSDictionary *json) {
        [self outputLog:json success:success];
    }];
}

/**
打开接收报警
 */
- (void)operateAcceptAlarmMessageCellButton{
    __block int permission = 271;
    if (false) {
       
        permission = (permission | 0b100000000);//现在只用第9位操作是否开启报警，第10位是否接受不用
    }else if (true) {
      
        permission = (permission & 0b11111111111111111111111011111111);
    }
    NSString *myAccountID = [LoginResult getAccount];
    [[GWNet shareInstance]modifyPermissionWithUserID:myAccountID sessionID:[LoginResult getSessionID1] deviceID:self.deviceModel.deviceID guestID:myAccountID permission:@(permission).stringValue completion:^(BOOL success, NSString *errorCode, NSString *errorString, NSDictionary<NSString *,id> *json) {
        [self outputLog:json success:success];
        
    }];
}

/**
 设置声控情景切换状态
 */
- (void)setDeviceSoundControlWorkModeStateExample {
    static BOOL on = YES;
    on = !on;
    [[GWP2PClient sharedClient] setDeviceSoundControlWorkModeState:on withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary)  {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 设置灯光控制状态
 */
- (void)setDeviceSoundControlLamplighStateExample {
    static BOOL on = YES;
    on = !on;
    [[GWP2PClient sharedClient] setDeviceSoundControlLamplighState:on withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary)  {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 设置声控拍照状态
 */
- (void)setDeviceSoundControlCaptureStateExample {
    static BOOL on = YES;
    on = !on;
    [[GWP2PClient sharedClient] setDeviceSoundControlCaptureState:on withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary)  {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 设置声控录像状态
 */
- (void)setDeviceSoundControlStateRecordExample {
    static BOOL on = YES;
    on = !on;
    [[GWP2PClient sharedClient] setDeviceSoundControlRecordState:on withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary)  {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 设置声控状态
 */
- (void)setDeviceSoundControlStateExample {
    static BOOL on = YES;
    on = !on;
    [[GWP2PClient sharedClient] setDeviceSoundControlState:on withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary)  {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 获取声控状态
 */
- (void)getDeviceSoundControlStateExample {
    [[GWP2PClient sharedClient] getDeviceSoundControlStateWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 获取声控图片
 */
- (void)getDeviceSoundControlPickturesExample {
    [[GWP2PClient sharedClient] getDeviceSoundControlPickturesFromDate:[NSDate dateWithTimeIntervalSince1970:0.f] toDate:[NSDate date] deviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 设置白光灯亮度
 */
- (void)setDeviceWhiteLightBrightnessExample {
    [[GWP2PClient sharedClient] setDeviceWhiteLightBrightness:66 withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 获取设备分辨率,IP地址,MAC(网卡)地址
 */
- (void)getDeviceResolutionAndIpAndMacAddressExample {
    [[GWP2PClient sharedClient] getDeviceResolutionAndIpAndMacAddressWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
   
}
/**
 获取SDKp2p库的版本号
 */
- (void)getSDKVersion {
  NSString *version =  [[GWP2PClient sharedClient] getP2PVersion];
    [self outputLog:@{@"version":version} success:YES];
    
}
/**
 获取,IP地址,DNS,网关，子网
 */
- (void)getDeviceDnsAndIpAndSubNetAndGateWayExample {
    [[GWP2PClient sharedClient] getDeviceDNSAndIpAndGetWayAndSubNetMaskWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
            [self outputLog:dataDictionary success:success];
    }];
    
}
/**
 设置,IP地址,DNS,网关，子网
 */
- (void)setDeviceDnsAndIpAndSubNetAndGateWayExample {
    [[GWP2PClient sharedClient] setDeviceDNSAndIpAndGetWayAndSubNetMaskWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword isAuto:1 deviceDNS:@"255.255.255.0" deviceIP:@"192.168.1.1" deviceSubNetMask:@"255.255.255.0" deviceGetWay:@"255.255.255.0" completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
         [self outputLog:dataDictionary success:success];
    }];
    
}
/**
 设置白光灯定时动作
 */
- (void)setDeviceWhiteLightSchedulesExample {
    GWWhiteLightScheduleModel *model1 = [[GWWhiteLightScheduleModel alloc] init];
    model1.hour = 1;
    model1.munite = 2;
    model1.on = YES;
    model1.enable = YES;
    GWWhiteLightScheduleModel *model2 = [[GWWhiteLightScheduleModel alloc] init];
    model2.hour = 5;
    model2.munite = 22;
    model2.on = YES;
    model2.enable = NO;
    [[GWP2PClient sharedClient] setDeviceWhiteLightSchedules:@[model1, model2] withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 获取白光灯定时动作设置
 */
- (void)getDeviceWhiteLightSchedulesExample {
    [[GWP2PClient sharedClient] getDeviceWhiteLightSchedulesWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 设置白光灯开关状态
 */
- (void)setDeviceWhiteLightStateExample {
    [[GWP2PClient sharedClient] setDeviceWhiteLightState:YES withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}
/**
 获取变倍变焦
 */
- (void)getAutoZoom {
    [[GWP2PClient sharedClient] getAutoZoomWithId:self.deviceModel.deviceID password:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 设置 获取变倍变焦
 */
- (void)setAutoZoom {
    [[GWP2PClient sharedClient] setAutoZoomWithId:self.deviceModel.deviceID password:self.deviceModel.devicePassword params:5 completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}
/**
 确认RTSP密码模式
 */
- (void)confirmRTSPPasswordModeExample {
    [[GWP2PClient sharedClient] confirmDeviceRTSPPasswordModeWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 设置RTSP密码模式
 */
- (void)setRTSPPasswordModeExample {
    [[GWP2PClient sharedClient] setDeviceRTSPPasswordMode:GWDeviceRTSPPasswordModeClosed withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 设置RTSP密码
 */
- (void)setRTSPPasswordExample {
    [[GWP2PClient sharedClient] setDeviceRTSPPassword:@"abc123" withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}
/**
 获取wifiw信息
 */
- (void)getWifiExample {
    [[GWP2PClient sharedClient] getDeviceWifiListWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary)
     {
         
         [self outputLog:dataDictionary success:success];
     }];
}



/**
 设置wifiw信息
 */
- (void)setWifiExample {
    [[GWP2PClient sharedClient] setDeviceWifiInNetworkModeWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword wifiEncryptedType:2 wifiName:@"SricamGC03" wifiPassword:@"999Sricam" completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary)
     {
       [self outputLog:dataDictionary success:success];
     }];
}

/**
 获取SD卡信息
 */
- (void)setDeviceFromConfigNetworkAPModeToNormalAPModeExample {
    [[GWP2PClient sharedClient] setDeviceFromConfigNetworkAPModeToNormalAPModeWithCompletionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 获取SD卡信息
 */
- (void)getDeviceStorageInfomationExample {
    [[GWP2PClient sharedClient] getDeviceStorageInfomationWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        NSNumber *sdCardID = dataDictionary[@"SD card ID"];
        self.sdCardID = sdCardID.integerValue;
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 格式化SD卡
 */
- (void)formatDeviceSDCardExample {
    [[GWP2PClient sharedClient] formatDeviceSDCard:self.sdCardID withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 设置手动录像开关
 */
- (void)setDeviceManuallyRecordStateExample {
    [[GWP2PClient sharedClient] setDeviceManuallyRecordState:YES withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 下载图片
 */
- (void)downloadPictureExample {
    NSString *documentPath = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES)[0];
    NSString *localPath = [NSString stringWithFormat:@"%@/20171122152515000V.png", documentPath];
    [[GWP2PClient sharedClient] downloadFileWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword remoteFilePath:@"/mnt/disc1/npc/SRImage/2017-11-22/20171122152515000V.jpg" localFilePath:localPath];
}

/**
 具体的报警消息
 */
typedef struct sAlarmInfoStore {
    unsigned int dwTime;///时间
    unsigned char bAlarmType;///类型
    unsigned char bDefence : 4;///防区 这里的 : 4 表示结构体中的 bDefence 这个值是取 unsigned char 这个字节中的4位
    unsigned char bChannel : 4;///通道 这里的 : 4 表示结构体中的 bChannel 这个值是取 unsigned char 这个字节中的前面:取过的接下来的4位
}__attribute__((packed)) sAlarmInfoStore;

/**
 获取报警消息的数据结构
 */
typedef struct sMesgAlarmInfo {
    unsigned char  bCmd;///设备指令类型标识
    unsigned char  bOption;  /// 0表示成功
    unsigned char  bAlarmInfoNs;///标识报警消息有多少条
    unsigned char  bReseve;
    unsigned int dwLastAlarmInfoIndex;
    sAlarmInfoStore  bAlarmInfo[2];//存储具体的报警结构体数据(sAlarmInfoStore) 0表示不确定这里的数据有多长
}__attribute__((packed)) sMesgAlarmInfo;//__attribute__((packed)) 一定要加,作用是字节对齐,不加设备收到的数据解析不正确,

#pragma pack(1)//告诉编译器,后面的内容以参数个字节单位进行对齐,参数可为 1, 4, 8, 128
/**
 这个结构体只是用来测试字节对齐的另一种方式
 */
typedef struct AA {
    char c;//1 4 bit
    int i;//4 4 bit
    float f;//4 8 bit
    struct AA *aa;//8 8 bit
} AA;//17 24 bit
#pragma pack()//告诉编译器,以默认的方式进行字节对齐, 位宽为8字节，结构体对齐方式为按4字节对齐

/**
 客户定制功能,直接发送二进制数据给设备
 
 注意:此指令也不能同时发多条,就是说发过这条指令后,也只能等回复或者超时后才能再发这条指令,如果客户定制的功能有多条不一样的指令,也只能同时发一条
 */
- (void)sendBinaryDataExample {
    //NSUInteger l = sizeof(AA);
    //以获取设备报警信息为例
    //封装数据结构
    sMesgAlarmInfo alarmInfo = {0};
    alarmInfo.bCmd = 121;//技威定义的设备通信标识
    NSUInteger toSendDataLength = sizeof(sMesgAlarmInfo);
    NSData *toSendData = [NSData dataWithBytes:&alarmInfo length:toSendDataLength];
    //发送二进制数据
    [[GWP2PClient sharedClient] sendBinaryDataToDevice:self.deviceModel.deviceID withDevicePassword:self.deviceModel.devicePassword data:toSendData completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        if (success) { //与设备通信成功
            NSData *receavedData = dataDictionary[@"data"];
            if (receavedData) {
                //数据解析
                sMesgAlarmInfo *receavedByte = (sMesgAlarmInfo *)receavedData.bytes;//数据强制转换
                if (receavedByte->bCmd == 122) {//表示是收到报警信息的数据
                    NSMutableArray *alarmArray = [NSMutableArray array];//用于存放报警信息
                    if (receavedByte->bOption == 1) {//1表示获取报警信息成功,其它值代表的含义,请咨询技威客服
                        //NSUInteger alarmStructLength = sizeof(sAlarmInfoStore);
                        for (int i = 0; i < receavedByte->bAlarmInfoNs; i++) {
                            NSMutableDictionary *alarmDictionary = [NSMutableDictionary dictionary];
                            //时间
                            NSInteger time = receavedByte->bAlarmInfo[i].dwTime;
                            [alarmDictionary setObject:@(time) forKey:@"time"];
                            //类型
                            [alarmDictionary setObject:@(receavedByte->bAlarmInfo[i].bAlarmType) forKey:@"type"];
                            //防区
                            [alarmDictionary setObject:@(receavedByte->bAlarmInfo[i].bDefence) forKey:@"defence"];
                            //通道
                            [alarmDictionary setObject:@(receavedByte->bAlarmInfo[i].bChannel) forKey:@"channel"];
                            
                            [alarmArray addObject:alarmDictionary];
                        }
                    }
                    
                    //处理收到的数据,UI要注意线程问题
                    NSLog(@"获取到设备报警消息 %d:%@", receavedByte->bAlarmInfoNs, alarmArray);
                    [self outputLog:alarmArray success:success];
                }
            }
        } else { //与设备通信失败
            NSNumber *failureReasonNumber = dataDictionary[GWP2PMessageErrorValue];
            //在下面这段代码中做错误的原因处理,GWP2PClient 分类中的逻辑也是一样的
            if (failureReasonNumber) {
                NSUInteger failureReasonValue = failureReasonNumber.unsignedIntegerValue;
                if (failureReasonValue == P2PClientMessageErrorPasswordFail) {
                    NSLog(@"密码错误");
                } else if (failureReasonValue == P2PClientMessageErrorTimeOut) {
                    NSLog(@"超时");
                } else if (failureReasonValue == P2PClientMessageErrorIOSPushError) {
                    NSLog(@"ios内部错误");
                } else if (failureReasonValue == P2PClientMessageErrorNoRight) {
                    NSLog(@"没有权限");
                } else if (failureReasonValue == P2PClientMessageErrorMessageIsSending) {
                    NSLog(@"当前请求正在进行");
                } else if (failureReasonValue == P2PClientMessageErrorParameterError) {
                    NSLog(@"参数错误");
                } else if (failureReasonValue == P2PClientMessageErrorOtherError) {
                    NSString *failureReasonDescription = dataDictionary[GWP2PMessageDescription];
                    NSLog(@"其它错误:%@", failureReasonDescription);
                } else if (failureReasonValue == P2PClientMessageErrorUnKnow) {
                    NSLog(@"未知错误");
                }
            }
        }
        
    }];
}

/**
 普通设备添加传感器
 */
- (void)addASensorExample {
    [[GWP2PClient sharedClient] operateASensor:1 withOperationType:P2POperationTypeInsert deviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 app发送串口透传数据
 
 一次最多只能发251个字节
 */
- (void)sendSerialTransmissionDataExample {
    Byte byte[128];
    for (int i = 0; i < 128; i++) {
        byte[i] = i;
    }
    NSData *data = [NSData dataWithBytes:&byte length:128];
    NSString *s = @"1";
    data = [s dataUsingEncoding:NSUTF8StringEncoding];
    [[GWP2PClient sharedClient] sendSerialTransmissionData:data withSendingMode:GWSerialTransmissionSendingModeIPC1 deviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 普通设备删除传感器
 */
- (void)deleteASensorExample {
    [[GWP2PClient sharedClient] operateASensor:1 withOperationType:P2POperationTypeDelete deviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 执行设备更新
 */
- (void)performUpdateExample {
    [[GWP2PClient sharedClient] performUpdateWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 取消设备更新
 */
- (void)cancelUpdateExample {
    [[GWP2PClient sharedClient] cancelUpdateWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 设置设备网络类型
 */
- (void)setDeviceNetworkTypeExample {
    [[GWP2PClient sharedClient] setDeviceNetworkType:GWDeviceNetworkTypeWired withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 设置设备时区
 */
- (void)setDeviceTimeZoneExample {
    [[GWP2PClient sharedClient] setDeviceTimeZone:9.5f withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 设置设备时间
 */
- (void)setDeviceTimeExample {
    [[GWP2PClient sharedClient] setDeviceTime:[NSDate date] withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 获取设备时间
 */
- (void)getDeviceTimeExample {
    [[GWP2PClient sharedClient] getDeviceTimeWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 设置报警账号
 */
- (void)setDeviceAlarmAccountExample {
    [[GWP2PClient sharedClient] setDeviceBindedAlarmAccounts:@[[LoginResult getAccount]] withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}
/**
 获取报警账号
 */
- (void)getDeviceAlarmAccountExample {
  [[GWP2PClient sharedClient] getDeviceBindedAlarmAccountWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}
/**
 门铃开锁
 */
- (void)doorbellDeviceUnlockExample {
    [[GWP2PClient sharedClient] doorbellDeviceUnlockWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 获取设备录像质量
 */
- (void)getRecordDefinitionExample {
    [[GWP2PClient sharedClient] getDeviceRecordDefinitionWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 设置设备录像质量
 */
- (void)setRecordDefinitionExample {
    [[GWP2PClient sharedClient] setDeviceRecordDefinition:GWP2PRecordDefinitionSuperDefinition withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 情景模式设备获取传感器
 */
- (void)sceneModeDeviceGetSensorsInfomationExample {
    [[GWP2PClient sharedClient] sceneModeDeviceGetSensorsInfomationWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 普通设备获取传感器
 */
- (void)getDeviceConnectedSensorsExample {
    [[GWP2PClient sharedClient] getDeviceConnectedSensorsWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 获取设备所有情景模式
 */
- (void)getDeviceSceneModelsExample {
    [[GWP2PClient sharedClient] getDeviceSceneModelsWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 获取回话文件
 */
- (void)getDevicePlaybackFilesExample {
    NSDate *endDate = [NSDate date];
    NSDate *startDate = [NSDate dateWithTimeIntervalSinceNow:-60 * 60 * 24 * 3];
    //NSLog(@"获取回话文件:%@ %@", endDate, startDate);
    [[GWP2PClient sharedClient] getDevicePlaybackFilesWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword startDate:startDate endDate:endDate completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 设置设备视频格式
 */
- (void)setDeviceRecordTypeExample {
    [[GWP2PClient sharedClient] setDeviceRecordType:GWP2PRecordTypeManual withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 设置设备彩色模式
 */
- (void)setDeviceColorModeExample {
    static GWP2PColorMode color = GWP2PColorModeBlackWhite;
    [[GWP2PClient sharedClient] setDeviceColorMode:color withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
        if (success) {
            NSLog(@"color: %d", color);
            if (color == GWP2PColorModeBlackWhite) {
                color = GWP2PColorModeColorful;
            } else {
                color = GWP2PColorModeBlackWhite;
            }
        }
    }];
}

/**
 设置设备视频格式
 */
- (void)setDeviceVideoFormatExample {
    [[GWP2PClient sharedClient] setDeviceVideoFormat:GWP2PSetVideoFormatNTSC withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 打开移动侦测灵敏度
 */
- (void)setMotionDetectExample {
    [[GWP2PClient sharedClient] setDeviceMotionDetetionState:YES withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
          [self outputLog:dataDictionary success:success];
    }];
}
/**
 设置移动侦测灵敏度
 */
- (void)setMotionDetectSensityvityExample {
    [[GWP2PClient sharedClient] setDeviceMotionDetetionSensitivity:3 withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 增加某预置位
 */
- (void)addDevicePresetPositionExample {
    [[GWP2PClient sharedClient] operateDevicePresetPositionWithOperationType:GWPresetPositionOperationTypeSet presetPositionIndexArray:@[@(0)] deviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}
/**
 转向某预置位
 */
- (void)operateDevicePresetPositionExample {
    [[GWP2PClient sharedClient] operateDevicePresetPositionWithOperationType:GWPresetPositionOperationTypeTurnTo presetPositionIndexArray:@[@(0)] deviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 获取设备定时布撤防数据,普通布防只是布防与不布防的操作,定时布防有很多数据,参见 GWSheduleDefencesModel
 */
- (void)getDeviceSheduleDefenceDataExample {
    [[GWP2PClient sharedClient] getDeviceSheduleDefenceDataWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 AP模式下设置设备wifi密码, 手机必须连接设备发出的wifi
 */
- (void)setDeviceWifiPasswordInAPModeExample {
    [[GWP2PClient sharedClient] setDeviceWifiPassword:@"要设备的密码" inAPModeWithCompletionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 获取多个用户或设备的在线状态
 */
- (void)getDevicesStatusExample {
    NSLog(@"getDevicesStatusExample");
    [[GWP2PClient sharedClient] getDevicesOrUersStatusWithDeviceIDs:@[@"4170345", self.deviceModel.deviceID] completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}


/**
 获取一个设备的多项状态信息
 */
- (void)getMulDevicesStatusExample {
    NSLog(@"getMulDevicesStatusExample %@ %@", self.deviceModel.deviceID, self.deviceModel.devicePassword);
    [[GWP2PClient sharedClient] getMultipleDeviceStatusWithDeviceID:self.deviceModel.deviceID password:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}


/**
 布防操作
 */
- (void)defenceOperationExample {
    NSLog(@"defenceOperationExample");
    [[GWP2PClient sharedClient] setDeviceDefenceState:YES withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}


/**
 获取设备版本信息
 */
- (void)getDeviceVersionExample {
    NSLog(@"getDeviceVersionExample");
    
    [[GWP2PClient sharedClient] getDeviceInfomationWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];

}

/**
 初始化设备密码
 注意:手机与设备必须在同一局域网内,否则初始化不成功
 */
- (void)initDevicePasswordExample {
    [[GWP2PClient sharedClient] setDeviceInitialPassword:@"qwe123" withDeviceID:self.deviceModel.deviceID completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

/**
 设置设备管理员密码
 */
- (void)setDeviceAdministratorPasswordExample {
    [[GWP2PClient sharedClient] setDeviceAdministratorPasswordWithOldPassword:self.deviceModel.devicePassword newPassword:@"qwe123" deviceID:self.deviceModel.deviceID completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}
/**
 设置设t访客密码
 */
- (void)setDeviceVisitorPasswordExample {
    
    [[GWP2PClient sharedClient] setDeviceVisitorPassword:@"qwrqw121" withAdministratorPassword:self.deviceModel.devicePassword deviceID:self.deviceModel.deviceID completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
    
  
}

/**
 设置报警邮箱
 */
- (void)setDeviceAlarmEmailExample {
    [[GWP2PClient sharedClient] setDeviceAlarmEmail:@"test@qq.com" withDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword isSupportSMTP:YES SMTPServer:@"smtp.qq.com" SMTPPort:465 SMTPUser:@"123123" SMTPPassword:@"1231231" encryptType:GWP2PAlarmEmailEncryptTypeNone emailTitle:@"报警时发送邮件的标题" emailContent:@"报警时发送邮件的内容" completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}
/**
 获取报警邮箱
 */
- (void)getDeviceAlarmEmailExample {
    [[GWP2PClient sharedClient] getDeviceAlarmEmailWithDeviceID:self.deviceModel.deviceID  devicePassword:self.deviceModel.devicePassword completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}
/**
 设备报警时,解除报警邮箱绑定
 */
- (void)unbindDeviceCurrentAlarmAccountExample {
    [[GWP2PClient sharedClient] unbindDeviceCurrentAlarmAccountWithDeviceID:self.deviceModel.deviceID devicePassword:self.deviceModel.devicePassword operationType:GWUnbindAlarmAccountOperationTypeUnbindAlarmAccount completionBlock:^(GWP2PClient *client, BOOL success, NSDictionary<NSString *,id> *dataDictionary) {
        [self outputLog:dataDictionary success:success];
    }];
}

- (void)testExample {
    NSLog(@"testExample");
}


#pragma mark - 日志
- (void)outputLog:(id)log success:(BOOL)success {
    NSLog(@"%@\n",log);
    dispatch_async(dispatch_get_main_queue(), ^{
        NSUInteger oldLength = self.logTextView.text.length;
        
        self.logTextView.text = [[self.logTextView.text stringByAppendingString:[NSString stringWithFormat:@"\n\n请求结果:%@ 时间:%@",@(success),[self.formatter stringFromDate:[NSDate date]]]] stringByAppendingString:[NSString stringWithFormat:@"\n%@",log]];
        
        NSUInteger newLength = self.logTextView.text.length;
        
        [self.logTextView scrollRangeToVisible:NSMakeRange(oldLength, newLength-oldLength)];
    });
}

- (IBAction)clearLogAction:(UIButton *)sender {
    
    self.logTextView.text = @"";
}

- (NSDateFormatter *)formatter {
    if (!_formatter) {
        _formatter = [[NSDateFormatter alloc] init];
        _formatter.dateFormat = @"yyyy-MM-dd HH:mm:ss";
        _formatter.timeZone = [NSTimeZone systemTimeZone];
    }
    
    return _formatter;
}

#pragma mark - UITableViewDataSource
- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section {
    if (tableView == self.categoryTableView) {
        return self.examples.count;
    }
    
    if (tableView == _exampleTableView) {
        return ((NSArray *)[self.examples[self.categoryTableView.indexPathForSelectedRow.row] valueForKey:@"example"]).count;
    }
    
    return 1;
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath {
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:@"cell"];
    
    if (!cell) {
        cell = [[UITableViewCell alloc] initWithStyle:UITableViewCellStyleDefault reuseIdentifier:@"cell"];
        cell.textLabel.font = [UIFont systemFontOfSize:13.0];
    }
    
    if (tableView == self.categoryTableView) {
        cell.textLabel.text = [self.examples[indexPath.row] valueForKey:@"category"];
    }
    
    if (tableView == self.exampleTableView) {
        SettingExample *example = [self.examples[self.categoryTableView.indexPathForSelectedRow.row] valueForKey:@"example"][indexPath.row];
        cell.textLabel.text = example.title;
        cell.backgroundColor = [UIColor clearColor];
    }
    
    return cell;
}


#pragma mark - UITableViewDelegate
- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath {
    if (tableView == self.categoryTableView) {
        [self.exampleTableView reloadData];
    }
    
    if (tableView == self.exampleTableView) {
        [tableView deselectRowAtIndexPath:indexPath animated:YES];
        SettingExample *example = [self.examples[self.categoryTableView.indexPathForSelectedRow.row] valueForKey:@"example"][indexPath.row];
        [self performSelector:example.selector withObject:nil afterDelay:0.0];
    }
}


@end
