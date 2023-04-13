add_library(TempFile TempFile.cpp)
target_link_libraries(TempFile File)
set_target_properties(TempFile PROPERTIES PUBLIC_HEADER "modules/testing/tempfile/TempFile.hpp")
target_include_directories(TempFile PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")