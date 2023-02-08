#ifndef StiltFox_UniversalLibrary_SFCrypto
#define StiltFox_UniversalLibrary_SFCrypto
#include <string>
namespace StiltFox
{
    namespace UniversalLibrary
    {
        namespace SFCrypto
        {
            std::string hashSha256(std::string);
            std::string hashMd5(std::string);
        }
    }
}
#endif