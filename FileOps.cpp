#include <filesystem>
#include <fstream>
#include "FileOps.hpp"

using namespace StiltFox::UniversalLibrary;
using namespace std;

string FileOps::readFile(string path)
{
    return readFirstNCharacters(path, -1);
}

string FileOps::readFirstNCharacters(string path, int numChars)
{
    string output;

    if(filesystem::exists(path))
    {
        ifstream stream(path, ios::in | ios::binary | ios::ate);

        if (stream.is_open())
        {
            int fileSize = stream.tellg();
            int readSize = fileSize < numChars || numChars < 0 ? fileSize : numChars;

            char* buffer = new char[readSize];

            stream.seekg(ios::beg);
            stream.read(buffer, readSize);
            stream.close();

            output = buffer;
            delete[] buffer;
        }
    }

    return output;
}