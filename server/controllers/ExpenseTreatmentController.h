#pragma once

#include "../models/ConnectionBd.h"
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <sstream>

class ExpenseTreatmentController
{

public:
    std::string getDataExpense();

    sql::PreparedStatement *pstmt;
    sql::ResultSet *res;
    std::ostringstream response_stream;
};