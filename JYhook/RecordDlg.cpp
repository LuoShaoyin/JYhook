// RecordDlg.cpp: 实现文件
//

#include "pch.h"
#include "JYhook.h"
#include "RecordDlg.h"
#include "afxdialogex.h"


// CRecordDlg 对话框

IMPLEMENT_DYNAMIC(CRecordDlg, CDialogEx)

CRecordDlg::CRecordDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_RECORD_DIALOG, pParent)
{
	for(DWORD i = 0; i < MAX_RECORD; i++)
		csAllRecord[i] = _T("");
	dwRecordTail = 0;
}

CRecordDlg::~CRecordDlg()
{
}

void CRecordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRecordDlg, CDialogEx)
	ON_BN_CLICKED(IDC_DEBUG, &CRecordDlg::OnBnClickedDebug)
	ON_BN_CLICKED(IDC_CLEAR_RECORD, &CRecordDlg::OnBnClickedClearRecord)
END_MESSAGE_MAP()


// CRecordDlg 消息处理程序


// 添加一条记录
void CRecordDlg::_AddRecord(DWORD dwStyle,CString csRecord)
{
	// TODO: 在此处添加实现代码 
	csAllRecord[dwRecordTail] = _T("");
	switch (dwStyle)
	{
	case RECORD_INFO:
		csAllRecord[dwRecordTail] += _T("[INFO]");
		break;
	case RECORD_SUCCEED:
		csAllRecord[dwRecordTail] += _T("[SUCCESS]");
		break;
	case RECORD_WARNING:
		csAllRecord[dwRecordTail] += _T("[WARNING]");
		break;
	case RECORD_ERROR:
		csAllRecord[dwRecordTail] += _T("[ERROR]");
		break;
	case RECORD_DEBUG:
		csAllRecord[dwRecordTail] += _T("[DEBUG]");
		break;
	}
	csRecord += _T("\r\n");
	csAllRecord[dwRecordTail] += csRecord;
	csRecordStyle[dwRecordTail] = dwStyle;
	dwRecordTail = (dwRecordTail + 1) % MAX_RECORD;
	OnBnClickedDebug();				//Update
}


void CRecordDlg::OnBnClickedDebug()
{
	// TODO: 在此添加控件通知处理程序代码
	CString csDisplay = _T("");
	DWORD i = dwRecordTail;
	do
	{
		if (csAllRecord[i] != _T(""))
		{
			if (csRecordStyle[i] != RECORD_DEBUG || \
				((CButton*)GetDlgItem(IDC_DEBUG))->GetCheck())
			{
				csDisplay += csAllRecord[i];
				//tmp = csDisplay.Right(11);
				//MessageBox(csDisplay);
			}
				
		}
		i = (i + 1) % MAX_RECORD;
	} while (i != dwRecordTail);
	SetDlgItemText(IDC_RECORD_OUTPUT, csDisplay);
}


void CRecordDlg::OnBnClickedClearRecord()
{
	for (DWORD i = 0; i < MAX_RECORD; i++)
	{
		csAllRecord[i] = _T("");
		csRecordStyle[i] = 0;
	}
	dwRecordTail = 0;
	OnBnClickedDebug();
}


BOOL CRecordDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		if (pMsg->message == WM_KEYDOWN)
			return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}
