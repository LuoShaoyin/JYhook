//Control.cpp
//���ܿ���
//
#include "pch.h"
#include "Control.h"

bool bDisableFullScreen;		//��ֹȫ��
WCHAR szMainWindowTitle[64][128];//�����ڱ���
bool bUnlockKeyboard;			//��������
bool bDisableExecute;			//��ֹ��������
bool bDisableDriver;			//��ֹ����������������Ϊ�����Ʒ�����Դ��
bool bDisableProcessOperation;	//��ֹ�������̣�ö�١����������𡢵������ȼ���
bool bCamouflageScreenShot;		//αװ��Ļ��ͼ
bool bDisableRemoteControl;		//��ֹԶ�̿���


bool ControlInit()
{

	//��ʼ������
	ZeroMemory(szMainWindowTitle, sizeof(szMainWindowTitle));
	wcscpy_s(szMainWindowTitle[0], L"��Ļ�㲥");
	wcscpy_s(szMainWindowTitle[1], L"ѧ����ʾ");
	wcscpy_s(szMainWindowTitle[2], L"����ӰԺ");
	wcscpy_s(szMainWindowTitle[3], L"����װ�");
	
	bDisableFullScreen = true;
	bUnlockKeyboard = true;
	bDisableExecute = true;
	bDisableDriver = true;
	bDisableProcessOperation = true;
	bCamouflageScreenShot = true;
	bDisableRemoteControl = true;

	return true;
}

//��ȡ���ƶ˵�����
bool UpdateSetting()
{
	return true;
}