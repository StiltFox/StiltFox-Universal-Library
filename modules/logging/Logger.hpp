#ifndef StiltFox_UniversalLibrary_Logging
#define StiltFox_UniversalLibrary_Logging
#include <string>
#include <unordered_map>

namespace StiltFox
{
    namespace UniversalLibrary
    {
        struct Logger
        {
            enum Level {DEBUG, INFO, WARN, ERROR};
            Level suppressionLevel;

            Logger(Level suppressionLevel = ERROR);
            void debug(std::string message);
            void info(std::string message);
            void warn(std::string message);
            void error(std::string message);

            protected:
            virtual void printOut(Level logLevel, std::string message);
            std::unordered_map<Logger::Level, std::string> stringValues;
        };
    }
}
#endif