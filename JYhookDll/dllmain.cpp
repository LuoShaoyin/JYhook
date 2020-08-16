// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "HookFunc.h"

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        MessageBox(NULL, L"dll已成功注入目标进程", L"成功", MB_OK);
        ControlInit();          //初始化控制模块
        HookInit();             //初始化hook模块
        GetTrueFuncAddress();   //获取真实的函数地址
        SetHooks();             //设置hook
        break;
    case DLL_PROCESS_DETACH:
        UnHooks();              //卸载hook
        HookFree();             //释放资源，要先Unhook，否则JY会UAF
        break;
    }
    return TRUE;
}


