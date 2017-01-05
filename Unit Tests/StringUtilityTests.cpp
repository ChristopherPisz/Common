
// Project Includes

// Common Library
#include "Exception.h"
#include "StringUtility.h"

// GTest Includes
#include <gtest/gtest.h>

//--------------------------------------------------------------------------------------------------
class StringUtilityTests : public ::testing::Test
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
TEST_F(StringUtilityTests, MultibyteToWide)
{
    // "I am a test"
    const char    utf8[]  = { 0x49, 0x20, 0x61, 0x6D, 0x20, 0x61, 0x20, 0x74, 0x65, 0x73, 0x74, 0x00 };
    const wchar_t utf16[] = { 0x0049, 0x0020, 0x0061, 0x006D, 0x0020, 0x0061, 0x0020, 0x0074, 0x0065, 0x0073, 0x0074, 0x0000 };

    // "Deutsche Ä"
    const char    utf8German[]  = { 0x44, 0x65, 0x75, 0x74, 0x73, 0x63, 0x68, 0x65, 0x20, 0xC3, 0x84, 0x00 };
    const wchar_t utf16German[] = { 0x0044, 0x0065, 0x0075, 0x0074, 0x0073, 0x0063, 0x0068, 0x0065, 0x0020, 0x00C4, 0x0000 };

    const std::string  utf8String        = utf8;
    const std::string  utf8GermanString  = utf8German;
    const std::wstring utf16String       = utf16;
    const std::wstring utf16GermanString = utf16German;
    
    std::wstring wresult = Common::MultibyteToWide(utf8String);
    std::string  result  = Common::WideToMultibyte(utf16String);

    EXPECT_EQ(wresult, utf16String);
    EXPECT_EQ(result, utf8String);

    wresult = Common::MultibyteToWide(utf8German);
    result  = Common::WideToMultibyte(utf16German);

    EXPECT_EQ(wresult, utf16German);
    EXPECT_EQ(result, utf8German);
}

