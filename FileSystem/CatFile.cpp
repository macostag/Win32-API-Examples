#include "pch.h"
#include <iostream>
#include <Windows.h>
#define BUF_SIZE 512

static void CatFile(HANDLE,HANDLE);

int main(int argc, LPCSTR argv[])
{
	BOOL dashS;
	int iArg;
	int iFirstFile;

	HANDLE hInfile;
	//Retrieves a standard input handle 
	HANDLE hStdinfile = GetStdHandle(STD_INPUT_HANDLE);
	//Retrieves a standard output handle
	HANDLE hStdoutfile = GetStdHandle(STD_OUTPUT_HANDLE);
	
	for (int iArg = 1; iArg < argc; iArg++) {
		hInfile = CreateFileA(argv[iArg], GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

		if (hInfile == INVALID_HANDLE_VALUE) {

			return 1;
		}
		else {

			CatFile(hInfile,hStdoutfile);

		}
	}

}

static void CatFile(HANDLE hInfile,HANDLE hOutfile) {

	TCHAR buffer[BUF_SIZE];
	DWORD nIn, nOut;

	while (ReadFile(hInfile,buffer,BUF_SIZE,&nIn,NULL) && nIn > 0 ){
		
		//WriteFile(hOutfile, buffer, nIn, &nOut, NULL);
		WriteConsoleA(hOutfile, buffer, BUF_SIZE, NULL, NULL);
	}
	return;
}
