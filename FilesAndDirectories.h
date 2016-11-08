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
/// Gets the fully qualified path to the current module.
/// Windows specific
/// 
/// This is preferred over getcwd(), because getcwd() can give different results depending where
/// The process was started from.
/// </summary>
/// <exception cref="Common::Exception">throws if path exceeds MAX_PATH</exception>
COMMON_API std::string GetModuleDirectory();

//--------------------------------------------------------------------------------------------------
} // End namespace
