#ifndef StiltFox_UniversalLibrary_FileLogger
#define StiltFox_UniversalLibrary_FileLogger
#include "File.hpp"
#include "logger.hpp"

namespace StiltFox
{
    namespace UniversalLibrary
    {
        struct FileLogger : public Logger
        {
            FileLogger(std::string filePath, bool create, Level suppressionLevel);

            protected:
            virtual void printOut(Level logLevel, std::string message);

            private:
            File logFile;
            bool create;
        };
    }
}
#endif