add_library(Logger logger.cpp)
set_target_properties(Logger PROPERTIES PUBLIC_HEADER "modules/logging/logger.hpp")
target_include_directories(Logger PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")

add_subdirectory(filelogger)