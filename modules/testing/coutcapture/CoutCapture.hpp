#ifndef StiltFox_UniversalLibrary_CoutCapture
#define StiltFox_UniversalLibrary_CoutCapture
#include <string>
#include <sstream>

namespace StiltFox
{
    namespace UniversalLibrary
    {
        class CoutCapture
        {
            std::stringstream capturedOutput;
            std::streambuf* origionalBuffer;

            public:
            CoutCapture();
            std::string getOutput();
            ~CoutCapture();
        };
    }
}
#endif