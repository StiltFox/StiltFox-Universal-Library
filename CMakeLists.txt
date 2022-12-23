cmake_minimum_required(VERSION 3.12.0)
project(StiltFox_Universal_Library VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 20)

include(CTest)
include(CMakePackageConfigHelpers)

include_directories(includes lib/sqlite)
add_subdirectory(lib EXCLUDE_FROM_ALL)

if(NOT SFSkipTesting)
  add_subdirectory(test)
endif()

add_library(File STATIC File.cpp)
set_target_properties(File PROPERTIES PUBLIC_HEADER "includes/File.hpp")
target_include_directories(File PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

add_library(SFCrypto STATIC Crypto.cpp)
target_link_libraries(SFCrypto cryptopp)
set_target_properties(SFCrypto PROPERTIES PUBLIC_HEADER "includes/SFCrypto.hpp")
target_include_directories(SFCrypto PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

add_library(SqliteConnection STATIC SqliteConnection.cpp)
target_link_libraries(SqliteConnection sqlite3 File)
set_target_properties(SqliteConnection PROPERTIES PUBLIC_HEADER "includes/DatabaseConnection.hpp")
target_include_directories(SqliteConnection PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

add_library(Color STATIC Color.cpp)
set_target_properties(Color PROPERTIES PUBLIC_HEADER "includes/Color.hpp")
target_include_directories(Color PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/UniversalLibraryConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/UniversalLibrary
)

install(FILES
          "${CMAKE_CURRENT_BINARY_DIR}/UniversalLibraryConfig.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/UniversalLibraryConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/UniversalLibrary
)

install(
    TARGETS File SFCrypto SqliteConnection sqlite3 Color cryptopp
    EXPORT UniversalLibrary
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT UniversalLibrary
        FILE UniversalLibraryTargets.cmake
        NAMESPACE UniversalLibrary::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/UniversalLibrary
)

set(version 0.0.1)

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/UniversalLibraryConfigVersion.cmake"
  VERSION "${version}"
  COMPATIBILITY AnyNewerVersion
)