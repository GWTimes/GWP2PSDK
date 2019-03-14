//
//  PlaybackController.m
//  GWP2P
//
//  Created by apple on 17/5/24.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import "PlaybackController.h"
#import "DeviceModel.h"

@interface PlaybackController ()

//xib上控件
@property (weak, nonatomic) IBOutlet UIView *playView;
@property (weak, nonatomic) IBOutlet UILabel *playProgressLabel;
@property (weak, nonatomic) IBOutlet UITextField *seekTimeTextField;

//播放器
@property (nonatomic, strong) GWP2PPlaybackPlayer *playbackPlayer;
@end

@implementation PlaybackController

- (void)viewDidLoad {
    [super viewDidLoad];
  
    self.playbackPlayer = [[GWP2PPlaybackPlayer alloc]init];

    [self.playView addSubview:self.playbackPlayer.viewController.view];
    [self addChildViewController:self.playbackPlayer.viewController];
    
    //添加监听
    [self.playbackPlayer addObserver:self forKeyPath:@"currentTime" options:NSKeyValueObservingOptionNew|NSKeyValueObservingOptionOld context:nil];
    [self.playbackPlayer addObserver:self forKeyPath:@"playbackState" options:NSKeyValueObservingOptionNew|NSKeyValueObservingOptionOld context:nil];
}

#pragma mark 设置播放器的frame
-(void)viewDidLayoutSubviews {

    [super viewDidLayoutSubviews];
    self.playbackPlayer.viewController.view.frame = self.playView.bounds;

}

#pragma mark 自动播放
-(void)viewDidAppear:(BOOL)animated {

    [super viewDidAppear:animated];
    [self playback:[[UIBarButtonItem alloc]init]];

}

//通知监听方法
- (void)observeValueForKeyPath:(NSString *)keyPath ofObject:(id)object change:(NSDictionary<NSKeyValueChangeKey,id> *)change context:(void *)context {
    if ([keyPath isEqualToString:@"currentTime"]) {
        dispatch_async(dispatch_get_main_queue(), ^{
            self.playProgressLabel.text = [NSString stringWithFormat:@"播放进度(单位:微秒μs):%lld/%lld",self.playbackPlayer.currentTime,self.playbackPlayer.totalTime];
        });
    } else if ([keyPath isEqualToString:@"playbackState"]) {
        NSLog(@"回放状态改变:%@",change);
    }
}

#pragma mark 销毁控制器
- (void)dealloc {
    [self.playbackPlayer removeObserver:self forKeyPath:@"currentTime"];
    [self.playbackPlayer removeObserver:self forKeyPath:@"playbackState"];
    
}

#pragma mark 播放
- (IBAction)playback:(UIBarButtonItem *)sender {
    
    [MBProgressManager showWaitingWithTitle:@"正在缓冲"];
    //[self.playbackPlayer setValue:@(GWP2PPlaybackStatePlaying) forKey:@"playbackState"];
    [self.playbackPlayer p2pCallPlaybackFileWithDeviceId:self.deviceModel.deviceID password:self.deviceModel.devicePassword playbackFile:self.fillModelArr[self.currentIndex] calling:^(NSDictionary *parameters) {
        NSLog(@"P2PCallingBlock--%@",parameters);
    } accept:^(NSDictionary *parameters) {
        NSLog(@"P2PAcceptBlock---%@",parameters);
    } reject:^(GWP2PCallError error, NSString *errorCode) {
        NSLog(@"P2PRejectBlock---%@",errorCode);
        [MBProgressManager showBriefAlert:@"缓冲失败"];
    } ready:^{
        NSLog(@"p2pCallPlaybackFile ready");
        [MBProgressManager hideAlert];
    }];
}

#pragma mark 推到某个时间
- (IBAction)seekToTime:(UIButton *)sender {
    uint64_t seekTime = [self.seekTimeTextField.text intValue] * 1000 * 1000;
    [self.playbackPlayer p2pSeekToTime:seekTime];
}

#pragma mark 加速
- (IBAction)fastForward:(UIBarButtonItem *)sender {
    [self.playbackPlayer p2pFastForwardOrCancel];
    
}

#pragma mark 暂停
- (IBAction)pause:(UIBarButtonItem *)sender {
    
    [self.playbackPlayer p2pPauseOrResume];
}

#pragma mark 前一个文件
- (IBAction)previous:(UIBarButtonItem *)sender {
    
    if (self.currentIndex == 0) {

        return;
    } else {
        [self.playbackPlayer p2pPlayPlaybackFile:self.fillModelArr[self.currentIndex - 1]];
        self.currentIndex -= 1;
    }
}

#pragma mark 后一个文件
- (IBAction)next:(UIBarButtonItem *)sender {
    
    if (self.currentIndex >= self.fillModelArr.count - 1) {
 
        return;
    } else {
        [self.playbackPlayer p2pPlayPlaybackFile:self.fillModelArr[self.currentIndex + 1]];
        self.currentIndex += 1;
    }
}



@end
