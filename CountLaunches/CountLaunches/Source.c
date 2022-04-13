#include <Windows.h>
#include <lmaccess.h>
#include <stdio.h>


int main() {
	LONG iRed;
	HKEY hKey;
	DWORD dwData = 0;
	DWORD cBuff = 4;
	iRed = RegCreateKeyEx(HKEY_LOCAL_MACHINE, L"SOFTWARE\\COUTING\\PROGRAM\\LAUNCHES", 0, NULL, REG_OPTION_VOLATILE, KEY_ALL_ACCESS | KEY_WOW64_64KEY, NULL, &hKey, NULL);
	if (iRed != ERROR_SUCCESS)
	{
		printf("The section was not created!\n");
		return 0;
	}
	if (iRed = RegQueryValueEx(hKey, L"DISCOVERY", NULL, NULL, &dwData, &cBuff) == ERROR_SUCCESS) {
		dwData++;
		if (dwData > 3) 
		{
			printf("The trial period is over!");
			return 0;
		} 
		else 
		{
			printf("Number of program launches: %d/3\n", dwData);
			RegSetValueEx(hKey, L"DISCOVERY", NULL, REG_DWORD, &dwData, 4);
		}
	}
	return 0;
}