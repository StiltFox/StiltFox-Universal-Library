add_library(Logger Logger.cpp)
set_target_properties(Logger PROPERTIES PUBLIC_HEADER "modules/logging/Logger.hpp")
target_include_directories(Logger PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

add_subdirectory(filelogger)

if(NOT SFSkipTesting)
    add_executable(LoggerTest LoggerTest.cpp)
    target_link_libraries(LoggerTest GTest::gtest_main Logger CoutCapture)
    gtest_discover_tests(LoggerTest)
endif()