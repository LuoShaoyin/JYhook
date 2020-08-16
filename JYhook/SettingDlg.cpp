// SettingDlg.cpp: 实现文件
//

#include "pch.h"
#include "Gamer.h"
#include "SettingDlg.h"
#include "afxdialogex.h"


// CSettingDlg 对话框

IMPLEMENT_DYNAMIC(CSettingDlg, CDialogEx)

CSettingDlg::CSettingDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SETTING_DIALOG, pParent)
{

}

CSettingDlg::~CSettingDlg()
{
}

void CSettingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSettingDlg, CDialogEx)
	ON_BN_CLICKED(IDC_OPEN_PHOTO_PATH, &CSettingDlg::OnBnClickedOpencamouflagepath)
    ON_BN_CLICKED(IDC_UPDATE, &CSettingDlg::OnBnClickedUpdate)
END_MESSAGE_MAP()


// CSettingDlg 消息处理程序


void CSettingDlg::OnBnClickedOpencamouflagepath()
{
    CString CamouflagePath = theApp.MainDlg->m_HomeDlg->csPath;
    CamouflagePath += _T("GamerDll\\CamouflagScreenshot");
    ShellExecute(theApp.MainDlg->m_hWnd, _T("explore"), CamouflagePath, NULL, NULL, NULL);
}

BOOL CSettingDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
    if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
        if (pMsg->message == WM_KEYDOWN)
            return TRUE;
    return CDialogEx::PreTranslateMessage(pMsg);
}


void CSettingDlg::OnBnClickedUpdate()
{
    MessageBox(_T("building...."), _T("Please wait"));
    return;
    CString csINIPath = theApp.MainDlg->m_HomeDlg->csPath;
    csINIPath += _T("GamerDll\\GamerDll.ini");
    if (UpdateSetting(csINIPath)) AddRecord(RECORD_SUCCEED, _T("已成功更新"));
    else AddRecord(RECORD_ERROR, _T("无法更新设置"));
}


bool CSettingDlg::UpdateSetting(LPCWSTR lpINIPath)
{
    //禁止全屏
    if (((CButton*)GetDlgItem(IDC_DISABLE_FULL_SCREEN))->GetCheck())
        WritePrivateProfileString(_T("Anti-control"), _T("DisableFullScreen"), _T("true"), lpINIPath);
    else
        WritePrivateProfileString(_T("Anti-control"), _T("DisableFullScreen"), _T("false"), lpINIPath);
    //禁止运行外部程序
    if (((CButton*)GetDlgItem(IDC_DISABLE_EXECUTE))->GetCheck())
        WritePrivateProfileString(_T("Anti-control"), _T("DisableExecute"), _T("true"), lpINIPath);
    else
        WritePrivateProfileString(_T("Anti-control"), _T("DisableExecute"), _T("false"), lpINIPath);
    //禁用过滤
    if (((CButton*)GetDlgItem(IDC_DISABLE_FILTER))->GetCheck())
        WritePrivateProfileString(_T("Anti-control"), _T("DisableFilter"), _T("true"), lpINIPath);
    else
        WritePrivateProfileString(_T("Anti-control"), _T("DisableFilter"), _T("false"), lpINIPath);
    //禁止操作进程
    if (((CButton*)GetDlgItem(IDC_DISABLE_OPEN_PROCESS))->GetCheck())
        WritePrivateProfileString(_T("Anti-control"), _T("DisableOpenProcess"), _T("true"), lpINIPath);
    else
        WritePrivateProfileString(_T("Anti-control"), _T("DisableOpenProcess"), _T("false"), lpINIPath);
    //解锁键盘
    if (((CButton*)GetDlgItem(IDC_UNLOCK_KEYBOARD))->GetCheck())
        WritePrivateProfileString(_T("Anti-control"), _T("UnlockKeyboard"), _T("true"), lpINIPath);
    else
        WritePrivateProfileString(_T("Anti-control"), _T("UnlockKeyboard"), _T("false"), lpINIPath);
    //解锁键盘
    if (((CButton*)GetDlgItem(IDC_CAMOUFLAGE_SCREENSHOT))->GetCheck())
        WritePrivateProfileString(_T("Anti-control"), _T("CamouflageScreenshot"), _T("true"), lpINIPath);
    else
        WritePrivateProfileString(_T("Anti-control"), _T("CamouflageScreenshot"), _T("false"), lpINIPath);
    //文件转存路径
    return TRUE;
}


BOOL CSettingDlg::OnInitDialog()
{
    CDialogEx::OnInitDialog();

    // TODO:  在此添加额外的初始化
    ((CButton*)GetDlgItem(IDC_DISABLE_FULL_SCREEN))->SetCheck(TRUE);
    ((CButton*)GetDlgItem(IDC_DISABLE_EXECUTE))->SetCheck(TRUE);
    ((CButton*)GetDlgItem(IDC_UNLOCK_KEYBOARD))->SetCheck(TRUE);
    ((CButton*)GetDlgItem(IDC_DISABLE_FILTER))->SetCheck(TRUE);
    ((CButton*)GetDlgItem(IDC_DISABLE_OPEN_PROCESS))->SetCheck(TRUE);
    ((CButton*)GetDlgItem(IDC_DISABLE_REMOTE_CONTROL))->SetCheck(TRUE);
    ((CButton*)GetDlgItem(IDC_CAMOUFLAGE_SCREENSHOT))->SetCheck(TRUE);

    return TRUE;  // return TRUE unless you set the focus to a control
                  // 异常: OCX 属性页应返回 FALSE
}
