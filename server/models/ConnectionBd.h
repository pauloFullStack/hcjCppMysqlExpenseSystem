#pragma once

// Arquivo ConnectionBd.h

#include <mysql_driver.h>
#include <mysql_connection.h>

class ConnectionBd
{
private:
    sql::mysql::MySQL_Driver *driver;
    sql::Connection *con;

public:
    // Construtor da classe
    ConnectionBd();

    // Destructor da classe
    ~ConnectionBd();

    // Método para obter a conexão
    sql::Connection *getConnection();
};
