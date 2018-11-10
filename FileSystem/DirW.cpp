#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <tchar.h>


int main(int argc, LPTSTR argv[])
{
	HANDLE searchHandle;
	DWORD pathLength;
	TCHAR currPath[MAX_PATH];
	WIN32_FIND_DATA findData;
	
	pathLength = GetCurrentDirectory(MAX_PATH, currPath);

	if (pathLength == 0 || pathLength > MAX_PATH) {

		std::cout << "GetCurrentDirectory failed";
	}
	
	wcscat_s(currPath, _T("\\*"));

	searchHandle = FindFirstFile(currPath, &findData);

	if (searchHandle == INVALID_HANDLE_VALUE) {
		std::cout << "Error opening Search Handle.";
		return 1;
	}
	
	do{
		
		DWORD tFile = GetFileAttributes(findData.cFileName);

		if (tFile == INVALID_FILE_ATTRIBUTES) {
			std::cout << "Error File Attributes.";
			return 1;
		}
		if (tFile == FILE_ATTRIBUTE_DIRECTORY) {
			_tprintf(TEXT("DIRECTORY : %s\n"), findData.cFileName);
					}
		else {
			_tprintf(TEXT("FILE : %s\n"), findData.cFileName);
		}

		LPSYSTEMTIME lFcreationTime ;
		SYSTEMTIME access_st;
		lFcreationTime = &access_st;

		FileTimeToSystemTime(&(findData.ftCreationTime), lFcreationTime);

		_tprintf(TEXT("CREATION TIME: " "%02d/%02d/%d  %02d:%02d \n\n"), 
			lFcreationTime->wMonth, lFcreationTime->wDay, lFcreationTime->wYear,
			lFcreationTime->wHour, lFcreationTime->wMinute);

		
	}while (FindNextFile(searchHandle, &findData) != 0);

	FindClose(searchHandle);

	return 0;
}	
