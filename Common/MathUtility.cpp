

// Project Includes
#include "stdafx.h"
#include "MathUtility.h"

// Standard Includes
#include <cmath>

//--------------------------------------------------------------------------------------------------
namespace Common
{

//--------------------------------------------------------------------------------------------------
bool AreAlmostEqual(const float & a, const float & b, const float epsilon /*= std::numeric_limits<float>::epsilon()*/)
{
    return (std::abs(a - b) < epsilon);
}

//--------------------------------------------------------------------------------------------------
bool AreAlmostEqual(const double & a, const double & b, const double epsilon /*= std::numeric_limits<double>::epsilon()*/)
{
    return (std::abs(a - b) < epsilon);
}

//--------------------------------------------------------------------------------------------------
} // End namespace