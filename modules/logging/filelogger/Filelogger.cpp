#include "Filelogger.hpp"

using namespace std;
using namespace StiltFox::UniversalLibrary;

FileLogger::FileLogger(string filePath, bool create, Level suppressionLevel) : Logger(suppressionLevel), logFile(filePath)
{
    this->create = create;
}

void FileLogger::printOut(Level logLevel, string message)
{
    if (logFile.exists() || create)
    {
        logFile.append("\n" + stringValues[logLevel] + ": " + message + "\n");
    }
}