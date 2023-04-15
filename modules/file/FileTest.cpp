#include <gtest/gtest.h>
#include <filesystem>
#include <fstream>
#include <sys/stat.h>
#include "File.hpp"

using namespace StiltFox::UniversalLibrary;
using namespace std;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////File canWrite tests////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, canWrite_will_return_true_if_we_can_write_to_the_File)
{
    //given we have a file that we have write permissions to
    ofstream goodFile(".FileOps_canWrite_good_File");
    goodFile.close();
    File file = ".FileOps_canWrite_good_File";

    //when we get write permissions
    bool actual = file.canWrite();

    //then we get back that we can write
    ASSERT_TRUE(actual);
    filesystem::remove_all(".FileOps_canWrite_good_File");
}

TEST(File, canWrite_will_return_true_on_a_path_that_is_writable_but_the_file_does_not_exist)
{
    //given we have a nonexisting writable path
    File file = ".FileOps_canWrite_good_File01";

    //when we get write permissions
    bool actual = file.canWrite();

    //then we get back that we can write
    ASSERT_TRUE(actual);
}

TEST(File, canWrite_will_return_false_on_a_file_with_bad_permissions)
{
    //given we have a file with bad permissions
    ofstream badFile(".FileOps_canWrite_bad_File");
    badFile.close();
    chmod(".FileOps_canWrite_bad_File", 0x000);
    File file = ".FileOps_canWrite_bad_File";

    //when we get write permissions
    bool actual = file.canWrite();

    //then we get back that we cannot write
    ASSERT_FALSE(actual);
    chmod(".FileOps_canWrite_bad_File", 0x777);
    filesystem::remove_all(".FileOps_canWrite_bad_File");
}

TEST(File, canWrite_will_return_false_for_a_non_existing_path_that_is_not_writable)
{
    //given we have an unwritable path
    filesystem::create_directories(".FileOpes_canWrite_bad_directory");
    chmod(".FileOpes_canWrite_bad_directory", 0x000);
    File file = ".FileOpes_canWrite_bad_directory/file.txt";

    //when we get write permissions
    bool actual = file.canWrite();

    //then we get back that we cannot write
    ASSERT_FALSE(actual);
    chmod(".FileOpes_canWrite_bad_directory", 0x777);
    filesystem::remove_all(".FileOpes_canWrite_bad_directory");
}

TEST(File, canWrite_will_not_create_a_file)
{
    //given we have a nonexisting file
    File file = ".FileOps_canWrite_non_existing_file";

    //when we get write permissions
    bool actual = file.canWrite();

    //then the file is not created
    ASSERT_FALSE(filesystem::exists(".FileOps_canWrite_non_existing_file"));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////File canRead tests/////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, canRead_will_return_true_if_we_can_read_the_File)
{
    //given we have a file that we have read permissions to
    ofstream goodFile(".FileOps_canRead_good_File");
    goodFile.close();
    File file = ".FileOps_canRead_good_File";

    //when we get read permissions
    bool actual = file.canRead();

    //then we get back that we can read
    ASSERT_TRUE(actual);
    filesystem::remove_all(".FileOps_canRead_good_File");
}

TEST(File, canRead_will_return_false_on_a_path_that_does_not_exist)
{
    //given we have a nonexisting path
    File file = ".FileOps_canRead_not_existing";

    //when we get read permissions
    bool actual = file.canRead();

    //then we get back that we cannot read
    ASSERT_FALSE(actual);
}

TEST(File, canRead_will_return_false_on_a_file_with_bad_permissions)
{
    //given we have a file with bad permissions
    ofstream badFile(".FileOps_canRead_bad_File");
    badFile.close();
    chmod(".FileOps_canRead_bad_File", 0x000);
    File file = ".FileOps_canRead_bad_File";

    //when we get read permissions
    bool actual = file.canRead();

    //then we get back that we cannot read
    ASSERT_FALSE(actual);
    chmod(".FileOps_canRead_bad_File", 0x777);
    filesystem::remove_all(".FileOps_canRead_bad_File");
}

TEST(File, canRead_will_not_create_a_file)
{
    //given we have a nonexisting file
    File file = ".FileOps_canRead_non_existing_file";

    //when we get read permissions
    bool actual = file.canRead();

    //then the file is not created
    ASSERT_FALSE(filesystem::exists(".FileOps_canRead_non_existing_file"));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////File canExecute tests///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, canExecute_will_return_true_if_we_can_execute_the_File)
{
    //given we have a file that we have execute permissions to
    ofstream goodFile(".FileOps_canExecute_good_File");
    goodFile.close();
    chmod(".FileOps_canExecute_good_File", 0x777);
    File file = ".FileOps_canExecute_good_File";

    //when we get execute permissions
    bool actual = file.canExecute();

    //then we get back that we can execute
    ASSERT_TRUE(actual);
    filesystem::remove_all(".FileOps_canExecute_good_File");
}

TEST(File, canExecute_will_return_false_on_a_path_that_does_not_exist)
{
    //given we have a nonexisting path
    File file = ".FileOps_canExecute_not_existing";

    //when we get execute permissions
    bool actual = file.canExecute();

    //then we get back that we cannot execute
    ASSERT_FALSE(actual);
}

TEST(File, canExecute_will_return_false_on_a_file_with_bad_permissions)
{
    //given we have a file with bad permissions
    ofstream badFile(".FileOps_canExecute_bad_File");
    badFile.close();
    chmod(".FileOps_canExecute_bad_File", 0x000);
    File file = ".FileOps_canExecute_bad_File";

    //when we get execute permissions
    bool actual = file.canExecute();

    //then we get back that we cannot execute
    ASSERT_FALSE(actual);
    chmod(".FileOps_canExecute_bad_File", 0x777);
    filesystem::remove_all(".FileOps_canExecute_bad_File");
}

TEST(File, canExecute_will_not_create_a_file)
{
    //given we have a nonexisting file
    File file = ".FileOps_canExecute_non_existing_file";

    //when we get read permissions
    bool actual = file.canExecute();

    //then the file is not created
    ASSERT_FALSE(filesystem::exists(".FileOps_canExecute_non_existing_file"));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////File exists tests/////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (File, exists_returns_true_when_the_referenced_file_exists)
{
    //given we have a file
    ofstream aFile(".FileOps_Exists_01");
    aFile.close();
    File file = ".FileOps_Exists_01";

    //when we check if the file exists
    bool actual = file.exists();

    //then we get back true
    ASSERT_TRUE(actual);
    filesystem::remove_all(".FileOps_Exists_01");
}

TEST(File, exists_returns_false_when_the_referenced_file_does_not_exist)
{
    //given we have a file that does not exist
    File file = ".FileOps_exists_non_existing";

    //when we check if the file exists
    bool actual = file.exists();

    //then we get back that the file does not exist
    ASSERT_FALSE(actual);
}

TEST(File, exists_returns_false_if_we_do_not_have_read_permissions_to_a_file)
{
    //given we have a file that we cannot read
    ofstream badFile(".FileOps_exists_badFile");
    badFile.close();
    chmod(".FileOps_exists_badFile", 0x000);
    File file = ".FileOps_exists_badFile";

    //when we check if the file exists
    bool actual = file.exists();

    //then we get back that the file does not exist
    ASSERT_FALSE(actual);
    chmod(".FileOps_exists_badFile", 0x777);
    filesystem::remove_all(".FileOps_exists_badFile");
}

TEST(File, exists_will_not_create_a_file)
{
    //given we have a file that does not exist
    File file = ".FileOps_exists_non_existing_file01";

    //when we check if the file exists
    bool actual = file.exists();

    //then the file is not created
    ASSERT_FALSE(filesystem::exists(".FileOps_exists_non_existing_file01"));
}

TEST(File, exists_will_return_true_For_a_directory)
{
    //given we have a directory
    filesystem::create_directories(".FileOps_exists_directory");
    File file = ".FileOps_exists_directory";

    //when we check if the file exists
    bool actual = file.exists();

    //then we get back true
    ASSERT_TRUE(actual);
    filesystem::remove_all(".FileOps_exists_directory");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////File touch tests//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST (File, touch_will_create_blank_file)
{
    //given we have a file that does not exist
    File file = ".FileOps_touch_01";

    //when we touch the file
    bool actual = file.touch();

    //then we get an empty file
    ASSERT_TRUE(actual);
    ASSERT_TRUE(filesystem::exists(".FileOps_touch_01"));
    ASSERT_TRUE(filesystem::is_regular_file(".FileOps_touch_01"));
    ASSERT_EQ(filesystem::file_size(".FileOps_touch_01"), 0);
    filesystem::remove_all(".FileOps_touch_01");
}

TEST(File, touch_will_return_false_if_writing_is_not_possible)
{
    //given we have a folder without read permissions
    filesystem::create_directories(".FileOps_touch_bad_permisisons");
    File badTouch = ".FileOps_touch_bad_permisisons/badTouch";
    chmod(".FileOps_touch_bad_permisisons", 0x000);

    //when we touch the file
    bool actual = badTouch.touch();

    //then we do not create the file and return false
    chmod(".FileOps_touch_bad_permisisons", 0x777);
    ASSERT_FALSE(actual);
    ASSERT_FALSE(filesystem::exists(".FileOps_touch_bad_permisisons/badTouch"));
    filesystem::remove_all(".FileOps_touch_bad_permisisons");
}

TEST(File, touch_will_return_true_and_not_modify_the_contents_of_an_existing_file)
{
    //given we have an existing file with some contents
    ofstream existingFile(".FileOps_touch_existing");
    existingFile << "here's some data";
    existingFile.close();
    File file = ".FileOps_touch_existing";

    //when we touch the file
    bool actual = file.touch();

    //then we return true and do not edit the file
    ASSERT_TRUE(actual);
    ASSERT_EQ(file.read(), "here's some data");
    filesystem::remove_all(".FileOps_touch_existing");
}

TEST(File, touch_will_create_required_directories)
{
    //given we have a file that needs several directories
    File file = ".FileOps_touch_dir1/ab/bf/test.txt";

    //when we touch the file
    bool actual = file.touch();

    //then we return true and create the file
    ASSERT_TRUE(actual);
    ASSERT_TRUE(filesystem::exists(".FileOps_touch_dir1/ab/bf/test.txt"));
    filesystem::remove_all(".FileOps_touch_dir1");
}

TEST(File, touch_will_crate_a_file_in_an_existng_directory)
{
    //given we have an existing directory
    filesystem::create_directories(".FileOps_touch_dir2/abcd");
    File file = ".FileOps_touch_dir2/abcd/test.txt";

    //when we touch the file
    bool actual = file.touch();

    //then we create the file and return true
    ASSERT_TRUE(actual);
    ASSERT_TRUE(filesystem::exists(".FileOps_touch_dir2/abcd/test.txt"));
    filesystem::remove_all(".FileOps_touch_dir2");
}

TEST(File, touch_will_return_false_if_touched_file_is_a_directory)
{
    //given we have a directory
    filesystem::create_directories(".FileOps_touch_dir3");
    File file = ".FileOps_touch_dir3";

    //when we touch the file
    bool actual = file.touch();

    //then we get back false
    ASSERT_FALSE(actual);
    filesystem::remove_all("FileOps_touch_dir3");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////File mkdir tests//////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, mkdir_will_create_a_directory)
{
    //given we have a path for a nonexisting directory
    File file = ".FileOps_mkdir_new_dir";

    //when we make the directory
    bool actual = file.mkdir();

    //then we get back true and the directory is created
    ASSERT_TRUE(actual);
    ASSERT_TRUE(filesystem::exists(".FileOps_mkdir_new_dir"));
    ASSERT_TRUE(filesystem::is_directory(".FileOps_mkdir_new_dir"));
    filesystem::remove_all(".FileOps_mkdir_new_dir");
}

TEST(File, mkdir_will_return_false_if_requested_path_is_unwriteable)
{
    //given we have a path for a directory with no permissions
    filesystem::create_directories(".FileOps_mkdir_bad_perms");
    chmod(".FileOps_mkdir_bad_perms", 0x000);
    File file = ".FileOps_mkdir_bad_perms/test";

    //when we make the directory
    bool actual = file.mkdir();

    //then we get back false and the directory does not exist
    chmod(".FileOps_mkdir_bad_perms", 0x777);
    ASSERT_FALSE(actual);
    ASSERT_FALSE(filesystem::exists(".FileOps_mkdir_bad_perms/test"));
    filesystem::remove_all(".FileOps_mkdir_bad_perms");
}

TEST(File, mkdir_will_return_false_if_the_file_is_a_regular_file_and_not_edit_it)
{
    //given we have a path to a regular file
    ofstream regFile(".FileOps_mkdir_regular_file");
    regFile << "values";
    regFile.close();
    File file = ".FileOps_mkdir_regular_file";

    //when we try to make a directory
    bool actual = file.mkdir();

    //then we do not alter the file and return false
    ASSERT_FALSE(actual);
    ASSERT_TRUE(filesystem::exists(".FileOps_mkdir_regular_file"));
    ASSERT_EQ(file.read(), "values");
    filesystem::remove_all(".FileOps_mkdir_regular_file");
}

TEST(File, mkdir_will_return_true_if_the_directory_already_exists)
{
    //given we have a directory that already exists
    filesystem::create_directories(".FileOps_mkdir_already_existing");
    File file = ".FileOps_mkdir_already_existing";

    //when we try to create the directory
    bool actual = file.mkdir();

    //then we get back true
    ASSERT_TRUE(actual);
    filesystem::remove_all(".FileOps_mkdir_already_existing");
}

TEST(File, mkdir_will_create_all_needed_directories)
{
    //given we want to create multiple directories
    File file = ".FileOps_mkdir_multi/directories/path";

    //when we try to make the path directory
    bool actual = file.mkdir();

    //then we get back true and the directories are made
    ASSERT_TRUE(actual);
    ASSERT_TRUE(filesystem::exists(".FileOps_mkdir_multi/directories/path"));
    filesystem::remove_all(".FileOps_mkdir_multi");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////File remove tests/////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, remove_will_delete_the_file_from_the_system)
{
    //given we have an existing file
    ofstream existingFile(".FileOps_remove_deleatable_file");
    existingFile.close();
    File file = ".FileOps_remove_deleatable_file";

    //when we try to remove the file
    bool actual = file.remove();

    //then we get back true and the file is removed
    ASSERT_TRUE(actual);
    ASSERT_FALSE(filesystem::exists(".FileOps_remove_deleatable_file"));
}

TEST(File, remove_will_return_false_and_not_remove_the_file_if_permissions_are_not_granted)
{
    //given we have an existing file with bad permissions
    ofstream badFile(".FileOps_remove_bad_permissions");
    badFile.close();
    File file = ".FileOps_remove_bad_permissions";
    chmod(".FileOps_remove_bad_permissions", 0x111);

    //when we try to remove the file
    bool actual = file.remove();

    //then we get back false and do not remove the file
    chmod(".FileOps_remove_bad_permissions", 0x777);
    ASSERT_FALSE(actual);
    ASSERT_TRUE(filesystem::exists(".FileOps_remove_bad_permissions"));
    filesystem::remove_all(".FileOps_remove_bad_permissions");
}

TEST(File, remove_will_delete_a_folder_with_things_in_it)
{
    //given we have a folder with stuff inside of it
    filesystem::create_directories(".FileOps_remove_multi/directories/and/stuff");
    File file = ".FileOps_remove_multi";

    //when we try to remove the file
    bool actual = file.remove();

    //then we get back true and everything is removed
    ASSERT_TRUE(actual);
    ASSERT_FALSE(filesystem::exists(".FileOps_remove_multi"));
}

TEST(File, remove_will_return_true_if_the_file_does_not_exist)
{
    //given we have a file that does not exist
    File file = ".FileOps_remove_does_not_exist";

    //when we try to remove the file
    bool actual = file.remove();

    //then we get back that the file is removed
    ASSERT_TRUE(actual);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////File isDirectory tests//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, isDirectory_will_return_true_if_the_file_is_a_directory)
{
    //given we have a directory
    filesystem::create_directories(".FileOps_isDirectory_directory");
    File file = ".FileOps_isDirectory_directory";

    //when we check if the file is a directory
    bool actual = file.isDirectory();

    //then we get back that the file is a directory
    ASSERT_TRUE(actual);
    filesystem::remove_all(".FileOps_isDirectory_directory");
}

TEST(File, isDirectory_will_return_false_if_the_file_is_not_a_directory)
{
    //given we have a regular file
    ofstream regularFile(".FileOps_isDirectory_regular_file");
    regularFile.close();
    File file = ".FileOps_isDirectory_regular_file";

    //when we check if the file is a directory
    bool actual = file.isDirectory();

    //then we get back that the file is not a directory
    ASSERT_FALSE(actual);
    filesystem::remove_all(".FileOps_isDirectory_regular_file");
}

TEST(File, isDirectory_will_return_false_if_we_dont_have_read_permissions)
{
    //given we have a folder with bad permissions
    filesystem::create_directories(".FileOps_isDirectory_bad_permissions");
    chmod(".FileOps_isDirectory_bad_permissions", 0x000);
    File file = ".FileOps_isDirectory_bad_permissions";

    //when we check if the file is a directory
    bool actual = file.isDirectory();

    //then we get back false
    chmod(".FileOps_isDirectory_bad_permissions", 0x777);
    ASSERT_FALSE(actual);
    filesystem::remove_all(".FileOps_isDirectory_bad_permissions");
}

TEST(File, isDirectory_will_return_false_if_the_file_does_not_exist)
{
    //given we have a file that does not exist
    File file = ".FileOps_isDirectory_does_not_exist";

    //when we check if the file is a directory
    bool actual = file.isDirectory();

    //we get back that the file is not a directory and we do not create it
    ASSERT_FALSE(actual);
    ASSERT_FALSE(filesystem::exists(".FileOps_isDirectory_does_not_exist"));
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////File getSize tests////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, getSize_will_return_negative_one_when_file_does_not_exist)
{
    //given we have a file that does not exist
    File file = ".FileOps_getSize_does_not_exist";

    //when we get the file size
    int size = file.getSize();

    //then we get back an error size
    ASSERT_EQ(size, -1);
}

TEST(File, getFileSize_will_not_create_a_File)
{
    //given we have a file that does not exist
    File file = ".FileOps_getSize_does_not_exist01";

    //when we get the file size
    file.getSize();
    
    //then we do not create the file
    ASSERT_FALSE(filesystem::exists(".FileOps_getSize_does_not_exist01"));
}

TEST(File, getSize_will_return_negative_if_we_do_not_have_permissions)
{
    // given we have a file with bad permissions
    ofstream badFile(".FileOps_getSize_bad_permissions");
    badFile.close();
    chmod(".FileOps_getSize_bad_permissions", 0x000);
    File file = ".FileOps_getSize_bad_permissions";

    //when we get the file size
    int actual = file.getSize();

    //then we get back an error size
    chmod(".FileOps_getSize_bad_permissions", 0x777);
    ASSERT_EQ(actual, -1);
    filesystem::remove_all(".FileOps_getSize_bad_permissions");
}

TEST(File, getSize_will_return_the_size_of_a_file)
{
    //given we have some files
    ofstream file0(".FileOps_getSize_size_00");
    file0 << "this is dr. jack bright.";
    file0.close();
    ofstream file1(".FileOps_getSize_size_01");
    file1.close();
    ofstream file2(".FileOps_getSize_size_02");
    file2 << "scp-000";
    file2.close();
    File f0 = ".FileOps_getSize_size_00";
    File f1 = ".FileOps_getSize_size_01";
    File f2 = ".FileOps_getSize_size_02";

    //when we get their file sizes
    int actual0 = f0.getSize();
    int actual1 = f1.getSize();
    int actual2 = f2.getSize();

    //then we get back the correct file sizes
    ASSERT_EQ(actual0, 24);
    ASSERT_EQ(actual1, 0);
    ASSERT_EQ(actual2, 7);
    filesystem::remove_all(".FileOps_getSize_size_00");
    filesystem::remove_all(".FileOps_getSize_size_01");
    filesystem::remove_all(".FileOps_getSize_size_02");
}

TEST(File, getSize_will_return_the_size_of_the_contents_of_a_directory_recursivly)
{
    //given we have a directory with contents
    filesystem::create_directories(".FileOps_getSize_folder/sub");
    filesystem::create_directories(".FileOps_getSize_folder/sub1/asdf");
    ofstream stream1(".FileOps_getSize_folder/sub/txt1");
    stream1 << "here's some data";
    stream1.close();
    ofstream stream2(".FileOps_getSize_folder/asdf.code");
    stream2 << "test";
    stream2.close();
    ofstream stream3(".FileOps_getSize_folder/sub1/asdf.brb");
    stream3 << "123456789";
    stream3.close();
    ofstream stream4(".FileOps_getSize_folder/sub1/pickle.jpg");
    stream4 << "here is a pickle";
    stream4.close();
    ofstream stream5(".FileOps_getSize_folder/sub1/asdf/something.jpg");
    stream5 << "this is a file";
    stream5.close();
    File file = ".FileOps_getSize_folder";

    //when we get the file size
    int actual = file.getSize();

    //then we get back the size of all the folder's contents
    ASSERT_EQ(actual, 59);
    filesystem::remove_all(".FileOps_getSize_folder");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////File copy tests/////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, copy_will_create_a_file_if_destination_does_not_exist)
{
    //given we have a file to copy
    ofstream toCopy(".FileOps_copy_source00");
    toCopy << "I was stuck staring into the unknown. the inky black.";
    toCopy.close();
    File file = ".FileOps_copy_source00";

    //when we try to copy the file to a non-existing location
    bool actual = file.copy(".FileOps_copy_dest00");

    //then we get back true and the file is copied
    ASSERT_TRUE(actual);
    ASSERT_TRUE(filesystem::exists(".FileOps_copy_source00"));
    ASSERT_TRUE(filesystem::exists(".FileOps_copy_dest00"));
    ASSERT_EQ(file.read(),"I was stuck staring into the unknown. the inky black.");
    ASSERT_EQ(((File)".FileOps_copy_dest00").read(), "I was stuck staring into the unknown. the inky black.");
    filesystem::remove_all(".FileOps_copy_source00");
    filesystem::remove_all(".FileOps_copy_dest00");

}

TEST(File, copy_will_replace_the_contents_of_an_existing_file)
{
    //given we have a existing dest file with contents
    ofstream toCopy(".FileOps_copy_source01");
    toCopy << "Secure, contain, protect";
    toCopy.close();
    ofstream destination(".FileOps_copy_dest01");
    destination << "It has been recorded that there was an XKclass end of the world senario";
    destination.close();
    File file = ".FileOps_copy_source01";

    //when we try to copy the file
    bool actual = file.copy(".FileOps_copy_dest01");

    //then we get back true and the contents is coppied over the old
    ASSERT_TRUE(actual);
    ASSERT_TRUE(filesystem::exists(".FileOps_copy_source01"));
    ASSERT_TRUE(filesystem::exists(".FileOps_copy_dest01"));
    ASSERT_EQ(file.read(),"Secure, contain, protect");
    ASSERT_EQ(((File)".FileOps_copy_dest01").read(), "Secure, contain, protect");
    filesystem::remove_all(".FileOps_copy_source01");
    filesystem::remove_all(".FileOps_copy_dest01");
}

TEST(File, copy_file_will_return_false_and_do_nothing_if_source_file_cannot_be_read)
{
    //given we have a source file without read permisisons
    ofstream toCopy(".FileOps_copy_source_bad");
    toCopy << "Secure, contain, protect";
    toCopy.close();
    chmod(".FileOps_copy_source_bad", 0x666);
    File file = ".FileOps_copy_source_bad";

    //when we try to copy the file
    bool actual = file.copy(".FileOps_copy_dest_bad");

    //then the file is not copied and we return false
    chmod(".FileOps_copy_source_bad", 0x777);
    ASSERT_FALSE(actual);
    ASSERT_FALSE(filesystem::exists(".FileOps_copy_dest_bad"));
    filesystem::remove_all(".FileOps_copy_source_bad");
}

TEST(File, copy_file_will_return_false_and_do_nothing_if_the_destination_cannot_be_written_to)
{
    //given we have a destination that cannot be written to
    ofstream toCopy(".FileOps_copy_source02");
    toCopy << "You do not have clearance to enter the chamber.";
    toCopy.close();
    ofstream bad(".FileOps_copy_dest_bad01");
    bad << "requires 05 clearance";
    bad.close();
    chmod(".FileOps_copy_dest_bad01", 0x555);
    File file = ".FileOps_copy_source02";

    //when we try to copy the file
    bool actual = file.copy(".FileOps_copy_dest_bad01");

    //then we get back false and nothing is changed
    chmod(".FileOps_copy_source02", 0x777);
    ASSERT_FALSE(actual);
    ASSERT_EQ(((File)".FileOps_copy_dest_bad01").read(), "requires 05 clearance");
    filesystem::remove_all(".FileOps_copy_dest_bad01");
    filesystem::remove_all(".FileOps_copy_source02");
}

TEST(File, copy_will_return_false_and_do_nothing_if_source_does_not_exist)
{
    //given we have a destination that does not exist
    File file = ".FileOps_copy_source_not_existing";

    //when we try to copy the file
    bool actual = file.copy(".FileOps_copy_dest_bad02");

    //then we get back false nd the file is not created
    ASSERT_FALSE(actual);
    ASSERT_FALSE(filesystem::exists(".FileOps_copy_dest_bad02"));
}

TEST(File, copy_will_ecursivly_copy_a_folder)
{
    //given we have a directory to copy with files in it
    filesystem::create_directories(".FileOps_copy_folder/sub");
    filesystem::create_directories(".FileOps_copy_folder/sub1/asdf");
    ofstream stream1(".FileOps_copy_folder/sub/txt1");
    stream1 << "here's some data";
    stream1.close();
    ofstream stream2(".FileOps_copy_folder/asdf.code");
    stream2 << "test";
    stream2.close();
    ofstream stream3(".FileOps_copy_folder/sub1/asdf.brb");
    stream3 << "123456789";
    stream3.close();
    ofstream stream4(".FileOps_copy_folder/sub1/pickle.jpg");
    stream4 << "here is a pickle";
    stream4.close();
    ofstream stream5(".FileOps_copy_folder/sub1/asdf/something.jpg");
    stream5 << "this is a file";
    stream5.close();
    File file = ".FileOps_copy_folder";

    //when we copy the folder to a new location
    bool actual = file.copy(".FileOps_copy_folder_dest");

    //then the whole folder and all files are coppied
    ASSERT_TRUE(actual);
    ASSERT_TRUE(filesystem::exists(".FileOps_copy_folder_dest"));
    ASSERT_TRUE(filesystem::exists(".FileOps_copy_folder_dest/asdf.code"));
    ASSERT_TRUE(filesystem::exists(".FileOps_copy_folder_dest/sub"));
    ASSERT_TRUE(filesystem::exists(".FileOps_copy_folder_dest/sub1"));
    ASSERT_TRUE(filesystem::exists(".FileOps_copy_folder_dest/sub/txt1"));
    ASSERT_TRUE(filesystem::exists(".FileOps_copy_folder_dest/sub1/asdf.brb"));
    ASSERT_TRUE(filesystem::exists(".FileOps_copy_folder_dest/sub1/pickle.jpg"));
    ASSERT_TRUE(filesystem::exists(".FileOps_copy_folder_dest/sub1/asdf"));
    ASSERT_TRUE(filesystem::exists(".FileOps_copy_folder_dest/sub1/asdf/something.jpg"));
    filesystem::remove_all(".FileOps_copy_folder_dest");
    filesystem::remove_all(".FileOps_copy_folder");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////File write tests/////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, write_will_return_false_if_the_file_is_a_directory)
{
    //Given we have a directory
    filesystem::create_directories(".FileOps_write_directory");
    File file = ".FileOps_write_directory";

    //When we try to write to the file
    bool actual = file.write("i dunno something");

    //Then we get back false
    ASSERT_FALSE(actual);
    filesystem::remove_all(".FileOps_write_directory");
}

TEST(File, write_will_create_the_file_if_it_does_not_exist)
{
    //Given we have a non-existing file
    File file = ".FileOps_write_non_existing";

    //When we try to write to the file
    bool actual = file.write("Here is a recording of incident SCP-682-5930.");

    //Then we get back true and the file is written with the desired contents
    ASSERT_TRUE(actual);
    ASSERT_TRUE(filesystem::exists(".FileOps_write_non_existing"));
    ASSERT_EQ(((File)".FileOps_write_non_existing").read(), "Here is a recording of incident SCP-682-5930.");
    filesystem::remove_all(".FileOps_write_non_existing");
}

TEST(File, write_will_overwrite_an_existing_file)
{
    //Given we have an existing file with contents
    ofstream existing(".FileOps_write_existing");
    existing << "this is a recount of the true SCP-001";
    existing.close();
    File file = ".FileOps_write_existing";

    //When we try to write to the file
    bool actual = file.write("[redacted]");

    //Then we get back true and the contents of the file is altered
    ASSERT_TRUE(actual);
    ASSERT_EQ(file.read(), "[redacted]");
    filesystem::remove_all(".FileOps_write_existing");
}

TEST(File, write_will_return_false_and_do_nothing_if_we_dont_have_write_permissions)
{
    //Given we have an existing file with bad permissions
    ofstream badFile(".FileOps_write_bad_perms");
    badFile << "this is a recount of the true SCP-001";
    badFile.close();
    chmod(".FileOps_write_bad_perms", 0x555);
    File file = ".FileOps_write_bad_perms";

    //When we try to write to the file
    bool actual = file.write("[redacted]");

    //Then we get back false and nothing is changed
    chmod(".FileOps_write_bad_perms", 0x777);
    ASSERT_FALSE(actual);
    ASSERT_EQ(file.read(), "this is a recount of the true SCP-001");
    filesystem::remove_all(".FileOps_write_bad_perms");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////File append tests////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, append_will_return_false_if_the_file_is_a_directory)
{
    //Given we have a directory
    filesystem::create_directories(".FileOps_append_directory");
    File file = ".FileOps_append_directory";

    //When we try to append to the file
    bool actual = file.append("data");

    //Then we get back false
    ASSERT_FALSE(actual);
    filesystem::remove_all(".FileOps_append_directory");
}

TEST(File, append_will_create_a_file_if_it_does_not_exist)
{
    //Given we have a non-existing file
    File file = ".FileOps_append_non_existing";

    //when we try to append to the file
    bool actual = file.append("[redacted]");

    //then we create the file and return true
    ASSERT_TRUE(actual);
    ASSERT_TRUE(filesystem::exists(".FileOps_append_non_existing"));
    ASSERT_EQ(file.read(), "[redacted]");
    filesystem::remove_all(".FileOps_append_non_existing");
}

TEST(File, append_will_append_to_an_existing_file)
{
    //given we have an existing file with some contents
    ofstream existing(".FileOps_append_existing");
    existing << "We will breif you shortly on ";
    existing.close();
    File file = ".FileOps_append_existing";

    //when we append to the file
    bool actual = file.append("SCP-682");

    //then we get back true and append the data
    ASSERT_TRUE(actual);
    ASSERT_EQ(file.read(), "We will breif you shortly on SCP-682");
    filesystem::remove_all(".FileOps_append_existing");
}

TEST(File, append_will_return_false_and_do_nothing_if_we_do_not_have_write_permission)
{
    //given we have an existing folder with bad permissions
    ofstream badFile(".FileOps_append_bad_perms");
    badFile << "some text";
    badFile.close();
    chmod(".FileOps_append_bad_perms", 0x555);
    File file = ".FileOps_append_bad_perms";

    //when we append to the file
    bool actual = file.append("[redacted]");

    //then we get back false and nothing is changed
    chmod(".FileOps_append_bad_perms", 0x777);
    ASSERT_FALSE(actual);
    ASSERT_EQ(file.read(), "some text");
    filesystem::remove_all(".FileOps_append_bad_perms");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////File read tests/////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, read_will_return_empty_if_there_is_no_File)
{
    //givn we have a file that does not exist
    File nonExistingFile = "/path/that/does/not/exist";

    //when we try to read the file
    string output = nonExistingFile.read();

    //then we get back a null pointer
    ASSERT_EQ(output, "");
}

TEST(File, read_will_not_create_file_if_it_does_not_exist)
{
    //given we provde a non-existing path
    File nonexistingFile = "test.txt";

    //when we try to read the file
    nonexistingFile.read();

    //then the file does not exist
    ASSERT_FALSE(filesystem::exists("test.txt"));
}

TEST(File, read_will_return_the_data)
{
    //given we provide an existing file with some data in it
    filesystem::create_directory(".FileOps_Read_test_temp");
    ofstream fileToRead(".FileOps_Read_test_temp/SCP-049.txt");
    fileToRead << "class: euclid";
    fileToRead.close();
    File notAFile = ".FileOps_Read_test_temp/SCP-049.txt";

    //when we try to read the file
    string output =  notAFile.read();

    //then we get back the contents of the file
    ASSERT_EQ(output, "class: euclid");
    filesystem::remove_all(".FileOps_Read_test_temp");
}

TEST(File, read_will_return_empty_if_the_file_has_bad_permissions)
{
    //given we provide a file with bad read permissions
    filesystem::create_directory(".FileOps_Read_test_temp_01");
    ofstream fileToRead(".FileOps_Read_test_temp_01/SCP-682.txt");
    fileToRead << "class: keter";
    fileToRead.close();
    chmod(".FileOps_Read_test_temp_01/SCP-682.txt", 0x00);
    File badPermissionFile = ".FileOps_Read_test_temp_01/SCP-682.txt";

    //when we try to read the file
    string output =  badPermissionFile.read();

    //then we get back the contents of the file
    ASSERT_EQ(output, "");

    chmod(".FileOps_Read_test_temp_01/SCP-682.txt", 0x777);
    filesystem::remove_all(".FileOps_Read_test_temp_01");
}

TEST(File, read_will_return_empty_if_the_file_is_a_folder)
{
    //given we have a directory
    filesystem::create_directory(".FileOps_read_directory");
    File file = ".FileOps_read_directory";

    //when we try to read the file
    string output = file.read();

    //then we get back empty
    ASSERT_EQ(output, "");
    filesystem::remove_all(".FileOps_read_directory");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////File readFirstNCharacters tests/////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    ofstream shortFile(".FileOps_ReadNChars_shortfile");
    shortFile << "apples";
    shortFile.close();
    File file = ".FileOps_ReadNChars_shortfile";

    //when we read too many chars
    string actual = file.readFirstNCharacters(88);

    //then we get back what's in the file
    ASSERT_EQ(actual, "apples");
    filesystem::remove_all(".FileOps_ReadNChars_shortfile");
}

TEST(File, readFirstNCharacters_will_return_whole_file_if_negative_size_is_passed_in)
{
    //given we have a file
    ofstream someFile(".FileOps_ReadNCharacters_full_file");
    someFile << "under no circumstances should SCP-009 breach containment";
    someFile.close();
    File file = ".FileOps_ReadNCharacters_full_file";

    //when we try to read a negative number of characters
    string actual = file.readFirstNCharacters(-1);

    //then we get back what's in the file
    ASSERT_EQ(actual, "under no circumstances should SCP-009 breach containment");
    filesystem::remove_all(".FileOps_ReadNCharacters_full_file");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////File readLastNCharacters tests/////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, readLastNCharacters_will_only_read_the_last_specified_characters)
{
    //given we have a really really long file
    ofstream longFile(".FileOps_ReadLastNChars_longfile");
    longFile << "this is a very long file\n with some file breaks here and there\n";
    longFile.close();
    File file = ".FileOps_ReadLastNChars_longfile";

    //when we read the last n bytes
    string actual = file.readLastNCharacters(6);

    //then we get back the last 6 characters
    ASSERT_EQ(actual, "there\n");
    filesystem::remove_all(".FileOps_ReadLastNChars_longfile");
}

TEST(File, readLastNCharacters_will_only_return_what_is_in_the_file_if_the_file_is_too_small)
{
    //given we have a short file
    ofstream shortFile(".FileOps_ReadLastNChars_shortfile");
    shortFile << "apples";
    shortFile.close();
    File file = ".FileOps_ReadLastNChars_shortfile";

    //when we read too many chars
    string actual = file.readLastNCharacters(88);

    //then we get back what's in the file
    ASSERT_EQ(actual, "apples");
    filesystem::remove_all(".FileOps_ReadLastNChars_shortfile");
}

TEST(File, readLastNCharacters_will_return_whole_file_if_negative_size_is_passed_in)
{
    //given we have a file
    ofstream someFile(".FileOps_ReadLastNCharacters_full_file");
    someFile << "under no circumstances should SCP-009 breach containment";
    someFile.close();
    File file = ".FileOps_ReadLastNCharacters_full_file";

    //when we try to read a negative number of characters
    string actual = file.readLastNCharacters(-1);

    //then we get back what's in the file
    ASSERT_EQ(actual, "under no circumstances should SCP-009 breach containment");
    filesystem::remove_all(".FileOps_ReadLastNCharacters_full_file");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////File getPath tests///////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

TEST(File, getPath_returns_the_whole_path_pointed_to_by_the_file)
{
    //given we have a file that points to a path
    File file = "some/path";

    //when we get the path
    string filePath = file.getPath();

    //then we get back the path
    ASSERT_EQ(filePath, "some/path");
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////