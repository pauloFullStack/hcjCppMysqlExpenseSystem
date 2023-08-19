#include "Base.h"
#include "./get/GetExpenseRoute.h"
#include "./post/PostExpenseRoute.h"
#include "./put/PutExpenseRoute.h"
#include "./delete/DeleteExpenseRoute.h"
#include <fstream>

Base::Base(std::string route, std::string method, int client_socket, std::string requestBody)
{
    size_t foundPosition = route.find("api");

    if (foundPosition != std::string::npos)
    {
        if (method == "GET")
        {
            if (route == "/api")
            {
                GetExpenseRoute dataExpense;
                response = dataExpense.GetExpense();
            }
        }
        else if (method == "POST")
        {
            if (route == "/api/post")
            {
                PostExpenseRoute createDataExpense;
                response = createDataExpense.PostExpense(requestBody);
            }
        }
        else if (method == "PUT")
        {
            if (route == "/api/put")
            {
                PutExpenseRoute updateDataExpense;
                response = updateDataExpense.PutExpense(requestBody);
            }
        }
        else if (method == "DELETE")
        {
            if (route == "/api/delete")
            {
                DeleteExpenseRoute deleteDataExpense;
                response = deleteDataExpense.DeleteExpense(requestBody);
            }
        }
        else
        {
            response = R"({"error": "Method not supported."})";
        }
    }
    else
    {
        if (method == "GET")
        {
            
            // Primeiro ver as aulas do uniube mais... criar um rota e controller para esse recurso... e criar uma pagina para cada disciplina no front... ai começar a desenvolver os sistemas... começar por algebra e calculo diferencial...  
            std::string basePath = "/var/www/html/views"; // Caminho base
            std::string extension = ".html";
            std::string path = basePath + route + extension;

            std::ifstream htmlFile(path);

            if (htmlFile.is_open())
            {
                std::string line;
                while (std::getline(htmlFile, line))
                {
                    response += line;
                }
                htmlFile.close();
            }
            else
            {
                response = "Erro ao abrir o arquivo.";
            }

            // response = R"(<div style="padding: 20px;" class="row" ><div class="col-lg-3 style-cols" ><h2>1º Semestre</h2></div></div>)";
        }
        else
        {
            response = R"({"error": "Method not supported."})";
        }
    }
};
