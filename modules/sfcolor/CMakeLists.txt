add_library(SFColor STATIC SFColor.cpp)
set_target_properties(SFColor PROPERTIES PUBLIC_HEADER "SFColor.hpp")
target_include_directories(SFColor PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")