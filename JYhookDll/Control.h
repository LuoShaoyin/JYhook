//Control.h
//���ܿ���ͷ�ļ�
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


extern bool bDisableFullScreen;			//��ֹȫ��
extern WCHAR szMainWindowTitle[64][128];//�����ڱ���
extern bool bUnlockKeyboard;			//��������
extern bool bDisableExecute;			//��ֹ��������
extern bool bDisableDriver;				//��ֹ����������������Ϊ�����Ʒ�����Դ��
extern bool bDisableProcessOperation;	//��ֹ�������̣�ö�١����������𡢵������ȼ���
extern bool bCamouflageScreenShot;		//αװ��Ļ��ͼ
extern bool bDisableRemoteControl;		//��ֹԶ�̿���
extern char RecvPath[256];				//�ļ�����·��

extern HWND hControlPortWindow;		//������Ϣ�Ĵ���
extern HANDLE hFileOut;				//��¼���ϲ�Ӧ�ö�ȡ����ʾ


bool ControlInit();
//��ȡ���ƶ˵�����
bool UpdateSetting();


#endif //_H_Control