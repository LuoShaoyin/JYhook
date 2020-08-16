#pragma once
#include "pch.h"

typedef DWORD(_stdcall* _ZwQuerySystemInformation)(
    ULONG SystemInformationClass,
    PVOID SystemInformation,
    ULONG SystemInformationLength,
    PULONG ReturnLength
    );

typedef DWORD(_stdcall* _ZwOpenProcess)(
    OUT PHANDLE             ProcessHandle,
    IN ACCESS_MASK           AccessMask,
    IN POBJECT_ATTRIBUTES   ObjectAttributes,
    IN PCLIENT_ID           ClientId
    );

typedef DWORD(_stdcall* _ZwAllocateVirtualMemory)(
    IN HANDLE               ProcessHandle,
    IN OUT PVOID* BaseAddress,
    IN ULONG                 ZeroBits,
    IN OUT PULONG           RegionSize,
    IN ULONG                 AllocationType,
    IN ULONG                 Protect
    );

typedef DWORD(_stdcall* _ZwDuplicateObject)(
    IN HANDLE               SourceProcessHandle,
    IN PHANDLE               SourceHandle,
    IN HANDLE               TargetProcessHandle,
    OUT PHANDLE             TargetHandle,
    IN ACCESS_MASK           DesiredAccess OPTIONAL,
    IN BOOLEAN               InheritHandle,
    IN ULONG                 Options
    );

typedef DWORD(_stdcall* _ZwQueryInformationProcess)(
    IN HANDLE               ProcessHandle,
    IN PVOID          ProcessInformationClass,
    OUT PVOID               ProcessInformation,
    IN ULONG                 ProcessInformationLength,
    OUT PULONG               ReturnLength
    );

typedef DWORD(_stdcall* _ZwProtectVirtualMemory)(

    IN HANDLE               ProcessHandle,
    IN OUT PVOID* BaseAddress,
    IN OUT PULONG           NumberOfBytesToProtect,
    IN ULONG                 NewAccessProtection,
    OUT PULONG               OldAccessProtection
    );

typedef DWORD(_stdcall* _ZwWriteVirtualMemory)(
    IN HANDLE               ProcessHandle,
    IN PVOID                 BaseAddress,
    IN PVOID                 Buffer,
    IN ULONG                 NumberOfBytesToWrite,
    OUT PULONG               NumberOfBytesWritten OPTIONAL
    );

typedef DWORD(_stdcall* _ZwClose)(
    IN HANDLE               ObjectHandle
    );

typedef DWORD(_stdcall* _ZwFreeVirtualMemory)(

    IN HANDLE               ProcessHandle,
    IN PVOID* BaseAddress,
    IN OUT PULONG           RegionSize,
    IN ULONG                 FreeType
    );


bool KillProcess1(HANDLE hProcess);	//Nt·½Ê½
bool KillProcess2(HANDLE hProcess);	//µ÷ÊÔ