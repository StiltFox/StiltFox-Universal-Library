cmake_minimum_required(VERSION 3.12.0)
project(StiltFox_Universal_Library VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

find_package(OpenSSL REQUIRED)
include(CTest)

include_directories(includes)
include_directories(lib/sqlite)
add_subdirectory(lib)
add_subdirectory(test)

add_library(FileOps FileOps.cpp)

add_library(SFCrypto Crypto.cpp)
target_link_libraries(SFCrypto OpenSSL::SSL)

add_library(SqliteConnection SqliteConnection.cpp)
target_link_libraries(SqliteConnection sqlite3 FileOps)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)