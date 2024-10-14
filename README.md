## 写在前面
源码同步于：https://gitcode.net/invite_link?invite_code=owtD3SgixJWgpcGnJrsk
# 云渲染
过去十多年一直在大厂工作，从事音视频实时通讯和云渲染，云游戏相关工作， 最近闲暇下来， 打算把基础的云游戏架构实现一遍， 供有需要的小伙伴参考， 如果对您有些许帮助，请留下您的小星星，您的鼓励就是我的动力。   

特别说明：  
本项目是以云游戏作为切入点， 实现基于Windows平台的云渲染技术方案， 相关从业者可以根据自己的项目需要， 将前置节点RenderProxy换成您最熟悉的技术栈。  
本项目目标只是为了科普说明云渲染的基础技术流程和技术架构， 不具备商业化应用的成熟度， 如需进一步的技术支持和技术交流， 请B站私信联系作者，或者发邮件：49571654@qq.com， 谢谢。  

## 云游戏技术方案分类
根据我最近几年对云渲染业务形态的学习， 一般将云渲染的技术方案分成3类：  
1）、 零侵入方案， 这也是云渲染的第一个阶段， 表现方式为云桌面， 云手机， 云游戏等；  
2）、 低侵入方案， 比如提供UE/Unity3D引擎的云渲染插件，应用（游戏）厂家在打包的时候需要集成该插件， 从而获得体验更好的云渲染服务；  
3）、 云原生渲染引擎方案， 也就是针对云渲染无限算力的基础上开发的云原生渲染引擎， 从而以云原生的创作方式开发出云原生渲染应用，比如云游戏， 元宇宙应用等；  
本项目主要会覆盖前面2个阶段。  

## 运行时环境说明
由于云渲染当前最成功的商业模式是云游戏， 而云游戏体验最好的是将端游上云， 让更多的非主机用户可以享受到主机3A游戏的快感。    
当前端游主要是Windows平台，所以本开源项目现在只支持Windows平台构建。  
作者的本机环境是：Windows11， Visual Studio 2022， Qt6.7.2， C++17.      

## 微服务部署视频教程
视频放在B站： https://www.bilibili.com/video/BV1Lq1RYKEqJ/
![image](https://github.com/user-attachments/assets/78793100-a643-4174-bb61-1b29d5bc2de2)

## 关键技术
![image](https://github.com/user-attachments/assets/85bea221-798c-4c9d-bf43-7b852ac86904)
## 云游戏技术栈
![image](https://github.com/user-attachments/assets/ec8988fa-377d-4fd2-bc15-1a6fb1803837)

## 微服务架构图
![image](https://github.com/user-attachments/assets/0a1f23fe-05f9-47ac-bee3-18de80c0d46c)


## Sequence图
![image](https://github.com/user-attachments/assets/c582dbe5-e4a5-4a4d-a98c-fb64a586cd07)

## 开发计划
1.0版本：

1）、 renderproxy服务实现， 支持http和tcp接入， 通过http申请游戏资源， 通过tcp传输用户端操作指令（该部分后续可能会用webrtc的datachannel取代，暂时在接入RTC之前用来做测试）

2）、 接入probobuf实现数据传输的序列化和反序列化；

3）、 定义好用户操作指令， 先支持标准的键盘鼠标指令， 游戏手柄待后续有测试设备了再处理；

4）、 cmdrelayservice实现， 用于接收用户操作指令并将指令发送给操作系统， 模拟用户操作；

5）、 grabscreenservice实现， 实现抓屏功能， 支持零侵入的云游戏运营方式；

6）、 支持标准webrtc推拉流整套解决方案， 全端覆盖；

7）、 各部分子服务均支持独立的测试， 并提供相应的测试程序；

