#include "PutExpenseRoute.h"
#include "../../controllers/UpdateExpenseController.h"
#include <string>

std::string PutExpenseRoute::PutExpense(std::string body)
{
    UpdateExpenseController up;
    return up.putExpense(body);
}