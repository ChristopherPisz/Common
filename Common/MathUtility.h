#pragma once
/*
* We cannot call this header Math.h, because a math.h (<cmath>) already exists.
*/

// Project Includes
#include "CommonLib.h"

// Standard Includes
#include <limits>

//--------------------------------------------------------------------------------------------------
namespace Common
{

//--------------------------------------------------------------------------------------------------
/// <summary>
/// Compares two floating point values for equality by using an epsilon that is the acceptable distance
/// between the two numbers.
///
/// You never want to compare real numbers directly because of the binary representation being 
/// approximations. Always be aware of the context when comparing.
/// </summary>
COMMON_API bool AreAlmostEqual(const float & a, const float & b, const float epsilon = std::numeric_limits<float>::epsilon());
COMMON_API bool AreAlmostEqual(const double & a, const double & b, const double epsilon = std::numeric_limits<double>::epsilon());

//--------------------------------------------------------------------------------------------------
} // End namespace

