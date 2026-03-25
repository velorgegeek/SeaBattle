#include <string>
#include "json.hpp"
#include <Winsock2.h>
#include "RequestToServer.h"
#include <Ws2tcpip.h>
#pragma comment(lib, "ws2_32.lib")

using json = nlohmann::json;

RequestToServer::RequestToServer(){
    init();
}
void RequestToServer::init() {
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
    }

    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        WSACleanup();
    }

    sockaddr_in serverAddress = { 0 };
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);

    //int result = inet_pton(AF_INET, "26.160.47.90", &(serverAddress.sin_addr));
    //if (result != 1) {
    //    closesocket(clientSocket);
    //    WSACleanup();
    //}

    //if (connect(clientSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == SOCKET_ERROR) {
    //    closesocket(clientSocket);
    //    WSACleanup();
    //}
}
void RequestToServer::sender(const json& s) {
    std::string reciveJson = s.dump();
    int bytesSent = send(clientSocket, reciveJson.c_str(), reciveJson.size(), 0);
}
json RequestToServer::reciver() {
    return {};
}