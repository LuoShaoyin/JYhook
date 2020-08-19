//hook函数实现
//*********************************
#include "pch.h"
#include "HookFunc.h"
#pragma warning(disable: 6387)
#pragma warning(disable: 28251)


// 保存真正的函数
_MoveWindow  trueMoveWindow;
_SetParent trueSetParent;
_SetWindowPos trueSetWindowPos;
_SetWindowLongA trueSetWindowLongA;
_SetWindowLongW trueSetWindowLongW;
_SetForegroundWindow trueSetForegroundWindow;
_ShowWindow trueShowWindow;

_SetWindowsHookExA trueSetWindowsHookExA;
_SetWindowsHookExW trueSetWindowsHookExW;

_NtCreateProcessEx trueNtCreateProcessEx;
_NtCreateUserProcess trueNtCreateUserProcess;

_DeviceIoControl trueDeviceIoControl;
_FilterSendMessage trueFilterSendMessage;

_SendInput trueSendInput;

_BitBlt trueBitBlt;

_ZwQuerySystemInformation trueZwQuerySystemInformation;
_NtOpenProcess trueNtOpenProcess;
_EnumWindows trueEnumWindows;
_SendMessage trueSendMessage;

//获取真正的函数地址
void GetTrueFuncAddress()
{
	//dll句柄
	HMODULE hUser32 = GetModuleHandle(_T("user32.dll"));
	HMODULE hGdi32 = GetModuleHandle(_T("gdi32.dll"));
	HMODULE hKernel32 = GetModuleHandle(_T("kernel32.dll"));
	HMODULE hFltLib = GetModuleHandle(_T("fltLib.dll"));
	HMODULE hNtdll = GetModuleHandle(_T("ntdll.dll"));
	HMODULE hNtosKrnl = GetModuleHandle(_T("NtosKrnl.exe"));
	//函数句柄
	trueMoveWindow	= (_MoveWindow)GetProcAddress(hUser32, "MoveWindow");
	trueSetParent = (_SetParent)GetProcAddress(hUser32, "SetParent");
	trueSetWindowPos= (_SetWindowPos)GetProcAddress(hUser32, "SetWindowPos");
	trueSetWindowLongA = (_SetWindowLongA)GetProcAddress(hUser32, "SetWindowLongA");
	trueSetWindowLongW = (_SetWindowLongW)GetProcAddress(hUser32, "SetWindowLongW");
	trueSetForegroundWindow = (_SetForegroundWindow)GetProcAddress(hUser32, "SetForegroundWindow");
	trueShowWindow = (_ShowWindow)GetProcAddress(hUser32, "ShowWindow");

	trueSetWindowsHookExA = (_SetWindowsHookExA)GetProcAddress(hUser32, "SetWindowsHookExA");
	trueSetWindowsHookExW = (_SetWindowsHookExW)GetProcAddress(hUser32, "SetWindowsHookExW");

	trueNtCreateProcessEx = (_NtCreateProcessEx)GetProcAddress(hNtdll, "NtCreateProcessEx");
	trueNtCreateUserProcess = (_NtCreateUserProcess)GetProcAddress(hNtdll, "NtCreateUserProcess");

	trueDeviceIoControl = (_DeviceIoControl)GetProcAddress(hKernel32, "DeviceIoControl");
	trueFilterSendMessage = (_FilterSendMessage)GetProcAddress(hFltLib, "FilterSendMessage");

	trueSendInput = (_SendInput)GetProcAddress(hUser32, "SendInput");

	trueBitBlt = (_BitBlt)GetProcAddress(hGdi32, "BitBlt");

	trueZwQuerySystemInformation = (_ZwQuerySystemInformation)GetProcAddress(hNtdll, "ZwQuerySystemInformation");
	trueNtOpenProcess = (_NtOpenProcess)GetProcAddress(hNtdll, "NtOpenProcess");
	trueEnumWindows = (_EnumWindows)GetProcAddress(hUser32, "EnumWindows");
	trueSendMessage = (_SendMessage)GetProcAddress(hUser32, "SendMessage");
}


//Hook & Unhook
void SetHooks()
{
	if (trueMoveWindow) Mhook_SetHook((PVOID*)&trueMoveWindow, hookMoveWindow);
	if (trueSetParent) Mhook_SetHook((PVOID*)&trueSetParent, hookSetParent);
	if (trueSetWindowPos) Mhook_SetHook((PVOID*)&trueSetWindowPos, hookSetWindowPos);
	if (trueSetWindowLongW) Mhook_SetHook((PVOID*)&trueSetWindowLongW, hookSetWindowLongW);
	if (trueSetForegroundWindow) Mhook_SetHook((PVOID*)&trueSetForegroundWindow, hookSetForegroundWindow);
	if (trueShowWindow) Mhook_SetHook((PVOID*)&trueShowWindow, hookShowWindow);

	if (trueSetWindowsHookExA) Mhook_SetHook((PVOID*)&trueSetWindowsHookExA, hookSetWindowsHookExA);
	if (trueSetWindowsHookExW) Mhook_SetHook((PVOID*)&trueSetWindowsHookExW, hookSetWindowsHookExW);

	if (trueNtCreateProcessEx) Mhook_SetHook((PVOID*)&trueNtCreateProcessEx, hookNtCreateProcessEx);
	if (trueNtCreateUserProcess) Mhook_SetHook((PVOID*)&trueNtCreateUserProcess, hookNtCreateUserProcess);

	if (trueDeviceIoControl) Mhook_SetHook((PVOID*)&trueDeviceIoControl, hookDeviceIoControl);
	if (trueFilterSendMessage) Mhook_SetHook((PVOID*)&trueFilterSendMessage, hookFilterSendMessage);

	if (trueSendInput) Mhook_SetHook((PVOID*)&trueSendInput, hookSendInput);

	if (trueBitBlt) Mhook_SetHook((PVOID*)&trueBitBlt, hookBitBlt);

	if (trueZwQuerySystemInformation) Mhook_SetHook((PVOID*)&trueZwQuerySystemInformation, hookZwQuerySystemInformation);
	if (trueNtOpenProcess) Mhook_SetHook((PVOID*)&trueNtOpenProcess, hookNtOpenProcess);
//	if (trueEnumWindows) Mhook_SetHook((PVOID*)&trueEnumWindows, hookEnumWindows);
	if (trueSendMessage) Mhook_SetHook((PVOID*)&trueSendMessage, hookSendMessage);
}
void UnHooks()
{
	if (trueMoveWindow) Mhook_Unhook((PVOID*)&trueMoveWindow);
	if (trueSetParent) Mhook_Unhook((PVOID*)&trueSetParent);
	if (trueSetWindowPos) Mhook_Unhook((PVOID*)&trueSetWindowPos);
	if (trueSetWindowLongW) Mhook_Unhook((PVOID*)&trueSetWindowLongW);
	if (trueSetForegroundWindow) Mhook_Unhook((PVOID*)&trueSetForegroundWindow);
	if (trueShowWindow) Mhook_Unhook((PVOID*)&trueShowWindow);

	if (trueSetWindowsHookExA) Mhook_Unhook((PVOID*)&trueSetWindowsHookExA);
	if (trueSetWindowsHookExW) Mhook_Unhook((PVOID*)&trueSetWindowsHookExW);

	if (trueNtCreateProcessEx) Mhook_Unhook((PVOID*)&trueNtCreateProcessEx);
	if (trueNtCreateUserProcess) Mhook_Unhook((PVOID*)&trueNtCreateUserProcess);

	if (trueDeviceIoControl) Mhook_Unhook((PVOID*)&trueDeviceIoControl);
	if (trueFilterSendMessage) Mhook_Unhook((PVOID*)&trueFilterSendMessage);

	if (trueSendInput) Mhook_Unhook((PVOID*)&trueSendInput);

	if (trueBitBlt) Mhook_Unhook((PVOID*)&trueBitBlt);

	if (trueZwQuerySystemInformation) Mhook_Unhook((PVOID*)&trueZwQuerySystemInformation);
	if (trueNtOpenProcess) Mhook_Unhook((PVOID*)&trueNtOpenProcess);
//	if (trueEnumWindows) Mhook_Unhook((PVOID*)&trueEnumWindows);
}

//需要的变量
int iScreenX, iScreenY;			//屏幕大小
HDC hDesktopDC;					//桌面DC
CImage lplCamouflageImage[MAXN_PHOTO];
HBITMAP hCamouflageImage[MAXN_PHOTO]; 
DWORD dwImageIndex;

HANDLE hDeviceTDNetFilter;
HANDLE hDeviceTDKeybd;
HANDLE hDeviceTDProcHook;


//初始化
bool HookInit()
{
	iScreenX = GetSystemMetrics(SM_CXSCREEN);
	iScreenY = GetSystemMetrics(SM_CYSCREEN);
	
	hDesktopDC = NULL;
	
	WCHAR wcd[128];
	_wgetcwd(wcd, 128);

	WCHAR PhotoPath[128];
	for (DWORD i = 0; i < MAXN_PHOTO; i++)
	{
		ZeroMemory(PhotoPath, sizeof(PhotoPath));
		wsprintf(PhotoPath, _T("%s%s%d%s"), wcd, _T("\\JYhookDll\\CamouflageScreenshot\\"), i, _T(".bmp"));
		lplCamouflageImage[i].Load(PhotoPath);
		hCamouflageImage[i] = lplCamouflageImage[i].Detach();
	}

	return true;
}
bool HookFree()
{
	for (DWORD i = 0; i < MAXN_PHOTO; i++)
		DeleteObject(hCamouflageImage[i]);
	return true;
}


//自定义的假函数
//禁止全屏
BOOL WINAPI hookMoveWindow(HWND hWnd, int X, int Y, int nWidth, int nHeight, BOOL bRepaint)
{
	if (bDisableFullScreen)
	{
		WCHAR szTitle[128];
		GetWindowTextW(hWnd, szTitle, 128);
		//要允许复合窗口中的子窗口回到父窗口
		//复合窗口中的子窗口负责全屏显示
		if (!wcscmp(szTitle, L"视频直播"))
		{
			if (nWidth == iScreenX && nHeight == iScreenY)
				return TRUE;
			else
				return trueMoveWindow(hWnd, X, Y, nWidth, nHeight, bRepaint);
		}
		for (auto i : szMainWindowTitle)
		{
			if (i[0] == 0) break;
			else if (!wcscmp(i, szTitle))
				return TRUE;
		}
	}
	return trueMoveWindow(hWnd, X, Y, nWidth, nHeight, bRepaint);
}
HWND WINAPI hookSetParent(HWND hWndChild, HWND hWndNewParent)
{
	if (bDisableFullScreen)
	{
		WCHAR szTitle[128];
		GetWindowText(hWndChild, szTitle, 128);
		//禁止复合窗口的子窗口离开父窗口
		if (!wcscmp(szTitle, L"视频直播"))
		{
			if (hWndNewParent == NULL)
				return NULL;
		}
	}
	return trueSetParent(hWndChild, hWndNewParent);
}
BOOL WINAPI hookSetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags)
{
	if (bDisableFullScreen)
	{
		if (GetParent(hWnd)) {
			return trueSetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
		}
		return trueSetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags | SWP_NOZORDER );
	}
	return trueSetWindowPos(hWnd, hWndInsertAfter, X, Y, cx, cy, uFlags);
}
LONG WINAPI hookSetWindowLongA(HWND hWnd, int nIndex, LONG dwNewLong)
{
	if (bDisableFullScreen)
	{
		WCHAR szTitle[128];
		GetWindowTextW(hWnd, szTitle, 128);
		for (auto i : szMainWindowTitle)
			if (i[0] == 0) break;
			else if (!wcscmp(i, szTitle))
				return GetWindowLongA(hWnd, nIndex);
	}
	return trueSetWindowLongA(hWnd, nIndex, dwNewLong);
}
LONG WINAPI hookSetWindowLongW(HWND hWnd, int nIndex, LONG dwNewLong)
{
	if (bDisableFullScreen )
	{
		if (GetParent(hWnd)) {
			return trueSetWindowLongW(hWnd, nIndex, dwNewLong);
		}
		return trueSetWindowLongW(hWnd, nIndex, dwNewLong);
	}
	return trueSetWindowLongW(hWnd, nIndex, dwNewLong);
}
BOOL WINAPI hookSetForegroundWindow(HWND hWnd)
{
	if (bDisableFullScreen)
		return TRUE;
	return trueSetForegroundWindow(hWnd);
}
BOOL WINAPI hookShowWindow(HWND hWnd, int  nCmdShow)
{
	if (bDisableFullScreen)
	{
		WCHAR szTitle[128];
		GetWindowText(hWnd, szTitle, 128);
		if (!wcscmp(szTitle, L"BlackScreen Window"))	//很智障的名字
			return TRUE;								//黑屏窗口不显示
		if(!GetParent(hWnd))
			trueSetWindowLongW(hWnd, GWL_STYLE, WS_OVERLAPPEDWINDOW);
	}
	return trueShowWindow(hWnd, nCmdShow);
}

//解锁键盘
LRESULT WINAPI LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}
LRESULT WINAPI LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	return CallNextHookEx(NULL, nCode, wParam, lParam);
}
HHOOK WINAPI hookSetWindowsHookExA(int idHook, HOOKPROC lpfn, HINSTANCE hmod, DWORD dwThreadId)
{
	if (bUnlockKeyboard)
	{
		if (idHook == WH_KEYBOARD_LL || idHook == WH_KEYBOARD)
			lpfn = LowLevelKeyboardProc;
		else if (idHook == WH_MOUSE_LL || idHook == WH_MOUSE)
			lpfn = LowLevelMouseProc;
	}
	return trueSetWindowsHookExA(idHook, lpfn, hmod, dwThreadId);
}
HHOOK WINAPI hookSetWindowsHookExW(int idHook, HOOKPROC lpfn, HINSTANCE hmod, DWORD dwThreadId)
{
	if (bUnlockKeyboard)
	{
		if (idHook == WH_KEYBOARD_LL || idHook == WH_KEYBOARD)
			lpfn = LowLevelKeyboardProc;
		else if (idHook == WH_MOUSE_LL || idHook == WH_MOUSE)
			lpfn = LowLevelMouseProc;
	}
	return trueSetWindowsHookExW(idHook, lpfn, hmod, dwThreadId);
}

//禁止运行程序
NTSTATUS NTAPI hookNtCreateProcessEx(PHANDLE ProcessHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL, HANDLE ParentProcess, BOOLEAN InheritObjectTable, HANDLE SectionHandle OPTIONAL, HANDLE DebugPort OPTIONAL, HANDLE ExceptionPort OPTIONAL, BOOLEAN InJob)
{
	//win xp
	if (bDisableExecute) return STATUS_SUCCESS;
	return trueNtCreateProcessEx(ProcessHandle, DesiredAccess, ObjectAttributes, ParentProcess, InheritObjectTable, SectionHandle, DebugPort, ExceptionPort, InJob);
}
NTSTATUS NTAPI hookNtCreateUserProcess(OUT PHANDLE ProcessHandle, OUT PHANDLE ThreadHandle, IN ACCESS_MASK ProcessDesiredAccess, IN ACCESS_MASK ThreadDesiredAccess, IN POBJECT_ATTRIBUTES ProcessObjectAttributes OPTIONAL, IN POBJECT_ATTRIBUTES ThreadObjectAttributes OPTIONAL, IN ULONG CreateProcessFlags, IN ULONG CreateThreadFlags, IN PRTL_USER_PROCESS_PARAMETERS ProcessParameters, IN PVOID Parameter9, IN PNT_PROC_THREAD_ATTRIBUTE_LIST AttributeList)
{
	//win 7 +
	if (bDisableExecute) return STATUS_SUCCESS;
	return trueNtCreateUserProcess(ProcessHandle, ThreadHandle, ProcessDesiredAccess, ThreadDesiredAccess, ProcessObjectAttributes, ThreadObjectAttributes, CreateProcessFlags, CreateThreadFlags, ProcessParameters, Parameter9, AttributeList);
}

//禁止文件过滤
void OpenDriver()
{
	hDeviceTDNetFilter = CreateFileW(L"\\\\.\\TDNetFilter", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	hDeviceTDKeybd = CreateFileW(L"\\\\.\\TDKeybd", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	hDeviceTDProcHook = CreateFileW(L"\\\\.\\TDProcHook", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
}
void CloseDriver()
{
	CloseHandle(hDeviceTDKeybd);
	CloseHandle(hDeviceTDNetFilter);
	CloseHandle(hDeviceTDProcHook);
}
BOOL WINAPI hookDeviceIoControl(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped)
{
	if (bDisableDriver)
		if (hDevice == hDeviceTDKeybd || hDevice == hDeviceTDNetFilter || hDevice == hDeviceTDProcHook)
			return TRUE;
	return trueDeviceIoControl(hDevice, dwIoControlCode, lpInBuffer, nInBufferSize, lpOutBuffer, nOutBufferSize, lpBytesReturned, lpOverlapped);
}
HRESULT WINAPI hookFilterSendMessage(HANDLE hPort, LPVOID lpInBuffer, DWORD dwInBufferSize, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned)
{
	//lpInbuffer: A 00 00 00 00 00 00 00 00 00 00 00 00 00 00
	//lpInbuffer + 0 --  control code
	//				应用程序
	//					05 -> 全部控制
	//		光驱			U盘
	//		0d				08 -> 全开
	//		10				0b -> 只读
	//		0f				0a -> 禁止执行
	//		0e				09 -> 全部禁止
	//				
	//lpInbuffer + 8 -- control context, this is  a address
	//the first 4 byte of the address means the length
	//and following are 4 byte means the  action , 0x6f means All Allow   *IMPORTANT
	//following are 12 byte circles
	if (bDisableDriver)
	{
		DWORD* typeCode = (DWORD*)lpInBuffer;
		switch (*typeCode)
		{
		case 0x10:
		case 0x0f:
		case 0x0e:
			*typeCode = 0x0d;	//光驱的限制
			break;
		case 0x0b:
		case 0x0a:
		case 0x09:
			*typeCode = 0x08;	//U盘的限制
			break;
		case 0x05:
			DWORD * *p = (DWORD**)((DWORD*)lpInBuffer + 2);	//locate
			BYTE* patchPtr = (BYTE*)*p;		//only DWORD* can conv to BYTE*
			if (patchPtr)
			{
				patchPtr += 4;		//offset = 4, the first 4 bytes means the length of the buf
				*patchPtr = 0x6f;	//patch code
			}
		}
	}
	return trueFilterSendMessage(hPort, lpInBuffer, dwInBufferSize, lpOutBuffer, dwOutBufferSize, lpBytesReturned);
}

//禁止远程控制
UINT WINAPI hookSendInput(_In_ UINT cInputs, _In_reads_(cInputs) LPINPUT pInputs, _In_ int cbSize)
{
	if (bDisableRemoteControl) return cInputs;
	return trueSendInput(cInputs, pInputs, cbSize);
}

//截图伪装
BOOL WINAPI hookBitBlt(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop)
{
	bool bCamouflage = false;
	if (bCamouflageScreenShot)
	{
		if (cx >= iScreenX - 40 && cy >= iScreenY - 40)
		{
			//这里的DesktopDC使用黑名单方式
			//因为极域在监视的时候会将主题强制改为Basic
			//Desktop DC会变
			//此外，重启explore.exe也会改变
			//极域每次监视前都先获取全屏的DC，于是检测到获取全屏幕时记录黑名单
			//被记录的这个hSrcDC就是全屏的DC
			hDesktopDC = hdcSrc;
			bCamouflage = true;
		}
		else if (hdcSrc == hDesktopDC)
		{
			bCamouflage = true;
		}
	}
	if (bCamouflage)			//劫持当前的BitBlt操作
	{
		x = y = 0;
		cx = iScreenX;
		cy = iScreenY;
		x1 = y1 = 0;
		HDC hCamouflageSrcDC;
		hCamouflageSrcDC = CreateCompatibleDC(hdc);
		if (time(NULL) % 4 == 0)
		{
			srand((UINT)time(NULL));
			dwImageIndex = rand() % MAXN_PHOTO;
		}
		HBITMAP hOldBitmap = (HBITMAP)SelectObject(hCamouflageSrcDC, hCamouflageImage[dwImageIndex]);

		BOOL bRet = trueBitBlt(hdc, x, y, cx, cy, hCamouflageSrcDC, x1, y1, rop);

		SelectObject(hCamouflageSrcDC, hOldBitmap);
		DeleteObject(hOldBitmap);
		DeleteDC(hCamouflageSrcDC);
		return bRet;
	}
	return trueBitBlt(hdc, x, y, cx, cy, hdcSrc, x1, y1, rop);
}

//禁止枚举进程, 窗口
NTSTATUS WINAPI hookZwQuerySystemInformation(
	_In_      SYSTEM_INFORMATION_CLASS SystemInformationClass,
	_Inout_   PVOID                    SystemInformation,
	_In_      ULONG                    SystemInformationLength,
	_Out_opt_ PULONG                   ReturnLength
) 
{
	ULONG mes = SystemInformationClass;
	if (bDisableProcessOperation && mes == 5) return NT_ERROR(1);
	return trueZwQuerySystemInformation(SystemInformationClass, SystemInformation, SystemInformationLength, ReturnLength);
}
NTSTATUS WINAPI hookNtOpenProcess(
	_Out_ PHANDLE ProcessHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ PCLIENT_ID ClientId
)
{
	if(bDisableProcessOperation)
		return NT_SUCCESS(0);
	return trueNtOpenProcess(ProcessHandle, DesiredAccess, ObjectAttributes, ClientId);
}
BOOL hookEnumWindows(WNDENUMPROC lpEnumFunc, LPARAM lParam)
{
	return FALSE;
}
LRESULT hookSendMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	if(bDisableProcessOperation)
		return 0;
	return trueSendMessage(hWnd, Msg, wParam, lParam);
}