#include <iostream>
#include "CoutCapture.hpp"

using namespace std;
using namespace StiltFox::UniversalLibrary;

CoutCapture::CoutCapture()
{
    origionalBuffer = cout.rdbuf();
    cout.rdbuf(capturedOutput.rdbuf());
}

string CoutCapture::getOutput()
{
    return capturedOutput.str();
}

CoutCapture::~CoutCapture()
{
    cout.rdbuf(origionalBuffer);
}