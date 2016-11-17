
// Project Includes

// Common Library
#include "Exception.h"
#include "FilesAndDirectories.h"

// GTest Includes
#include <gtest/gtest.h>

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
    EXPECT_EQ(emptyString, result = Common::GetParentDirectory(emptyString));
    
    std::string testPath1  = "C";
    std::string testPath2  = "C:\\";
    std::string testPath3  = "C:\\Windows";
    std::string testPath4  = "C:\\Windows\\system32";
    std::string testPath5  = "C:\\Windows\\system32\\";

    EXPECT_EQ(emptyString, result = Common::GetParentDirectory(emptyString));
    EXPECT_EQ(emptyString, result = Common::GetParentDirectory(testPath1));
    EXPECT_EQ(emptyString, result = Common::GetParentDirectory(testPath2));
    EXPECT_EQ(testPath2,   result = Common::GetParentDirectory(testPath3));
    EXPECT_EQ(testPath3,   result = Common::GetParentDirectory(testPath4));
    EXPECT_EQ(testPath3,   result = Common::GetParentDirectory(testPath5));

    testPath2  = "C:/";
    testPath3  = "C:/Windows";
    testPath4  = "C:/Windows/system32";
    testPath5  = "C:/Windows/system32/";

    EXPECT_EQ(emptyString, result = Common::GetParentDirectory(testPath2));
    EXPECT_EQ(testPath2,   result = Common::GetParentDirectory(testPath3));
    EXPECT_EQ(testPath3,   result = Common::GetParentDirectory(testPath4));
    EXPECT_EQ(testPath3,   result = Common::GetParentDirectory(testPath5));

    testPath1              = "\\";
    testPath2             = "\\Debug";
    testPath3              = "\\Debug\\x86";
    testPath4              = "/";
    testPath5              = "/Debug";
    std::string testPath6  = "/Debug/x86";

    EXPECT_EQ(emptyString, result = Common::GetParentDirectory(testPath1));
    EXPECT_EQ(testPath1,   result = Common::GetParentDirectory(testPath2));
    EXPECT_EQ(testPath2,   result = Common::GetParentDirectory(testPath3));
    EXPECT_EQ(emptyString, result = Common::GetParentDirectory(testPath4));
    EXPECT_EQ(testPath4,   result = Common::GetParentDirectory(testPath5));
    EXPECT_EQ(testPath5,   result = Common::GetParentDirectory(testPath6));

    testPath1  = "#?!NotAPath#?!";
    
    EXPECT_EQ(emptyString, result = Common::GetParentDirectory(testPath1));
}

//--------------------------------------------------------------------------------------------------
TEST_F(FileAndDirectoryTests, IsDirectory)
{
    std::string path = Common::GetModuleDirectoryA();
    EXPECT_TRUE(Common::IsDirectory(path));

    // Travel up two directories
    // We assume the orginal project settings for output directory and source locations
    path = Common::GetParentDirectory(path);
    path = Common::GetParentDirectory(path);

    path += "\\Unit Tests\\FileAndDirectoryTest.cpp";
    EXPECT_FALSE(Common::IsDirectory(path));

    std::string path1 = "C:";
    std::string path2 = "C:\\";
    std::string path3 = "C:\\Windows";
    std::string path4 = "C:\\Windows\\";

    EXPECT_TRUE(Common::IsDirectory(path1));
    EXPECT_TRUE(Common::IsDirectory(path2));
    EXPECT_TRUE(Common::IsDirectory(path3));
    EXPECT_TRUE(Common::IsDirectory(path4));

    path1 = "C:";
    path2 = "C:/";
    path3 = "C:/Windows";
    path4 = "C:/Windows/";

    EXPECT_TRUE(Common::IsDirectory(path1));
    EXPECT_TRUE(Common::IsDirectory(path2));
    EXPECT_TRUE(Common::IsDirectory(path3));
    EXPECT_TRUE(Common::IsDirectory(path4));

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
    std::string path = Common::GetModuleDirectoryA();
    EXPECT_FALSE(Common::IsFile(path));

    // Travel up two directories
    // We assume the orginal project settings for output directory and source locations
    path = Common::GetParentDirectory(path);
    path = Common::GetParentDirectory(path);

    std::string path1 = path + "\\Unit Tests\\FileAndDirectoryTest.cpp";
    std::string path2 = "C:\\";
    std::string path3 = "C:\\Windows";
    std::string path4 = "C:\\Windows\\";

    EXPECT_TRUE(Common::IsFile(path));

    path = "C:\\";
    EXPECT_FALSE(Common::IsFile(path));

    path = "C:\\*";
    EXPECT_FALSE(Common::IsFile(path));
}

//--------------------------------------------------------------------------------------------------
TEST_F(FileAndDirectoryTests, MakeDirectory)
{
    std::string path = Common::GetModuleDirectoryA();
    EXPECT_FALSE(Common::IsFile(path));

    // Travel up two directories
    // We assume the orginal project settings for output directory and source locations
    path = Common::GetParentDirectory(path);
    path = Common::GetParentDirectory(path);

    // Make the directory
    path += "\\Unit Tests\\Temp";
    Common::MakeDirectory(path);

    EXPECT_TRUE(Common::IsDirectory(path));

    // Attempt to make a directory using an invalid path
    path += "\\*?#WhatWhat*!?";

    EXPECT_THROW(Common::MakeDirectory(path);, Common::Exception);
    EXPECT_FALSE(Common::IsDirectory(path));

    // Delete the directory
}

