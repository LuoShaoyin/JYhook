// CAbout.cpp: 实现文件
//

#include "pch.h"
#include "Gamer.h"
#include "CAbout.h"
#include "afxdialogex.h"


// CAbout 对话框

IMPLEMENT_DYNAMIC(CAbout, CDialogEx)

CAbout::CAbout(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ABOUT_DIALOG, pParent)
{

}

CAbout::~CAbout()
{
}

void CAbout::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAbout, CDialogEx)
END_MESSAGE_MAP()


// CAbout 消息处理程序


BOOL CAbout::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		if (pMsg->message == WM_KEYDOWN)
			return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
