//
//  MonitorController.m
//  GWP2P
//
//  Created by apple on 17/5/24.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import "MonitorController.h"
#import "DeviceModel.h"

@interface MonitorController () <GWP2PVideoPlayerProtocol>
@property (nonatomic, strong) DeviceModel *deviceModel;
@property (nonatomic, strong) GWP2PVideoPlayer *player;

@property (weak, nonatomic) IBOutlet UIView *playView;
@property (weak, nonatomic) IBOutlet UIActivityIndicatorView *activityView;
@property (weak, nonatomic) IBOutlet UIImageView *screenShotView;
@property (weak, nonatomic) IBOutlet NSLayoutConstraint *playViewRatio;

@property (weak, nonatomic) IBOutlet UIToolbar *PTZDirectionBar;
@end

@implementation MonitorController

- (void)viewDidLoad {
    [super viewDidLoad];
    self.navigationItem.title = _deviceModel.deviceID;
    self.automaticallyAdjustsScrollViewInsets = NO;
    self.navigationController.interactivePopGestureRecognizer.enabled = NO;
    
    //获取播放器比例
    CGFloat ratio = [self raitoFromSubtype:_deviceModel.deviceSubtype];
    [self.playViewRatio setValue:@(ratio) forKey:@"multiplier"];
    
    //添加播放器
    self.player = [[GWP2PVideoPlayer alloc] init];
    self.player.delegate = self;
    self.player.viewController.view.backgroundColor = [UIColor redColor];
    [self.playView addSubview:self.player.viewController.view];
#warning 下面这句话必须要加，否则监控画面不能显示
    [self addChildViewController:self.player.viewController];
    
    [self.playView bringSubviewToFront:self.activityView];
    [self.playView bringSubviewToFront:self.screenShotView];
    self.screenShotView.hidden = YES;
}

- (void)viewDidLayoutSubviews {
    [super viewDidLayoutSubviews];
    self.player.viewController.view.frame = self.playView.bounds;
}

#pragma mark - 播放画面比例
- (CGFloat)raitoFromSubtype:(GWP2PDeviceIPCSubtype)subtype {
    GWP2PDeviceVideoRatio ratio = [GWP2PDevice getVideoRatioWithSubtype:subtype];
    if (ratio==GWP2PDeviceVideoRatio16X9) {
        return 16.0 / 9;
    }
    if (ratio==GWP2PDeviceVideoRatio1X1) {
        return 1/1;
    }
    if (ratio==GWP2PDeviceVideoRatio4X3) {
        return 4.0/3;
    }
    return 16.0/9;
}

- (void)dealloc {
    NSLog(@"%s %d",__func__,__LINE__);
    [self.player p2pStop];
}

#pragma mark - 通用功能
- (IBAction)call:(id)sender {
    __weak typeof(self) weakSelf = self; //这里的几个代码块都要用弱引用
    [self.activityView startAnimating];
    dispatch_async(dispatch_get_global_queue(0, 0), ^{
        [weakSelf.player p2pCallDeviceWithDeviceId:_deviceModel.deviceID password:_deviceModel.devicePassword definition:GWP2PPTZDefinitionSD calling:^(NSDictionary *parameters) {
            NSLog(@"[p2pCallDevice-Calling],paras=%@",parameters);
        } accept:^(NSDictionary *parameters) {
            NSLog(@"[p2pCallDevice-Accept],paras=%@",parameters);
        } reject:^(GWP2PCallError error, NSString *errorCode) {
            NSLog(@"[p2pCallDevice-Reject],error=%ld,errorCode=%@",(unsigned long)error, errorCode);
            dispatch_async(dispatch_get_main_queue(), ^{
                [weakSelf.activityView stopAnimating];
            });
        } ready:^{
            NSLog(@"[p2pCallDevice-Ready] %@",[NSThread currentThread]);
            dispatch_async(dispatch_get_main_queue(), ^{
                [weakSelf.activityView stopAnimating];
            });
            //全景设备，180全景默认电视广角，360全景默认显示混合模式
            GWP2PFisheyeType fisheyeType = [GWP2PDevice getFisheyeTypeWithSubtype:weakSelf.deviceModel.deviceSubtype];
            if (fisheyeType == GWP2PFisheyeType180) {
                weakSelf.player.showMode = PM_WIDE_ANGLE;
            } else if (fisheyeType == GWP2PFisheyeType360) {
                weakSelf.player.showMode = PM_MIX;
            } else {
                //其它设备用默认的显示，没有形变
            }
        }];
    });
}

- (IBAction)stop:(id)sender {
    [self.player p2pStop];
}

- (IBAction)talkSwitch:(id)sender {
    static BOOL talkSwitch = YES;
    talkSwitch = !talkSwitch;
    NSLog(@"talkSwitch %d",talkSwitch);
    
    [self.player p2pEnableSpeak:talkSwitch];
    
}

- (IBAction)screenShot:(id)sender {
    __weak typeof(self) weakself = self;
    //todo: 不停截图内存升高
    [self.player p2pScreenshot:^(UIImage *screenshot, NSTimeInterval timeInterval) {
        dispatch_async(dispatch_get_main_queue(), ^{
            //weakself.screenShotView.image = nil;
            weakself.screenShotView.image = screenshot;
            weakself.screenShotView.hidden = NO;
            dispatch_after(dispatch_time(DISPATCH_TIME_NOW, (int64_t)(3.0 * NSEC_PER_SEC)), dispatch_get_main_queue(), ^{
                weakself.screenShotView.hidden = YES;
            });
            
        });
    }];
}

- (IBAction)mute:(id)sender {
    static BOOL isMute = NO;
    isMute = !isMute;
    self.player.mute = isMute;
}

- (IBAction)gestureSwitch:(UIBarButtonItem *)sender {
    //新全景模式(半球,圆柱,画卷,四分,混合,广角六个模式)下的手势禁用无效
    self.player.enableGesture = !self.player.enableGesture;
}

#pragma mark - 设置分辨率，鱼眼不支持
- (IBAction)PTZChangeDenifition:(UIBarButtonItem *)sender {
    
    switch (sender.tag) {
        case 0:
            [self.player p2pSetDefinition:GWP2PPTZDefinitionLD];
            break;
        case 1:
            [self.player p2pSetDefinition:GWP2PPTZDefinitionSD];
            break;
        case 2:
            [self.player p2pSetDefinition:GWP2PPTZDefinitionHD];
            break;
            
        default:
            break;
    }
}

#pragma mark - 云台控制上下左右，鱼眼不支持
- (IBAction)PTZTurnToDirection:(UIBarButtonItem *)sender {
    switch (sender.tag) {
        case 0:
            [self.player p2pTurnDirection:GWP2PPTZDirectionUp];
            break;
        case 1:
            [self.player p2pTurnDirection:GWP2PPTZDirectionLeft];
            break;
        case 2:
            [self.player p2pTurnDirection:GWP2PPTZDirectionDown];
            break;
        case 3:
            [self.player p2pTurnDirection:GWP2PPTZDirectionRight];
            break;
            
        default:
            break;
    }
}

#pragma mark - 录制MP4，全部设备都支持
- (IBAction)startRecordMP4:(UIBarButtonItem *)sender {
    NSString *savePath = [self getRecordFilePathWithDeviceId:self.deviceModel.deviceID];
    [self.player startRecordWithSavePath:savePath saveToPhotosAlbum:YES eventHandler:^(MP4RecordEvent stopEvent) {
        switch (stopEvent) {
            case MP4RecordEventStart:
                NSLog(@"录像开始（初始化需要少量时间等待关键帧）");
                break;
            case MP4RecordEventStop:
                NSLog(@"主动调用了stopRecord");
                break;
            case MP4RecordEventRatioChanged:
                NSLog(@"切换了监控清晰度，录像停止（正常保存）");
                break;
                
            default:
                break;
        }
    }];
}

- (IBAction)stopRecordMP4:(UIBarButtonItem *)sender {
    [self.player stopRecord];
}

- (NSString*)getRecordFilePathWithDeviceId:(NSString*)deviceId {
    NSString *rootPath = [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) objectAtIndex:0];
    
    
    NSTimeInterval timeInterval = [[NSDate date] timeIntervalSince1970];
    
    NSString *savePath = [NSString stringWithFormat:@"%@/recordMP4/%@",rootPath,deviceId];

    NSFileManager *manager = [NSFileManager defaultManager];
    if(![manager fileExistsAtPath:savePath]){
        [manager createDirectoryAtPath:savePath withIntermediateDirectories:YES attributes:nil error:nil];
    }
    NSString* fullPath = [NSString stringWithFormat:@"%@/%ld.mp4",savePath,(long)timeInterval];
    return fullPath;
}

#pragma mark - 切换全景模式，建议(普通IPC不要做,360全景设备做半球,圆柱,画卷,四分,混合五个模式,180全景设备做广角一个模式)
- (IBAction)switchPanoMode:(UIBarButtonItem *)sender {
    //全景变化现在支持所有设备，但是在不恰当的设备上使用画面会看起来严重变形
    PanoMode mode = self.player.showMode;
    mode++;
    if (mode > PM_QUAD) {
        mode = PM_HALF_SPHERE;
    }
    self.player.showMode = mode;
}

#pragma mark - 代理回调测试
- (void)p2pPlayer:(GWP2PPlayer *)player recieveGestureRecognizer:(UIGestureRecognizer *)gesture {
    NSLog(@"-----delegate---recieveGestureRecognizer");
}

- (void)p2pVideoPlayer:(GWP2PVideoPlayer *)player numberOfAudiencesChange:(NSUInteger)currentNumber {
    NSLog(@"-----delegate---numberOfAudiencesChange");
    
}

@end
