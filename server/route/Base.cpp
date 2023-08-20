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

            // Criar um rota e controller para esse recurso...
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
        }
        else
        {
            response = R"({"error": "Method not supported."})";
        }
    }
};
