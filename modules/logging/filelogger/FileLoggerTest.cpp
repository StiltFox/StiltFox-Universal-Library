#include <gtest/gtest.h>
#include "CoutCapture.hpp"
#include "File.hpp"
#include "FileLogger.hpp"

using namespace std;
using namespace StiltFox::UniversalLibrary;

class FileLoggerTest : public ::testing::TestWithParam<Logger::Level>
{
    protected:
    CoutCapture output;
};
/*
TEST_F(FileLoggerTest, debug_will_output_to_file_if_the_file_exists_and_can_be_written_to)
{
    //given we have a file that we can write to
    File logFile = ".FileLogger_tmp_00";
    logFile.touch();
    FileLogger logger(".FileLogger_tmp_00", false, Logger::DEBUG);

    //when we log to that file
    logger.debug("hello world");

    //then we output to the file and not the console
    ASSERT_EQ(logFile.read(), "DEBUG: hello world\n");
    ASSERT_EQ(output.getOutput(), "");
    logFile.remove();
}

/*
TEST_F(FileLoggerTest, debug_will_output_to_file_if_the_file_does_not_exist_and_create_is_true_and_we_can_write)
{}

TEST_F(FileLoggerTest, debug_will_output_to_console_if_file_exists_and_cannot_be_written_to)
{}

TEST_F(FileLoggerTest, debug_will_output_to_console_if_file_does_not_exist_and_create_is_false)
{}

TEST_F(FileLoggerTest, debug_will_output_to_console_if_the_file_does_not_exist_and_create_is_true_and_file_cannot_be_created)
{
}

TEST_F(FileLoggerTest, debug_will_append_to_new_line_if_file_already_has_contents)
{}*/