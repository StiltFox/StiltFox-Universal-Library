#include <gtest/gtest.h>
#include "CoutCapture.hpp"
#include "Logger.hpp"

using namespace std;
using namespace StiltFox::UniversalLibrary;

class LoggerTest : public ::testing::TestWithParam<Logger::Level>
{
    protected:
    CoutCapture output;
};

class DebugNegativeTest : public LoggerTest {};
class InfoPositiveTest : public LoggerTest {};
class InfoNegativeTest : public LoggerTest {};
class WarnPositiveTest : public LoggerTest {};
class ErrorPositiveTest : public LoggerTest {};

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

TEST_P(InfoPositiveTest, info_will_print_an_info_message)
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

TEST_P(InfoNegativeTest, info_will_not_print_if_log_level_is_higher_than_info)
{
    //given we have a logger with a suppression level higer than info
    Logger logger(GetParam());

    //when we print an Info message
    logger.info("i can write anything here");

    //then we log nothing
    ASSERT_EQ(output.getOutput(), "");
}

TEST_P(WarnPositiveTest, warn_will_print_a_warn_message)
{
    //given we have a logger with a log level of warn or lower
    Logger logger(GetParam());

    //when we print a warn message
    logger.warn("this is a test message");

    //then we get back a warn log
    ASSERT_EQ(output.getOutput(), "WARN: this is a test message\n");
}

TEST_P(WarnPositiveTest, warn_will_escape_new_lines_and_slashes)
{
    //given we have a logger with a log level of warn or lower
    Logger logger(GetParam());

    //when we print a warn message
    logger.warn("this is a test message\nwe even\\ have a new line.\n\nor two");

    //then we excape the unwanted characters and print
    ASSERT_EQ(output.getOutput(), "WARN: this is a test message\\nwe even\\\\ have a new line.\\n\\nor two\n");
}

TEST_F(LoggerTest, warn_will_not_print_if_level_is_error)
{
    //given we have a logger with a level of Error
    Logger logger(Logger::ERROR);

    //when we print a warn message
    logger.warn("i can write anything here");

    //then we print nothing
    ASSERT_EQ(output.getOutput(), "");
}

TEST_P(ErrorPositiveTest, error_will_print_an_error_log_no_matter_what_level)
{
    //given we have any logger
    Logger logger(GetParam());

    //when we print an error
    logger.error("this is a test message");

    //then we log an error message
    ASSERT_EQ(output.getOutput(), "ERROR: this is a test message\n");
}

TEST_P(ErrorPositiveTest, error_will_escape_new_lines_and_slashes)
{
    //given we have any logger
    Logger logger(GetParam());

    //when we print an error
    logger.error("this is a test message\nwe even\\ have a new line.\n\nor two");

    //then we excape the unwanted characters and print
    ASSERT_EQ(output.getOutput(), "ERROR: this is a test message\\nwe even\\\\ have a new line.\\n\\nor two\n");
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

INSTANTIATE_TEST_SUITE_P(LoggerTest, InfoNegativeTest, ::testing::Values(Logger::ERROR,Logger::WARN),
[](const ::testing::TestParamInfo<InfoPositiveTest::ParamType>& info) 
{
    return Logger::getLevelAsString(info.param);
});

INSTANTIATE_TEST_SUITE_P(LoggerTest, WarnPositiveTest, ::testing::Values(Logger::DEBUG, Logger::INFO, Logger::WARN),
[](const ::testing::TestParamInfo<InfoPositiveTest::ParamType>& info) 
{
    return Logger::getLevelAsString(info.param);
});

INSTANTIATE_TEST_SUITE_P(LoggerTest, ErrorPositiveTest, ::testing::Values(Logger::DEBUG, Logger::INFO, Logger::WARN, Logger::ERROR),
[](const ::testing::TestParamInfo<InfoPositiveTest::ParamType>& info) 
{
    return Logger::getLevelAsString(info.param);
});