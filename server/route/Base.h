#pragma once

#include <string>

class Base
{

public:
    std::string response;

public:
    Base(std::string, std::string, int, std::string);
    std::string returnRequest();
};
