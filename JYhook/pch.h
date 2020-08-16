// pch.h: 这是预编译标头文件。
// 下方列出的文件仅编译一次，提高了将来生成的生成性能。
// 这还将影响 IntelliSense 性能，包括代码完成和许多代码浏览功能。
// 但是，如果此处列出的文件中的任何一个在生成之间有更新，它们全部都将被重新编译。
// 请勿在此处添加要频繁更新的文件，这将使得性能优势无效。

#ifndef PCH_H
#define PCH_H

// 添加要在此处预编译的标头
#pragma warning(disable:28253)


#include "framework.h"
#include <tlhelp32.h>
#include <afxcontrolbars.h>
#include <afxdialogex.h>
#include <atlconv.h>
#include "..\MINT\MINT.h"	//Nt函数支持 https://github.com/Chuyu-Team/MINT

#define RECORD_INFO		0
#define RECORD_SUCCEED	1
#define RECORD_WARNING	2
#define RECORD_ERROR	3
#define RECORD_DEBUG	4
#define AddRecord(Style, Record) theApp.MainDlg->m_RecordDlg->_AddRecord(Style,Record)

#endif //PCH_H
