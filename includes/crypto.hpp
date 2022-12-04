#ifndef StiltFox_UniversalLibrary_Crypto
#define StiltFox_UniversalLibrary_Crypto
#include <string>
namespace StiltFox
{
    namespace UniversalLibrary
    {
        namespace Crypto
        {
            std::string hashSha256(std::string);
            std::string hashMd5(std::string);
        }
    }
}
#endif