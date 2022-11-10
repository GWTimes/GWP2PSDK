//
//  GWP2PClient+Message.h
//  GWP2P
//
//  Created by hongxiaobin on 2022/4/2.
//  Copyright © 2022 apple. All rights reserved.
//

#import <GWP2P/GWP2P.h>

NS_ASSUME_NONNULL_BEGIN

@interface GWP2PClient (Message)

/// 清空消息的id相关信息
+ (void)clearMessageInfo;

/// 设置当前的消息账号
+ (void)setMessageAccount:(NSString *)account;

/// 设置最后的系统消息id
+ (void)setLastSystemMessageId:(long long)messageId;

/// 获取最后的系统消息id
+ (NSString *)getLastSystemMessageId;

/// 设置最后的授权消息id
+ (void)setLastAuthorityMessageId:(long long)messageId;

/// 获取最后的授权消息id
+ (NSString *)getLastAuthorityMessageId;

@end

NS_ASSUME_NONNULL_END
