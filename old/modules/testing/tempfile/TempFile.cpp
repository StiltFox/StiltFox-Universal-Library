#include "TempFile.hpp"

using namespace std;
using namespace StiltFox::UniversalLibrary;

TemporaryFile::TemporaryFile(const char* filePath, string data, filesystem::perms permissions) : File(filePath)
{
    if (exists()) remove();
    touch();
    filesystem::permissions(filePath, permissions, filesystem::perm_options::replace);
    write(data);
}

TemporaryFile::TemporaryFile(string filePath, string data, filesystem::perms permissions) : TemporaryFile(filePath.c_str(), data, permissions) {}

TemporaryFile::~TemporaryFile()
{
    filesystem::permissions(getPath(),filesystem::perms::all,filesystem::perm_options::replace);
    if (exists()) remove();
}