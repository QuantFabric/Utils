#include "SQLiteManager.hpp"
#include <stdio.h>


int main(int argc, char* argv[])
{
    Utils::SQLiteManager* sqliteManager = Utils::Singleton<Utils::SQLiteManager>::GetInstance();
    std::string errorString;
    if(sqliteManager->LoadDataBase("test.db", errorString))
    {
        printf("LoadDataBase successed.\n");
    }
    else
    {
        printf("%s\n", errorString.c_str());
    }
    // Create Table
    std::string CREATE_TABLE = "CREATE TABLE IF NOT EXISTS RiskLimit(ID INT PRIMARY KEY NOT NULL,\
                                                    FlowLimit  INT NOT NULL,\
                                                    InstrumentCancelledLimit INT NOT NULL,\
                                                    OrderCancelLimit INT NOT NULL);";
    if(sqliteManager->Execute(CREATE_TABLE, &Utils::SQLiteManager::callback, errorString))
    {
        printf("CREATE_TABLE Execute successed.\n");
    }
    else
    {
        printf("%s\n", errorString.c_str());
    }
    // Create Table
    CREATE_TABLE = "CREATE TABLE IF NOT EXISTS InstrumentLimit(InstrumentKey CHAR[32] PRIMARY KEY NOT NULL, CancelCount   INT NOT NULL);";
    if(sqliteManager->Execute(CREATE_TABLE, &Utils::SQLiteManager::callback, errorString))
    {
        printf("CREATE_TABLE Execute successed.\n");
    }
    else
    {
        printf("%s\n", errorString.c_str());
    }
    // Insert
    std::string INSERT = "INSERT INTO InstrumentLimit(InstrumentKey, CancelCount) VALUES ('HX-1:IC2108', 1);";
    if(sqliteManager->Execute(INSERT, &Utils::SQLiteManager::callback, errorString))
    {
        printf("INSERT Execute successed.\n");
    }
    else
    {
        printf("%s\n", errorString.c_str());
    }
    // Select
    std::string SELECT = "SELECT * FROM InstrumentLimit WHERE InstrumentKey = 'HX-1:IC2108';";
    if(sqliteManager->Execute(SELECT, &Utils::SQLiteManager::callback, errorString))
    {
        printf("SELECT Execute successed.\n");
    }
    else
    {
        printf("%s\n", errorString.c_str());
    }
    // Update
    std::string UPDATE = "UPDATE InstrumentLimit SET CancelCount = 2 WHERE InstrumentKey = 'HX-1:IC2108';";
    if(sqliteManager->Execute(UPDATE, &Utils::SQLiteManager::callback, errorString))
    {
        printf("UPDATE Execute successed.\n");
    }
    else
    {
        printf("%s\n", errorString.c_str());
    }
    sqliteManager->CloseDataBase(errorString);

    return 0;
}

// g++ SQLiteManagerTest.cpp -o test -lsqlite3