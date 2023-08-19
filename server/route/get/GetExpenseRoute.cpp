#include "GetExpenseRoute.h"
#include "../../controllers/ExpenseTreatmentController.h"
#include <string>

std::string GetExpenseRoute::GetExpense()
{           
        ExpenseTreatmentController ExpenseTreatment;
        return ExpenseTreatment.getDataExpense();   
}