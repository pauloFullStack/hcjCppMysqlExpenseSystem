#include "ConnectHttp.h"
#include "./route/Base.h"

/**
 * sendResponse constrói uma resposta HTTP com cabeçalhos e corpo da resposta e a envia para o cliente através do client_socket.
 * 
 * @var client_socket: O client_socket é uma variável que representa o socket (soquete) de comunicação entre o servidor e um cliente específico. Em um servidor que lida com várias conexões simultâneas, como um servidor HTTP, um novo client_socket é criado para cada cliente que se conecta ao servidor.
 * 
 * 
 */
void ConnectHttp::sendResponse(int client_socket, const std::string &response)
{
    // Constrói a resposta HTTP, incluindo cabeçalhos como Status, Content-Length, Content-Type, e Access-Control-Allow.
    http_response =
        "HTTP/1.1 200 OK\r\n"
        // std::to_string = A função std::to_string em C++ é usada para converter valores numéricos, como inteiros ou números de ponto flutuante, em strings. 
        "Content-Length: " + std::to_string(response.length()) + "\r\n"
        "Content-Type: application/json\r\n"
        "Access-Control-Allow-Origin: *\r\n"
        "Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS\r\n"
        "Access-Control-Allow-Headers: Content-Type\r\n"
        "\r\n" +
        response;

    // Tudo sobre a função 'send' e seus argumentos passados
    #pragma region o que e send(client_socket, http_response.c_str(), http_response.length(), 0)
    // send(client_socket, http_response.c_str(), http_response.length(), 0) = Envia a resposta para o cliente conectado usando o socket. 
    
    // O que são os argumentos passado na função 'send';
    
    // client_socket: Este é o primeiro parâmetro e representa o soquete do cliente para o qual você deseja enviar os dados. O client_socket é o identificador da conexão com um cliente específico, que foi obtido quando a conexão foi aceita usando a função accept.

    //http_response.c_str(): Este é o segundo parâmetro e representa os dados que você deseja enviar. Neste caso, você está usando http_response.c_str(), que é um ponteiro constante para a representação C-style da string http_response. Isso fornece os dados da resposta HTTP que você deseja enviar.
    
    //http_response.length(): Este é o terceiro parâmetro e indica o tamanho dos dados que você deseja enviar. Você está usando http_response.length(), que retorna o comprimento da string http_response, ou seja, o número de caracteres na resposta HTTP que você está enviando.
    
    //0: Este é o quarto parâmetro, que são os chamados "flags" ou indicadores. Neste caso, o valor 0 é passado, o que indica que nenhuma opção ou configuração adicional está sendo especificada. Isso significa que a função send deve operar em seu comportamento padrão.
    #pragma endregion
    #pragma region o que e http_response.c_str() 
    // http_response.c_str() = A função c_str() retorna um ponteiro constante para a sequência de caracteres interna da std::string. Esse ponteiro pode ser usado para acessar os caracteres da string, mas lembre-se de que é constante, o que significa que você não pode modificar o conteúdo da string por meio desse ponteiro. É uma maneira de permitir que você use uma std::string em contextos que requerem uma string C-style sem a necessidade de copiar os dados da string.

    // C-style = quer dizer estilo na linguagem C
    #pragma endregion
    #pragma region o que e http_response.length()
    // http_response.length() = A função length() é um método (ou membro) da classe std::string e é usada para obter o tamanho da string, ou seja, o número de caracteres que ela contém. O tamanho da string inclui todos os caracteres, incluindo espaços em branco, letras, números e qualquer outro caractere na string.
    #pragma endregion
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
