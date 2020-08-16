//hook函数声明
//感谢martona的mhook项目
//https://github.com/martona/mhook
//*********************************

#pragma once
#include "pch.h"
#include "mhook-lib\mhook.h"
#include "Control.h"

#define MAXN_PHOTO 8		//伪装截图的图片数

//定义出函数指针
typedef BOOL(WINAPI* _MoveWindow)(__in HWND hWnd, __in int X, __in int Y, __in int nWidth, __in int nHeight, __in BOOL bRepaint);
typedef HWND(WINAPI* _SetParent)(HWND hWndChild, HWND hWndNewParent);
typedef BOOL(WINAPI* _SetWindowPos)(__in HWND hWnd, __in_opt HWND hWndInsertAfter, __in int X, __in int Y, __in int cx, __in int cy, __in UINT uFlags);
typedef LONG(WINAPI* _SetWindowLongA)(__in HWND hWnd, __in int nIndex, __in LONG dwNewLong);
typedef LONG(WINAPI* _SetWindowLongW)(__in HWND hWnd, __in int nIndex, __in LONG dwNewLong);
typedef BOOL(WINAPI* _SetForegroundWindow)(HWND hWnd);
typedef BOOL(WINAPI* _ShowWindow)(HWND hWnd, int  nCmdShow);

typedef HHOOK(WINAPI* _SetWindowsHookExA)(__in int idHook, __in HOOKPROC lpfn, __in_opt HINSTANCE hmod, __in DWORD dwThreadId);
typedef HHOOK(WINAPI* _SetWindowsHookExW)(__in int idHook, __in HOOKPROC lpfn, __in_opt HINSTANCE hmod, __in DWORD dwThreadId);

typedef NTSTATUS(NTAPI* _NtCreateProcessEx)(PHANDLE ProcessHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL, HANDLE ParentProcess, BOOLEAN InheritObjectTable, HANDLE SectionHandle OPTIONAL, HANDLE DebugPort OPTIONAL, HANDLE ExceptionPort OPTIONAL, BOOLEAN InJob);
typedef struct _NT_PROC_THREAD_ATTRIBUTE_ENTRY {
	ULONG Attribute;    // PROC_THREAD_ATTRIBUTE_XXX，参见MSDN中UpdateProcThreadAttribute的说明
	SIZE_T Size;        // Value的大小
	ULONG_PTR Value;    // 保存4字节数据（比如一个Handle）或数据指针
	ULONG Unknown;      // 总是0，可能是用来返回数据给调用者
} PROC_THREAD_ATTRIBUTE_ENTRY, * PPROC_THREAD_ATTRIBUTE_ENTRY;
typedef struct _NT_PROC_THREAD_ATTRIBUTE_LIST {
	ULONG Length;       // 结构总大小
	PROC_THREAD_ATTRIBUTE_ENTRY Entry[1];
} NT_PROC_THREAD_ATTRIBUTE_LIST, * PNT_PROC_THREAD_ATTRIBUTE_LIST;
typedef NTSTATUS(NTAPI* _NtCreateUserProcess)(OUT PHANDLE ProcessHandle, OUT PHANDLE ThreadHandle, IN ACCESS_MASK ProcessDesiredAccess, IN ACCESS_MASK ThreadDesiredAccess, IN POBJECT_ATTRIBUTES ProcessObjectAttributes OPTIONAL, IN POBJECT_ATTRIBUTES ThreadObjectAttributes OPTIONAL, IN ULONG CreateProcessFlags, IN ULONG CreateThreadFlags, IN PRTL_USER_PROCESS_PARAMETERS ProcessParameters, IN PVOID Parameter9, IN PNT_PROC_THREAD_ATTRIBUTE_LIST AttributeList);

typedef BOOL(WINAPI* _DeviceIoControl)(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped);
typedef HRESULT(WINAPI* _FilterSendMessage)(HANDLE hPort, LPVOID lpInBuffer, DWORD dwInBufferSize, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned);

typedef UINT(WINAPI* _SendInput)(_In_ UINT cInputs, _In_reads_(cInputs) LPINPUT pInputs, _In_ int cbSize);

typedef BOOL(WINAPI* _BitBlt)(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop);

typedef NTSTATUS(WINAPI* _ZwQuerySystemInformation)(
	_In_      SYSTEM_INFORMATION_CLASS SystemInformationClass,
	_Inout_   PVOID                    SystemInformation,
	_In_      ULONG                    SystemInformationLength,
	_Out_opt_ PULONG                   ReturnLength
);
typedef NTSTATUS(WINAPI* _NtOpenProcess)(
	_Out_ PHANDLE ProcessHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ PCLIENT_ID ClientId
);
typedef BOOL (WINAPI* _EnumWindows)(WNDENUMPROC lpEnumFunc,	LPARAM lParam);
typedef LRESULT (WINAPI* _SendMessage)(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam );

void GetTrueFuncAddress();
void SetHooks();
void UnHooks();

bool HookInit();
bool HookFree();


//自定义的假函数
BOOL WINAPI hookMoveWindow(__in HWND hWnd, __in int X, __in int Y, __in int nWidth, __in int nHeight, __in BOOL bRepaint);
HWND WINAPI hookSetParent(HWND hWndChild,HWND hWndNewParent);
BOOL WINAPI hookSetWindowPos(__in HWND hWnd, __in_opt HWND hWndInsertAfter, __in int X, __in int Y, __in int cx, __in int cy, __in UINT uFlags);
LONG WINAPI hookSetWindowLongA(__in HWND hWnd, __in int nIndex, __in LONG dwNewLong);
LONG WINAPI hookSetWindowLongW(__in HWND hWnd, __in int nIndex, __in LONG dwNewLong);
BOOL WINAPI hookSetForegroundWindow(HWND hWnd);
BOOL WINAPI hookShowWindow(HWND hWnd, int  nCmdShow);

LRESULT WINAPI LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam);
LRESULT WINAPI LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);
HHOOK WINAPI hookSetWindowsHookExA(__in int idHook, __in HOOKPROC lpfn, __in_opt HINSTANCE hmod, __in DWORD dwThreadId);
HHOOK WINAPI hookSetWindowsHookExW(__in int idHook, __in HOOKPROC lpfn, __in_opt HINSTANCE hmod, __in DWORD dwThreadId);

NTSTATUS NTAPI hookNtCreateProcessEx(PHANDLE ProcessHandle, ACCESS_MASK DesiredAccess, POBJECT_ATTRIBUTES ObjectAttributes OPTIONAL, HANDLE ParentProcess, BOOLEAN InheritObjectTable, HANDLE SectionHandle OPTIONAL, HANDLE DebugPort OPTIONAL, HANDLE ExceptionPort OPTIONAL, BOOLEAN InJob);
NTSTATUS NTAPI hookNtCreateUserProcess(OUT PHANDLE ProcessHandle, OUT PHANDLE ThreadHandle, IN ACCESS_MASK ProcessDesiredAccess, IN ACCESS_MASK ThreadDesiredAccess, IN POBJECT_ATTRIBUTES ProcessObjectAttributes OPTIONAL, IN POBJECT_ATTRIBUTES ThreadObjectAttributes OPTIONAL, IN ULONG CreateProcessFlags, IN ULONG CreateThreadFlags, IN PRTL_USER_PROCESS_PARAMETERS ProcessParameters, IN PVOID Parameter9, IN PNT_PROC_THREAD_ATTRIBUTE_LIST AttributeList);

void OpenDriver();
void CloseDriver();
BOOL WINAPI hookDeviceIoControl(HANDLE hDevice, DWORD dwIoControlCode, LPVOID lpInBuffer, DWORD nInBufferSize, LPVOID lpOutBuffer, DWORD nOutBufferSize, LPDWORD lpBytesReturned, LPOVERLAPPED lpOverlapped);
HRESULT WINAPI hookFilterSendMessage(HANDLE hPort, LPVOID lpInBuffer, DWORD dwInBufferSize, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned);

UINT WINAPI hookSendInput(_In_ UINT cInputs, _In_reads_(cInputs) LPINPUT pInputs, _In_ int cbSize);

BOOL WINAPI hookBitBlt(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop);

NTSTATUS WINAPI hookZwQuerySystemInformation(
	_In_      SYSTEM_INFORMATION_CLASS SystemInformationClass,
	_Inout_   PVOID                    SystemInformation,
	_In_      ULONG                    SystemInformationLength,
	_Out_opt_ PULONG                   ReturnLength
);
NTSTATUS WINAPI hookNtOpenProcess(
	_Out_ PHANDLE ProcessHandle,
	_In_ ACCESS_MASK DesiredAccess,
	_In_ POBJECT_ATTRIBUTES ObjectAttributes,
	_In_opt_ PCLIENT_ID ClientId
);
BOOL hookEnumWindows(WNDENUMPROC lpEnumFunc, LPARAM lParam);
LRESULT  hookSendMessage(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam);