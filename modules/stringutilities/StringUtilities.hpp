#ifndef StiltFox_UniversalLibrary_StringManipulation
#define StiltFox_UniversalLibrary_StringManipulation
#include <string>
#include <unordered_map>
namespace StiltFox
{
    namespace UniversalLibrary
    {
        namespace StringUtilities
        {
            std::string parseLine(const std::string&);
            std::string parseToDelim(const std::string& toParse, const std::string& delim, bool matchAny = false);
            std::unordered_map<std::string,std::string> parseMap(const std::string& toParse, const std::string& valueDelim, const std::string& entryDelim);
        }
    }
}
#endif