#include <gtest/gtest.h>
#include <sstream>
#include "Logger.hpp"

using namespace std;
using namespace StiltFox::UniversalLibrary;

class CaptureCout
{
    stringstream capturedOutput;
    streambuf* origionalBuffer;

    public:
    CaptureCout()
    {
        origionalBuffer = cout.rdbuf();
        cout.rdbuf(capturedOutput.rdbuf());
    }

    string getOutput()
    {
        return capturedOutput.str();
    }

    ~CaptureCout()
    {
        cout.rdbuf(origionalBuffer);
    }
};

TEST(Logger, debug_will_print_a_debug_message)
{
    //given we have a logger with suppression level debug
    CaptureCout output;
    Logger logger(Logger::DEBUG);

    //when we print a debug message
    logger.debug("this is a test message");

    //then we get back a debug log
    ASSERT_EQ(output.getOutput(), "DEBUG: this is a test message\n");
}