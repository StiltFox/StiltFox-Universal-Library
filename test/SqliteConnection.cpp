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
std::string insertFileA = "INSERT INTO FILEDATA (hashcode, title, trash) values ('abc','scp-009',false);";
std::string insertFileB = "INSERT INTO FILEDATA (hashcode, title, trash) values ('asd','scp-000',true);";

void setupDatabase(std::string databasePath)
{
    sqlite3* connection;
    sqlite3_stmt* createFileStmt;
    sqlite3_stmt* createTagStmt;
    sqlite3_stmt* stmtFileA;
    sqlite3_stmt* stmtFileB;

    sqlite3_open(databasePath.c_str(), &connection);

    sqlite3_prepare(connection, createFileData.c_str(), createFileData.length(), &createFileStmt, nullptr);
    sqlite3_step(createFileStmt);
    sqlite3_finalize(createFileStmt);
    
    sqlite3_prepare(connection, createFileTag.c_str(), createFileTag.length(), &createTagStmt, nullptr);
    sqlite3_step(createTagStmt);
    sqlite3_finalize(createTagStmt);

    sqlite3_prepare(connection, insertFileA.c_str(), insertFileA.length(), &stmtFileA, nullptr);
    sqlite3_step(stmtFileA);
    sqlite3_finalize(stmtFileA);

    sqlite3_prepare(connection, insertFileB.c_str(), insertFileB.length(), &stmtFileB, nullptr);
    sqlite3_step(stmtFileB);
    sqlite3_finalize(stmtFileB);

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

TEST(SqliteConnection, connect_will_return_true_and_connect_to_an_empty_file)
{
    //given we have an empty file
    ofstream emptyFile(".sqliteConnection_emptyfile.txt");
    emptyFile.close();
    SqliteConnection connection = ".sqliteConnection_emptyfile.txt";

    //when we try to connect to the file
    bool actual = connection.connect();

    //then we connect
    ASSERT_TRUE(actual);
    ASSERT_TRUE(connection.isConnected());
    std::filesystem::remove_all(".sqliteConnection_emptyfile.txt");
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
    filesystem::remove_all(".sqliteConnection_test_database.db");
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
    filesystem::remove_all(".sqliteConnection_test_database_01.db");
}

TEST(SqliteConnection, performQuery_will_return_the_results_of_a_query_in_string_form)
{
    //given we have a database connection and some data
    setupDatabase(".sqliteConnection_test_database_02.db");
    SqliteConnection connection = ".sqliteConnection_test_database_02.db";

    //when we perform a query
    connection.connect();
    vector<unordered_map<string,string>> actual = connection.performQuery("Select * from FILEDATA;", vector<string>{});

    //then we get back the data from the query
    ASSERT_EQ(actual, (vector<unordered_map<string,string>>{{{"hashcode", "abc"}, {"title", "scp-009"}, {"trash", "0"}}, {{"hashcode", "asd"}, {"title", "scp-000"}, {"trash", "1"}}}));
    filesystem::remove_all(".sqliteConnection_test_database_02.db");
}

TEST(SqliteConnection, performQuery_will_execute_a_parameterized_query)
{
    //given we have a database connection with some data
    setupDatabase(".sqliteConnection_test_database_03.db");
    SqliteConnection connection = ".sqliteConnection_test_database_03.db";

    //when we perform a parameterized query
    connection.connect();
    vector<unordered_map<string,string>> actual = connection.performQuery("Select title from FILEDATA where trash = ?", vector<string>{"1"});

    //then we get back the data from the query
    ASSERT_EQ(actual, (vector<unordered_map<string,string>>{{{"title", "scp-000"}}}));
    filesystem::remove_all(".sqliteConnection_test_database_03.db");
}

TEST(SqliteConnection, getAllData_will_get_all_data_from_the_database)
{
    //given we have a database connection with some data
    setupDatabase(".sqliteConnection_test_database_04.db");
    SqliteConnection connection = ".sqliteConnection_test_database_04.db";
    connection.connect();

    //when we get all the data
    auto actual = connection.getAllData();

    //then we get back all the data in the database
    ASSERT_EQ(actual, (unordered_map<string,vector<unordered_map<string,string>>>{{"FILETAG",{}},{"FILEDATA",{{{"trash","0"},{"title","scp-009"},{"hashcode","abc"}},{{"trash","1"},{"title","scp-000"},{"hashcode","asd"}}}}}));
    filesystem::remove_all(".sqliteConnection_test_database_04.db");
}