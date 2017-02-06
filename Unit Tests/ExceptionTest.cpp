// Project Includes

// Common Library
#include "Exception.h"
#include "FilesAndDirectories.h"

// GTest Includes
#include <gtest/gtest.h>


//--------------------------------------------------------------------------------------------------
class ExceptionTests : public ::testing::Test
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
TEST_F(ExceptionTests, FilePathTest)
{
    const std::string message = "Test Reason";

    try
    {
        throw Common::Exception(__FILE__, __LINE__, message);
    }
    catch(Common::Exception & e)
    {
        // Get path of the current running module
        std::string expectedPath = Common::GetModuleDirectoryA();

        // Travel up two directories
        // We assume the orginal project settings for output directory and source locations
        expectedPath = Common::GetParentDirectoryFromPath(expectedPath);
        expectedPath = Common::GetParentDirectoryFromPath(expectedPath);

        expectedPath += "\\Unit Tests\\ExceptionTest.cpp";
        std::transform(expectedPath.begin(), expectedPath.end(), expectedPath.begin(), ::tolower);

        std::string resultPath = e.GetFilePath();
        EXPECT_EQ(expectedPath, resultPath);

        return;
    }

    // Test case should not reach this point
    FAIL();
}

//--------------------------------------------------------------------------------------------------
TEST_F(ExceptionTests, LineTest)
{
    const std::string message = "Test Reason";

    try
    {
        throw Common::Exception(__FILE__, __LINE__, message);
    }
    catch(Common::Exception & e)
    {
        const unsigned expectedLine = 77;
        unsigned resultLine = e.GetLine();
        
        EXPECT_EQ(expectedLine, resultLine);

        return;
    }

    // Test case should not reach this point
    FAIL();
}

//--------------------------------------------------------------------------------------------------
TEST_F(ExceptionTests, ReasonTest)
{
    const std::string message = "Test Reason";

    try
    {
        throw Common::Exception(__FILE__, __LINE__, message);
    }
    catch(Common::Exception & e)
    {
        std::string reason = e.GetReason();
        EXPECT_EQ(message, reason);

        return;
    }

    // Test case should not reach this point
    FAIL();
}

//--------------------------------------------------------------------------------------------------
TEST_F(ExceptionTests, WhenTest)
{
    const std::string message = "Test Reason";
    boost::posix_time::ptime approximateTimeOfThrow;

    try
    {
        approximateTimeOfThrow = boost::posix_time::microsec_clock::local_time();
        throw Common::Exception(__FILE__, __LINE__, message);
    }
    catch(Common::Exception & e)
    {
        // The best we can really do, without special hardware and testing, is see if the time was close
        // Good enough for our purposes
        boost::posix_time::ptime upper =  approximateTimeOfThrow + boost::posix_time::time_duration(0, 0, 0, 10);
        boost::posix_time::ptime lower =  approximateTimeOfThrow - boost::posix_time::time_duration(0, 0, 0, 10);

        EXPECT_LT(e.GetWhen(), upper);
        EXPECT_GT(e.GetWhen(), lower);

        return;
    }

    // Test case should not reach this point
    FAIL();
}