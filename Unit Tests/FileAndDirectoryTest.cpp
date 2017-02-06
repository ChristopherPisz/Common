
// Project Includes

// Common Library
#include "Exception.h"
#include "FilesAndDirectories.h"

// GTest Includes
#include <gtest/gtest.h>

// Standard Includes
#include <fstream>

//--------------------------------------------------------------------------------------------------
class FileAndDirectoryTests : public ::testing::Test
{

protected:

    //--------------------------------------------------------------------------------------------------
    void SetUp()
    {
    }

    //--------------------------------------------------------------------------------------------------
    static void SetUpTestCase()
    {
    }

    //--------------------------------------------------------------------------------------------------
    void TearDown()
    {
    }

    //--------------------------------------------------------------------------------------------------
    static void TearDownTestCase()
    {
    }
};

//--------------------------------------------------------------------------------------------------
TEST_F(FileAndDirectoryTests, GetParentDirectory)
{
    std::string result;

    const std::string emptyString;
    EXPECT_EQ(emptyString, result = Common::GetParentDirectoryFromPath(emptyString));
    
    std::string testPath1  = "C";
    std::string testPath2  = "C:\\";
    std::string testPath3  = "C:\\Windows";
    std::string testPath4  = "C:\\Windows\\system32";
    std::string testPath5  = "C:\\Windows\\system32\\";

    EXPECT_EQ(emptyString, result = Common::GetParentDirectoryFromPath(emptyString));
    EXPECT_EQ(emptyString, result = Common::GetParentDirectoryFromPath(testPath1));
    EXPECT_EQ(emptyString, result = Common::GetParentDirectoryFromPath(testPath2));
    EXPECT_EQ(testPath2,   result = Common::GetParentDirectoryFromPath(testPath3));
    EXPECT_EQ(testPath3,   result = Common::GetParentDirectoryFromPath(testPath4));
    EXPECT_EQ(testPath3,   result = Common::GetParentDirectoryFromPath(testPath5));

    testPath2  = "C:/";
    testPath3  = "C:/Windows";
    testPath4  = "C:/Windows/system32";
    testPath5  = "C:/Windows/system32/";

    EXPECT_EQ(emptyString, result = Common::GetParentDirectoryFromPath(testPath2));
    EXPECT_EQ(testPath2,   result = Common::GetParentDirectoryFromPath(testPath3));
    EXPECT_EQ(testPath3,   result = Common::GetParentDirectoryFromPath(testPath4));
    EXPECT_EQ(testPath3,   result = Common::GetParentDirectoryFromPath(testPath5));

    testPath1              = "\\";
    testPath2             = "\\Debug";
    testPath3              = "\\Debug\\x86";
    testPath4              = "/";
    testPath5              = "/Debug";
    std::string testPath6  = "/Debug/x86";

    EXPECT_EQ(emptyString, result = Common::GetParentDirectoryFromPath(testPath1));
    EXPECT_EQ(testPath1,   result = Common::GetParentDirectoryFromPath(testPath2));
    EXPECT_EQ(testPath2,   result = Common::GetParentDirectoryFromPath(testPath3));
    EXPECT_EQ(emptyString, result = Common::GetParentDirectoryFromPath(testPath4));
    EXPECT_EQ(testPath4,   result = Common::GetParentDirectoryFromPath(testPath5));
    EXPECT_EQ(testPath5,   result = Common::GetParentDirectoryFromPath(testPath6));

    testPath1  = "#?!NotAPath#?!";
    
    EXPECT_EQ(emptyString, result = Common::GetParentDirectoryFromPath(testPath1));
}

//--------------------------------------------------------------------------------------------------
TEST_F(FileAndDirectoryTests, IsDirectory)
{
    std::string path1 = "C:";
    std::string path2 = "C:\\";
    std::string path3 = "C:\\Windows";
    std::string path4 = "C:\\Windows\\";
    std::string path5 = "C:\\Windows\\notepad.exe";
    std::string path6 = "C:\\Windows\\notepad.exe\\";

    EXPECT_TRUE(Common::IsDirectory(path1));
    EXPECT_TRUE(Common::IsDirectory(path2));
    EXPECT_TRUE(Common::IsDirectory(path3));
    EXPECT_TRUE(Common::IsDirectory(path4));

    EXPECT_FALSE(Common::IsDirectory(path5));
    EXPECT_FALSE(Common::IsDirectory(path6));

    path1 = "C:";
    path2 = "C:/";
    path3 = "C:/Windows";
    path4 = "C:/Windows/";
    path5 = "C:/Windows/notepad.exe";
    path5 = "C:/Windows/notepad.exe/";

    EXPECT_TRUE(Common::IsDirectory(path1));
    EXPECT_TRUE(Common::IsDirectory(path2));
    EXPECT_TRUE(Common::IsDirectory(path3));
    EXPECT_TRUE(Common::IsDirectory(path4));

    EXPECT_FALSE(Common::IsDirectory(path5));
    EXPECT_FALSE(Common::IsDirectory(path6));

    path1 = "C:\\*";
    path2 = "C:/*";
    path3 = "#$GibberJabber$#";

    EXPECT_FALSE(Common::IsDirectory(path1));
    EXPECT_FALSE(Common::IsDirectory(path2));
    EXPECT_FALSE(Common::IsDirectory(path3));
}

//--------------------------------------------------------------------------------------------------
TEST_F(FileAndDirectoryTests, IsFile)
{
	std::string path1 = "C:";
	std::string path2 = "C:\\";
    std::string path3 = "C:\\Windows";
    std::string path4 = "C:\\Windows\\";
	std::string path5 = "C:\\Windows\\notepad.exe";
	std::string path6 = "C:\\Windows\\notepad.exe\\";

    EXPECT_FALSE(Common::IsFile(path1));
    EXPECT_FALSE(Common::IsFile(path2));
    EXPECT_FALSE(Common::IsFile(path3));
    EXPECT_FALSE(Common::IsFile(path4));

    EXPECT_TRUE(Common::IsFile(path5));
    
    EXPECT_FALSE(Common::IsFile(path6));

	path2 = "C:/";
	path3 = "C:/Windows";
	path4 = "C:/Windows/";
	path5 = "C:/Windows/notepad.exe";
    path6 = "C:/Windows/notepad.exe/";

    EXPECT_FALSE(Common::IsFile(path2));
    EXPECT_FALSE(Common::IsFile(path3));
    EXPECT_FALSE(Common::IsFile(path4));

    EXPECT_TRUE(Common::IsFile(path5));

    EXPECT_FALSE(Common::IsFile(path6));

    path2 = "*";
    path3 = "C:\\*";
    path4 = "C:/*";
    path5 = "#?!Gibberish!?#";

    EXPECT_FALSE(Common::IsFile(path2));
    EXPECT_FALSE(Common::IsFile(path3));
    EXPECT_FALSE(Common::IsFile(path4));
    EXPECT_FALSE(Common::IsFile(path5));
}

//--------------------------------------------------------------------------------------------------
TEST_F(FileAndDirectoryTests, MakeDirectory)
{
    std::string path = Common::GetModuleDirectoryA();
    EXPECT_FALSE(Common::IsFile(path));

    // Travel up two directories
    // We assume the orginal project settings for output directory and source locations
    path = Common::GetParentDirectoryFromPath(path);
    path = Common::GetParentDirectoryFromPath(path);

    // Make the directory
    std::string path1 = path  + "\\Unit Tests\\Temp";
    std::string path2 = path1 + "\\*?#WhatWhat*!?";

    Common::MakeDirectory(path1);
    EXPECT_THROW(Common::MakeDirectory(path2); , Common::Exception);

    EXPECT_TRUE(Common::IsDirectory(path1));
    EXPECT_FALSE(Common::IsDirectory(path2));

    // Make a directory that already exists
    Common::MakeDirectory(path1);

    EXPECT_TRUE(Common::IsDirectory(path1));

    // Delete the directory
    Common::DeleteDirectory(path1);
    EXPECT_FALSE(Common::IsDirectory(path1));
}

//--------------------------------------------------------------------------------------------------
TEST_F(FileAndDirectoryTests, GetFileSize)
{
    std::string directoryPath = Common::GetModuleDirectoryA();

    // Travel up two directories
    // We assume the orginal project settings for output directory and source locations
    directoryPath = Common::GetParentDirectoryFromPath(directoryPath);
    directoryPath = Common::GetParentDirectoryFromPath(directoryPath);

    // Make the directory
    directoryPath = directoryPath + "\\Unit Tests\\Temp";
    Common::MakeDirectory(directoryPath);

    EXPECT_TRUE(Common::IsDirectory(directoryPath));
    
    // Create the file
    std::string filePath = directoryPath + "\\GetFileSizeTest.txt";
    std::ofstream file(filePath);

    EXPECT_TRUE(file);
    
    file << "This line is 21 bytes";
    file.close();

    // Check the results
    EXPECT_EQ(21, Common::GetFileSize(filePath));

    // Append some to the file
    file.open(filePath, std::ios::app);

    EXPECT_TRUE(file);

    file << "Here are 23 more bytes.";

    file.close();

    // Check the results
    EXPECT_EQ(44, Common::GetFileSize(filePath));

    // Delete the directory
    Common::DeleteDirectory(directoryPath);
    EXPECT_FALSE(Common::IsDirectory(directoryPath));
}

