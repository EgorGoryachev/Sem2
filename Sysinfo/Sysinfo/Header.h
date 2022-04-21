#pragma once
#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "netapi32.lib")
#pragma warning(disable : 4996)

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <lm.h>
#include <locale.h>
#include <time.h>

void userInfo();
void getUserInfo(char* Name);
void systemInfo();