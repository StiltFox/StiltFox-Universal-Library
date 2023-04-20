#include "FileLogger.hpp"

using namespace std;
using namespace StiltFox::UniversalLibrary;

FileLogger::FileLogger(string filePath, bool create, Level suppressionLevel) : Logger(suppressionLevel), logFile(filePath)
{
    this->create = create;
}

void FileLogger::printOut(Level logLevel, string message, bool bypass)
{
    if (logFile.canWrite() && (logFile.exists() || create))
    {
        if (logFile.getSize() > 0 && logFile.readLastNCharacters(1) != "\n") logFile.append("\n");
        if (bypass)
        {
            logFile.append(message + "\n");
        }
        else if (logLevel >= suppressionLevel)
        {
            logFile.append(stringValues.at(logLevel) + ": " + message + "\n");
        }    
    }
    else
    {
        Logger::printOut(Logger::ERROR, "could not write to log file " + logFile.getPath());
        Logger::printOut(logLevel, message, bypass);
    }
}