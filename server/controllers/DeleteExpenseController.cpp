#include "./DeleteExpenseController.h"

std::string DeleteExpenseController::deleteExpense(std::string body)
{

    nlohmann::json data;

    try
    {

        ConnectionBd connection;

        sql::Connection *con = connection.getConnection();

        std::string query = "DELETE FROM crudcpp WHERE id = ? ";
        pstmt = con->prepareStatement(query);

        nlohmann::json jsonData = nlohmann::json::parse(body);

        int id = jsonData["id"];

        pstmt->setInt(1, id);

        res = pstmt->executeUpdate();

        if (res > 0)
        {
            data["success"] = true;
            data["type"] = "DELETE";
            data["mensage"] = "Deletado com sucesso";
            return data.dump();
        }

        data["success"] = false;
        data["mensage"] = "Erro ao Deletado";
        data["type"] = "DELETE";
        return data.dump();
    }
    catch (const std::exception &e)
    {
        data["success"] = false;
        data["mensage"] = "Falha de conexão";
        return data.dump();
    }
};
