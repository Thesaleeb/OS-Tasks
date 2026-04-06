#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main() {
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2,2), &wsaData);

    int serverSocket, clientSocket;
    char message[1024];

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(5000);
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    bind(serverSocket, (sockaddr*)&serverAddress, sizeof(serverAddress));

    listen(serverSocket, 1);
    cout << "Waiting for client...\n";

    clientSocket = accept(serverSocket, NULL, NULL);
    cout << "Client connected!\n";

    while (true) {
        recv(clientSocket, message, 1024, 0);
        cout << "Client: " << message << endl;

        cout << "You: ";
        cin.getline(message, 1024);
        send(clientSocket, message, strlen(message), 0);
    }

    closesocket(serverSocket);
    WSACleanup();
    return 0;
}