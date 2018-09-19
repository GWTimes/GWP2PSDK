//
//  GWP2PInterface.h
//  P2PSDK
//
//  Created by apple on 17/2/6.
//  Copyright © 2017年 gwell. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "P2PCInterface.h"


#ifdef DEBUG
#define GWLog(fmt, ...) NSLog((@"\n%s [Line %d] " fmt @"\n "), __PRETTY_FUNCTION__, __LINE__, ##__VA_ARGS__);
#else
#define GWLog(...)
#endif

@class GWP2PInterface;

#pragma mark -

@protocol GWP2PInterfaceProtocol <NSObject>

/**
 发送消息状态回调
 @param messageID  消息编号
 @param distanceID 对方(接收方)ID
 @param error      消息的发送状态(错误代码)
 */
- (void)p2pInterface:(GWP2PInterface *)p2pInterface receivedSendedMessageAckWithMessageID:(DWORD)messageID distanceID:(DWORD)distanceID error:(DWORD)error;

/**
 收到远程消息回调
 @param maessage           消息数据
 @param deviceID           对方(发送方)ID
 @param hasCheckedPassword 是否已经验证密码。true:已验证;false:未验证;
 @param messageSize        消息长度(以字节为单位)
 */
- (void)p2pInterface:(GWP2PInterface *)p2pInterface receivedRemoteMessage:(void *)maessage withDeviceID:(DWORD)deviceID hasCheckedPassword:(BOOL)hasCheckedPassword messageSize:(DWORD)messageSize;

/**
 收到从P2P服务器服务器获取设备及好友用户信息回调
 
 @param pFriends  设备及好友用户信息
 */
- (void)p2pInterface:(GWP2PInterface *)p2pInterface didGetDevicesOrFriendUsersStatusFromP2PServerWithFriendsInfomation:(sFriendsType *)pFriends;

/**
 收到从index服务器获取设备及好友用户信息回调
 
 @param pFriends  设备及好友用户信息
 */
- (void)p2pInterface:(GWP2PInterface *)p2pInterface didGetDevicesOrFriendUsersStatusFromIndexServerWithFriendsInfomation:(sFriendsTypeV2 *)pFriends;

/**
 下载文件回调

 @param deviceID  设备ID
 @param filename  文件路径
 @param errorCode 错误码
 */
- (void)p2pInterface:(GWP2PInterface *)p2pInterface receivedDownloadRemoteFileACKWithDeviceID:(DWORD)deviceID fileName:(char *)filename erroeCode:(DWORD)errorCode;

@end

#pragma mark - 呼叫
@protocol GWP2PInterfaceCallProtocol <NSObject>

/**
 设备正在呼叫的回调,包括主动呼叫和NPC被动呼叫
 @param parameters 回调传递的参数,详见struct sP2PInitPrm参数的注释
 */
- (void)p2pInterface:(GWP2PInterface *)p2pInterface callingWithParameters:(sCallingPrmType *)parameters
;

/**
 呼叫被拒绝
 @param type      呼叫类型:主动或者被动呼叫
 @param errorOption   断开的原因枚举,详见CALL_ERROR_枚举
 @param errorCode     服务器新定义的错误码,非0时一般需要在UI呈现给用户 详见http://gwellserver2:8008

 */
- (void)p2pInterface:(GWP2PInterface *)p2pInterface rejectCallWithType:(DWORD)type errorOption:(DWORD)errorOption errorCode:(DWORD)errorCode;

/**
 呼叫被接受
 @param type        呼叫类型:主动或者被动呼叫
 @param paratmeters 回调的参数,暂无文档和详细注释,需参考原代码
 */
- (void)p2pInterface:(GWP2PInterface *)p2pInterface accepteCallWithType:(DWORD)type paratmeters:(DWORD *)paratmeters;

/**
 呼叫接受后通道连接成功
 */
- (void)p2pInterfaceCallConnectionReady:(GWP2PInterface *)p2pInterface;


@end


@protocol GWP2PInterfaceUserCommandProtocol <NSObject>


/**
 收到用户设置/信息等回调数据

 @param command      指令编号
 @param option       选项
 @param data         数据
 @param dataLength   数据长度
 */
- (void)p2pInterface:(GWP2PInterface *)p2pInterface receiveUserDataWithCommand:(DWORD)command option:(DWORD)option data:(DWORD *)data dataLength:(DWORD)dataLength;

@end


/**
 音视频H264+AMR格式数据回调
 */
@protocol GWP2PInterfaceAVProtocol <NSObject>

@optional
/**
 音视频头信息
 由于硬件（嵌入式）原因，部分设备回调的视频宽高不准确，所以在录制MP4等情况时不使用这个信息

 @param pAVInfo 音视频信息
 */
- (void)p2pInterface:(GWP2PInterface *)p2pInterface recvAVHeader:(sAVInfoType *)pAVInfo;


/**
 回调P2P内部通过FFMpeg解码后的视频分辨率，比recvAVHeader返回的准确，目前主要用于MP4录制，不需要额外再解码宽高

 @param videoWidth 视频宽度
 @param videoHeight 视频高度
 */
- (void)p2pInterface:(GWP2PInterface *)p2pInterface recvVideoWidth:(int)videoWidth videoHeight:(int)videoHeight;


/**
 音视频数据

 @param pAudioData 音频数据
 @param dwAudioLen 音频长度
 @param dwFrames 音频帧数
 @param u64APTS 音频pts
 @param pVideoData 视频数据
 @param dwVideoLen 视频长度
 @param u64VPTS 视频pts
 */
- (void)p2pInterface:(GWP2PInterface *)p2pInterface recvAVData:(BYTE *)pAudioData audioLen:(DWORD) dwAudioLen frames:(DWORD)dwFrames APTS:(UINT64)u64APTS videoData:(BYTE *)pVideoData videoLen:(DWORD)dwVideoLen VPTS:(UINT64)u64VPTS;

@end


/**
 封装P2PCInterface的类
 */
@interface GWP2PInterface : NSObject

@property (weak, nonatomic) id<GWP2PInterfaceProtocol> delegate;
@property (weak, nonatomic) id<GWP2PInterfaceCallProtocol> callDelegate;
@property (weak, nonatomic) id<GWP2PInterfaceUserCommandProtocol> userCommandDelegate;
@property (weak, nonatomic) id<GWP2PInterfaceAVProtocol> avDelegate;

//yooseeInitPrm、yooseeDecPrm、p2pSystemMsgNotify用于Yoosee集成SDK过渡，兼容Yoosee旧代码，让Yoosee的P2PClient能收到函数回调
@property (nonatomic, assign) sP2PInitPrm yooseeInitPrm;
@property (nonatomic) sRecAndDecPrm yooseeDecPrm; //用不到，暂时保留相关代码

#pragma mark - 单例
/**
 *  获取单例
 */
+ (instancetype)sharedInterface;

#pragma mark - 连接服务器
- (BOOL)connectWithAccount:(NSString *)account
                  codeStr1:(NSString *)codeStr1
                  codeStr2:(NSString *)codeStr2
                sessionID1:(NSString *)sessionID1
                sessionID2:(NSString *)sessionID2
               customerIDs:(NSArray <NSNumber *> *)customerIDsArray
                appVersion:(NSString *)appVersion
           messageLanguage:(NSString *)messageLanguage
       lastSystemMessageID:(NSString *)lastSystemMessageID
    lastAuthorityMessageID:(NSString *)lastAuthorityMessageID;

- (void)disconnect;

- (DWORD)linkStatus;

#pragma mark - 发送消息
/**
 发送远程消息

 @param deviceID        对方(接收方)ID
 @param devicePassword  对方(接收方)的访问密码(某些消息不需要密码,则填 0)
 @param messageID       消息编号。用来区分同一发送者发出的不同消息;(建议使用一个全局变量,每发送一条编号自增 1)
 @param message         消息的内容
 @param messageSize     消息的长度(字节为单位),不能超过 1024
 @param pPushMesg       暂时填NULL
 @param dwPushMesgLen   暂时填0
 @param dwType          暂时填0

 @return 命令入队是否成功。 入队成功不代表真正发送到了设备端,只是进入了本机的发送队列里。是否真正 发送成功需要从回调函数vSendMessageAck()中获取
 */
- (BOOL)sendRemoteMessageWithDeviceID:(DWORD)deviceID
                       devicePassword:(DWORD)devicePassword
                            messageID:(DWORD)messageID
                              message:(void *)message
                          messageSize:(DWORD)messageSize
                          pushMessage:(char *)pPushMesg
                    pushMessageLength:(DWORD)dwPushMesgLen
                                 type:(DWORD)dwType;

#pragma mark - 获取好友用户及设备列表在线状态等信息
/**
 index服务器,获取好友用户及设备列表在线状态等信息
 
 @param tables  设备ID数组
 @param count   设备ID个数
 */
- (void)getDevicesOrFriendUsersStatusFromIndexServerWithIDsTable:(DWORD[])tables IDcount:(DWORD)count;

/**
 P2P服务器,获取好友用户及设备列表在线状态等信息
 
 @param tables  设备ID数组
 @param count   设备ID个数
 */
- (void)getDevicesOrFriendUsersStatusFromP2PServerWithIDsTable:(DWORD[])tables IDcount:(DWORD)count;

#pragma mark - 下载文件
- (BOOL)downloadFileWithDeviceID:(unsigned int)deviceID
                  devicePassword:(unsigned int)devicePassword
                  remoteFilePath:(char *)remoteFilePath
                   localFilePath:(char *)localFilePath;


#pragma mark - 设备呼叫(监控/对讲/回放)
/**
 呼叫设备
 @param u64Id       设备id
 @param fgSuperCall KTRUE:监控,  KFALSE : 视频电话。
 @param dwPassword  加密后的设备密码
 @param pdwPrm      参数
 @param strPushMesg cString类型的消息,默认传空
 */
- (void)p2pCallWithId:(UInt64)u64Id
          fgSuperCall:(KBOOL)fgSuperCall
             password:(DWORD)dwPassword
            parameter:(DWORD *)pdwPrm
          pushMessage:(char *)strPushMesg
       useVideoStream:(BOOL)useVideoStream;

/**
 主动挂断
 */
- (void)p2pHangup;

/**
 接收设备的通话请求
 @param pdwPrm 设备端定义的参数
 */
- (void)p2pAcceptWithParameter:(DWORD *)pdwPrm;



/**
 在CallConnectionReady后,循环调用此方法获取视频帧

 @return GAVFrame
 */
- (GAVFrame *)p2pGetVideoFrameToDisplay;

/**
 获取视频流缓存
 
 @param buffer 视频数据
 @param size 长度
 @param pts pts
 @return 是否成功
 */
- (BOOL)p2pGetVideoStreamBuffer:(uint8_t *)buffer size:(uint32_t *)size pts:(uint64_t *)pts;

//GBOOL    fgStartAVEncAndSend(DWORD dwVideoFrameRate);


/**
 开始接收并解码音视频数据
 */
- (void)p2pStartAVRecieveAndDecode;

/**
 开启视频对讲时到对方的传输通道
 @param dwVideoFrameRate 视频帧率,参考Yoosee暂时固定为16
 */
- (void)p2pStartAVEncodeAndSend:(DWORD)dwVideoFrameRate;

#pragma mark - 用户控制命令

/**
 发送用户控制命令 镜头控制/SD卡/获取回放文件等

 @param command      指令编号
 @param option       选项
 @param data         数据
 @param dataLength   数据长度
 */
- (void)p2pSendUserCommand:(DWORD)command option:(DWORD)option data:(BYTE *)data dataLength:(DWORD)dataLength;

#pragma mark - H265解码和录制新增
/**
 视频类型，setter方法会决定解码器选择
 */
@property (nonatomic, assign) int videoType;

/**
 获取到解码后的音视频数据回调，用于录制
 */
@property (nonatomic, copy) void (^getDecodedAVData)(BYTE *videoData, int videoSize, GAVFrame *videoFrame, BYTE *audioData, int audioSize);

@end
