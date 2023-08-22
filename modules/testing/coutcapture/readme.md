# Stilt Fox™ CoutCapture

This class is intended to help with capturing console output from programs. When this class is initialized it replaces the std::cout buffer with it's own internal buffer. From there, the console output is stored and can be read using the included methods.

IMPORTANT: It is your responsibility to insure thread safety when doing this. Be sure to lock the thread before capturing console output. Multiple threads writing to std::cout at once can lead to unexpected behavior.

## Constructors

### Default Constructor

This constructor first saves the current std::cout buffer to memory, then replaces the buffer with it's own.

## Methods

### std::string getOutput()

* Inputs
    * none
* Outputs
    * All text printed to std::cout before this method was called.
        * This will be returned as an std::string

## DeConstructor

The deconstructor will put the origonal buffer back into std::cout. std::cout messages will no longer be captured and it will output to whatever it was writing to before.

## Usage Example

> #include &lt;Stilt_Fox/UniversalLibrary/CoutCapture.hpp&gt;  
> #include &lt;gtest/gtest.h&gt;  
> #include &lt;iostream&gt;
>
> using namespace std;  
> using namespace StiltFox::UniversalLibrary;
> 
> TEST(sampleTest, CoutCapture_will_capture_the_output_from_cout)  
>{  
> &nbsp;&nbsp;&nbsp;&nbsp;//given we have a CoutCapture object  
> &nbsp;&nbsp;&nbsp;&nbsp;CoutCapture output;  
>
> &nbsp;&nbsp;&nbsp;&nbsp;//when we print to cout  
> &nbsp;&nbsp;&nbsp;&nbsp;cout &lt;&lt; "お元気ですか。";  
>
> &nbsp;&nbsp;&nbsp;&nbsp;//then we get back the console output  
> &nbsp;&nbsp;&nbsp;&nbsp;ASSERT_EQ(output.getOutput(), "お元気ですか。");  
>}