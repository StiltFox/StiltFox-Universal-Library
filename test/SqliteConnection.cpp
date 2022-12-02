#include <gtest/gtest.h>
#include <sqlite3.h>
#include <filesystem>
#include <fstream>
#include <string>
#include "DatabaseConnection.hpp"

using namespace StiltFox::UniversalLibrary;
using namespace std;

std::string createFileData = "CREATE TABLE IF NOT EXISTS FILEDATA (hashcode VARCHAR(255) NOT NULL,title VARCHAR(255),trash BOOLEAN NOT NULL,CONSTRAINT FILE_DATA_PRIMARY_KEY PRIMARY KEY (hashcode));";
std::string createFileTag = "CREATE TABLE IF NOT EXISTS FILETAG (filetagid VARBINARY NOT NULL,name VARCHAR(255) NOT NULL,categoryid VARBINARY NOT NULL,CONSTRAINT FILE_TAG_PRIMARY_KEY PRIMARY KEY (filetagid),CONSTRAINT FILE_TAG_FK_CATEGORY_ID FOREIGN KEY (categoryid) REFERENCES tagcategory(categoryid) ON DELETE RESTRICT ON UPDATE RESTRICT);";

void setupDatabase(std::string databasePath)
{
    sqlite3* connection;
    sqlite3_stmt* createFileStmt;
    sqlite3_stmt* createTagStmt;

    sqlite3_open(databasePath.c_str(), &connection);

    sqlite3_prepare(connection, createFileData.c_str(), createFileData.length(), &createFileStmt, nullptr);
    sqlite3_step(createFileStmt);
    sqlite3_finalize(createFileStmt);
    
    sqlite3_prepare(connection, createFileTag.c_str(), createFileTag.length(), &createTagStmt, nullptr);
    sqlite3_step(createTagStmt);
    sqlite3_finalize(createTagStmt);

    sqlite3_close(connection);
}

TEST(SqliteConnection, connect_will_return_false_and_not_connect_if_the_file_does_not_exist)
{
    //given we try to connect to a non-existing database
    SqliteConnection connection = ".non-existing.db";

    //when we try to connect
    bool actual = connection.connect();

    //then we did not connect
    ASSERT_FALSE(actual);
    ASSERT_FALSE(connection.isConnected());
}

TEST(SqliteConnection, connect_will_not_create_a_file)
{
    //given we have a non-existing database
    SqliteConnection connection = ".non-existing.db";

    //when we try to connect
    connection.connect();

    //then we did not create the database
    ASSERT_FALSE(std::filesystem::exists(".non-existing.db"));
}

TEST(SqliteConnection, connect_will_return_false_and_not_connect_if_the_file_is_not_a_database)
{
    //given we have a file that is not a database
    ofstream badFile(".sqliteConnection_regularfile.txt");
    badFile << "scp-001 proposal draft.";
    badFile.close();
    SqliteConnection connection = ".sqliteConnection_regularfile.txt";

    //when we try to connect to the file
    bool actual = connection.connect();

    //then we dont connect
    ASSERT_FALSE(actual);
    ASSERT_FALSE(connection.isConnected());
    std::filesystem::remove_all(".sqliteConnection_regularfile.txt");
}

TEST(SqliteConnection, getMetaData_gets_the_metadata_from_a_database)
{
    //given we have a database to query
    setupDatabase(".sqliteConnection_test_database.db");
    SqliteConnection connection = ".sqliteConnection_test_database.db";

    //when we get the metadata for the database
    connection.connect();
    unordered_map<string, unordered_map<string, string>> actual = connection.getMetaData();

    //then we get back a map of all the tables and columns
    ASSERT_EQ(actual, (unordered_map<string, unordered_map<string, string>>{
        {"FILEDATA",{{"hashcode", "VARCHAR(255)"}, {"title", "VARCHAR(255)"}, {"trash", "BOOLEAN"}}},
        {"FILETAG",{{"filetagid", "VARBINARY"},{"name", "VARCHAR(255)"},{"categoryid", "VARBINARY"}}}
    }));
    std::filesystem::remove_all(".sqliteConnection_test_database.db");
}

TEST(SqliteConnection, getMetaData_will_return_nothing_if_the_database_is_not_connected)
{
    //given we have a database connection
    setupDatabase(".sqliteConnection_test_database_01.db");
    SqliteConnection connection = ".sqliteConnection_test_database_01.db";

    //when we get back the metadata for the database
    unordered_map<string, unordered_map<string, string>> actual = connection.getMetaData();

    //then we get back nothing because we didnt connect
    ASSERT_EQ(actual, (unordered_map<string, unordered_map<string, string>>{}));
    std::filesystem::remove_all(".sqliteConnection_test_database_01.db");
}