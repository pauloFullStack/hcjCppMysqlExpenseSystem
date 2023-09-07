#pragma once

#include <iostream>
#include <string>
#include <openssl/sha.h>


class Password
{

public:
    std::string response;

public:
    std::string createHashPassword(const std::string &);
};
