//Control.cpp
//功能控制
//
#include "pch.h"
#include "Control.h"

bool bDisableFullScreen;		//禁止全屏
WCHAR szMainWindowTitle[64][128];//主窗口标题
bool bUnlockKeyboard;			//解锁键盘
bool bDisableExecute;			//禁止运行命令
bool bDisableDriver;			//禁止调用驱动（驱动是为了限制访问资源）
bool bDisableProcessOperation;	//禁止操作进程（枚举、结束、挂起、调整优先级）
bool bCamouflageScreenShot;		//伪装屏幕截图
bool bDisableRemoteControl;		//禁止远程控制


bool ControlInit()
{

	//初始化变量
	ZeroMemory(szMainWindowTitle, sizeof(szMainWindowTitle));
	wcscpy_s(szMainWindowTitle[0], L"屏幕广播");
	wcscpy_s(szMainWindowTitle[1], L"学生演示");
	wcscpy_s(szMainWindowTitle[2], L"网络影院");
	wcscpy_s(szMainWindowTitle[3], L"共享白板");
	
	bDisableFullScreen = true;
	bUnlockKeyboard = true;
	bDisableExecute = true;
	bDisableDriver = true;
	bDisableProcessOperation = true;
	bCamouflageScreenShot = true;
	bDisableRemoteControl = true;

	return true;
}

//读取控制端的设置
bool UpdateSetting()
{
	return true;
}