#include "Header.h"

void userInfo();
void getUserInfo(char* localname);
void systemInfo();

int main(void) {
	setlocale(LC_ALL, "Rus");
	char my_buffer[UNLEN + 1];
	DWORD size = sizeof(my_buffer);
	if (GetUserNameW(my_buffer, &size) == ERROR_INSUFFICIENT_BUFFER) 
	{
		printf("THE BUFFER IS TOO SMALL");
		return 0;
	};
	userInfo();
	getUserInfo(my_buffer);
	systemInfo();
	system("pause");
	return 0;
}