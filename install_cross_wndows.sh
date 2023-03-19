#!/bin/bash
mkdir buildWin
cd buildWin
cmake .. -DCMAKE_TOOLCHAIN_FILE=cmake_files/windows.cmake -DSFSkipTesting=true
cmake --build .
cmake --install . --prefix ~/.local/dev-win
cd ..