#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <sys/stat.h>
#include "File.hpp"

using namespace StiltFox::UniversalLibrary;
using namespace std;

TEST(File, read_file_will_return_empty_if_there_is_no_File)
{
    //givn we have a file that does not exist
    File nonExistingFile = "/path/that/does/not/exist";

    //when we try to read the file
    string output = nonExistingFile.readFile();

    //then we get back a null pointer
    ASSERT_EQ(output, "");
}

TEST(File, read_file_will_not_create_file_if_it_does_not_exist)
{
    //given we provde a non-existing path
    File nonexistingFile = "test.txt";

    //when we try to read the file
    nonexistingFile.readFile();

    //then the file does not exist
    ASSERT_FALSE(filesystem::exists("test.txt"));
}

TEST(File, read_file_will_return_the_data)
{
    //given we provide an existing file with some data in it
    filesystem::create_directory(".FileOps_Read_test_temp");
    ofstream fileToRead(".FileOps_Read_test_temp/SCP-049.txt");

    fileToRead << "class: euclid";
    fileToRead.close();
    File notAFile = ".FileOps_Read_test_temp/SCP-049.txt";

    //when we try to read the file
    string output =  notAFile.readFile();

    //then we get back the contents of the file
    ASSERT_EQ(output, "class: euclid");

    filesystem::remove_all(".FileOps_Read_test_temp");
}

TEST(File, read_file_will_return_empty_if_the_file_has_bad_permissions)
{
    //given we provide a file with bad read permissions
    filesystem::create_directory(".FileOps_Read_test_temp_01");
    ofstream fileToRead(".FileOps_Read_test_temp_01/SCP-682.txt");

    fileToRead << "class: keter";
    fileToRead.close();
    chmod(".FileOps_Read_test_temp_01/SCP-682.txt", 0x00);
    File badPermissionFile = ".FileOps_Read_test_temp_01/SCP-682.txt";

    //when we try to read the file
    string output =  badPermissionFile.readFile();

    //then we get back the contents of the file
    ASSERT_EQ(output, "");

    chmod(".FileOps_Read_test_temp_01/SCP-682.txt", 0x777);
    filesystem::remove_all(".FileOps_Read_test_temp_01");
}

TEST(File, readFirstNCharacters_will_only_read_the_first_specified_characters)
{
    //given we have a really really long file
    ofstream longFile(".FileOps_ReadNChars_longfile");
    longFile << "this is a very long file\n with some file breaks here and there\n";
    longFile.close();
    File file = ".FileOps_ReadNChars_longfile";

    //when we read the first n bytes
    string actual = file.readFirstNCharacters(6);

    //then we get back the first 6 characters
    ASSERT_EQ(actual, "this i");
    filesystem::remove_all(".FileOps_ReadNChars_longfile");
}

TEST(File, readFirstNCharacters_will_only_return_what_is_in_the_file_if_the_file_is_too_small)
{
    //given we have a short file
    std::ofstream shortFile(".FileOps_ReadNChars_shortfile");
    shortFile << "apples";
    shortFile.close();
    File file = ".FileOps_ReadNChars_shortfile";

    //when we read too many chars
    std::string actual = file.readFirstNCharacters(88);

    //then we get back what's in the file
    ASSERT_EQ(actual, "apples");
    std::filesystem::remove_all(".FileOps_ReadNChars_shortfile");
}