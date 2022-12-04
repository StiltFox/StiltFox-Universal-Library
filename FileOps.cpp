#include <filesystem>
#include <fstream>
#include <functional>
#include "File.hpp"

using namespace StiltFox::UniversalLibrary;
using namespace std;

File::File(const char* filePath)
{
    path = filePath;
}

void File::operator=(string filePath)
{
    path = filePath;
}

string File::readFile()
{
    return readFirstNCharacters(-1);
}

string File::readFirstNCharacters(int numChars)
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

int File::getFileSize()
{
    int output = -1;

    if (filesystem::exists(path))
    {
        ifstream stream(path, ios::in | ios::binary | ios::ate);
        if (stream.is_open()) output = stream.tellg();
        stream.close();
    }

    return output;
}

void File::write(string toWrite)
{
    ofstream stream(path, ofstream::out | ofstream::trunc);
    if (stream.is_open()) stream << toWrite;
    stream.close();
}

void File::append(string toWrite)
{
    ofstream stream(path, ofstream::out | ofstream::app);
    if (stream.is_open()) stream << toWrite;
    stream.close();
}