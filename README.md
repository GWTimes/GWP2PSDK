# GWP2PSDK
GWP2P SDK 是基于技威时代的纯C语言P2P库，使用Objective-C进行封装的一个SDK。屏蔽其内部复杂细节，对外提供较为简洁的API接口，方便第三方应用快速集成智能摄像机等设备的APP功能。

文档连接：http://sdk.yoosee.co/

### 更新日志：

2019.08.02

1. 因为SDK的包名与appid和token是进行了绑定了的，运行Demo时请将申请的包名及AppId，AppToken,AppVersion在LoginViewController进行替换，否则将无法进行请求和运行。
2. **为了防止与其它SDK冲突，我们整合了所有静态库，打包成了一个动态库，因此整个SDK只有一个GWP2P.framework，不需要加入任何依赖**
3. P2P内核更新至3.0版本，支持监控秒连功能（前提是设备固件也必须是p2p3.0的，并且要调用接口获取设备列表在线状态）
4. 接口更新：所有接口全面更新至Yoosee最新版本，因此有少量接口有轻微改动
5. 接口简化：整合GWNet和GWP2P；删除Mp4录制类并将功能整合至播放器类中
6. 修复bug，提高稳定性
7. GWP2P.framework支持-force_load编译参数，请参考demo的other linker flags进行设置，以防编译不过，推荐不再用-ObjC
8. 因为采用的是动态库所以要在工程-General-Embedded Binaries中添加，动态库上架必须只能用真机库
![image](https://github.com/GWTimes/GWP2PSDK/tree/master/GWP2PDemo/png/embeded.png "不设置工程会报错找不到库文件")
9. 因为新SDK支持2.0和3.0设备，默认监控3.0设备，如果要兼容2.0设备，在监控之前先要获取设备支持的p2p版本号,请调用下面的接口。
- (void)getDevicesOrUersStatusWithDeviceIDs:(NSArray<NSString *> *)deviceIDsArray
completionBlock:(CompletionBlock)completionBlock;


2018.09.19

1. SDK首次提交github，版本1.5.0，上一版1.4.1下载地址：http://doc.cloud-links.net/SDK/iOS/

2. **请注意FFmpeg版本回退至2.7.7，与Yoosee保持兼容，amr库更新支持模拟器，删除额外的静态库，所以建议第三方静态库重新添加一遍！**
3. 支持模拟器调试啦，不过模拟器下声音不能正常播放，暂不解决
4. GWP2P.framework支持-force_load编译参数，推荐不再用-ObjC
5. 监控回放都使用全新的OpenGL全景库，可参考MonitorController，GWPanoSDK被废弃
6. 新增SimpleConfig配网方式，内置在声波配网接口中
7. 全新的p2p库内核，p2p秒上线

### 补充说明：

1. 未来将加快SDK的发布节奏，如果有什么问题可在Issues中反馈，如果比较急的问题可联系客服。
2. 目前已将全景功能全面集成在了GWP2P中，废弃掉了GWPanoSDK，未来将把GWNet集成进GWP2P，实现技威静态库的统一。