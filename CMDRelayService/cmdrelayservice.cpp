// CMDRelayService.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//
#include <boost/interprocess/ipc/message_queue.hpp>   
#include <iostream>   
#include <vector>  
#include "inputcmd.pb.h"
#include "json/json.h"
#include "renderbase/util/jsonutil.h"
#include <windows.h> //windows.h head file must located here.

using namespace boost::interprocess;
const std::string MQName = "rendercmdmq";
const int MaxMsgNumber = 100;
const int MaxMsgSize = 1024;

void deserialize(std::string& serialized, int& length, std::string& str) {
    std::istringstream iss(serialized);
    iss.read(reinterpret_cast<char*>(&length), sizeof(length));
    str.resize(length);
    iss.read(&str[0], length);
    serialized = serialized.substr(sizeof(length) + length);
}

//鼠标移动到指定位置  
void MouseMove(int x, int y)
{
    double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;//获取屏幕分辨率宽度  
    double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;//获取屏幕分辨率高度  
    double fx = x * (65535.0f / fScreenWidth);
    double fy = y * (65535.0f / fScreenHeight);
    INPUT  Input = { 0 };
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    Input.mi.dx = fx;
    Input.mi.dy = fy;
    SendInput(1, &Input, sizeof(INPUT));
}

void MouseHoverMove(int x, int y)
{
    double fScreenWidth = ::GetSystemMetrics(SM_CXSCREEN) - 1;//获取屏幕分辨率宽度  
    double fScreenHeight = ::GetSystemMetrics(SM_CYSCREEN) - 1;//获取屏幕分辨率高度  
    double fx = x * (65535.0f / fScreenWidth);
    double fy = y * (65535.0f / fScreenHeight);
    INPUT  Input = { 0 };
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_MOVE | MOUSEEVENTF_ABSOLUTE;
    Input.mi.dx = fx;
    Input.mi.dy = fy;
    SendInput(1, &Input, sizeof(INPUT));
}

//鼠标左键按下  
void MouseLeftDown()
{
    INPUT  Input = { 0 };
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
    SendInput(1, &Input, sizeof(INPUT));
}

//鼠标左键放开  
void MouseLeftUp()
{
    INPUT  Input = { 0 };
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_LEFTUP;
    SendInput(1, &Input, sizeof(INPUT));

}

//鼠标右键按下
void MouseRightDown()
{
    INPUT  Input = { 0 };
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    SendInput(1, &Input, sizeof(INPUT));
}

//鼠标右键放开    
void MouseRightUp()
{
    INPUT  Input = { 0 };
    Input.type = INPUT_MOUSE;
    Input.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    SendInput(1, &Input, sizeof(INPUT));
}

void KeyDown(std::string name, WORD key)
{
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    SendInput(1, &input, sizeof(INPUT));
}

void KeyUp(std::string name, WORD key)
{
    INPUT input = { 0 };
    input.type = INPUT_KEYBOARD;
    input.ki.wVk = key;
    input.ki.dwFlags = KEYEVENTF_KEYUP;
    SendInput(1, &input, sizeof(INPUT));
}

void handleCMD(const std::string& content) 
{
    if (content.size() == 0) {
        std::cout << "handleCMD content.length() == 0 " << std::endl;
        return;
    }
    std::map<std::string, Json::Value> values = JsonUtil::fromString(content);
    if (values.size() == 0) {
        std::cout << "handleCMD parse cmd failed from json." << std::endl;
        return;
    }
    int type = JsonUtil::getJsonUInt32(values["type"]);
    if (type == render::CMDType::CMD_KEY) {
        int keycode = JsonUtil::getJsonUInt32(values["keycode"]);
        std::string name = JsonUtil::getJsonString(values["keyname"]);
        int action = JsonUtil::getJsonUInt32(values["action"]);
        std::cout << "handleCMD, CMD_KEY action: " << action << ", keycode:" << keycode << ", keyname: " << name << ", type: " << type << std::endl;
        if (action == render::KeyActionType::KEY_DOWN) {
            KeyDown(name, keycode);
        }
        else if (action == render::KeyActionType::KEY_UP) {
            KeyUp(name, keycode);
        }
        else {
            std::cout << "unkonw key action type: " << type << ", content: " << content << std::endl;
        }
    }
    else if (type == render::CMDType::CMD_MOUSE) {
        int action = JsonUtil::getJsonUInt32(values["action"]);
        int x = JsonUtil::getJsonUInt32(values["x"]);
        int y = JsonUtil::getJsonUInt32(values["y"]);
        std::cout << "handleCMD, CMD_MOUSE action: " << action << ", x:" << x << ", y: " << y << ", type: " << type << std::endl;
        if (action == render::MouseActionType::MOUSE_LEFT_DOWN) {
            MouseLeftDown();
        }
        else if (action == render::MouseActionType::MOUSE_LEFT_UP) {
            MouseLeftUp();
        }
        else if (action == render::MouseActionType::MOUSE_MOVE) {
            MouseMove(x, y);
        }
        else if (action == render::MouseActionType::MOUSE_RIGHT_DOWN) {
            MouseRightDown();
        }
        else if (action == render::MOUSE_RIGHT_UP) {
            MouseRightUp();
        }
        else if (type == render::MouseActionType::MOUSE_HOVERMOVE) {
            int action = JsonUtil::getJsonUInt32(values["action"]);
            int x = JsonUtil::getJsonUInt32(values["x"]);
            int y = JsonUtil::getJsonUInt32(values["y"]);
            std::cout << "handleCMD, CMD_HOVERMOVE action: " << action << ", x:" << x << ", y: " << y << ", type: " << type << std::endl;
            MouseHoverMove(x, y);
        }
        else {
            std::cout << "unkonw mouse action type: " << type << ", content: " << content << std::endl;
        }
    }
   
    else {
        std::cout << "unkonw action type: " << type << ", content: "<< content<<std::endl;
    }
}

int main()
{
    try {
        //Open a message queue.   
        message_queue mq(open_only, MQName.c_str());

        unsigned int priority = 0;
        message_queue::size_type recvd_size = 0;

        //Receive 100 numbers   
        while(true) {
            int count = mq.get_num_msg();
            //for (int i = 0; i < count; i++) {
                char data[MaxMsgSize] = { 0 };
                recvd_size = 0;
                //mq.receive(data, MaxMsgSize, recvd_size, priority);
                bool ret = mq.try_receive(data, MaxMsgSize, recvd_size, priority);
                //if (!ret) {
                //    std::cout << "try receive data from mq failed." << std::endl;
                //}
                if (recvd_size > 0) {
                    render::Message msg;
                    msg.ParseFromString(data);
                    std::string content = msg.content();
                    handleCMD(content);
                    std::cout << "recvd_size:"<< recvd_size<<", recv input content: " << content << std::endl;
                }
                else {
                    Sleep(10);
                }
            //}
        }
    }
    catch (interprocess_exception& ex) {
        message_queue::remove(MQName.c_str());
        std::cout << "receive data from mq exception: " << ex.what() << std::endl;
        return 1;
    }
    std::cout << "cmdrelayservice exit, try to remove mq." << std::endl;
    message_queue::remove(MQName.c_str());
    return 0;
}