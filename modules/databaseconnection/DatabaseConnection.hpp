#ifndef StiltFox_UniversalLibrary_DatabaseConnection
#define StiltFox_UniversalLibrary_DatabaseConnection
#include <string>
#include <functional>
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
            virtual void performUpdate(std::string, std::vector<std::string>) = 0;
            virtual std::vector<std::unordered_map<std::string,std::string>> performQuery(std::string) = 0;
            virtual std::vector<std::unordered_map<std::string,std::string>> performQuery(std::string, std::vector<std::string>) = 0;
            virtual std::unordered_map<std::string,std::vector<std::unordered_map<std::string, std::string>>> getAllData() = 0;

            bool isConnected()
            {
                return connection != nullptr;
            }
        };
    }
}
#endif