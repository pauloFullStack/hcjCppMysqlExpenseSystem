// Arquivo ConnectionBd.cpp

#include "ConnectionBd.h"

// Implementação do construtor
ConnectionBd::ConnectionBd()
{
    // Crie uma instância do driver MySQL Connector/C++
    driver = sql::mysql::get_mysql_driver_instance();

    // Cria a conexão con as credenciais do usuário com permissão
    con = driver->connect("localhost", "user_paulo", "Davi91445129!");

    // Especifique o banco de dados a ser usando
    con->setSchema("cpp");
}

// Implementação do destructor
ConnectionBd::~ConnectionBd()
{
    delete con;
}

// Implementação do método para obter a conexão
sql::Connection* ConnectionBd::getConnection()
{
    return con;
}
