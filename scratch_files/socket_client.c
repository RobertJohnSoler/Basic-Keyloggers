#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdio.h>
#include <string.h>

// ip address is 192.168.56.1

int main()
{
    int status, client_fd;
    struct sockaddr_in serv_addr;
    const char* hello = "Hello from client";
    char buffer[1024] = { 0 };
    WSADATA wsaData;
    const char* server_ip = "172.20.10.2";

    // start winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("WSAStartup failed\n");
        return 1;
    }

    // initialize socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("\n Socket creation error \n");
        WSACleanup();
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    // Convert IPv4 and IPv6 addresses from text to binary form
    if (inet_pton(AF_INET, server_ip, &serv_addr.sin_addr) <= 0) {
        printf("\nInvalid address/ Address not supported \n");
        closesocket(client_fd);
        WSACleanup();
        return -1;
    }

    // connect to server
    if ((status = connect(client_fd, (struct sockaddr*)&serv_addr,sizeof(serv_addr))) < 0) {
        printf("\nConnection Failed \n");
        closesocket(client_fd);
        WSACleanup();
        return -1;
    }

    // send message to server
    send(client_fd, hello, strlen(hello), 0);
    printf("Hello message sent\n");

    // closing the connected socket
    closesocket(client_fd);
    WSACleanup();
    return 0;
}