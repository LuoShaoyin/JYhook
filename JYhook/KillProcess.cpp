#include "pch.h"
#include "KillProcess.h"



//�ڴ�����

//Nt��ʽ
bool KillProcess1(HANDLE hProcess)
{
    return NtTerminateProcess(hProcess, 4) == STATUS_SUCCESS;
}
//����
bool KillProcess2(HANDLE hProcess)
{
    // TODO: �ڴ˴����ʵ�ִ���.
    //����ԱȨ��(�ر���system)�µ��ã�Ȼ��һ�нԿ�ɱ
    //����ɱwininit.exe?
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