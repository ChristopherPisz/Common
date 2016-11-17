

#include <iostream>
#include <sstream>

#include <boost/filesystem.hpp>


// Just a garbage console application to do some manual testing.
int main()
{
    boost::filesystem::path();
    boost::filesystem::path path1("C://PATH");
    boost::filesystem::path path2("C:/PATH");
    boost::filesystem::path path3("C:\\PATH");
    boost::filesystem::path path4("\\PATH");
    boost::filesystem::path path5("/PATH");
    boost::filesystem::path path6("//PATH");
    boost::filesystem::path path7("#?!NotAPath#?!");
    boost::filesystem::path path8("\\");
    boost::filesystem::path path9("/");

    std::cout << path1.parent_path() << std::endl;
    std::cout << path2.parent_path() << std::endl;
    std::cout << path3.parent_path() << std::endl;
    std::cout << path4.parent_path() << std::endl;
    std::cout << path5.parent_path() << std::endl;
    std::cout << path6.parent_path() << std::endl;
    std::cout << path7.parent_path() << std::endl;
    std::cout << path8.parent_path() << std::endl;
    std::cout << path9.parent_path() << std::endl;

    return 0;
}