#include <stdio.h>
#include <Windows.h>
#include <tchar.h>
#include <WtsApi32.h>
#include <sddl.h>

#pragma comment (lib, "wtsapi32")
#pragma comment (lib, "Advapi32")


void main() {
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
		if (dwData > 1)
		{
			dwData--;
			dwData--;
			RegSetValueEx(hKey, L"DISCOVERY", NULL, REG_DWORD, &dwData, 4);
			return 0;
		}
		else
		{
			RegSetValueEx(hKey, L"DISCOVERY", NULL, REG_DWORD, &dwData, 4);
		}
	}

	DWORD level = 1;
	PWTS_PROCESS_INFO_EX processListing = NULL;
	DWORD processCount = 0;
	char Button;
	do
	{
		if (!WTSEnumerateProcessesEx(WTS_CURRENT_SERVER_HANDLE, &level, WTS_ANY_SESSION, (LPTSTR*)&processListing, &processCount)) 
		{
			_tprintf(_T("WTSEnumerateProcessesEx"), 0);
		}

		_tprintf(_T("Processes found: %d\n\n"), processCount);
		LPTSTR stringSID = NULL;
		PWTS_PROCESS_INFO_EX originalPtr = processListing;
		_tprintf(_T("#\tPID\tHandles\tThreads\tProcess Name\n\n"));

		for (DWORD counter = 1; counter <= processCount; counter++) 
		{
			_tprintf(_T("%d\t"), counter);
			_tprintf(_T("%d\t"), processListing->ProcessId);
			_tprintf(_T("%d\t"), processListing->HandleCount);
			_tprintf(_T("%d\t"), processListing->NumberOfThreads);
			_tprintf(_T("%s\n"), processListing->pProcessName);
			processListing++;
		}
		printf("Press enter to refresh the list or press the other button to finish.");
		scanf_s("%c", &Button);
		system("cls");
	} while (Button == 10);

	dwData--;
	RegSetValueEx(hKey, L"DISCOVERY", NULL, REG_DWORD, &dwData, 4);
	return 0;
}
