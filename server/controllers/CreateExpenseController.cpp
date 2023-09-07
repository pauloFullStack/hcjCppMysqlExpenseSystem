#include "./CreateExpenseController.h"
#include "../helper/password/Password.h"

std::string CreateExpenseController::createExpense(std::string body)
{

    nlohmann::json data;

    try
    {

        ConnectionBd connection;

        sql::Connection *con = connection.getConnection();

        std::string query = "INSERT INTO login_users (name, email, user, password) VALUES (?, ?, ?, ?)";
        pstmt = con->prepareStatement(query);

        nlohmann::json jsonData = nlohmann::json::parse(body);

        std::string name = jsonData["name"];
        std::string email = jsonData["email"];
        std::string user = jsonData["user"];
        
        pstmt->setString(1, name);
        pstmt->setString(2, email);
        pstmt->setString(3, user);
        Password password;
        pstmt->setString(4, password.createHashPassword(jsonData["password"]));

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
