#ifndef StiltFox_UniversalLibrary_DatabaseConnection
#define StiltFox_UniversalLibrary_DatabaseConnection
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <vector>
namespace StiltFox
{
    namespace UniversalLibrary
    {
        class DatabaseConnection
        {
            protected:
            void* connection = nullptr;
            std::string connectionString;

            public:
            virtual bool connect() = 0;
            virtual void disconnect() = 0;
            virtual std::unordered_set<std::string> validate(std::unordered_map<std::string, std::unordered_map<std::string, std::string>>) = 0;
            virtual std::unordered_map<std::string, std::unordered_map<std::string, std::string>> getMetaData() = 0;
            virtual void performUpdate(std::string) = 0;
            virtual std::vector<std::unordered_map<std::string,std::string>> performQuery(std::string) = 0;
            virtual std::vector<std::unordered_map<std::string,std::string>> performQuery(std::string, std::vector<std::string>) = 0;

            bool isConnected()
            {
                return connection != nullptr;
            }
        };

        class SqliteConnection : public DatabaseConnection
        {
            bool checkIfValidSqlDatabase();

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
            std::vector<std::unordered_map<std::string, std::string>> performQuery(std::string) override;
            std::vector<std::unordered_map<std::string, std::string>> performQuery(std::string, std::vector<std::string>) override;

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