#include "DeleteExpenseRoute.h"
#include "../../controllers/DeleteExpenseController.h"
#include <string>

std::string DeleteExpenseRoute::DeleteExpense(std::string body)
{
    DeleteExpenseController del;
    return del.deleteExpense(body);
}