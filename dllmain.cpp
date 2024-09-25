// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "周围对象.h"
#include "绘制.h"
/*
* 已经找到的数据如下：
自身X坐标：hw.dll+10F7F60-4

自身Y坐标：hw.dll+10F7F60-8

自身Z坐标：hw.dll+10F7F60    (hw.dll+1121A90)

自身垂直朝向：hw.dll+10569A4

自身水平朝向：hw.dll+10569A8

其中一个玩家的坐标为：hw.dll+11D0284

其中一个人物死亡标志：hw.dll+746A64

具体找的过程：https://0xcc12138.github.io/%E6%89%BE%E5%9F%BA%E5%9C%B0%E5%9D%80/
*/
DWORD Time = 0;

DWORD WINAPI ThreadFunc(LPVOID lpParam)
{
    HWND hwnd = FindWindowA(NULL, "Counter-Strike");
    unsigned int cstrike基地址 = (unsigned int)GetModuleHandleA("cstrike.exe");
    if (!cstrike基地址)
    {
        MessageBox(0, L"获取基地址失败！", L"Error", 0);
        return 0;
    }
    DWORD 矩阵基地址 = cstrike基地址 + 0x1820100;
    绘制 FPS绘制(hwnd, 矩阵基地址);

    while (TRUE)
    {
        FPS绘制.目标周围对象.刷新周围数据();
        for (int i = 0; i < FPS绘制.目标周围对象.对象数量-1; i++)
        {
            FPS绘制.世界坐标转为屏幕坐标_矩阵(*FPS绘制.目标周围对象.对象列表[i], FPS绘制.目标屏幕坐标结构[i]);
            if(FPS绘制.目标周围对象.对象列表[i]->死亡标志!=1)
                FPS绘制.画线(FPS绘制.目标屏幕坐标结构[i].x坐标, FPS绘制.目标屏幕坐标结构[i].y坐标,FPS绘制.目标周围对象.对象列表[i]->阵营标志);
            //FPS绘制.绘制字符串(FPS绘制.目标屏幕坐标结构[i].x坐标, FPS绘制.目标屏幕坐标结构[i].y坐标);
            FPS绘制.自瞄();
        }
        Sleep(20);
        Time++;
    }
}



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        HANDLE hThread;
        DWORD threadId;
        

        // 创建线程
        hThread = CreateThread(
            NULL,                   // 默认安全属性
            0,                      // 默认堆栈大小
            ThreadFunc,             // 线程函数的入口地址
            NULL,                 // 传递给线程函数的参数
            0,                      // 线程创建标志
            &threadId               // 接收线程标识符
        );
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

