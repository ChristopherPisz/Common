

// Project Includes
#include "stdafx.h"
#include "MathUtility.h"

//--------------------------------------------------------------------------------------------------
namespace Common
{

//--------------------------------------------------------------------------------------------------
bool AreAlmostEqual(const float & a, const float & b, const float epsilon /*= std::numeric_limits<float>::epsilon()*/)
{
    // If diff is smaller than n% of max(abs(A),abs(B)) then A and B can be considered equal.
    return (fabs(a - b) < epsilon);
}

//--------------------------------------------------------------------------------------------------
bool AreAlmostEqual(const double & a, const double & b, const double epsilon /*= std::numeric_limits<double>::epsilon()*/)
{
    // If diff is smaller than n% of max(abs(A),abs(B)) then A and B can be considered equal.
    return (fabs(a - b) < epsilon);
}

//--------------------------------------------------------------------------------------------------
} // End namespace