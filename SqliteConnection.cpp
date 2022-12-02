#include <filesystem>
#include <sqlite3.h>
#include <vector>
#include "DatabaseConnection.hpp"
#include "FileOps.hpp"

using namespace StiltFox::UniversalLibrary;
using namespace std;

bool SqliteConnection::connect()
{
    bool output = false;
    
    if(connection == nullptr && checkIfValidSqlDatabase())
    {
        sqlite3* newConnection;
        if (sqlite3_open(connectionString.c_str(), &newConnection) == SQLITE_OK)
        {
            connection = newConnection;
            output = true;
        }
    }

    return output;
}

void SqliteConnection::disconnect()
{
    sqlite3_close((sqlite3*)connection);
    connection = nullptr;
}

unordered_map<string, unordered_map<string, string>> SqliteConnection::getMetaData()
{
    unordered_map<string, unordered_map<string, string>> output;

    if (connection != nullptr)
    {
        sqlite3* dbConnection = (sqlite3*)connection;
        sqlite3_stmt* statement = nullptr;
        sqlite3_stmt* tableInfoStmt = nullptr;

        if (sqlite3_prepare(dbConnection, "select tbl_name from sqlite_schema where type = 'table';", -1, &statement, NULL) == SQLITE_OK &&
            sqlite3_prepare(dbConnection, "select * from pragma_table_info(?);", -1, &tableInfoStmt, nullptr) == SQLITE_OK)
        {
            while (sqlite3_step(statement) == SQLITE_ROW)
            {
                string tableName = (char*)sqlite3_column_text(statement, 0);
                sqlite3_bind_text(tableInfoStmt, 1, tableName.c_str(), tableName.size(), SQLITE_STATIC);
                while (sqlite3_step(tableInfoStmt) == SQLITE_ROW)
                {
                    output[tableName][(char*)sqlite3_column_text(tableInfoStmt,1)] = (char*)sqlite3_column_text(tableInfoStmt, 2);
                }
                sqlite3_reset(tableInfoStmt);
            }
        }

        sqlite3_finalize(statement);
        sqlite3_finalize(tableInfoStmt);
    }

    return output;
}

unordered_set<string> SqliteConnection::validate(unordered_map<string, unordered_map<string, string>> validStructure)
{
    unordered_set<string> output;
    unordered_map<string, unordered_map<string, string>> metadata = getMetaData();

    for (auto const&[tableName, columnData] : metadata)
    {
        if (validStructure.contains(tableName))
        {
            for (auto const&[columnName, columnType] : columnData)
            {
                if(validStructure[tableName].contains(columnName))
                {
                    if (validStructure[tableName][columnName] != columnType)
                        output.insert("Column " + columnName + " in table " + tableName + " is the wrong type; expected: " + validStructure[tableName][columnName] + " actual: " + columnType);
                }
                else
                {
                    output.insert("Unwanted column in " + tableName + ": " + columnName);
                }
            }
        }
        else
        {
            output.insert("Unwanted table " + tableName);
        }
    }

    for (auto const&[tableName, columnData] : validStructure)
    {
        if (metadata.contains(tableName))
        {
            for (auto const&[columnName, columnType] : columnData)
                if (!metadata[tableName].contains(columnName)) output.insert("Misssing column in " + tableName + " type " + columnType);
        }
        else
        {
            output.insert("Missing table " + tableName);
        }
    }

    return output;
}

bool SqliteConnection::checkIfValidSqlDatabase()
{
    return FileOps::readFirstNCharacters(connectionString, 16) == "SQLite format 3\000";
}