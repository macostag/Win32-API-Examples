#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <tchar.h>

int main(int argc, LPCSTR argv[])
{
	HANDLE hNewFile;

	LPFILETIME  lpSystemTime;
	FILETIME sysTime;
	lpSystemTime = &sysTime;

	if (argc < 2) {
		_tprintf(_T("Usage: touch[options] files"));
		return 1;
	}

	for (int i = 1; i < argc; i++) {
		_tprintf(_T("File: %S \n"),argv[i]);

		hNewFile = CreateFileA(argv[i], GENERIC_READ | GENERIC_WRITE, 0, NULL, 
			OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL,NULL);

		if (hNewFile == INVALID_HANDLE_VALUE) {
			_tprintf(_T("touch error: Cannot open file. \n"));
			continue;
		}

		GetSystemTimeAsFileTime(lpSystemTime);

		SetFileTime(hNewFile, NULL, lpSystemTime, NULL);

		CloseHandle(hNewFile);
	
	}
	

}

