add_library(File STATIC File.cpp)
set_target_properties(File PROPERTIES PUBLIC_HEADER "modules/file/File.hpp")
target_include_directories(File PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

if(NOT SFSkipTesting)
    add_executable(FileTest FileTest.cpp)
    target_link_libraries(FileTest GTest::gtest_main File)
    gtest_discover_tests(FileTest)
endif()