#include "PostExpenseRoute.h"
#include "../../controllers/CreateExpenseController.h"
#include <string>

std::string PostExpenseRoute::PostExpense(std::string body)
{
    CreateExpenseController create;
    return create.createExpense(body);
}