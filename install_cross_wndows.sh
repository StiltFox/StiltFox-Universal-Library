#!/bin/bash
mkdir buildWin
cd buildWin
cmake .. -DCMAKE_TOOLCHAIN_FILE=cmake_files/windows.cmake -DSFSkipTesting=True -DCMAKE_BUILD_TYPE=Release
cmake --build .
cmake --install . --prefix ~/.local/dev-win
cd ..