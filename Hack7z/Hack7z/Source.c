#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

int main(void) {
	char* tmp_str = "7z e -p00001991 secret.7z";
	char* str = (char*)malloc(26 * sizeof(char));
	for (int i = 0; i < 26; i++) {
		str[i] = tmp_str[i];
	}
	if (str) str[25] = '\0';
	for (int i = 0; i <= 3; i++) {
		for (int j = 0; j <= 9; j++) {
			for (int k = 0; k <= 1; k++) {
				for (int m = 0; m <= 9; m++) {
					str[7] = 48 + i;
					str[8] = 48 + j;
					str[9] = 48 + k;
					str[10] = 48 + m;
					printf("%s\n", str);
					if (system(str) == 0) system("pause");

				}
			}
		}
	}
	free(str);
	return 0;
}