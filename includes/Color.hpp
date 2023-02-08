#ifndef StiltFox_UniversalLibrary_Color
#define StiltFox_UniversalLibrary_Color
namespace StiltFox
{
    namespace UniversalLibrary
    {
        class Color
        {
            double r;
            double g;
            double b;

            public:
            Color();
            Color(int,int,int);
            Color(double,double,double);
            Color invert();
        };
    }
}
#endif