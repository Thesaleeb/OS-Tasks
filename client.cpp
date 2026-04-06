#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);

    int clientSocket;
    char message[1024];

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(5000);
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));
    cout << "Connected to server!\n";

    while (true) {
        cout << "You: ";
        cin.getline(message, 1024);
        send(clientSocket, message, strlen(message), 0);

        recv(clientSocket, message, 1024, 0);
        cout << "Server: " << message << endl;
    }

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}