#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <stdio.h>
#include <sddl.h>

void printError();
void lookupSid(PSID,HANDLE,HANDLE,DWORD);

int main()
{
	BOOL bResult = FALSE;
	BOOL bLookup = FALSE;
	BOOL bConvert = FALSE;
	HANDLE hToken = NULL;
	
	//Opens an currentLocalProcess.
	HANDLE hCurrentProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, GetCurrentProcessId());


	//Opens the access token associated with a process.
	if (!OpenProcessToken(hCurrentProcess, TOKEN_QUERY, &hToken)) {
		printError();
		CloseHandle(hToken);
		CloseHandle(hCurrentProcess);
		return -1;
	}

	//Initial query to determine the necessary buffer size for TokenUser.
	DWORD dwReturnLength = 0;
	bResult = GetTokenInformation(hToken, TokenUser, NULL, 0, &dwReturnLength);


	//Retrieves a specified type of information about user associated with an access token.
	PTOKEN_USER TokenUserInformation = (PTOKEN_USER)LocalAlloc(LPTR, dwReturnLength);
	bResult = GetTokenInformation(hToken, TokenUser, TokenUserInformation, dwReturnLength, &dwReturnLength);

	if (!bResult) {
		printError();
		CloseHandle(hToken);
		CloseHandle(hCurrentProcess);
		return -1;
	}

	//Retrieves the name of the account for this SID and the name of the first domain on which this SID is found.
	lookupSid(TokenUserInformation->User.Sid, hToken, hCurrentProcess,1);
	

	//Converts a security identifier (SID) to a string format.
	LPTSTR lpSID = NULL;
	PSID pSidUser = TokenUserInformation->User.Sid;
	bConvert = ConvertSidToStringSid(pSidUser, &lpSID);

	if (!bConvert) {
		printError();
		CloseHandle(hToken);
		CloseHandle(hCurrentProcess);
		return -1;
	}
	_tprintf(TEXT("User SID access TOKEN : %s\n"), lpSID);


	//Initial query to determine the necessary buffer size for TokenGroups.
	dwReturnLength = 0;
	GetTokenInformation(hToken, TokenGroups, NULL, 0, &dwReturnLength);


	//Retrieves a specified type of information about the group security identifiers (SIDs) in an access token.
	bResult = FALSE;
	PTOKEN_GROUPS TokenGroupsInformation = (PTOKEN_GROUPS)LocalAlloc(LPTR, dwReturnLength);
	bResult = GetTokenInformation(hToken, TokenGroups, TokenGroupsInformation, dwReturnLength, &dwReturnLength);

	if (!bResult) {
		printError();
		CloseHandle(hToken);
		CloseHandle(hCurrentProcess);
		return -1;
	}

	_tprintf(TEXT("\n\nGroups access TOKEN: \n"));
	for (int i = 0; i < TokenGroupsInformation->GroupCount; i++) {

		lookupSid(TokenGroupsInformation->Groups[i].Sid, hToken, hCurrentProcess, 2);

	}

	//Initial query to determine the necessary buffer size for TokenPrivileges.
	dwReturnLength = 0;
	GetTokenInformation(hToken, TokenPrivileges, NULL, 0, &dwReturnLength);

	//Retrieves information about a set of privileges for an access token.
	bResult = FALSE;
	PTOKEN_PRIVILEGES TokenPrivilegesInformation = (PTOKEN_PRIVILEGES)LocalAlloc(LPTR, dwReturnLength);
	bResult = GetTokenInformation(hToken, TokenPrivileges, TokenPrivilegesInformation, dwReturnLength, &dwReturnLength);

	if (!bResult) {
		printError();
		CloseHandle(hToken);
		CloseHandle(hCurrentProcess);
		return -1;
	}

	_tprintf(TEXT("\n\nPrivileges access TOKEN: \n"));

	for (int j = 0; j < TokenPrivilegesInformation->PrivilegeCount; j++) {

		BOOL bLookupPriv = FALSE;
		TCHAR tPrivName[1024];
		DWORD dwPrivName = 1024;
		dwPrivName = sizeof(tPrivName);
		LUID pLuid = TokenPrivilegesInformation->Privileges[j].Luid;


		bLookupPriv = LookupPrivilegeName(NULL, &pLuid, tPrivName, &dwPrivName);

		if (!bLookupPriv) {
			printError();
			CloseHandle(hToken);
			CloseHandle(hCurrentProcess);
			return -1;
		}

		_tprintf(TEXT("%s \n"), tPrivName);
		
	}


	//Close Handles.
	CloseHandle(hToken);
	CloseHandle(hCurrentProcess);
	return 0;
}

void printError()
{
	DWORD eNum;
	TCHAR sysMsg[256];
	TCHAR* p;
	TCHAR msg[] = TEXT("ERROR");
	eNum = GetLastError();
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, eNum,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		sysMsg, 256, NULL);

	// Trim the end of the line and terminate it with a null
	p = sysMsg;
	while ((*p > 31) || (*p == 9))
		++p;
	do { *p-- = 0; } while ((p >= sysMsg) &&
		((*p == '.') || (*p < 33)));

	// Display the message
	_tprintf(TEXT("\n\t%s failed with error %d (%s)"), msg, eNum, sysMsg);
}

VOID lookupSid(PSID pSid,HANDLE hToken, HANDLE hCurrentProcess, DWORD selection) {

	BOOL bLookup = FALSE;
	DWORD dwUserName = 1024;
	DWORD dwDomainName = 1024;
	SID_NAME_USE psUser;
	TCHAR tUsername[1024];
	TCHAR tDomain[1024];

	dwUserName = sizeof(tUsername);
	dwDomainName = sizeof(tDomain);

	bLookup = LookupAccountSid(NULL, pSid, tUsername, &dwUserName, tDomain, &dwDomainName, &psUser);
	
	if (!bLookup) {
		printError();
		CloseHandle(hToken);
		CloseHandle(hCurrentProcess);
		exit(-1);
	}

	switch (selection)
	{
	
	case 1:
		_tprintf(TEXT("User name access TOKEN : %s \n"), tUsername);
		break;

	case 2:
		_tprintf(TEXT("%s \n"), tUsername);
		break;

	case 3:

		break;
	
	default:
		break;
	}
}
