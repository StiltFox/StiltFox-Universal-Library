#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <sys/stat.h>
#include "FileOps.hpp"

using namespace StiltFox::UniversalLibrary::FileOps;

TEST(FileOps, read_file_will_return_empty_if_there_is_no_File)
{
    //givn we provide a string that does not exist
    std::string nonExistingPath = "/path/that/does/not/exist";

    //when we try to read the file
    std::string output = readFile(nonExistingPath);

    //then we get back a null pointer
    ASSERT_EQ(output, "");
}

TEST(FileOps, read_file_will_not_create_file_if_it_does_not_exist)
{
    //given we provde a non-existing path
    std::string nonexistingPath = "test.txt";

    //when we try to read the file
    readFile(nonexistingPath);

    //then the file does not exist
    ASSERT_FALSE(std::filesystem::exists(nonexistingPath));
}

TEST(FileOps, read_file_will_return_the_data)
{
    //given we provide an existing file with some data in it
    std::filesystem::create_directory(".FileOps_Read_test_temp");
    std::ofstream fileToRead(".FileOps_Read_test_temp/SCP-049.txt");

    fileToRead << "class: euclid";
    fileToRead.close();

    //when we try to read the file
    std::string output =  readFile(".FileOps_Read_test_temp/SCP-049.txt");

    //then we get back the contents of the file
    ASSERT_EQ(output, "class: euclid");

    std::filesystem::remove_all(".FileOps_Read_test_temp");
}

TEST(FileOps, read_file_will_return_empty_if_the_file_has_bad_permissions)
{
    //given we provide a file with bad read permissions
    std::filesystem::create_directory(".FileOps_Read_test_temp_01");
    std::ofstream fileToRead(".FileOps_Read_test_temp_01/SCP-682.txt");

    fileToRead << "class: keter";
    fileToRead.close();
    chmod(".FileOps_Read_test_temp_01/SCP-682.txt", 0x00);

    //when we try to read the file
    std::string output =  readFile(".FileOps_Read_test_temp_01/SCP-682.txt");

    //then we get back the contents of the file
    ASSERT_EQ(output, "");

    chmod(".FileOps_Read_test_temp_01/SCP-682.txt", 0x777);
    std::filesystem::remove_all(".FileOps_Read_test_temp_01");
}

TEST(FileOps, readFirstNCharacters_will_only_read_the_first_specified_characters)
{
    //given we have a really really long file
    std::ofstream longFile(".FileOps_ReadNChars_longfile");
    longFile << "this is a very long file\n with some file breaks here and there\n";
    longFile.close();

    //when we read the first n bytes
    std::string actual = readFirstNCharacters(".FileOps_ReadNChars_longfile", 6);

    //then we get back the first 6 characters
    ASSERT_EQ(actual, "this i");
    std::filesystem::remove_all(".FileOps_ReadNChars_longfile");
}

TEST(FileOps, readFirstNCharacters_will_only_return_what_is_in_the_file_if_the_file_is_too_small)
{
    //given we have a short file
    std::ofstream shortFile(".FileOps_ReadNChars_shortfile");
    shortFile << "apples";
    shortFile.close();

    //when we read too many chars
    std::string actual = readFirstNCharacters(".FileOps_ReadNChars_shortfile", 88);

    //then we get back what's in the file
    ASSERT_EQ(actual, "apples");
    std::filesystem::remove_all(".FileOps_ReadNChars_shortfile");
}