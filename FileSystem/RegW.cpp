#include "pch.h"
#include <iostream>
#include <Windows.h>
#include <tchar.h>
#include <strsafe.h>

#define MAX_KEY_LENGTH 255
#define MAX_VALUE_NAME 16383

int main(int argc, LPCSTR argv[])
{
	HKEY hKey,hKey1;
	hKey = HKEY_CURRENT_USER;
	LPCSTR lsubKey = NULL;
	HKEY pKeyResult;
	
	   
	if (RegOpenKeyEx(hKey, TEXT("SOFTWARE\\7-Zip"), 0, KEY_READ, &pKeyResult) != ERROR_SUCCESS) {
		_tprintf(TEXT("Error : Open Key \n"));
		return 1;
	}
	
	TCHAR achKey[MAX_KEY_LENGTH];   // buffer for subkey name
	TCHAR achValue[MAX_VALUE_NAME];
	
	DWORD cbName,cbValueName,cbValue;                   // size of name string
	TCHAR buffer[MAX_PATH];
	LPWSTR    lpClass = buffer;  // buffer for class name 

	DWORD    cchClassName = MAX_PATH;  // size of class string 
	DWORD    cSubKeys = 0;               // number of subkeys 
	DWORD    cbMaxSubKey;              // longest subkey size 
	DWORD    cchMaxClass;              // longest class string 
	DWORD    cValues;              // number of values for key 
	DWORD    cchMaxValue;          // longest value name 
	DWORD    cbMaxValueData;       // longest value data 
	DWORD    cbSecurityDescriptor; // size of security descriptor 
	FILETIME ftLastWriteTime;      // last write time 

	DWORD i, retCode;

	retCode = RegQueryInfoKey(pKeyResult,	//A handle to an open registry key
		lpClass,	//A pointer to a buffer that receives the user-defined class of the key
						&cchClassName, //A pointer to a variable that specifies the size of the buffer pointed to by the lpClass parameter,
						NULL, //This parameter is reserved
						&cSubKeys, //A pointer to a variable that receives the number of subkeys that are contained by the specified ke
						&cbMaxSubKey, //A pointer to a variable that receives the size of the key's subkey with the longest name
						&cchMaxClass, //A pointer to a variable that receives the size of the longest string that specifies a subkey class	
						&cValues,   //A pointer to a variable that receives the number of values that are associated with the key 
						&cchMaxValue, // A pointer to a variable that receives the size of the key's longest value name
						&cbMaxValueData, // A pointer to a variable that receives the size of the longest data component among the key's values, in bytes. 
						&cbSecurityDescriptor,   // A pointer to a variable that receives the size of the key's security descriptor 
						&ftLastWriteTime);       // A pointer to a FILETIME structure that receives the last write time.

	if (retCode != ERROR_SUCCESS) {
		_tprintf(TEXT("Error : Query Key \n"));
		return 1;
	}
	
	_tprintf(TEXT("Number of Sub Keys: %d \n"), cSubKeys);
	
	//Enum Keys
	for (int i = 0; i < cSubKeys; i++) {
		
		cbName = MAX_VALUE_NAME;
		
		retCode =	RegEnumKeyEx(pKeyResult,
			i,
			achKey,
			&cbName,
			NULL,
			NULL,
			NULL,
			&ftLastWriteTime);
		
 		if (retCode == ERROR_SUCCESS) {

			_tprintf(TEXT("%s\n"), achKey);
		}

	}

	_tprintf(TEXT("\nNumber of values: %d\n"), cValues);

	//Enum Values
	for (int i = 0; i < cValues; i++) {
		cbValue = MAX_VALUE_NAME;

		RegEnumValue(pKeyResult,
			i,
			achValue,
			&cbValue,
			NULL,
			NULL,
			NULL,
			NULL);

		if (retCode == ERROR_SUCCESS)
		{
			_tprintf(TEXT("(%d) %s\n"), i + 1, achValue);
		}


	}


	return 0;
}
