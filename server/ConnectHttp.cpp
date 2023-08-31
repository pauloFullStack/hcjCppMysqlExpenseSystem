#include "ConnectHttp.h"
#include "./route/Base.h"
// Comerçar por aquir o estudo do c++ comentar cada ponto  do codigo,para que serve e se esta correto usar assim, e o porque que esta correto...
void ConnectHttp::sendResponse(int client_socket, const std::string &response)
{
    http_response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Length: " +
        std::to_string(response.length()) + "\r\n"
                                            "Content-Type: application/json\r\n"
                                            "Access-Control-Allow-Origin: *\r\n"
                                            "Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS\r\n"
                                            "Access-Control-Allow-Headers: Content-Type\r\n"
                                            "\r\n" +
        response;

    send(client_socket, http_response.c_str(), http_response.length(), 0);
}

ConnectHttp::ConnectHttp()
{

    try
    {

        server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket == -1)
        {
            std::cerr << "Falha ao criar soquete" << std::endl;
        }

        sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_addr.s_addr = INADDR_ANY;
        server_address.sin_port = htons(port);

        // Definir opção SO_REUSEADDR para reutilizar o endereço local (porta) imediatamente após encerrar o servidor
        int reuseAddr = 1;
        if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuseAddr, sizeof(reuseAddr)) == -1)
        {
            std::cerr << "Falha ao definir a opção SO_REUSEADDR: " << std::endl;
            close(server_socket);
        }

        if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
        {
            std::cerr << "Falha ao ligar o soquete" << std::endl;
            close(server_socket);
        }

        if (listen(server_socket, 10) == -1)
        {
            std::cerr << "Falha ao ouvir no soquete" << std::endl;
            close(server_socket);
        }

        std::cout << "Servidor ouvindo na porta " << port << std::endl;

        bool shouldContinue = true;
        while (shouldContinue)
        {
            sockaddr_in client_address;
            socklen_t client_address_size = sizeof(client_address);
            int client_socket = accept(server_socket, (struct sockaddr *)&client_address, &client_address_size);

            if (client_socket == -1)
            {
                std::cerr << "Falha ao aceitar a conexão do cliente" << std::endl;
                shouldContinue = false;
                close(server_socket);
                continue;
            }

            char buffer[4096];

            while (true)
            {
                int bytes_received = recv(client_socket, buffer, sizeof(buffer) - 1, 0);

                if (bytes_received <= 0)
                {
                    break;
                }

                buffer[bytes_received] = '\0';
                request += buffer;

                if (request.find("\r\n\r\n") != std::string::npos)
                {
                    requestBody = request.substr(request.find("\r\n\r\n") + 4);
                    break;
                }
            }

            std::istringstream iss(request);
            std::string method, route;
            iss >> method >> route;

            Base routeBase(route, method, client_socket, requestBody);            

            // Limpa a variavel que vem rota, body
            request.clear();

            sendResponse(client_socket, routeBase.response);

            close(client_socket);
        }

        close(server_socket);
    }
    catch (const std::runtime_error &ex)
    {
        std::cout << "Exceção capturada: " << ex.what() << std::endl;
    }
}
