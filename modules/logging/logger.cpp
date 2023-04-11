#include <iostream>
#include "logger.hpp"

using namespace std;
using namespace StiltFox::UniversalLibrary;

Logger::Logger(Level suppressLvl)
{
    suppressionLevel = suppressLvl;
    stringValues = {{Logger::DEBUG, "DEBUG"}, {Logger::INFO, "INFO"}, {Logger::WARN, "WARN"}, {Logger::ERROR, "ERROR"}};
}

void Logger::debug(string message)
{
    printOut(DEBUG, message);
}

void Logger::info(string message)
{
    printOut(INFO, message);
}

void Logger::warn(string message)
{
    printOut(WARN, message);
}

void Logger::error(string message)
{
    printOut(ERROR, message);
}

void Logger::printOut(Level logLevel, string message)
{
    if (logLevel >= suppressionLevel)
    {
        cout << stringValues[logLevel] << ": " << message << endl;
    }
}