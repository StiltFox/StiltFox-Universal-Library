#include <gtest/gtest.h>
#include <filesystem>
#include "CoutCapture.hpp"
#include "File.hpp"
#include "TempFile.hpp"
#include "FileLogger.hpp"

using namespace std;
using namespace StiltFox::UniversalLibrary;

class FileLoggerTest : public ::testing::TestWithParam<Logger::Level>
{
    protected:
    CoutCapture output;
};

TEST_F(FileLoggerTest, debug_will_output_to_file_if_the_file_exists_and_can_be_written_to)
{
    //given we have a file that we can write to
    TemporaryFile logFile = ".FileLogger_tmp_00";
    FileLogger logger(".FileLogger_tmp_00", false, Logger::DEBUG);

    //when we log to that file
    logger.debug("hello world");

    //then we output to the file and not the console
    ASSERT_EQ(logFile.read(), "DEBUG: hello world\n");
    ASSERT_EQ(output.getOutput(), "");
}

TEST_F(FileLoggerTest, debug_will_output_to_file_if_the_file_does_not_exist_and_create_is_true_and_we_can_write)
{
    //given we have a file that does not exist but we allow creation
    File logFile = ".FileLogger_tmp_01";
    FileLogger logger(".FileLogger_tmp_01", true, Logger::DEBUG);

    //when we log to that file
    logger.debug("hello world");

    //then we create the file and write to it
    ASSERT_TRUE(logFile.exists());
    ASSERT_EQ(logFile.read(), "DEBUG: hello world\n");
    ASSERT_EQ(output.getOutput(), "");
    logFile.remove();
}

TEST_F(FileLoggerTest, debug_will_output_to_console_if_file_exists_and_cannot_be_written_to)
{
    //Given we have a file that cannot be written to
    TemporaryFile logFile(".FileLogger_tmp_02", "", filesystem::perms::none);
    FileLogger logger(".FileLogger_tmp_02", false, Logger::DEBUG);

    //when we log to that file
    logger.debug("hello world");

    //then we log out an error to the console
    ASSERT_EQ(logFile.read(), "");
    ASSERT_EQ(output.getOutput(), "ERROR: could not write to log file " + logFile.getPath() + "\nDEBUG: hello world\n");
}

TEST_F(FileLoggerTest, debug_will_output_to_console_if_file_does_not_exist_and_create_is_false)
{
    //given we have a file that does not exist and create is set to false
    File logFile = ".FileLogger_tmp_03";
    FileLogger logger(".FileLogger_tmp_03", false, Logger::DEBUG);

    //when we log to that file
    logger.debug("hello world");

    //then we log out an error to the console
    ASSERT_FALSE(logFile.exists());
    ASSERT_EQ(output.getOutput(), "ERROR: could not write to log file " + logFile.getPath() + "\nDEBUG: hello world\n");
}

TEST_F(FileLoggerTest, debug_will_output_to_console_if_the_file_does_not_exist_and_create_is_true_and_file_cannot_be_created)
{
    //given we have a directory that we do not have permissions to
    filesystem::create_directories(".FileLogger_tmp_04");
    filesystem::permissions(".FileLogger_tmp_04", filesystem::perms::none, filesystem::perm_options::replace);
    FileLogger logger(".FileLogger_tmp_04/newFile", true, Logger::DEBUG);

    //when we log to that file
    logger.debug("hello world");

    //then we log out an error to the console
    filesystem::permissions(".FileLogger_tmp_04", filesystem::perms::all, filesystem::perm_options::replace);
    ASSERT_FALSE(filesystem::exists(filesystem::path(".FileLogger_tmp_04/newFile")));
    ASSERT_EQ(output.getOutput(), "ERROR: could not write to log file .FileLogger_tmp_04/newFile\nDEBUG: hello world\n");
    filesystem::remove(".FileLogger_tmp_04");
}

TEST_F(FileLoggerTest, debug_will_append_to_new_line_if_file_already_has_contents)
{
    //given we have a file with information already in it.
    TemporaryFile tempFile(".FileLogger_tmp_05", "mahnamana");
    FileLogger logger(".FileLogger_tmp_05", true, Logger::DEBUG);

    //when we log to that file
    logger.debug("do-dooo-da-do-do");

    //then we append the log to the file
    ASSERT_EQ(tempFile.read(), "mahnamana\nDEBUG: do-dooo-da-do-do\n");
    ASSERT_EQ(output.getOutput(), "");
}

TEST_F(FileLoggerTest, debug_will_not_append_a_new_line_to_a_file_if_the_file_already_ends_with_new_line)
{
    //given we have a file that already has a new line
    TemporaryFile tempFile(".FileLogger_tmp_05", "mahnamana\n");
    FileLogger logger(".FileLogger_tmp_05", true, Logger::DEBUG);

    //when we log to that file
    logger.debug("do-dooo-da-do-do");

    //then we append the log to the file without a new line
    ASSERT_EQ(tempFile.read(), "mahnamana\nDEBUG: do-dooo-da-do-do\n");
    ASSERT_EQ(output.getOutput(), "");
}