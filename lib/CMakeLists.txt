add_subdirectory(sqlite)
set(CRYPTOPP_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/cryptopp)
set(CRYPTOPP_BUILD_TESTING false)
add_subdirectory(cryptopp-cmake)

if(NOT SFSkipTesting)
    add_subdirectory(googletest)
endif()