
#include <stdio.h>
#include <windows.h>
#include <conio.h>

int main()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hf;
	LPCWSTR file = L"*.txt";
	LPCWSTR fileExe = L"D:\\Infa2\\SuitableFiles\\Debug\\*.exe";
	hf = FindFirstFile(file, &FindFileData);
	if (hf != INVALID_HANDLE_VALUE)
	{
		do
		{
			printf("File name: ");
			for (int i = 0; i < 280;i++) {
				if (FindFileData.cFileName[i] != '\0') 
				{
					printf("%c", FindFileData.cFileName[i]);
				}
				else 
				{
					break;
				}
			}
			printf("\n");
			printf("File size: %d byte\n", FindFileData.nFileSizeLow);
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
	hf = FindFirstFile(fileExe, &FindFileData);
	if (hf != INVALID_HANDLE_VALUE)
	{
		do
		{
			printf("File name: ");
			for (int i = 0; i < 280; i++) {
				if (FindFileData.cFileName[i] != '\0')
				{
					printf("%c", FindFileData.cFileName[i]);
				}
				else
				{
					break;
				}
			}
			printf("\n");
			printf("File size: %d byte\n", FindFileData.nFileSizeLow);
		} while (FindNextFile(hf, &FindFileData) != 0);
		FindClose(hf);
	}
	_getch();
	return 0;
}