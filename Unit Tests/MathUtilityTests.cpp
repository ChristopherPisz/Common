
// Project Includes

// Common Library
#include "Exception.h"
#include "MathUtility.h"

// Boost Includes
#include <boost/math/special_functions/next.hpp>

// GTest Includes
#include <gtest/gtest.h>

//--------------------------------------------------------------------------------------------------
class MathUtilityTests : public ::testing::Test
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
TEST_F(MathUtilityTests, Compare)
{
    // Let's assume we were comparing monetary values
    // Let's also assume we're not concerned with the implications of truncating the values
    const size_t significantDigits  = FLT_DIG;
    const float  originalNumber     = 100.000f;
    const float  nextAvailavleFloat = boost::math::float_next(originalNumber);

    EXPECT_TRUE (Common::AreAlmostEqual(originalNumber, originalNumber + 0.001f, 0.01f));
    EXPECT_TRUE (Common::AreAlmostEqual(originalNumber, originalNumber + 0.009f, 0.01f));
    EXPECT_FALSE(Common::AreAlmostEqual(originalNumber, originalNumber + 0.010f, 0.01f));
}

