# Stilt Fox™ Universal Library for C++
This library is a set of classes that are used regularly in our projects. It contains things that are generic enough to go in about any project, and it's broken up in a way that you only link to what you need. Only need http processing? Only link libHttpMessage.a... or dll if you're a windows person. These libraries also try to avoid non-portable code, though that has not been tested. We here at Stilt Fox™ run Ubuntu, so your milage may vary.

Stilt Fox™ is not liable for any damages done to your hardware. For more information see LICENSE file.

Stilt Fox™ is trademarked. You may not use the Stilt Fox™ name, however this code is free to reference and use.

You may contribute to this library, however all contributions will share the same license as this library and you agree that Stilt Fox™ owns the copyright for any contributions.

## Compiling the Library
### Supported Systems
- Linux (tested on Pop_Os and Ubuntu)
- Mac (not tested)
- windows (can confirm that the code will cross compile, however this is not tested yet on an actual windows machine)

### Pre Requisites
- CMake must be installed on the system
    - Must be version 3.0.0 or higher
- CryptoPP
    - Can be installed using sudo apt on Ubuntu. It's called libcrypto++-dev
    - Can be built and installed from [source](https://github.com/weidai11/cryptopp)
- Sqlite3
    - Can be installed using sudo apt on Ubuntu. It's called libsqlite3-dev.
    - Can be built from [source](https://sqlite.org/index.html). Add it as a subdirectory to the CMake project.
        - You will need to add the library to the CMake build.
- GTest
    - This is only to run the tests. If you do not care about this and just want ot use the library, you can skip this.
    - Just like the ones before it, this can also be sudo apt installed.
    - [source](https://github.com/google/googletest)

### installation
Right now the only supported installation method is an sh script that runs on linux "install_linux.sh". The other install scripts are not tested and should not be used. In line 6 there is a prefix path listed in the install command. You may delete this to install the libraries in the default location, or change the prefix path to point to a custom install location.

## Project Structure
### modules
This is where the majority of the code is at. This folder contains the code that we wrote. There will be more readme files in there, with information specific to each library.

### cmake_files
This folder just contains some experimental build files.