#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <tchar.h>


int main()
{
	_SYSTEM_INFO lpSysInfo ;
	WORD wProcessorArchitecture;
	DWORD dwPageSize;
	
	GetSystemInfo(&lpSysInfo);
	
	wProcessorArchitecture = lpSysInfo.wProcessorArchitecture;
	dwPageSize = lpSysInfo.dwPageSize;

	if (wProcessorArchitecture == PROCESSOR_ARCHITECTURE_INTEL) {
		_tprintf(TEXT("PROCESSOR_ARCHITECTURE : x86 \n"));
	}

	if (wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64) {
		_tprintf(TEXT("PROCESSOR_ARCHITECTURE : x64 \n"));
	}

	
}
