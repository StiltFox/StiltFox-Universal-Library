#!/bin/bash
mkdir build
cd build
cmake .. -DSFSkipTesting=true
cmake --build .
cmake --install . --prefix ~/.local/dev-bin --config Release
cd ..
mkdir buildWin
cd buildWin
cmake .. -DCMAKE_TOOLCHAIN_FILE=windows.cmake -DSFSkipTesting=true
cmake --build .
cmake --install . --prefix ~/.local/dev-win --config Release
cd ..