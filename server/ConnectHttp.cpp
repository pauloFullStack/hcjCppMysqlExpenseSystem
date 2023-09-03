#include "ConnectHttp.h"
#include "./route/Base.h"

// Sobre a função 'sendResponse' e seus parametro
#pragma region o que faz sendResponse(int client_socket, const std::string &response)
/**
    sendResponse constrói uma resposta HTTP com cabeçalhos e corpo da resposta e a envia para o cliente através do client_socket.
 
    @var client_socket: O client_socket é uma variável que representa o socket (soquete) de comunicação entre o servidor e um cliente específico. Em um servidor que lida com várias conexões simultâneas, como um servidor HTTP, um novo client_socket é criado para cada cliente que se conecta ao servidor.
    
    @var &response(o & na variável &response indica que está sendo passada uma referência (ou endereço) para a variável response): Portanto, esse parâmetro const std::string &response permite que a função sendResponse receba uma referência imutável a uma string, use essa string para construir a resposta HTTP, mas não permita que a função modifique a string original. Isso é útil porque a função sendResponse geralmente não precisa ou não deve modificar a resposta original que está sendo enviada para o cliente.

    O que são soquetes: 

    Um soquete (socket) é uma interface de programação de aplicativos (API) que permite a comunicação entre processos ou programas em diferentes computadores ou em uma mesma máquina. Os soquetes são amplamente usados em redes de computadores para estabelecer conexões e permitir a transferência de dados entre sistemas.

    Aqui estão algumas características importantes dos soquetes:

    Comunicação entre processos: Os soquetes permitem que processos ou programas em diferentes máquinas (ou no mesmo computador) se comuniquem e troquem informações.

    Endereço IP e Porta: Cada soquete é identificado por um endereço IP e uma porta. O endereço IP identifica o computador ou dispositivo, enquanto a porta identifica um processo específico em um computador. Portas diferentes são usadas para diferentes tipos de comunicação.

    Protocolo de Transporte: Os soquetes podem ser usados com diferentes protocolos de transporte, como TCP (Transmission Control Protocol) e UDP (User Datagram Protocol). O TCP é orientado à conexão e oferece garantias de entrega confiável, enquanto o UDP é mais leve e oferece uma comunicação não confiável.

    Tipos de Soquetes: Existem diferentes tipos de soquetes, como soquetes de fluxo (stream sockets) e soquetes de datagrama (datagram sockets). Os soquetes de fluxo são usados com o protocolo TCP e oferecem uma conexão confiável, enquanto os soquetes de datagrama são usados com o protocolo UDP e oferecem comunicação não confiável e sem conexão.

    API de Programação: Para usar soquetes em programas, as linguagens de programação fornecem uma API de soquete que permite a criação, configuração e uso de soquetes em aplicativos.

    Os soquetes são amplamente utilizados em várias aplicações de rede, como servidores web (usando HTTP sobre TCP) = Quando dizemos "usando HTTP sobre TCP", estamos indicando que as solicitações e respostas HTTP são encapsuladas em pacotes TCP para serem transmitidas pela rede. Isso é importante porque o HTTP, por si só, não fornece garantias de entrega confiável, e é aí que o TCP entra em cena. O TCP cuida de todos os aspectos relacionados à confiabilidade da transmissão, garantindo que os dados do HTTP sejam entregues corretamente e em ordem.

    Em resumo, quando você navega na web, seu navegador faz solicitações HTTP para servidores web. Essas solicitações e as respostas correspondentes são transmitidas usando o protocolo HTTP, mas esses dados são enviados através da infraestrutura do TCP para garantir a confiabilidade da comunicação. Portanto, a combinação de HTTP sobre TCP é fundamental para a funcionalidade da World Wide Web., servidores de email (usando SMTP, POP3, IMAP sobre TCP), transferência de arquivos (usando FTP sobre TCP), jogos online (usando UDP para baixa latência) e muito mais.

    Em resumo, um soquete é uma abstração que permite a comunicação entre processos ou programas em diferentes computadores ou na mesma máquina, facilitando a troca de dados por meio de redes de computadores.
 * 
 * 
 */
#pragma endregion
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

    // Sobre a função 'send' e seus argumentos
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
