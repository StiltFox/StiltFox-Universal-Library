#!/bin/bash
rm -rf buildMac
mkdir buildMac
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=cmake_files/Mac.cmake -DSFSkipTesting=true -DCMAKE_BUILD_TYPE=Release
cmake --build .
cmake --install . --prefix ~/.local/dev-bin
cd ..