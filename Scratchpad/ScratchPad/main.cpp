

#include <iostream>
#include <sstream>

#include <boost/filesystem.hpp>


// Just a garbage console application to do some manual testing.
int main()
{
    const std::string test1 = "D:\\Programing Projects\\Git Workspace\\Common\\x64\\Debug";
    const std::string test2 = "D:\Programing Projects\\Git Workspace\\Common\\x64\\Debug\\";
    const std::string test3 = "D:/Programing Projects/Git Workspace/Common/x64/Debug";
    const std::string test4 = "D:/Programing Projects/Git Workspace/Common/x64/Debug/";

    if (!boost::filesystem::native(test1))
    {
        std::cout << "Boost says the following path is not valid for the native operating system: " << test1 << std::endl;
    }

    if (!boost::filesystem::native(test2))
    {
        std::cout << "Boost says the following path is not valid for the native operating system: " << test2 << std::endl;
    }

    if (!boost::filesystem::native(test3))
    {
        std::cout << "Boost says the following path is not valid for the native operating system: " << test3 << std::endl;
    }

    if (!boost::filesystem::native(test4))
    {
        std::cout << "Boost says the following path is not valid for the native operating system: " << test4 << std::endl;

    }

    const char * temp = reinterpret_cast<const char *>(L"D:\\Programing Projects\\Git Workspace\\Common\\x64\\Debug");
    if (!boost::filesystem::native(temp))
    {
        std::cout << "Boost says the following path is not valid for the native operating system: " << temp << std::endl;

    }

    std::cout << boost::filesystem::native("C://PATH") << std::endl;
    std::cout << boost::filesystem::native("C:/PATH") << std::endl;
    std::cout << boost::filesystem::native("C:\\PATH") << std::endl;
    std::cout << boost::filesystem::native("C:\PATH") << std::endl;
    std::cout << boost::filesystem::native("\PATH") << std::endl;
    std::cout << boost::filesystem::native("\\PATH") << std::endl;
    std::cout << boost::filesystem::native("/PATH") << std::endl;
    std::cout << boost::filesystem::native("//PATH") << std::endl;

    return 0;
}