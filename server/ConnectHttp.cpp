#include "ConnectHttp.h"
#include "./route/Base.h"

// Sobre a função 'sendResponse' e seus parametro
#pragma region __ o que faz sendResponse(int client_socket, const std::string &response)
/*
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

Em resumo, quando você navega na web, seu navegador faz solicitações HTTP para servidores web. Essas solicitações e as respostas correspondentes são transmitidas usando o protocolo HTTP, mas esses dados são enviados através da infraestrutura do TCP para garantir a confiabilidade da comunicação. Portanto, a combinação de HTTP sobre TCP é fundamental para a funcionalidade da World Wide Web... servidores de email (usando SMTP, POP3, IMAP sobre TCP), transferência de arquivos (usando FTP sobre TCP), jogos online (usando UDP para baixa latência) e muito mais.

Em resumo, um soquete é uma abstração que permite a comunicação entre processos ou programas em diferentes computadores ou na mesma máquina, facilitando a troca de dados por meio de redes de computadores.
 */
#pragma endregion
void ConnectHttp::sendResponse(int client_socket, const std::string &response)
{
    // Constrói a resposta HTTP, incluindo cabeçalhos como Status, Content-Length, Content-Type, e Access-Control-Allow.
    http_response =
        "HTTP/1.1 200 OK\r\n"
        // std::to_string = A função std::to_string em C++ é usada para converter valores numéricos, como inteiros ou números de ponto flutuante, em strings.
        "Content-Length: " +
        std::to_string(response.length()) + "\r\n"
                                            "Content-Type: application/json\r\n"
                                            "Access-Control-Allow-Origin: *\r\n"
                                            "Access-Control-Allow-Methods: GET, POST, PUT, DELETE, OPTIONS\r\n"
                                            "Access-Control-Allow-Headers: Content-Type\r\n"
                                            "\r\n" +
        response;

// Sobre a função 'send' e seus argumentos
#pragma region __ o que e send(client_socket, http_response.c_str(), http_response.length(), 0)
/*
send(client_socket, http_response.c_str(), http_response.length(), 0) = Envia a resposta para o cliente conectado usando o socket.

O que são os argumentos passado na função 'send';

client_socket: Este é o primeiro parâmetro e representa o soquete do cliente para o qual você deseja enviar os dados. O client_socket é o identificador da conexão com um cliente específico, que foi obtido quando a conexão foi aceita usando a função accept.

http_response.c_str(): Este é o segundo parâmetro e representa os dados que você deseja enviar. Neste caso, você está usando http_response.c_str(), que é um ponteiro constante para a representação C-style da string http_response. Isso fornece os dados da resposta HTTP que você deseja enviar.

http_response.length(): Este é o terceiro parâmetro e indica o tamanho dos dados que você deseja enviar. Você está usando http_response.length(), que retorna o comprimento da string http_response, ou seja, o número de caracteres na resposta HTTP que você está enviando.

0: Este é o quarto parâmetro, que são os chamados "flags" ou indicadores. Neste caso, o valor 0 é passado, o que indica que nenhuma opção ou configuração adicional está sendo especificada. Isso significa que a função send deve operar em seu comportamento padrão.
*/
#pragma endregion
#pragma region __ o que e http_response.c_str()
// http_response.c_str() = A função c_str() retorna um ponteiro constante para a sequência de caracteres interna da std::string. Esse ponteiro pode ser usado para acessar os caracteres da string, mas lembre-se de que é constante, o que significa que você não pode modificar o conteúdo da string por meio desse ponteiro. É uma maneira de permitir que você use uma std::string em contextos que requerem uma string C-style sem a necessidade de copiar os dados da string.

// C-style = quer dizer estilo na linguagem C
#pragma endregion
#pragma region __ o que e http_response.length()
// http_response.length() = A função length() é um método (ou membro) da classe std::string e é usada para obter o tamanho da string, ou seja, o número de caracteres que ela contém. O tamanho da string inclui todos os caracteres, incluindo espaços em branco, letras, números e qualquer outro caractere na string.
#pragma endregion
    send(client_socket, http_response.c_str(), http_response.length(), 0);
}

ConnectHttp::ConnectHttp()
{

    try
    {
#pragma region __ server_socket = socket(AF_INET, SOCK_STREAM, 0)
/* socket é uma função que cria um novo soquete.

AF_INET é um parâmetro que especifica o domínio do soquete, neste caso, o domínio IPv4, que é usado para comunicação pela Internet.

SOCK_STREAM é um parâmetro que especifica o tipo de soquete, neste caso, um soquete de fluxo, que é usado para comunicações confiáveis baseadas em TCP (Transmission Control Protocol).

0 é o protocolo a ser usado. Nesse caso, 0 indica que o sistema deve escolher automaticamente o protocolo apropriado com base no domínio e no tipo do soquete.

A linha de código cria um soquete server_socket e o atribui a uma variável para que possa ser usado posteriormente na comunicação com os clientes. Se a criação do soquete falhar, a função socket retorna -1, e o código verifica se server_socket é igual a -1. Se isso acontecer, ele imprime uma mensagem de erro "Falha ao criar soquete" usando std::cerr.

Em resumo, esse código é responsável por criar um soquete do servidor para aguardar conexões de clientes e lida com possíveis erros na criação do soquete.
*/
#pragma endregion
        server_socket = socket(AF_INET, SOCK_STREAM, 0);
        if (server_socket == -1)
        {
            std::cerr << "Falha ao criar soquete" << std::endl;
        }

#pragma region __ sockaddr_in server_address;
// sockaddr_in é uma estrutura que contém informações sobre o endereço e a porta para a qual o servidor deve ser vinculado. Ela é comumente usada com soquetes do tipo AF_INET (IPv4).
#pragma endregion
        sockaddr_in server_address;
#pragma region __ server_address.sin_family;
// server_address.sin_family define a família de endereços que o servidor usará. Neste caso, AF_INET indica que o servidor usará endereços IPv4.
#pragma endregion
        server_address.sin_family = AF_INET;
#pragma region __ server_address.sin_addr.s_addr
// server_address.sin_addr.s_addr especifica o endereço IP ao qual o servidor estará associado. INADDR_ANY é uma constante que representa qualquer endereço IP disponível na máquina. Isso significa que o servidor estará disponível em todas as interfaces de rede da máquina.
#pragma endregion
        server_address.sin_addr.s_addr = INADDR_ANY;
#pragma region __ server_address.sin_port
// server_address.sin_addr.s_addr especifica o endereço IP ao qual o servidor estará associado. INADDR_ANY é uma constante que representa qualquer endereço IP disponível na máquina. Isso significa que o servidor estará disponível em todas as interfaces de rede da máquina.
#pragma endregion
        server_address.sin_port = htons(port);

// Este trecho de código trata da configuração e vinculação do soquete do servidor para que ele possa escutar conexões de clientes.
#pragma region __ Primeiro if
/*
Aqui, está sendo configurada a opção SO_REUSEADDR para o soquete do servidor. Essa opção permite que você reutilize o mesmo endereço local (porta) imediatamente após encerrar o servidor, mesmo que ainda haja conexões pendentes ou sockets em espera. Isso pode ser útil para evitar problemas de "endereço já em uso" ao reiniciar o servidor rapidamente após uma interrupção.

A variável reuseAddr é definida como 1 para habilitar a opção SO_REUSEADDR.

A função setsockopt é usada para definir opções de soquete. Ela recebe como argumentos o descritor do soquete (server_socket), o nível de opção (SOL_SOCKET para opções gerais de soquete), o nome da opção (SO_REUSEADDR) e um ponteiro para o valor da opção (&reuseAddr). O último argumento é o tamanho do valor da opção (sizeof(reuseAddr)).

Se a configuração da opção falhar (retorno igual a -1), uma mensagem de erro é exibida, e o soquete do servidor é fechado.
*/
#pragma endregion
        int reuseAddr = 1;
        // Primeiro if
        if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &reuseAddr, sizeof(reuseAddr)) == -1)
        {
            std::cerr << "Falha ao definir a opção SO_REUSEADDR: " << std::endl;
            close(server_socket);
        }
#pragma region __ Segundo if
/*
Nesta parte, o código está vinculando (binding) o soquete do servidor ao endereço e à porta especificados. A função bind é usada para associar o soquete server_socket ao endereço e à porta definidos na estrutura server_address.

Se a vinculação falhar (retorno igual a -1), uma mensagem de erro é exibida, e o soquete do servidor é fechado.
*/
#pragma endregion
        // Segundo if
        if (bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1)
        {
            std::cerr << "Falha ao ligar o soquete" << std::endl;
            close(server_socket);
        }
#pragma region __ Terceiro if
/*
Por fim, o código está colocando o soquete em modo de escuta (listen) para aguardar conexões de clientes. A função listen é usada para isso, e o segundo argumento 10 especifica o número máximo de conexões pendentes que podem ser enfileiradas para este soquete.

Se a operação de escuta falhar (retorno igual a -1), uma mensagem de erro é exibida, e o soquete do servidor é fechado.

Em resumo, esse trecho de código configura, vincula e coloca o soquete do servidor em modo de escuta, permitindo que ele aceite conexões de clientes e lide com possíveis erros ao longo do caminho.
*/
#pragma endregion
        // Terceiro if
        if (listen(server_socket, 10) == -1)
        {
            std::cerr << "Falha ao ouvir no soquete" << std::endl;
            close(server_socket);
        }
        std::cout << "Servidor ouvindo na porta " << port << std::endl;

// Este trecho de código faz parte de um servidor HTTP e lida com a comunicação com os clientes.
#pragma region __ Inicio loop
// O código inicia um loop while que permite ao servidor continuar a aceitar conexões e processar solicitações dos clientes. A variável shouldContinue é usada como uma condição para controlar o loop.
#pragma endregion
        bool shouldContinue = true;
        while (shouldContinue)
        {
#pragma region __ Primeiro Fluxo do loop
/*
Dentro do loop, o servidor aguarda uma conexão de cliente usando a função accept. A função accept bloqueia a execução até que uma conexão seja estabelecida por um cliente. Quando uma conexão é aceita, ela retorna um novo soquete client_socket que será usado para se comunicar com o cliente. A estrutura client_address contém informações sobre o cliente, como o endereço IP e a porta.

Se a função accept falhar (retorno igual a -1), uma mensagem de erro é exibida, e a variável shouldContinue é definida como false para sair do loop. Além disso, o soquete do servidor (server_socket) é fechado, encerrando o servidor.
*/
#pragma endregion
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

#pragma region __ Segundo Fluxo do loop
/*
Após aceitar a conexão, o servidor entra em um loop interno para receber os dados enviados pelo cliente. Ele utiliza a função recv para receber dados do cliente e armazená-los em um buffer chamado buffer. O tamanho do buffer é de 4096 bytes.

O loop continua até que a função recv retorne um valor menor ou igual a zero, indicando que a conexão foi fechada ou ocorreu um erro.

Durante a recepção dos dados, o servidor acumula os dados recebidos na variável request e verifica se a sequência "\r\n\r\n" aparece na string request. Isso é um indicativo de que a parte de cabeçalho da solicitação HTTP foi recebida completamente, e o corpo da solicitação (se houver) começa após essa sequência. O corpo da solicitação é então extraído e armazenado em requestBody.
*/
#pragma endregion
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

#pragma region __ Terceiro Fluxo loop
/*
Após receber e processar a solicitação HTTP, o código cria um objeto routeBase com base na rota, no método, no soquete do cliente e no corpo da solicitação.

A variável request é limpa para receber a próxima solicitação.

Em seguida, a função sendResponse é chamada para enviar uma resposta HTTP de volta para o cliente usando o client_socket.

Finalmente, o client_socket é fechado para encerrar a conexão com o cliente.

O servidor continuará a executar esse loop, aceitando conexões e processando solicitações de clientes até que shouldContinue seja definido como false, o que ocorrerá se houver algum erro na aceitação da conexão ou se o servidor for encerrado deliberadamente. Após a saída do loop, o soquete do servidor (server_socket) é fechado para encerrar o servidor completamente.
*/
#pragma endregion
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
