#include "./ExpenseTreatmentController.h"

std::string ExpenseTreatmentController::getDataExpense()
{

    ConnectionBd connection;

    sql::Connection *con = connection.getConnection();

    // Criar consulta SELECT
    std::string query = "SELECT * FROM crudcpp";

    // Crie um objeto PreparedStatement para executar a consulta
    pstmt = con->prepareStatement(query);

    // Execute a consulta e armazene o resultado em um objeto ResultSet
    res = pstmt->executeQuery();

    // Criar um stream de saída para construir a resposta JSON
    // std::ostringstream response_stream;

    // Iniciar o objeto JSON
    response_stream << "{";

    // Crie um array JSON para armazenar os registros do banco de dados
    response_stream << "\"data\":[";

    bool first_row = true;
    while (res->next())
    {
        if (!first_row)
        {
            response_stream << ",";
        }

        response_stream << "{";
        response_stream << "\"id\":" << res->getInt("id") << ",";
        response_stream << "\"nome\":\"" << res->getString("nome") << "\",";
        response_stream << "\"mail\":\"" << res->getString("mail") << "\"";
        response_stream << "}";

        first_row = false;
    }

    // Fechar o array JSON
    response_stream << "]";

    // Fechar o objeto JSON
    response_stream << "}";

    // Libere os recursos do ResultSet e PreparedStatement
    delete res;
    delete pstmt;

    return response_stream.str();
};