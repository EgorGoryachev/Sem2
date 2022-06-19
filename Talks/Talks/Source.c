#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <conio.h>
#pragma comment(lib,"Ws2_32.lib")

void chat(SOCKET s);

int main() {
	WSADATA ws;
	WSAStartup(MAKEWORD(2, 2), &ws);

	SOCKET s;
	s = socket(AF_INET, SOCK_STREAM, 0);

	SOCKADDR_IN sa;
	memset(&sa, 0, sizeof(sa));
	sa.sin_family = AF_INET;
	sa.sin_port = htons(6666);

	char c;
	printf("s - server\nk - client\n");
	scanf_s("%c", &c);

	if (c == 'k') {
		system("cls");
		char ip[100];
		printf("Set ip address:");
		scanf("\n%100[0-9.]", ip);
		inet_pton(AF_INET, ip, (PVOID*)(&sa.sin_addr.S_un.S_addr));
		connect(s, &sa, sizeof(sa));
		chat(s);
	}

	if (c == 's') {
		system("cls");
		bind(s, &sa, sizeof(sa));
		listen(s, 100);

		char buf[200];
		memset(buf, 0, sizeof(buf));

		SOCKET client_socket;
		SOCKADDR_IN client_addr;
		int client_addr_size = sizeof(client_addr);

		while (client_socket = accept(s, &client_addr, &client_addr_size)) {
			printf("connect OK\n");
			chat(client_socket);
		}
	}

	closesocket(s);
	return 0;
}

void chat(SOCKET s) {
	char mass[200];
	WSAEventSelect(s, 0, FD_READ);
	printf("To start writing, press F1\n");
	do
	{
		if ((GetKeyState(VK_F1) < 0) && (GetForegroundWindow() == GetConsoleWindow())) {
			while (_getch() != 0);
			scanf("\n%200[0-9a-zA-Z.,+-/*><!? ]", mass);
			send(s, mass, sizeof(mass), 0);
		}
		if (recv(s, mass, sizeof(mass), 0) > 0) {
			printf("Server: %s\n", mass);
		}
	} while (GetKeyState(VK_ESCAPE) >= 0);
}