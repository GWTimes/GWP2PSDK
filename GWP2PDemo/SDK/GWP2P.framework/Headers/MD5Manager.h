//
//  MD5Manager.h
//  2cu
//
//  Created by wutong on 15/12/16.
//  Copyright © 2015年 guojunyi. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface MD5Manager : NSObject

/*
函数功能:     密码转换
szPassword:  1～30位字符串
返回:         10位以下的unsigned int型数字
 */
+(unsigned int)GetTreatedPassword:(char*) szPassword;


/*
 函数功能:md5加密 兼容rtsp密码时会用到
 szInputBuffer:     6～30位字符串 (如果输入字符串位数不在6~30之间，或者输入10位以下的纯数字，则不作任何处理，直接返回NO)
 szOutputBuffer:    32个字节的字符串，用来保存md5密码后的数据
 返回:               YES成功加密，结果保存在szOutputBuffer中；NO加密失败
 */
+(BOOL)GetMD5PasswordWithSrc:(char*)szInputBuffer Dst:(char*)szOutputBuffer;


/*
 函数功能:服务器保存的设备密码的解密函数（应用场景：从服务器获取设备列表）
 szSrcData:密文
 szUserID:登陆账号关联的ID
 szOutputBuffer:用于保存明文的缓存，由用户提供
  iLength:用于保存明文的缓存的长度
 返回值:YES成功 NO因输出缓存太小而执行失败
 */
+(BOOL)PassswrodDecrypt:(char*)szSrcData UserID:(char*)szUserID Dst:(char*)szOutputBuffer Len:(unsigned int)iLength;

/*
 函数功能:服务器保存的设备密码的加密函数（应用场景：上传设备列表到服务器）
 szSrcData:明文
 szUserID:登陆账号关联的ID
 szOutputBuffer:用于保存密文的缓存，由用户提供
 iLength:用于保存密文的缓存的长度
 返回值:YES成功 NO因输出缓存太小而执行失败
 */
+(BOOL)PasswordEncrypt:(char*)szSrcData UserID:(char*)szUserID Dst:(char*)szOutputBuffer Len:(unsigned int)iLength;

/*
 函数功能:base64解密,扫描二维码用到。
 */
+(char *)lib_base64_decode:(const char* )data len:(int)data_len;

/**
 加密设备ID，用于绑定主人验证
 */
+ (UInt64)getSecretDeviceIdWithDeviceId:(NSString *)deviceId;
@end
