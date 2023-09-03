#include <cstdlib>
#include <ctime>
#include "SFColor.hpp"

using namespace StiltFox::UniversalLibrary;
using namespace std;

Color::Color()
{
    srand((unsigned int)time(nullptr));
    r = rand()/RAND_MAX;
    g = rand()/RAND_MAX;
    b = rand()/RAND_MAX;
}

Color::Color(int red, int green, int blue) : Color(red/255.0,green/255.0,blue/255.0){}

Color::Color(double red, double green, double blue)
{
    r = red < 0 ? 0 : red > 1 ? 1 : red;
    g = green < 0 ? 0 : green > 1 ? 1 : green;
    b = blue < 0 ? 0 : blue > 1 ? 1 : blue;
}

Color Color::invert()
{
    return {1-r, 1-g, 1-b};
}