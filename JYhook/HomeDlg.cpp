#include "pch.h"
// CHomeDlg.cpp: 实现文件
//


#include "JYhook.h"
#include "JYhookDlg.h"
#include "HomeDlg.h"
#include "KillProcess.h"
#include "afxdialogex.h"


// CHomeDlg 对话框

IMPLEMENT_DYNAMIC(CHomeDlg, CDialogEx)

CHomeDlg::CHomeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_HOME_DIALOG, pParent)
{
    hStudentMain = NULL;
    szExeFile[0] = '\0';
}

CHomeDlg::~CHomeDlg()
{
}

void CHomeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CHomeDlg, CDialogEx)
    ON_WM_TIMER()
    ON_EN_SETFOCUS(IDC_PROC_NAME, &CHomeDlg::OnSetfocusProcname)
    ON_EN_KILLFOCUS(IDC_PROC_NAME, &CHomeDlg::OnKillfocusProcname)
    ON_BN_CLICKED(IDC_PROC_KILL, &CHomeDlg::OnBnClickedKill)
	ON_BN_CLICKED(IDC_INJECT, &CHomeDlg::OnBnClickedInject)
END_MESSAGE_MAP()


// CHomeDlg 消息处理程序


BOOL CHomeDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if (pMsg->wParam == VK_RETURN || pMsg->wParam == VK_ESCAPE)
		if (pMsg->message == WM_KEYDOWN)
			return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CHomeDlg::GetProcessInfo(const WCHAR* pName)
{
	// TODO: 在此处添加实现代码.
    CString csDisplay;
    HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (INVALID_HANDLE_VALUE == hSnapshot) {
        return;
    }
    PROCESSENTRY32 pe = { sizeof(pe) };
    for (BOOL ret = Process32First(hSnapshot, &pe); ret; ret = Process32Next(hSnapshot, &pe))
    {
        if (wcscmp(pe.szExeFile, pName) == 0)
        {
            wcscpy_s(szExeFile, pName);
            hStudentMain = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe.th32ProcessID);
            csDisplay.Format(L"%d",pe.th32ProcessID);
            SetDlgItemText(IDC_PROC_ID, csDisplay);
            DWORD dMaxSize = 128;
            QueryFullProcessImageName(hStudentMain, 0, szFullPath, &dMaxSize);
            csDisplay.Format(L"%s", szFullPath);
            SetDlgItemText(IDC_PROC_PATH, csDisplay);
            CloseHandle(hSnapshot);

            CString csFullPath = szFullPath;
            CString csExeName = szExeFile;
            csPath = csFullPath.Left(csFullPath.GetLength() - csExeName.GetLength());

            return;
        }
    }
    CloseHandle(hSnapshot);
    csDisplay.Format(L"没有找到进程");
    SetDlgItemText(IDC_PROC_ID, csDisplay);
    SetDlgItemText(IDC_PROC_PATH, csDisplay);
    if (hStudentMain) CloseHandle(hStudentMain);
}

void CHomeDlg::OnTimer(UINT_PTR nIDEvent)
{
    // TODO: 在此添加消息处理程序代码和/或调用默认值
    CString csName;
    switch (nIDEvent)
    {
    case 1:
        GetDlgItemText(IDC_PROC_NAME, csName);
        GetProcessInfo(csName.GetBuffer());
        break;
    case 2:
        if (::FindWindowEx(HWND_MESSAGE, 0, _T("JYhookDllControlPort"), NULL) == NULL)
            GetDlgItem(IDC_INJECT)->EnableWindow(TRUE);
        else
            GetDlgItem(IDC_INJECT)->EnableWindow(FALSE);
        break;
    }
    CDialogEx::OnTimer(nIDEvent);
}

void CHomeDlg::PreInitDialog()
{
    // TODO: 在此添加专用代码和/或调用基类
    CString csName;
    csName.Format(L"StudentMain.exe");
    SetDlgItemText(IDC_PROC_NAME, csName);
    SetTimer(1, 250, NULL);
    //SetTimer(2, 250, NULL);
    CDialogEx::PreInitDialog();
}

void CHomeDlg::OnSetfocusProcname()
{
    KillTimer(1);
}
void CHomeDlg::OnKillfocusProcname()
{
    SetTimer(1, 250, NULL);
}


void CHomeDlg::OnBnClickedKill()
{
    // TODO: 在此添加控件通知处理程序代码
    //注入不了就杀死
    NtTerminateProcess(hStudentMain, 4);
    KillProcess2(hStudentMain);
}


BOOL CHomeDlg::InjectDll(HANDLE hProcess, LPCWSTR lpDllPath)
{
    const char* RemotePath = ".\\JYhookDll\\JYhookDll.dll";

    AddRecord(RECORD_DEBUG, _T("开始注入"));
    HANDLE hThread = NULL;
    HMODULE hMod = NULL;
    LPVOID pRemoteBuf = NULL;  // 存储在目标进程申请的内存地址  
    DWORD dwBufSize = (DWORD)(strlen(RemotePath) + 1) * sizeof(char);  // 存储DLL文件路径所需的内存空间大小  
    LPTHREAD_START_ROUTINE pThreadProc;
    
    CreateDirectory(csPath + _T("JYhookDll\\"), NULL);

    CopyFile(lpDllPath, csPath + _T("JYhookDll\\JYhookDll.dll"), FALSE);

    pRemoteBuf = VirtualAllocEx(hProcess, NULL, dwBufSize, MEM_COMMIT, PAGE_READWRITE);  // 在目标进程空间中申请内存  
    if (!pRemoteBuf)
    {
        AddRecord(RECORD_DEBUG, _T("无法在远程进程申请空间"));
        return FALSE;
    }
    AddRecord(RECORD_DEBUG, _T("在远程进程申请空间成功"));
    if (!WriteProcessMemory(hProcess, pRemoteBuf, (LPVOID)RemotePath, dwBufSize, NULL))   // 向在目标进程申请的内存空间中写入DLL文件的路径
    {
        AddRecord(RECORD_DEBUG, _T("无法写入dll路径"));
        return FALSE;
    }
    AddRecord(RECORD_DEBUG, _T("写入dll路径成功"));
    hMod = GetModuleHandle(L"kernel32.dll");
    if (!hMod)
    {
        AddRecord(RECORD_DEBUG,_T("无法获取kernel32.dll句柄"));
        return FALSE;
    }
    pThreadProc = (LPTHREAD_START_ROUTINE)GetProcAddress(hMod, "LoadLibraryA");  // 获得LoadLibrary()函数的地址  
    if (!pThreadProc)
    {
        AddRecord(RECORD_DEBUG, _T("无法获取LoadLibraryA()地址"));
        return FALSE;
    }
    AddRecord(RECORD_DEBUG, _T("得到LoadLibraryA()地址"));
    hThread = CreateRemoteThread(hProcess, NULL, 0, pThreadProc, pRemoteBuf, 0, NULL);
    if (!hThread)
    {
        AddRecord(RECORD_DEBUG, _T("无法创建远程线程"));
        return FALSE;
    }
    AddRecord(RECORD_DEBUG, _T("等待远程线程回复"));
    WaitForSingleObject(hThread, 5);
    CloseHandle(hThread);
    AddRecord(RECORD_DEBUG, _T("注入完成"));
    return TRUE;
}
BOOL CHomeDlg::HijackDll(LPCWSTR lpDllPath)
{
    //劫持 libTDAjust
    AddRecord(RECORD_DEBUG, _T("开始劫持"));
    CString csFullPath = szFullPath;
    CString csExeName = szExeFile;
    CString csPath;
    CString csBackupPath, cslibTDAjustPath;
    csPath = csFullPath.Left(csFullPath.GetLength() - csExeName.GetLength());
    csBackupPath = csPath + _T("libTDAjust");
    cslibTDAjustPath = csPath + _T("libTDAjust.dll");
    
    KillProcess2(hStudentMain);
    AddRecord(RECORD_DEBUG, _T("备份原文件"));
    CopyFile(cslibTDAjustPath, csBackupPath, TRUE);
    MessageBox(cslibTDAjustPath);
    if (!CopyFile(_T(".\\JYhookDll.dll"), cslibTDAjustPath, FALSE))
    {
        AddRecord(RECORD_DEBUG, _T("无法劫持"));
        return FALSE;
    }
    ShellExecute(NULL, _T("open"), csFullPath, NULL, NULL, NULL);
    AddRecord(RECORD_DEBUG, _T("劫持完成"));
    
    return TRUE;
}
void CHomeDlg::OnBnClickedInject()
{
    if (!InjectDll(hStudentMain,L".\\JYhookDll.dll"))
    {
        AddRecord(RECORD_ERROR, _T("注入失败"));
        AfxMessageBox(_T("注入失败"));
        return;
    }
    AddRecord(RECORD_SUCCEED, _T("注入成功"));
    CreateDirectory(csPath + _T("JYhookDll\\CamouflageScreenshot"), NULL);
}
