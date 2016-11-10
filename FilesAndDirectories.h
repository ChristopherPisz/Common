#pragma once

// Project Includes
#include "CommonLib.h"

// Standard Includes
#include <string>

/*
* Most of these functions just wrap boost:filesystem
* Previously I was using the Windows API and would prefer the portability of boost if possible.
* 
* The boost documentation is not very clear on how to get meaningful error information.
* Note that all the system error codes boost::filesystem::filesystem_error::code() returns
* can be found in the Windows documentation at
* https://msdn.microsoft.com/en-us/library/windows/desktop/ms681381(v=vs.85).aspx
* Also, boost::filesystem::filesystem_error::message() makes an attempt at human readable
* error messages.
*/

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
COMMON_API std::string GetModuleDirectoryA();
COMMON_API std::wstring GetModuleDirectoryW();

/// <summary>
/// Gets the parent directory of a given path to a file or directory.
/// </summary>
/// <returns>returns the parent directory if one exists. Otherwise, empty string</return>
/// <exception cref="Common::Exception">throws if the path is invalid</exception>
COMMON_API std::string GetParentDirectory(const std::string & path);
COMMON_API std::wstring GetParentDirectory(const std::wstring & path);

/// <summary>
/// Check if a specified path is a directory
/// </summary>
COMMON_API bool IsDirectory(const std::string & path);
COMMON_API bool IsDirectory(const std::wstring & path);

/// <summary>
/// Check if a specified path is a file
/// </summary>
COMMON_API bool IsFile(const std::string & path);
COMMON_API bool IsFile(const std::wstring & path);

/// <summary>
/// Creates a directory at the specified location
/// </summary>
/// <exception cref="Common::Exception">
/// throws if path exceeds MAX_PATH.
/// throws if unable to crate a directory at the specified path.
/// </exception>
COMMON_API void MakeDirectory(const std::string & path);

/// <summary>
/// </summary>
COMMON_API void DeleteDirectory(const std::string & path);

//--------------------------------------------------------------------------------------------------
} // End namespace
