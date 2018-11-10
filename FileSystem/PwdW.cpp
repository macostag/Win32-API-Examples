#include "pch.h"
#include <Windows.h>
#include <iostream>
#define LEN_PATH (MAX_PATH + 2)

int main()
{
	TCHAR pwdBuff[LEN_PATH];
	DWORD nOfchar;
	
	DWORD lenCurDir = GetCurrentDirectory(LEN_PATH ,pwdBuff);

	if (lenCurDir == 0) {
		printf("ERROR!\n");
		return 1;
	}

	printf("Your current directory is: %S\n", pwdBuff);
	

	return 0;
}

