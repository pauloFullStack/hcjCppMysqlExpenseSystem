#pragma once

#include "../models/ConnectionBd.h"
#include <cppconn/resultset.h>
#include <cppconn/prepared_statement.h>
#include <sstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include <string>
#include <map>

class DeleteExpenseController
{

public:
    std::string deleteExpense(std::string);

    sql::PreparedStatement *pstmt;
    int res;
    std::ostringstream response_stream;
};