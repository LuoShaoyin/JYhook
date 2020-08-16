#pragma once


// CHomeDlg 对话框

class CHomeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHomeDlg)

public:
	CHomeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CHomeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_HOME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	//StudentMain信息获取
	HANDLE hStudentMain;
	WCHAR szExeFile[128];
	WCHAR szFullPath[MAX_PATH];
	CString csPath;
	void GetProcessInfo(const WCHAR* pName);
	virtual void PreInitDialog();
	afx_msg void OnSetfocusProcname();
	afx_msg void OnKillfocusProcname();
	//dll注入失败，直接杀
	afx_msg void OnBnClickedKill();
	//dll注入
	BOOL InjectDll(HANDLE hProcess, LPCWSTR lpDllPath);
	BOOL HijackDll(LPCWSTR lpDllPath);
	afx_msg void OnBnClickedInject();
};
