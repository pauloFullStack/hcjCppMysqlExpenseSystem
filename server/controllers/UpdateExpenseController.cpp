#include "./UpdateExpenseController.h"

std::string UpdateExpenseController::putExpense(std::string body)
{

    nlohmann::json data;

    try
    {

        ConnectionBd connection;

        sql::Connection *con = connection.getConnection();

        std::string query = "UPDATE crudcpp SET nome = ?, mail = ? WHERE id = ? ";
        pstmt = con->prepareStatement(query);

        nlohmann::json jsonData = nlohmann::json::parse(body);

        std::string nome = jsonData["nome"];
        std::string email = jsonData["email"];
        int id = jsonData["id"];

        pstmt->setString(1, nome);
        pstmt->setString(2, email);
        pstmt->setInt(3, id);

        res = pstmt->executeUpdate();

        if (res > 0)
        {
            data["success"] = true;
            data["type"] = "PUT";
            data["mensage"] = "atualizado com sucesso";
            return data.dump();
        }

        data["success"] = false;
        data["mensage"] = "Erro ao atualizar";
        data["type"] = "PUT";
        return data.dump();
    }
    catch (const std::exception &e)
    {
        data["success"] = false;
        data["mensage"] = "Falha de conexão";
        return data.dump();
    }
};
