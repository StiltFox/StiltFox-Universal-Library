# Stilt Fox™ Universal Library Testing Modules
This set of modules is only intended to be used for unit tests. We suppose you could use them for other things; however,
they were mostly intended to automate complex tasks like creating temporary files.

NOTE: These classes are not unit tested. They are a part of the testing framework itself. Because of this, the other various unit tests tht they are used in demonstrate them working properly. This is the only package that we do not intend to release unit tests for.

## Included Modules
* [CoutCapture](coutcapture)
    * This module helps get data back from the console. It captures when a program uses the std::cout class and makes it available to you as an output for your tests.

* [TempFile](tempfile)
    * This class creates a temporary file that will be deleted once the class leaves scope. This makes it so you don't have to worry about the cleanup yourself. Just create a file, test against it's contents then proceed to the next test.