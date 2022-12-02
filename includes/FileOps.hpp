#ifndef StiltFox_Utilities_FileOps
#define StiltFox_Utilities_FileOps
#include <string>
namespace StiltFox
{
    namespace UniversalLibrary
    {
        namespace FileOps
        {
            std::string readFile(std::string);
            std::string readFirstNCharacters(std::string, int);
        }
    }
}
#endif