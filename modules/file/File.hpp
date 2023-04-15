#ifndef StiltFox_UniversalLibrary_File
#define StiltFox_UniversalLibrary_File
#include <functional>
#include <unordered_set>
#include <string>
namespace StiltFox
{
    namespace UniversalLibrary
    {
        class File
        {
            std::string path;
            void createParentPath();

            public:
            File(const char*);
            File(std::string);

            bool canWrite();
            bool canRead();
            bool canExecute();
            bool exists();
            bool touch();
            bool mkdir();
            bool remove();
            bool isDirectory();
            int getSize();
            bool copy(std::string);
            bool write(std::string);
            bool append(std::string);
            std::string read();
            std::string readFirstNCharacters(int);
            std::string readLastNCharacters(int);
            std::string getPath();

            std::string getExtension();
            std::string getNameWithoutExtension();
            std::unordered_set<std::string> list();
            std::unordered_set<std::string> list(std::function<void(std::string)>);
            
            void operator=(std::string);
        };
    }
}
#endif