#ifndef StiltFox_UniversalLibrary_TempFile
#define StiltFox_UniversalLibrary_TempFile
#include <filesystem>
#include "File.hpp"

namespace StiltFox
{
    namespace UniversalLibrary
    {
        struct TemporaryFile : public File
        {
            TemporaryFile(const char* path, std::string data = "", std::filesystem::perms permissions = std::filesystem::perms::all);
            TemporaryFile(std::string path, std::string data = "", std::filesystem::perms permissions = std::filesystem::perms::all);
            ~TemporaryFile();
        };
    }
}
#endif