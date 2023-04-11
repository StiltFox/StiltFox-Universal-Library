# Stilt Fox™ Universal Library for C++
This library is a set of classes that are used regularly in our projects. It contains things that are generic enough to go in about any project, and it's broken up in a way that you only link to what you need. Only need http processing? Only link libHttpMessage.a... or dll if you're a windows person. These libraries also try to avoid non-portable code, though that has not been tested. We here at Stilt Fox™ run Ubuntu, so your milage may vary.

Stilt Fox™ is not liable for any damages done to your hardware. For more information see LICENSE file.

Stilt Fox™ is trademarked. You may not use the Stilt Fox™ name, however this code is free to reference and use.

You may contribute to this library, however all contributions will share the same license as this library and you agree that Stilt Fox™ owns the copyright for any contributions.

This library is not yet public as it contains code that is not ours in the lib folder. We wish to rectify this before going public. If you distribute this library before release charges will be pressed. Thank you for understanding.

## Compiling the Library
### Supported Systems
- Linux (tested on Pop_Os and Ubuntu)
- Mac (not tested)
- windows (can confirm that the code will cross compile, however this is not tested yet on an actual windows machine)

### Pre Requisites
- CMake must be installed on the system
    - Must be version 3.0.0 or higher

## Project Structure
### modules
This is where the majority of the code is at. This folder contains the code that we wrote. There will be more readme files in there, with information specific to each library.

### lib
This code is not code that we developed. All code in here has it's own license and terms. The licenses here allow me to redistribute the code. More readme files here, if one was not provided by the creators.