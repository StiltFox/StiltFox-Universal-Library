#ifndef StiltFox_Utilities_File
#define StiltFox_Utilities_File
#include <string>
namespace StiltFox
{
    namespace UniversalLibrary
    {
        class File
        {
            std::string path;

            public:
            File(const char*);

            std::string readFile();
            std::string readFirstNCharacters(int);
            int getFileSize();
            void write(std::string);
            void append(std::string);
            
            void operator=(std::string);
        };
    }
}
#endif