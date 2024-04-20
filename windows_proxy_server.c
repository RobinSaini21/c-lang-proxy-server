#include <stdio.h>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

void handle_request(SOCKET client_socket)
{
    char buffer[1024]; // Fixed-size buffer
    int bytesReceived;
    
    // Loop until the entire request is received
    do {
        bytesReceived = recv(client_socket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            // Process the received data if needed
        } else if (bytesReceived == 0) {
            printf("Connection closed by client.\n");
            break; // Connection closed by client
        } else {
            printf("Error in recv: %d\n", WSAGetLastError());
            break; // Error in recv
        }
    } while (bytesReceived == sizeof(buffer)); // Continue until buffer is full

    printf("Received request:\n%s\n", buffer);
    const char response[] = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><body><h1>Yellow, World!</h1></body></html>";
    int bytesSent = send(client_socket, response, strlen(response), 0);
    if (bytesSent == SOCKET_ERROR) {
        printf("Error in send: %d\n", WSAGetLastError());
    }

    // No need to free buffer since it's not dynamically allocated
}


int proxy_server()
{
    WSADATA wsaData;
    SOCKET listenSocket, clientSocket;
    struct sockaddr_in serverAddr, clientAddr;
    int clientAddrLen = sizeof(clientAddr);
    

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        printf("WSAStartup failed.\n");
        return 1;
    }

    if ((listenSocket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
    {
        printf("Error creating socket.\n");
        return 1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddr.sin_port = htons(8080);
    if (bind(listenSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
    {
        printf("Bind failed.\n");
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR)
    {
        printf("Listen failed.\n");
        closesocket(listenSocket);
        WSACleanup();
        return 1;
    }

    printf("Server listening on port 8080...\n");

    while (1)
    {
        clientSocket = accept(listenSocket, (struct sockaddr *)&clientAddr, &clientAddrLen);
        if (clientSocket == INVALID_SOCKET)
        {
            printf("Accept failed.\n");
            closesocket(listenSocket);
            WSACleanup();
            return 1;
        }

        printf("Client connected: %s:%d\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));

        handle_request(clientSocket);
        closesocket(clientSocket);
    }

    closesocket(listenSocket);
    WSACleanup();

    return 0;
}
