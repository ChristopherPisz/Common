#pragma once

// Project Includes
#include "CommonLib.h"

// Standard Includes
#include <string>

//--------------------------------------------------------------------------------------------------
namespace Common
{

//--------------------------------------------------------------------------------------------------
/// <summary>
/// Converts a narrow string to wide string
/// </summary>
/// <exception cref="Common::Exception">
/// throws a character in the source string cannot be converted using the system default locale
/// IMPORTANT! If you use this function in your logging of thrown exceptions, don't get yourself
///            stuck in a loop of exceptions. Catch!
/// </exception>
COMMON_API std::wstring MultibyteToWide(const std::string & source);

/// <summary>
/// Converts a wide string to narrow string
/// IMPORTANT! If you use this function in your logging of thrown exceptions, don't get yourself
///            stuck in a loop of exceptions. Catch!
/// </summary>
/// <exception cref="Common::Exception">throws a character in the source string cannot be converted using the system default locale</exception>
COMMON_API std::string WideToMultibyte(const std::wstring & source);

/// <summary>
/// Replaces all occurances of a search string, within a string, with a replacement string
/// </summary>
COMMON_API std::string ReplaceAllOccurances(const std::string & source, const std::string & a, const std::string & b);

//--------------------------------------------------------------------------------------------------
} // End namespace
