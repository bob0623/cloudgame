## 写在前面
源码同步于： [https://gitcode.net/derry_123/renderproxy](https://gitcode.net/invite_link?invite_code=owtD3SgixJWgpcGnJrsk)
# 云游戏
an software architecture for cloud game. 

过去十多年一直在大厂工作，从事音视频实时通讯和云渲染，云游戏相关工作， 最近闲暇下来， 打算把基础的云游戏架构实现一遍， 供有需要的小伙伴参考， 如果对您有些许帮助，请留下您的小星星，您的鼓励就是我的动力。

## 微服务部署视频教程
视频放在B站： https://www.bilibili.com/video/BV1Lq1RYKEqJ/
![image](https://github.com/user-attachments/assets/78793100-a643-4174-bb61-1b29d5bc2de2)

## 关键技术
![image](https://github.com/user-attachments/assets/85bea221-798c-4c9d-bf43-7b852ac86904)
## 云游戏技术栈
![image](https://github.com/user-attachments/assets/ec8988fa-377d-4fd2-bc15-1a6fb1803837)

## 微服务架构图
![image](https://github.com/user-attachments/assets/26cb4845-0ec6-4b05-b7e7-53b9c4d11e7d)

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

