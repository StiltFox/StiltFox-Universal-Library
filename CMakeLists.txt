cmake_minimum_required(VERSION 3.12.0)
project(StiltFox_Universal_Library VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(GTest)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
set(version 0.1.0)

if(NOT SFSkipTesting)
message(STATUS ${SFSkipTesting})
  include(GoogleTest)
  enable_testing()
endif()

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include_directories(modules/databaseconnection modules/stringutilites modules/file modules/logging modules/logging/filelogger
  modules/testing/coutcapture)
add_subdirectory(modules)

configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake_files/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/UniversalLibraryConfig.cmake"
  INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/UniversalLibrary
)

install(FILES
          "${CMAKE_CURRENT_BINARY_DIR}/UniversalLibraryConfig.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/UniversalLibraryConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/UniversalLibrary
)

install(
    TARGETS File SFCrypto SqliteConnection SFColor httpmessage stringutilities Logger FileLogger CoutCapture TempFile
    EXPORT UniversalLibrary
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/Stilt_Fox/UniversalLibrary
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}/Stilt_Fox/UniversalLibrary
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}/Stilt_Fox/UniversalLibrary
    INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Stilt_Fox/UniversalLibrary
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/Stilt_Fox/UniversalLibrary
)

install(EXPORT UniversalLibrary
        FILE UniversalLibraryTargets.cmake
        NAMESPACE UniversalLibrary::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/UniversalLibrary
)

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/UniversalLibraryConfigVersion.cmake"
  VERSION "${version}"
  COMPATIBILITY AnyNewerVersion
)