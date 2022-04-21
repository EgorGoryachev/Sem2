#include "Header.h"

void userInfo() {
	LPUSER_INFO_0 usBuff;
	DWORD filter = 0;
	DWORD level = 0;
	DWORD prefmaxlen = 512;
	DWORD entriesread;
	DWORD totalentries;
	NET_API_STATUS result;
	printf("User Information:\n");
	result = NetUserEnum(NULL, level, filter, (LPBYTE*)&usBuff, prefmaxlen, &entriesread, &totalentries, NULL);
	for (DWORD i = 0; i < entriesread; i++)
	{
		printf("%i: ", i + 1);
		wprintf(L"%s \n", usBuff[i].usri0_name);
	}
	printf("\n");
}

void getUserInfo(char* Name) {
	printf("getUserInfo:\n");
	NET_API_STATUS status;
	LPUSER_INFO_1 pBuf1;
	status = NetUserGetInfo(NULL, Name, 1, (LPBYTE*)&pBuf1);

	if (status == NERR_Success)
	{
		if (pBuf1 != NULL)
		{
			wprintf(L"1:User account name: %s\n", pBuf1->usri1_name);
			wprintf(L"2:Password: %s\n", pBuf1->usri1_password);
			wprintf(L"3:Password age (seconds): %d\n", pBuf1->usri1_password_age);
			wprintf(L"4:Privilege level: %d\n", pBuf1->usri1_priv);
			wprintf(L"5:Flags (in hex): %x\n", pBuf1->usri1_flags);
			wprintf(L"6:User account name: %s\n", pBuf1->usri1_name);
			wprintf(L"7:Password: %s\n", pBuf1->usri1_password);
		}
	}
	printf("\n");
}

void systemInfo() {
	printf("sysinfo:\n");
	char buff[MAX_COMPUTERNAME_LENGTH + 1];
	unsigned long size = MAX_COMPUTERNAME_LENGTH + 1;
	GetComputerNameA(buff, &size);
	printf("1:Computer name: %s\n", buff);
	time_t rawtime;
	time(&rawtime);
	printf("2:Data and time: %s", ctime(&rawtime));
	printf("\n");
}