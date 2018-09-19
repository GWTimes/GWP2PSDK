# GWP2PSDK
GWP2P SDK 是基于技威时代的纯C语言P2P库，使用Objective-C进行封装的一个SDK。屏蔽其内部复杂细节，对外提供较为简洁的API接口，方便第三方应用快速集成智能摄像机等设备的APP功能。

文档连接：http://sdk.yoosee.co/

### 更新日志：

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