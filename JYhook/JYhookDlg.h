
// JYhookDlg.h: 头文件
//

#pragma once
#include "HomeDlg.h"
#include "RecordDlg.h"
#include "SettingDlg.h"

#define MAX_PAGE 4

// CJYhookDlg 对话框
class CJYhookDlg : public CDialogEx
{
// 构造
public:
	CJYhookDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_JYhook_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	CTabCtrl m_Tab;
	CDialog* m_Page[MAX_PAGE];
	CRecordDlg* m_RecordDlg;			//公开Addrecord
	CHomeDlg* m_HomeDlg;				//公开基本信息


	void InitAllDlg(CRect rc);
	void HideAllDlg();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);

	BOOL GetSystem();
};
