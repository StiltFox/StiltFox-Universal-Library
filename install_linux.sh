#!/bin/bash
mkdir build
cd build
cmake .. -DSFSkipTesting=true
cmake --build .
cmake --install . --prefix ~/.local/dev-bin
cd ..