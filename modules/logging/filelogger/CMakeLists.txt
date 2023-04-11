add_library(FileLogger filelogger.cpp)
target_link_libraries(FileLogger Logger)
set_target_properties(FileLogger PROPERTIES PUBLIC_HEADER "modules/logging/filelogger/filelogger.hpp")
target_include_directories(FileLogger PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")