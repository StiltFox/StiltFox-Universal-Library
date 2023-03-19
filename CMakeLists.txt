cmake_minimum_required(VERSION 3.12.0)
project(StiltFox_Universal_Library VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(GoogleTest)
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
set(version 0.1.0)
enable_testing()

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

include_directories(lib/sqlite modules/databaseconnection modules/stringutilites)
add_subdirectory(lib EXCLUDE_FROM_ALL)
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
    TARGETS File SFCrypto SqliteConnection sqlite3 SFColor cryptopp httpmessage stringutilities
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

# generate the version file for the config file
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/UniversalLibraryConfigVersion.cmake"
  VERSION "${version}"
  COMPATIBILITY AnyNewerVersion
)