#include "pch.h"
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <stdio.h>


#define INFO_BUFFER_SIZE 32767

int main()
{
	TCHAR lpBuffer[INFO_BUFFER_SIZE];
	DWORD dBuffer = INFO_BUFFER_SIZE;

	if (!GetUserName(lpBuffer, &dBuffer)) {

		_tprintf(TEXT("Error: GetUserName"));

	}else {

		_tprintf(TEXT("\nUser name:          %s"), lpBuffer);

	}
}
