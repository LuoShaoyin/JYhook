
// JYhookDlg.cpp: 实现文件
//

#include "pch.h"
#include "JYhook.h"
#include "JYhookDlg.h"
#include "SettingDlg.h"
#include "CAbout.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CJYhookDlg 对话框



CJYhookDlg::CJYhookDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_JYhook_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	ZeroMemory(m_Page, MAX_PAGE * sizeof(CDialog*));
}

void CJYhookDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB, m_Tab);
}

BEGIN_MESSAGE_MAP(CJYhookDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, &CJYhookDlg::OnSelchangeTab)
END_MESSAGE_MAP()


// CJYhookDlg 消息处理程序

BOOL CJYhookDlg::OnInitDialog()
{
	if (!GetSystem())
	{
		MessageBox(_T("获取权限失败"), _T("错误"), NULL);
		exit(0);
	}
	

	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	ShowWindow(SW_MINIMIZE);

	// TODO: 在此添加额外的初始化代码

	m_Tab.InsertItem(0, L"主页");
	m_Tab.InsertItem(1, L"设置");
	m_Tab.InsertItem(2, L"消息");
	m_Tab.InsertItem(3, L"关于");
	CRect rc;
	m_Tab.GetClientRect(&rc);
	rc.top += 28;
	InitAllDlg(rc);
	HideAllDlg();
	m_Page[0]->ShowWindow(SW_SHOW);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CJYhookDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CJYhookDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



BOOL CJYhookDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		if (pMsg->message == WM_KEYDOWN)
			return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CJYhookDlg::InitAllDlg(CRect rc)
{
	// TODO: 在此处添加实现代码.
	m_Page[0] = m_HomeDlg = new CHomeDlg;
	m_Page[1] = new CSettingDlg;
	m_Page[2] = m_RecordDlg = new CRecordDlg;
	m_Page[3] = new CAbout;
	m_Page[0]->Create(IDD_HOME_DIALOG, &m_Tab);
	m_Page[1]->Create(IDD_SETTING_DIALOG, &m_Tab);
	m_Page[2]->Create(IDD_RECORD_DIALOG, &m_Tab);
	m_Page[3]->Create(IDD_ABOUT_DIALOG, &m_Tab);
	for (auto dialog : m_Page)
		if (dialog)
			dialog->MoveWindow(rc);
}

void CJYhookDlg::HideAllDlg()
{
	for (auto dialog : m_Page)
		if(dialog)
			dialog->ShowWindow(SW_HIDE);
}

void CJYhookDlg::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: 在此添加控件通知处理程序代码
	HideAllDlg();
	//if (FindWindow(_T("JYhookDllControlPort"), _T("JYhookDllControlWindow")) == NULL && m_Tab.GetCurSel() == 1)
	//{
	//	MessageBox(_T("请先完成注入！"), _T("错误"), MB_ICONERROR);
	//	m_Tab.SetCurSel(0);
	//}
	m_Page[m_Tab.GetCurSel()]->ShowWindow(SW_SHOW);
	*pResult = 0;
}

BOOL CJYhookDlg::GetSystem()
{
	HANDLE hToken;
	LUID sedebugnameValue;
	TOKEN_PRIVILEGES tkp;


	if (NtOpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken) != STATUS_SUCCESS) {
		return false;
	}

	if (!LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &sedebugnameValue)) {
		__try {
			if (hToken) {
				CloseHandle(hToken);
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {};
		return false;
	}

	tkp.PrivilegeCount = 1;
	tkp.Privileges[0].Luid = sedebugnameValue;
	tkp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	if (!AdjustTokenPrivileges(hToken, FALSE, &tkp, sizeof(tkp), NULL, NULL)) {
		__try {
			if (hToken) {
				CloseHandle(hToken);
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) {};
		return false;
	}

	return true;
}