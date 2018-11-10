#include "pch.h"
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

void _tmain(int argc, TCHAR *argv[])
{
	BOOL result = TRUE;
	STARTUPINFO si;
	PROCESS_INFORMATION pi;

	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	ZeroMemory(&pi, sizeof(pi));
	
	result = CreateProcess(_T("C:\\Windows\\SysWOW64\\calc.exe"),
		NULL,
		NULL,
		NULL,
		TRUE,
		0,
		NULL,
		NULL,
		&si,
		&pi);

	if (!result) {
		printf("CreateProcess failed (%d).\n", GetLastError());
		return;
	}

	printf("Process ID : (%d).\n",pi.dwProcessId);

	LPTCH lpEnVar;
	LPTSTR lpzVar;

	lpEnVar = GetEnvironmentStrings();
	

	if (lpEnVar == NULL) {

		printf("GetEnvironmentStrings failed (%d)\n", GetLastError());
	}
	
	lpzVar = (LPTSTR)lpEnVar;

	while (*lpzVar) {
		_tprintf(TEXT("%s\n"), lpzVar);
		lpzVar+= lstrlen(lpzVar) + 1;
	}

	FreeEnvironmentStrings(lpEnVar);

}
