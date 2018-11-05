#include "pch.h"
#include <iostream>
#include <windows.h>
#include <tchar.h>
#include <stdlib.h>
#include <sddl.h>
#include <stdio.h>

#define BUFFER_SIZE 32767

int main()
{
	//find the current user's name
	TCHAR tAccountName[BUFFER_SIZE];
	DWORD lAccountName = BUFFER_SIZE;

	if (!GetUserName(tAccountName,&lAccountName)) {
		_tprintf(TEXT("GetUserName() failed with error %d \n"), GetLastError());
		return -1;
	}

	//Retrieves a security identifier(SID) for the current user.
	LPTSTR tSystemName = NULL;
	BYTE pSid[SECURITY_MAX_SID_SIZE];
	DWORD dSid = SECURITY_MAX_SID_SIZE;
	TCHAR lpRDomain[BUFFER_SIZE];
	DWORD dRDomain = BUFFER_SIZE;
	SID_NAME_USE spName = SidTypeInvalid;

	BOOL bResult = LookupAccountName(tSystemName, tAccountName, pSid, &dSid, lpRDomain, &dRDomain, &spName);
	if (!bResult) {
		_tprintf(TEXT("LookupAccountName() failed with error %d \n"), GetLastError());
		return -1;
	}

	//Converts a security identifier (SID) to a string format.
	LPTSTR lpSID = NULL;

	BOOL bConvert = ConvertSidToStringSid(pSid, &lpSID);
	if (!bConvert) {
		_tprintf(TEXT("ConvertSidToStringSid() failed with error %d \n"), GetLastError());
		return -1;
	}
	
	_tprintf(TEXT("Current User: %s \n"), tAccountName);
	_tprintf(TEXT("Domain: %s \n"), lpRDomain);
	_tprintf(TEXT("SID: %s \n"), lpSID);

	return 0;

}
