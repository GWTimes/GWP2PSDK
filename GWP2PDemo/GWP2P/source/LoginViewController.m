//
//  LoginViewController.m
//  GWP2P
//
//  Created by zengyuying on 17/5/22.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import "LoginViewController.h"
#import <GWP2P/GWP2P.h>
#import "AppDelegate.h"
#import "LoginResult.h"

@interface LoginViewController ()
@property (weak, nonatomic) IBOutlet UITextField *accountTextField;
@property (weak, nonatomic) IBOutlet UITextField *passwordTextField;

@end

@implementation LoginViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    
    self.accountTextField.text = [self getAccountFromPreference];
    self.passwordTextField.text = [self getPasswordFromPreference];
    
    //初始化GWNet
    [self initGWNet];
    
}


/**
 初始化GWNet
 */
- (void)initGWNet {
    
    //以下GWNet初始化参数仅在本项目测试使用,和bundleID是绑定的,放到其他项目调用GWNet接口会返回errorCode20000
    GWNetSingleton.theAppName = @"GWP2PDemo";
    GWNetSingleton.theAppVersion = @"04.73.00.00";
    GWNetSingleton.theAppId = @"d6bf22be8aed98714beedc1d5297e6b2";
    GWNetSingleton.theAppToken = @"465993f9d8974b448e993889cba499fd5afb94955412f7020a255b0e1b236572";
   
}

- (IBAction)loginBtnAction:(UIButton *)sender {
    //sender.enabled = NO;
    
    [self saveAccountToPreference:self.accountTextField.text];
    [self savePasswordToPreference:self.passwordTextField.text];
    [MBProgressManager showWaitingWithTitle:@"正在登录"];
    
    //登录Web服务器
    NSInteger timeZone = [NSTimeZone systemTimeZone].secondsFromGMT / 60;
    [GWNetSingleton loginWithUserName:self.accountTextField.text withPassword:self.passwordTextField.text withAppleToken:nil withTimeZone:timeZone completion:^(BOOL success, NSString *errorCode, NSString *errorString, NSDictionary *json) {
        [MBProgressManager hideAlert];
        NSLog(@"success:%d errorCode:%@ errorString:%@", success, errorCode, errorString);
        dispatch_async(dispatch_get_main_queue(), ^{
            //sender.enabled = YES;
            //登录成功后连接P2P
            if ([errorCode isEqualToString:@"0"]) {
                
                NSString *p2pAccount = [NSString stringWithFormat:@"0%d",[json[@"UserID"] intValue] & 0x7fffffff];
                NSString *p2pVerifyCode1 = json[@"P2PVerifyCode1"];
                NSString *p2pVerifyCode2 = json[@"P2PVerifyCode2"];
                NSString *sessionID1 = json[@"SessionID"];
                NSString *sessionID2 = json[@"SessionID2"];
                
                
                //这个连接返回的结果只是指本地处理结果。因为和P2P服务器的连接是异步的,需要通过GWP2PClient的linkStatus属性判断当前与P2P服务器的连接状态。
                //linkStatus判断的是和服务器连接的情况.当手机和设备处于同一局域网的情况时，如果调用接口时传的是设备局域网IP地址的最后一位，而不是传设备ID，那么将不走我们的服务器，在局域网内直接把信息发给设备，这时，尽管linkStatus返回的状态异常，也可以成功控制设备。
                NSLog(@"开始连接p2p");
                BOOL success = [[GWP2PClient sharedClient] connectWithAccount:p2pAccount codeStr1:p2pVerifyCode1 codeStr2:p2pVerifyCode2 sessionID1:sessionID1 sessionID2:sessionID2 customerIDs:nil];
                
                if (success) {
                    
                    NSLog(@"连接p2p成功");
                    [LoginResult setAccount:p2pAccount];
                    
                    [LoginResult setP2PVerifyCode1:p2pVerifyCode1];
                    [LoginResult setP2PVerifyCode2:p2pVerifyCode2];
                    [LoginResult setSessionID1:sessionID1];
                    [LoginResult setSessionID2:sessionID2];
                    
                    //跳转到设备列表
                    UITabBarController *tabBarVC = [[UIStoryboard storyboardWithName:@"Main" bundle:nil] instantiateInitialViewController];
                    [self presentViewController:tabBarVC animated:YES completion:nil];;
                }
            }else {
                [MBProgressManager showBriefAlert:@"登录失败"];
            }
        });
        
    }];
    
    
}

- (IBAction)thirdLoginBtnAction:(UIButton *)sender {
    [self saveAccountToPreference:self.accountTextField.text];
    [self savePasswordToPreference:self.passwordTextField.text];
    [MBProgressManager showWaitingWithTitle:@"正在登录"];
    
    //第三方登陆
    NSInteger timeZone = [NSTimeZone systemTimeZone].secondsFromGMT / 60;
    [GWNetSingleton thirdLoginWithPlatformType:@"3" withUnionID:@"test" withUser:@"" withPassword:@"" withAppleToken:@"" withOption:@"3" withStoreID:@"" withNickName:@"老王" timeZone:timeZone completion:^(BOOL success, NSString *errorCode, NSString *errorString, NSDictionary *json) {
        [MBProgressManager hideAlert];
        NSLog(@"errorCode:%@ errorString:%@ json:%@", errorCode, errorString, json);
    }];
}

- (NSString *)getAccountFromPreference {
    return [[NSUserDefaults standardUserDefaults] valueForKey:@"kGWLoginAccount"];
}

- (void)saveAccountToPreference:(NSString *)account {
    [[NSUserDefaults standardUserDefaults] setValue:account forKey:@"kGWLoginAccount"];
}

- (NSString *)getPasswordFromPreference {
    return [[NSUserDefaults standardUserDefaults] valueForKey:@"kGWLoginPassword"];
}

- (void)savePasswordToPreference:(NSString *)password {
    [[NSUserDefaults standardUserDefaults] setValue:password forKey:@"kGWLoginPassword"];
}



@end
