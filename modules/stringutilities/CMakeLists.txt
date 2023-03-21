add_library(stringutilities StringUtilities.cpp)
set_target_properties(stringutilities PROPERTIES PUBLIC_HEADER "modules/stringutilities/StringUtilities.hpp")
target_include_directories(stringutilities PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")


if(NOT SFSkipTesting)
    add_executable(stringutilitiestest StringUtilitiesTest.cpp)
    target_link_libraries(stringutilitiestest GTest::gtest_main stringutilities)
    gtest_discover_tests(stringutilitiestest)
endif()