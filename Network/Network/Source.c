#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib,"Ws2_32.lib")

void ñalculator(char buf[]);

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
		inet_pton(AF_INET, "127.0.0.1", (PVOID*)(&sa.sin_addr.S_un.S_addr));
		connect(s, &sa, sizeof(sa));

		char mass[200];
		do {
			scanf("\n%200[0-9a-zA-Z.,+-/*>< ]", mass);
			send(s, mass, sizeof(mass), 0);

			recv(s, mass, sizeof(mass), 0);
			printf("Server: %s\n", mass);
		} while (1);
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
			while (recv(client_socket, buf, sizeof(buf), 0) > 0)
			{
				printf("Client: %s\n", buf);
				ñalculator(buf);
				send(client_socket, buf, sizeof(buf), 0);
			}
		}
	}

	closesocket(s);
	return 0;
}

void ñalculator(char buf[]) {
	char operation;
	int number1, number2, result;
	int tmp = 0;
	int tmp1 = 0;
	number1 = atoi(buf);
	for (int i = 0; i < 200; i++) {
		if (buf[i] == 42 || buf[i] == 43 || buf[i] == 47 || buf[i] == 45 || buf[i] == 60 || buf[i] == 62) {
			operation = buf[i];
			tmp++;
			buf[i] = 'q';
			for (tmp1 = 0; tmp1 < 200; tmp1++) {
				if ((buf[i + 1] >= 48) && (buf[i + 1] <= 57)) {
					buf[tmp1] = buf[i + 1];
					i++;
				}
			}
		}
		if ((buf[i + 1] == 60) || (buf[i + 1] == 62)) {
			operation = buf[i + 1];
		}
		if (tmp > 0) {
			number2 = atoi(buf);
			tmp = 0;
		}
		buf[i] = 'q';
	}
	switch (operation)
	{
	case '-':
		result = number1 - number2;
		_itoa(result, buf, 10);
		break;
	case '+':
		result = number1 + number2;
		_itoa(result, buf, 10);
		break;
	case '/':
		result = number1 / number2;
		_itoa(result, buf, 10);
		break;
	case '*':
		result = number1 * number2;
		_itoa(result, buf, 10);
		break;
	case '<':
		result = (number1 << number2);
		_itoa(result, buf, number2);
		break;
	case '>':
		result = (number1 >> number2);
		_itoa(result, buf, number2);
		break;
	}
}