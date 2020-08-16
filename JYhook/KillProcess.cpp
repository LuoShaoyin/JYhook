#include "pch.h"
#include "KillProcess.h"



//内存清零

//Nt方式
bool KillProcess1(HANDLE hProcess)
{
    return NtTerminateProcess(hProcess, 4) == STATUS_SUCCESS;
}
//调试
bool KillProcess2(HANDLE hProcess)
{
    // TODO: 在此处添加实现代码.
    //管理员权限(特别是system)下调用，然后一切皆可杀
    //试试杀wininit.exe?
    DWORD dwExitCodeOfProcess = 0;
    NTSTATUS ntStat;
    HANDLE hDebugObject;
    OBJECT_ATTRIBUTES oa;
    InitializeObjectAttributes(&oa, 0, 0, 0, 0);
    ntStat = NtCreateDebugObject(&hDebugObject, DEBUG_ALL_ACCESS, &oa, DEBUG_KILL_ON_CLOSE);
    if (ntStat >= STATUS_SUCCESS)
    {
        NtDebugActiveProcess(hProcess, hDebugObject);
        return true;
    }
    else
    {
        return false;
    }
    CloseHandle(hDebugObject);
}