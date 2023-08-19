#include "./CreateExpenseController.h"

std::string CreateExpenseController::createExpense(std::string body)
{

    nlohmann::json data;

    try
    {

        ConnectionBd connection;

        sql::Connection *con = connection.getConnection();

        std::string query = "INSERT INTO crudcpp (nome, mail) VALUES (?, ?)";
        pstmt = con->prepareStatement(query);

        nlohmann::json jsonData = nlohmann::json::parse(body);

        std::string nome = jsonData["nome"];
        std::string email = jsonData["email"];

        pstmt->setString(1, nome);
        pstmt->setString(2, email);

        res = pstmt->executeUpdate();

        if (res > 0)
        {
            data["success"] = true;
            data["type"] = "POST";
            data["mensage"] = "adicionado com sucesso";
            return data.dump();
        }

        data["success"] = false;
        data["type"] = "POST";
        data["mensage"] = "Erro ao adicionar";
        return data.dump();
    }
    catch (const std::exception &e)
    {
        data["success"] = false;
        data["mensage"] = "Falha de conexão";
        return data.dump();
    }
};
