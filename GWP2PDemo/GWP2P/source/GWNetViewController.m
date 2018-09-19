//
//  GWNetViewController.m
//  GWP2P
//
//  Created by USER on 2018/4/19.
//  Copyright © 2018年 gwell. All rights reserved.
//

#import "GWNetViewController.h"
#import "GWSharingViewController.h"



@interface GWNetViewController ()

@end


@implementation GWNetViewController

- (void)viewDidLoad {
    [super viewDidLoad];
}

- (IBAction)sharing:(id)sender {
    GWSharingViewController *sharingViewController = [[GWSharingViewController alloc] init];
    sharingViewController.hidesBottomBarWhenPushed = YES;
    [self.navigationController pushViewController:sharingViewController animated:YES];
}

@end
