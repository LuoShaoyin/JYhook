#pragma once

#define MAX_RECORD 64

// CRecordDlg 对话框

class CRecordDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CRecordDlg)

public:
	CRecordDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRecordDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RECORD_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	CString csAllRecord[MAX_RECORD];
	DWORD csRecordStyle[MAX_RECORD];
	DWORD dwRecordTail;
public:
	// 添加一条记录
	void _AddRecord(DWORD dwStyle, CString csRecord);
	afx_msg void OnBnClickedDebug();
	afx_msg void OnBnClickedClearRecord();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
