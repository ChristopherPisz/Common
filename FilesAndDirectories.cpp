
// Project Includes
#include "Exception.h"
#include "FilesAndDirectories.h"
#include "StringUtility.h"

// Boost Includes
#include <boost/filesystem.hpp>

// Windows Includes
#include <windows.h>
#include <shellapi.h>

//--------------------------------------------------------------------------------------------------
namespace Common
{

//--------------------------------------------------------------------------------------------------
std::string GetModuleDirectoryA()
{
    // Boost::filesystem::current_path returns as if getcwd()
    // Therefore it is not reliable. 
    // An executable can be started from another or the command line, cwd can change in a thread, etc.
    // Better to use the Windows API for this.

    HMODULE module = GetModuleHandleA(NULL);

    char buffer[MAX_PATH];
    DWORD size = GetModuleFileNameA(module, buffer, MAX_PATH);

    if( !size || size == MAX_PATH )
    {
        DWORD errorCode = GetLastError();
        std::ostringstream msg("GetModuleFileName failed with error code ");
        msg << errorCode;

        throw Common::Exception(__FILE__, __LINE__, msg.str());
    }

    // Remove the last slash from the returned string
    std::string path = buffer;
    std::string::size_type lastSlash = path.find_last_of('\\');

    if( lastSlash != std::string::npos )
    {
        path = path.substr(0, lastSlash);
    }

    return path;
}

//--------------------------------------------------------------------------------------------------
std::wstring GetModuleDirectoryW()
{
    // Boost::filesystem::current_path returns as if getcwd()
    // Therefore it is not reliable. 
    // An executable can be started from another or the command line, cwd can change in a thread, etc.
    // Better to use the Windows API for this.

    HMODULE module = GetModuleHandleW(NULL);

    wchar_t buffer[MAX_PATH];
    DWORD size = GetModuleFileNameW(module, buffer, MAX_PATH);

    if( !size || size == MAX_PATH )
    {
        DWORD errorCode = GetLastError();
        std::ostringstream msg("GetModuleFileName failed with error code ");
        msg << errorCode;

        throw Common::Exception(__FILE__, __LINE__, msg.str());
    }

    // Remove the last slash from the returned string
    std::wstring path = buffer;
    std::wstring::size_type lastSlash = path.find_last_of(L'\\');

    if( lastSlash != std::wstring::npos )
    {
        path = path.substr(0, lastSlash);
    }

    return path;
}

//--------------------------------------------------------------------------------------------------
std::string GetParentDirectory(const std::string & path)
{
    if( path.empty() )
    {
        return std::string();
    }

    // Remove any trailing slashes
    std::string cleanPath(path);

    if (cleanPath.back() == '\\' ||
        cleanPath.back() == '/')
    {
        cleanPath.pop_back();
    }

    // Get the parent directory using boost
    boost::filesystem::path boostPath(cleanPath);

    if( !boostPath.has_parent_path() )
    {
        return std::string();
    }

    return boostPath.parent_path().string();

    /*
    // Return the substring up to the last slash, if it exists

    // Windows style path
    size_t index = path.find_last_of("\\");

    if( index != std::string::npos )
    {
        return path.substr(0, index);
    }

    // Unix style path
    index = path.find_last_of("/");
    if( index != std::string::npos )
    {
        return path.substr(0, index);
    }

    // There was no directory in the given path
    return std::string();
    */
}

//--------------------------------------------------------------------------------------------------
std::wstring GetParentDirectory(const std::wstring & path)
{
    if( path.empty() )
    {
        return std::wstring();
    }

    // Remove any trailing slashes
    std::wstring cleanPath(path);

    if (cleanPath.back() == '\\' ||
        cleanPath.back() == '/')
    {
        cleanPath.pop_back();
    }

    // Get the parent directory using boost
    boost::filesystem::path boostPath(cleanPath);

    if( !boostPath.has_parent_path() )
    {
        return std::wstring();
    }

    return boostPath.parent_path().wstring();

    /*
    // Return the substring up to the last slash, if it exists

    // Windows style path
    size_t index = path.find_last_of(L"\\");

    if( index != std::wstring::npos )
    {
        return path.substr(0, index);
    }

    // Unix style path
    index = path.find_last_of(L"/");
    if( index != std::wstring::npos )
    {
        return path.substr(0, index);
    }

    // There was no directory in the given path
    return path;
    */
}

//--------------------------------------------------------------------------------------------------
bool IsDirectory(const std::string & path)
{
    // Check for empty path
    if (path.empty())
    {
        return false;
    }

    return boost::filesystem::is_directory(path);

    /*
    // Get the attibutes from Windows
    DWORD attributes = GetFileAttributesA(path.c_str());

    if (attributes == INVALID_FILE_ATTRIBUTES )
    {
        return false;
    }

    return (attributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY;
    */
}

//--------------------------------------------------------------------------------------------------
bool IsDirectory(const std::wstring & path)
{
    // Check for empty path
    if (path.empty())
    {
        return false;
    }

    return boost::filesystem::is_directory(path);

    /*
    // Get the attibutes from Windows
    DWORD attributes = GetFileAttributesW(path.c_str());

    if (attributes == INVALID_FILE_ATTRIBUTES )
    {
        return false;
    }

    return (attributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY;
    */
}

//--------------------------------------------------------------------------------------------------
bool IsFile(const std::string & path)
{
    // Check for an empty path
    if (path.empty())
    {
        return false;
    }

    return boost::filesystem::is_regular_file(path);

    /*
    // Get the attibutes from Windows
    DWORD attributes = GetFileAttributesA(path.c_str());

    if (attributes == INVALID_FILE_ATTRIBUTES )
    {
        return false;
    }

    // If we did not get INVALID_FILE_ATTRIBUTES, then it is either a directory or a file
    // If it isn't a directory, then it's a file
    return (attributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
    */
}

//--------------------------------------------------------------------------------------------------
bool IsFile(const std::wstring & path)
{
    // Check for empty path
    if (path.empty())
    {
        return false;
    }

    return boost::filesystem::is_regular_file(path);

    /*
    // Get the attibutes from Windows
    DWORD attributes = GetFileAttributesW(path.c_str());

    if (attributes == INVALID_FILE_ATTRIBUTES )
    {
        return false;
    }

    // If we did not get INVALID_FILE_ATTRIBUTES, then it is either a directory or a file
    // If it isn't a directory, then it's a file
    return (attributes & FILE_ATTRIBUTE_DIRECTORY) == 0;
    */
}

//--------------------------------------------------------------------------------------------------
void MakeDirectory(const std::string & path)
{
    try
    {
       // Creates all directories in the path if they do not exist
       boost::filesystem::create_directories(path);
    }
    catch(boost::filesystem::filesystem_error & e)
    {
        // Maybe I am missing something, but getting error information out of boost::filesystem seems to be a bitch
        //
        // The codes are found in boost::system::errc::<your code here>
        // Try and get the value and then find the Windows codes mapped to the boost codes.
        // The actual numeric value can be found in the header with the Windows codes - errno.h under _CRT_NO_POSIX_ERROR_CODES.
        //
        // You'll have to compare against specific ones and make your own meaningful error message.
        const boost::system::error_code & errorCode = e.code();

        // TODO - Add switch for meaningful codes, handle, and make manual error messages       
        std::ostringstream msg;
        msg << "boost::filesystem::create_directories failed with message: '" << (errorCode.message().empty() ? "<empty>" : errorCode.message()) << "'";
        msg << " and error code: '" << errorCode << "'";

        // Use our own exception type
        throw Common::Exception(__FILE__, __LINE__, msg.str());
    }

    /*
    if( path.empty() )
    {
        const std::string msg("Path is empty");
        throw Common::Exception(__FILE__, __LINE__, msg);
    }

    if( path.size() > MAX_PATH )
    {
        const std::string msg("Path size is greater than MAX_PATH");
        throw Common::Exception(__FILE__, __LINE__, msg);
    }

    // Simplify by only dealing with one type of slash
    std::string cleanPath = Common::ReplaceAllOccurances(path, "/", "\\");

    // If the path does not end with a slash, append one
    if (cleanPath.back() != '\\')
    {
        cleanPath += "\\";
    }

    // Iterate through the directories in the path
    size_t index = 0;
    while( index != std::string::npos && index < cleanPath.size() )
    {
        index = cleanPath.find_first_of("\\", index);

        // Check if we found a directory seperator
        if( index == std::string::npos )
        {
            continue;
        }

        // Check if the ancestor directory already exists
        const std::string currentDirectory = cleanPath.substr(0, index);

        if( !IsDirectory(currentDirectory) )
        {
            if (!CreateDirectoryA(currentDirectory.c_str(), NULL))
            {
                DWORD errorCode = GetLastError();
                std::ostringstream msg("CreateDirectory failed with error code ");
                msg << errorCode << " when called with argument: " << currentDirectory;

                throw Common::Exception(__FILE__, __LINE__, msg.str());
            }
        }

        // Next search
        ++index;
    }
    */
}

//--------------------------------------------------------------------------------------------------
void DeleteDirectory(const std::string & path)
{
    if( !Common::IsDirectory(path) )
    {
        const std::string msg("Path is not a valid directory");
        throw Common::Exception(__FILE__, __LINE__, msg);
    }

    try
    {
       // Removes the directory, its subdirectories, and all their contents
       boost::filesystem::remove_all(path);
    }
    catch(boost::filesystem::filesystem_error & e)
    {
        const boost::system::error_code & errorCode = e.code();

        // TODO - Add switch for meaningful codes, handle, and make manual error messages       
        std::ostringstream msg;
        msg << "boost::filesystem::remove_all failed with message: '" << (errorCode.message().empty() ? "<empty>" : errorCode.message()) << "'";
        msg << " and error code: '" << errorCode << "'";

        // Use our own exception type
        throw Common::Exception(__FILE__, __LINE__, msg.str());
    }
}

//--------------------------------------------------------------------------------------------------
} // End namespace