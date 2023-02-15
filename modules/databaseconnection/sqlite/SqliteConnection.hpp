#ifndef StiltFox_UniversalLibrary_SqliteConnection
#define StiltFox_UniversalLibrary_SqliteConnection
#include "DatabaseConnection.hpp"
namespace StiltFox
{
    namespace UniversalLibrary
    {
        class SqliteConnection : public DatabaseConnection
        {
            bool checkIfValidSqlDatabase();
            void forEachTable(std::function<void(std::string)>);

            public:
            SqliteConnection(const char* connection)
            {
                connectionString = connection;
            }

            bool connect() override;
            void disconnect() override;
            std::unordered_set<std::string> validate(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>) override;
            std::unordered_map<std::string, std::unordered_map<std::string, std::string>> getMetaData() override;
            void performUpdate(std::string) override;
            void performUpdate(std::string, std::vector<std::string>) override;
            std::vector<std::unordered_map<std::string, std::string>> performQuery(std::string) override;
            std::vector<std::unordered_map<std::string, std::string>> performQuery(std::string, std::vector<std::string>) override;
            std::unordered_map<std::string,std::vector<std::unordered_map<std::string, std::string>>> getAllData() override;

            void operator=(std::string connection)
            {
                connectionString = connection;
            }

            ~SqliteConnection()
            {
                if (connection != nullptr) disconnect();
            }
        };
    }
}
#endif