#include "./Password.h"

std::string Password::createHashPassword(const std::string &password)
{
    // Inicialize a estrutura de contexto SHA256
    SHA256_CTX sha256;
    SHA256_Init(&sha256);

    // Adicione a senha à estrutura de contexto
    SHA256_Update(&sha256, password.c_str(), password.size());

    // Finalize o cálculo do hash
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_Final(hash, &sha256);

    // Converta o hash binário para uma string hexadecimal
    std::string hashedPassword;
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        char hex[3];
        snprintf(hex, sizeof(hex), "%02x", hash[i]);
        hashedPassword += hex;
    }

    return hashedPassword;
};
