#include <gtest/gtest.h>
#include <sstream>
#include <ostream>
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

class LoggerTest : public ::testing::TestWithParam<Logger::Level>
{
    protected:
    CaptureCout output;
};

class DebugNegativeTest : public LoggerTest {};
class InfoPositiveTest : public LoggerTest {};

TEST_F(LoggerTest, debug_will_print_a_debug_message)
{
    //given we have a logger with suppression level of debug
    Logger logger(Logger::DEBUG);

    //when we print a debug message
    logger.debug("this is a test message");

    //then we get back a debug log
    ASSERT_EQ(output.getOutput(), "DEBUG: this is a test message\n");
}

TEST_F(LoggerTest, debug_will_escape_newlines_and_slashes)
{
    //given we have a logger with suppression level of debug
    Logger logger(Logger::DEBUG);

    //when we print a debug message
    logger.debug("this is a test message\nwe even\\ have a new line.\n\nor two");

    //then we get back a debug log
    ASSERT_EQ(output.getOutput(), "DEBUG: this is a test message\\nwe even\\\\ have a new line.\\n\\nor two\n");
}

TEST_P(DebugNegativeTest, debug_will_not_print_if_log_level_is_not_debug)
{
    //given we have a logger with a suppression level of anything other than debug
    Logger logger(GetParam());

    //when we print a debug message
    logger.debug("i can write anything here");

    //then we log nothing
    ASSERT_EQ(output.getOutput(), "");
}

TEST_P(InfoPositiveTest, info_will_print_a_debug_message)
{
    //given we have a logger with suppression level of info or below
    Logger logger(GetParam());

    //when we print a Info message
    logger.info("this is a test message");

    //then we get back an Info log
    ASSERT_EQ(output.getOutput(), "INFO: this is a test message\n");
}

TEST_P(InfoPositiveTest, info_will_escape_newlines_and_slashes)
{
    //given we have a logger with suppression level of info or below
    Logger logger(GetParam());

    //when we print a debug message
    logger.info("this is a test message\nwe even\\ have a new line.\n\nor two");

    //then we get back a debug log
    ASSERT_EQ(output.getOutput(), "INFO: this is a test message\\nwe even\\\\ have a new line.\\n\\nor two\n");
}



INSTANTIATE_TEST_SUITE_P(LoggerTest, DebugNegativeTest, ::testing::Values(Logger::ERROR,Logger::INFO,Logger::WARN),
[](const ::testing::TestParamInfo<DebugNegativeTest::ParamType>& info) 
{
    return Logger::getLevelAsString(info.param);
});

INSTANTIATE_TEST_SUITE_P(LoggerTest, InfoPositiveTest, ::testing::Values(Logger::INFO,Logger::DEBUG),
[](const ::testing::TestParamInfo<InfoPositiveTest::ParamType>& info) 
{
    return Logger::getLevelAsString(info.param);
});