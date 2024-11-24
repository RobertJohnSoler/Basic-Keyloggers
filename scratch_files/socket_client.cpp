#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
//using namespace std;

int main() {
    // Initialize WSA variables
    WSADATA wsaData;
    int wserr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wserr = WSAStartup(wVersionRequested, &wsaData);
    const char* server_ip = "10.0.0.184";

    // Check for initialization success
    if (wserr != 0) {
        std::cout << "Winsock dll not found" << std::endl;
        return 0;
    } else {
        std::cout << "Winsock dll found" << std::endl;
        std::cout << "Status: " << wsaData.szSystemStatus << std::endl;
    }

    // Create a socket
    SOCKET clientSocket;
    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    // Check for socket creation success
    if (clientSocket == INVALID_SOCKET) {
        std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    } else {
        std::cout << "Socket is OK!" << std::endl;
    }

    // Continue with the client setup...
    // (See the full code here: https://github.com/Tharun8951/cpp-tcp-server/")

    //connection to server
    sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(server_ip);
    clientService.sin_port = htons(8080);

    if(connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR){
        std::cout << "Client: connect() - Failed to connect: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    } else {
        std::cout << "Client: Connect() is OK!" << std::endl;
        std::cout << "Client: Can start sending and receiving data..." << std::endl;
    }

    char buffer[200];
    printf("Sending hello message to the server... \n");
    const char* msg = "Hello from my cpp client!\n";
    int sent = send(clientSocket, msg, strlen(msg), 0);
    if(sent == SOCKET_ERROR){
        std::cout << "Server send error: " << WSAGetLastError() << std::endl;
        return -1;
    } else {
        std::cout << "Server: sent" << sent << std::endl;
    }

    closesocket(clientSocket);
    WSACleanup();
    std::cout << "Client socket closed." << std::endl;
    return 0;

}