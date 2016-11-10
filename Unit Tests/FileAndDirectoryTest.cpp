
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

    path = "C:\\";
    EXPECT_TRUE(Common::IsDirectory(path));

    path = "C:\\*";
    EXPECT_FALSE(Common::IsDirectory(path));
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

    path += "\\Unit Tests\\FileAndDirectoryTest.cpp";
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

