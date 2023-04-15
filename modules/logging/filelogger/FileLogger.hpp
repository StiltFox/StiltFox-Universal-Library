#ifndef StiltFox_UniversalLibrary_FileLogger
#define StiltFox_UniversalLibrary_FileLogger
#include "File.hpp"
#include "Logger.hpp"

namespace StiltFox
{
    namespace UniversalLibrary
    {
        struct FileLogger : public Logger
        {
            FileLogger(std::string filePath, bool create = true, Level suppressionLevel = ERROR);

            protected:
            virtual void printOut(Level logLevel, std::string message);

            private:
            File logFile;
            bool create;
        };
    }
}
#endif