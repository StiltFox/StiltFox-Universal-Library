# Stilt Fox™ TempFile

This class is used to create temporary files for unit tests. This class will create itself upon instantiation and delete itself when this object leaves scope. If you intend to pass a temporary file from one method to another, use a pointer to avoid deconstruction.

This class extends the [StiltFox::UniversalLibrary::File](../../file) class, and has public access to all of it's methods.

## Constructors

### TemporaryFile(const char* filePath, string data, filesystem::perms permissions)

* Inputs
    * filePath
        * This is a string that represents the path to the temporary file you wish to create. This could be a relative or absolute path.
    * Data
        * This is the data to initialize the file with. If you wish for an empty file, simply pass "".
    * permissions
        * This represents the file permissions you want the file to have.
        * Defaults to all privileges granted

### TemporaryFile(string filePath, string data, filesystem::perms permissions)

This is the exact same thing as the previous constructor, but it takes an std::string as the filePath. This constructor is for convenience.

## DeConstructor
The created file will be deleted from the file system.

## Usage Example

> #include &lt;Stilt_Fox/UniversalLibrary/TempFile.hpp&gt;  
>
> using namespace StiltFox::UniversalLibrary;
> 
> int main()  
>{   
> &nbsp;&nbsp;&nbsp;&nbsp;TemporaryFile tempFile = ".temp_file_001";  
> &nbsp;&nbsp;&nbsp;&nbsp;tempFile.write("Here is some data");  
>  
> &nbsp;&nbsp;&nbsp;&nbsp;TemporaryFile tempFile2(".temp_file_002", "We can also put data here!");  
> 
> &nbsp;&nbsp;&nbsp;&nbsp;//Now let's create one with only read permissions  
> &nbsp;&nbsp;&nbsp;&nbsp;TemporaryFile tempFile3(".temp_file_003", "read only", "");  
>}
