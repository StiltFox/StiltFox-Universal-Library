#!/bin/bash
mkdir build
cd build
cmake .. -DSFSkipTesting=true -DCMAKE_BUILD_TYPE=Release
cmake --build .
cmake --install . --prefix ~/.local/dev-bin
cd ..