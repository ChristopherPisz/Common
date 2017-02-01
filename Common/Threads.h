#pragma once

// Project Includes
#include "CommonLib.h"

// Standard Library Includes
#include <string>

//--------------------------------------------------------------------------------------------------
namespace Common
{

//--------------------------------------------------------------------------------------------------
/// <summary>
/// Sets the name of the current thread, as it will appear in the threads window in Visual Studio
/// For Debugging purposes
/// </summary>
COMMON_API void SetCurrentThreadName(const std::string & name);

//--------------------------------------------------------------------------------------------------
} // End namespace

