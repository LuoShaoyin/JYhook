//Control.h
//功能控制头文件
//

#pragma once
#ifndef _H_Control
#define _H_Control
#include "pch.h"

#define RECORD_INFO		 0x00
#define RECORD_SUCCEED	 0x01
#define RECORD_WARNING	 0x02
#define RECORD_ERROR	 0x03
#define RECORD_DEBUG	 0x04
#define RECORD_IMPORTANT 0x10

#define WM_UPDATA_SETTING		WM_USER + 1
#define WM_MESSAGE_SEND_BACK	WM_USER + 2


extern bool bDisableFullScreen;			//禁止全屏
extern WCHAR szMainWindowTitle[64][128];//主窗口标题
extern bool bUnlockKeyboard;			//解锁键盘
extern bool bDisableExecute;			//禁止运行命令
extern bool bDisableDriver;				//禁止调用驱动（驱动是为了限制访问资源）
extern bool bDisableProcessOperation;	//禁止操作进程（枚举、结束、挂起、调整优先级）
extern bool bCamouflageScreenShot;		//伪装屏幕截图
extern bool bDisableRemoteControl;		//禁止远程控制
extern char RecvPath[256];				//文件接受路径

extern HWND hControlPortWindow;		//接收消息的窗口
extern HANDLE hFileOut;				//记录，上层应用读取后显示


bool ControlInit();
//读取控制端的设置
bool UpdateSetting();


#endif //_H_Control