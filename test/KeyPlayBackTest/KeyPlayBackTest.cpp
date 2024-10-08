#include <windows.h>
#include <iostream>
#include <vector>

HHOOK g_hHook;
HHOOK g_hMouseHook;

struct KeyMsgInfo {
    WPARAM wParam;
    LPARAM lParam;
    DWORD vkCode;
};
struct MouseMsgInfo {
    WPARAM wParam;
    int x;
    int y;
};

std::vector<KeyMsgInfo> oMsgList;
std::vector<MouseMsgInfo> oMouseMsgList;

bool bRecording = false;
HINSTANCE hInstance;
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

void SendRightClick() {
    // 创建一个INPUT结构数组，用于存储鼠标事件
    INPUT mouseInputs[2] = { 0 };

    int x = GetSystemMetrics(SM_CXSCREEN)*3/4;
    int y = GetSystemMetrics(SM_CYSCREEN)*3/4;
    MOUSEINPUT mi;
    mi.dx = 0;
    mi.dy = 0;
    mi.mouseData = 0;
    mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
    // 设置第一个INPUT结构体，表示鼠标按下事件
    mouseInputs[0].type = INPUT_MOUSE;
    //mouseInputs[0].mi = mi;
    mouseInputs[0].mi.dx = 0;
    mouseInputs[0].mi.dy = 0;
    mouseInputs[0].mi.mouseData = 0;
    mouseInputs[0].mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;

    // 设置第二个INPUT结构体，表示鼠标抬起事件
    mouseInputs[1].type = INPUT_MOUSE;
    mi.dwFlags = MOUSEEVENTF_RIGHTUP;
    //mouseInputs[1].mi = mi;
    std::cout << "x: " << mi.dx << " y: " << mi.dy<<std::endl;
    mouseInputs[1].mi.dx = 0;
    mouseInputs[1].mi.dy = 0;
    mouseInputs[1].mi.mouseData = 0;
    mouseInputs[1].mi.dwFlags = MOUSEEVENTF_RIGHTUP;

    // 发送鼠标事件
    SendInput(ARRAYSIZE(mouseInputs), mouseInputs, sizeof(INPUT));
}

void PressKey(WPARAM wParam, LPARAM lParam, DWORD time = 50)
{
    //keybd_event(key, 0, 0, 0);
    //Sleep(time);
    //keybd_event(key, 0, KEYEVENTF_KEYUP, 0);
    HWND hwndFocus = GetForegroundWindow();
    //std::cout << "postmessage: " << wParam << " " << lParam <<" "<< WM_KEYDOWN <<" "<< WM_KEYUP <<" "<< VK_SPACE << std::endl;

    //INPUT inputs[8] = {};
    //ZeroMemory(inputs, sizeof(inputs));

    //inputs[0].type = INPUT_KEYBOARD;
    //inputs[0].ki.wVk = 'A';

    //inputs[1].type = INPUT_KEYBOARD;
    //inputs[1].ki.wVk = 'A';
    //inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;

    //inputs[2].type = INPUT_KEYBOARD;
    //inputs[2].ki.wVk = 'S';

    //inputs[3].type = INPUT_KEYBOARD;
    //inputs[3].ki.wVk = 'S';
    //inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;

    //inputs[4].type = INPUT_KEYBOARD;
    //inputs[4].ki.wVk = 'D';

    //inputs[5].type = INPUT_KEYBOARD;
    //inputs[5].ki.wVk = 'D';
    //inputs[5].ki.dwFlags = KEYEVENTF_KEYUP;

    //inputs[6].type = INPUT_KEYBOARD;
    //inputs[6].ki.wVk = 'W';

    //inputs[7].type = INPUT_MOUSE;
    //inputs[7].ki.wVk = 'W';
    //inputs[7].ki.dwFlags = KEYEVENTF_KEYUP;

    //UINT uSent = SendInput(ARRAYSIZE(inputs), inputs, sizeof(INPUT));
    //if (uSent != ARRAYSIZE(inputs))
    //{
    //    std::cout<< "SendInput failed: "<< HRESULT_FROM_WIN32(GetLastError())<<std::endl;
    //}


    //SendRightClick(); //鼠标当前位置显示右键菜单；

    /*将鼠标移动到屏幕绝对坐标再显示右键菜单， 示例代码绝对坐标是屏幕中央位置*/
    MouseMove((::GetSystemMetrics(SM_CXSCREEN) - 1)/2, (::GetSystemMetrics(SM_CYSCREEN) - 1) / 2);
    MouseRightDown();
    MouseRightUp();
}


void MouseEvent(DWORD dwFlags, DWORD x, DWORD y, DWORD dwData)
{
    //std::cout << "MouseEvent: x:" << x << ", y:" << y << std::endl;
    //mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, dwData, 0);
    //Sleep(3000);
    POINT pt = { x, y };
    ClientToScreen(GetForegroundWindow(), &pt);

    // 移动鼠标
    SetCursorPos(pt.x, pt.y);

    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, dwData, 0);
}

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode >= 0 && wParam == WM_KEYDOWN)
    {
        KBDLLHOOKSTRUCT* pkbhs = (KBDLLHOOKSTRUCT*)lParam;
        if (bRecording && pkbhs->vkCode != VK_F9) {
            //oMsgList.push_back({ wParam, lParam, pkbhs->vkCode });
            std::cout << nCode << " " << wParam << " "<< pkbhs->vkCode << std::endl;
        }

        if (pkbhs->vkCode == VK_F9)
        {
            //the code below added for test SendInput method.
            //PressKey(0,0);
            //return CallNextHookEx(g_hHook, nCode, wParam, lParam);

            bRecording = !bRecording;
            if (bRecording)
            {
                oMsgList.clear();
                oMouseMsgList.clear();
                std::cout << nCode << " " << "开始记录……" << std::endl;
            }
            else
            {
                std::cout << "开始回放……" << std::endl;
                Sleep(3000);
                for (auto& item : oMsgList)
                {
                    //std::cout << item.wParam << " " << item.vkCode << std::endl;
                    PressKey(item.wParam, item.lParam);
                }
                //for (auto& item : oMouseMsgList)
                //{
                //    std::cout << "play back: " << nCode << " " << item.wParam << " " << item.x << "," << item.y << std::endl;
                //    MouseEvent(0, item.x, item.y, 0);

                //}
            }
        }

        if (pkbhs->vkCode == VK_F11)
        {
            PostQuitMessage(0);
        }
    }
    return CallNextHookEx(g_hHook, nCode, wParam, lParam);
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
     if (nCode >= 0 && (wParam == WM_LBUTTONUP || wParam == WM_MOUSEMOVE))
     {
         //std::cout << "bRecording: " << bRecording << std::endl;
         if (bRecording) {
             MSLLHOOKSTRUCT* pMouseStruct = (MSLLHOOKSTRUCT*)lParam;
             int xPos = pMouseStruct->pt.x;
             int yPos = pMouseStruct->pt.y;
             //oMouseMsgList.push_back({ wParam, xPos, yPos });
             //std::cout << "record mouse: " << nCode << " " << wParam << " " << xPos << "," << yPos << std::endl;
         }
         else {
             for (auto& item : oMouseMsgList)
             {
                 std::cout << nCode << " " << item.wParam << " " << item.x << "," << item.y << std::endl;
             }
         }
    }
    return CallNextHookEx(g_hMouseHook, nCode, wParam, lParam);
}

int main()
{
    /*测试SendInput接口回放键盘鼠标事件*/
    for (int i = 0; i < 1; i++) {
        Sleep(3000);
        PressKey(0, 0);
    }


    /*测试HOOK截取键盘鼠标消息代码段*/
    //hInstance = GetModuleHandle(NULL);

    //g_hHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, hInstance, 0);
    //g_hMouseHook = SetWindowsHookEx(WH_MOUSE_LL, MouseProc, hInstance, 0);

    //MSG msg;
    //while (GetMessage(&msg, NULL, 0, 0))
    //{
    //    TranslateMessage(&msg);
    //    DispatchMessage(&msg);
    //}

    //UnhookWindowsHookEx(g_hHook);
    //UnhookWindowsHookEx(g_hMouseHook);
    return 0;
}
