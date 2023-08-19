#pragma once

#include <netinet/in.h>
#include <string>
#include <sstream>
#include <iostream>
#include <unistd.h>

class ConnectHttp
{

public:
    const int port = {8080};
    int server_socket, bytes_received, client_socket;
    char buffer[4096];
    std::string request, method, route, response, http_response, requestBody {""};
    sockaddr_in server_address, client_address;
    socklen_t client_address_size;
    std::istringstream iss;

public:
    // Construtor da classe
    ConnectHttp();

    void sendResponse(int, const std::string &);
};