add_library(CoutCapture CoutCapture.cpp)
set_target_properties(CoutCapture PROPERTIES PUBLIC_HEADER "main/inquisitor/coutcapture/CoutCapture.hpp")
target_include_directories(CoutCapture PUBLIC "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>" "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>")