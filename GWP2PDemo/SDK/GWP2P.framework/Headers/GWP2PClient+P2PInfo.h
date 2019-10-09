//
//  GWP2PClient+P2PInfo.h
//  GWP2P
//
//  Created by yuguihua on 2019/6/10.
//  Copyright © 2019 apple. All rights reserved.
//

#import <GWP2P/GWP2P.h>

NS_ASSUME_NONNULL_BEGIN

@interface GWP2PClient (P2PInfo)
-(NSString *)getP2PVersion;

/**
 要先初始化p2p库

 @param open 是否打开p2p打印
 */
-(void)setLogLevel:(BOOL)open;

@end

NS_ASSUME_NONNULL_END
