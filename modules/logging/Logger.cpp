#include <iostream>
#include <sstream>
#include "Logger.hpp"

using namespace std;
using namespace StiltFox::UniversalLibrary;

const std::unordered_map<Logger::Level, std::string> Logger::stringValues = {{Logger::DEBUG, "DEBUG"}, {Logger::INFO, "INFO"}, {Logger::WARN, "WARN"}, {Logger::ERROR, "ERROR"}};

string cleanString(string& stringToClean)
{
    stringstream output;

    for (int x=0; x<stringToClean.length(); x++)
    {
        switch (stringToClean.at(x))
        {
            case '\\':
                output << "\\\\";
                break;
            case '\n':
                output << "\\n";
                break;
            default:
                output << stringToClean.at(x);
        }
    }

    return output.str();
}

Logger::Logger(Level suppressLvl)
{
    suppressionLevel = suppressLvl;
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

void Logger::bypass(string message)
{
    printOut(INFO, message, true);
}

string Logger::getLevelAsString(Level level)
{
    return stringValues.at(level);
}

void Logger::printOut(Level logLevel, string message, bool bypass)
{
    if (bypass)
    {
        cout << message << endl;
    }
    else
    {
        if (logLevel >= suppressionLevel)
            cout << stringValues.at(logLevel) << ": " << cleanString(message) << endl;
    }
}