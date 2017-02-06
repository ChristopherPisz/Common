
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
bool IsDirectory(const std::string & path)
{
    // Check for empty path
    if (path.empty())
    {
        return false;
    }

    return boost::filesystem::is_directory(path);
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
}

//--------------------------------------------------------------------------------------------------
void RemoveFile(const std::string & path)
{
    if( !Common::IsFile(path) )
    {
        const std::string msg("Path is not a valid file");
        throw Common::Exception(__FILE__, __LINE__, msg);
    }

    try
    {
        // Removes file
        boost::filesystem::remove(path);
    }
    catch( boost::filesystem::filesystem_error & e )
    {
        const boost::system::error_code & errorCode = e.code();

        // TODO - Add switch for meaningful codes, handle, and make manual error messages       
        std::ostringstream msg;
        msg << "boost::filesystem::remove failed with message: '" << (errorCode.message().empty() ? "<empty>" : errorCode.message()) << "'";
        msg << " and error code: '" << errorCode << "'";

        // Use our own exception type
        throw Common::Exception(__FILE__, __LINE__, msg.str());
    }
}

//--------------------------------------------------------------------------------------------------
void RemoveFile(const std::wstring & path)
{
    if( !Common::IsFile(path) )
    {
        const std::string msg("Path is not a valid file");
        throw Common::Exception(__FILE__, __LINE__, msg);
    }

    try
    {
        // Removes file
        boost::filesystem::remove(path);
    }
    catch( boost::filesystem::filesystem_error & e )
    {
        const boost::system::error_code & errorCode = e.code();

        // TODO - Add switch for meaningful codes, handle, and make manual error messages       
        std::ostringstream msg;
        msg << "boost::filesystem::remove failed with message: '" << (errorCode.message().empty() ? "<empty>" : errorCode.message()) << "'";
        msg << " and error code: '" << errorCode << "'";

        // Use our own exception type
        throw Common::Exception(__FILE__, __LINE__, msg.str());
    }
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
}

//--------------------------------------------------------------------------------------------------
void MakeDirectory(const std::wstring & path)
{
    try
    {
        // Creates all directories in the path if they do not exist
        boost::filesystem::create_directories(path);
    }
    catch (boost::filesystem::filesystem_error & e)
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
void DeleteDirectory(const std::wstring & path)
{
    if (!Common::IsDirectory(path))
    {
        const std::string msg("Path is not a valid directory");
        throw Common::Exception(__FILE__, __LINE__, msg);
    }

    try
    {
        // Removes the directory, its subdirectories, and all their contents
        boost::filesystem::remove_all(path);
    }
    catch (boost::filesystem::filesystem_error & e)
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
void MoveFileOrDirectory(const std::string & sourcePath, const std::string destinationPath)
{
    if( IsFile(destinationPath) || IsDirectory(destinationPath) )
    {
        const std::string msg("Destination path already exists");
        throw Common::Exception(__FILE__, __LINE__, msg);
    }

    try
    {
        // Moves/Renames source to destination
        boost::filesystem::rename(sourcePath, destinationPath);
    }
    catch( boost::filesystem::filesystem_error & e )
    {
        const boost::system::error_code & errorCode = e.code();

        // TODO - Add switch for meaningful codes, handle, and make manual error messages       
        std::ostringstream msg;
        msg << "boost::filesystem::rename failed with message: '" << (errorCode.message().empty() ? "<empty>" : errorCode.message()) << "'";
        msg << " and error code: '" << errorCode << "'";

        // Use our own exception type
        throw Common::Exception(__FILE__, __LINE__, msg.str());
    }
}

//--------------------------------------------------------------------------------------------------
void MoveFileOrDirectory(const std::wstring & sourcePath, const std::wstring destinationPath)
{
    if( IsFile(destinationPath) || IsDirectory(destinationPath) )
    {
        const std::string msg("Destination path already exists");
        throw Common::Exception(__FILE__, __LINE__, msg);
    }

    try
    {
        // Moves/Renames source to destination
        boost::filesystem::rename(sourcePath, destinationPath);
    }
    catch( boost::filesystem::filesystem_error & e )
    {
        const boost::system::error_code & errorCode = e.code();

        // TODO - Add switch for meaningful codes, handle, and make manual error messages       
        std::ostringstream msg;
        msg << "boost::filesystem::rename failed with message: '" << (errorCode.message().empty() ? "<empty>" : errorCode.message()) << "'";
        msg << " and error code: '" << errorCode << "'";

        // Use our own exception type
        throw Common::Exception(__FILE__, __LINE__, msg.str());
    }
}

//--------------------------------------------------------------------------------------------------
size_t GetFileSize(const std::string & filePath)
{
    if( !IsFile(filePath) )
    {
        return 0;
    }
    else
    {
        return boost::filesystem::file_size(filePath);
    }
}

//------------------------------------------------------------------------------
const std::string GetFileOrDirectoryNameFromPath(const std::string & path)
{
    std::string fileOrDirectoryName;

    // Check for windows slashes
    std::string::size_type lastSlash = path.find_last_of('\\');

    if( lastSlash != std::wstring::npos )
    {
        fileOrDirectoryName = path.substr(lastSlash + 1);
        return fileOrDirectoryName;
    }

    // Check for other slashes
    lastSlash = path.find_last_of('/');

    if( lastSlash != std::wstring::npos )
    {
        fileOrDirectoryName = path.substr(lastSlash + 1);
        return fileOrDirectoryName;
    }

    // There were no slashes at all
    fileOrDirectoryName = path;
    return fileOrDirectoryName;
}

//------------------------------------------------------------------------------
const std::wstring GetFileOrDirectoryNameFromPath(const std::wstring & path)
{
    std::wstring fileOrDirectoryName;

    // Check for windows slashes
    std::wstring::size_type lastSlash = path.find_last_of('\\');

    if( lastSlash != std::wstring::npos )
    {
        fileOrDirectoryName = path.substr(lastSlash + 1);
        return fileOrDirectoryName;
    }

    // Check for other slashes
    lastSlash = path.find_last_of('/');

    if( lastSlash != std::wstring::npos )
    {
        fileOrDirectoryName = path.substr(lastSlash + 1);
        return fileOrDirectoryName;
    }

    // There were no slashes at all
    fileOrDirectoryName = path;
    return fileOrDirectoryName;
}

//--------------------------------------------------------------------------------------------------
std::string GetParentDirectoryFromPath(const std::string & path)
{
    if( path.empty() )
    {
        return std::string();
    }

    // Remove any trailing slashes
    std::string cleanPath(path);

    if( cleanPath.back() == '\\' ||
        cleanPath.back() == '/' )
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
}

//--------------------------------------------------------------------------------------------------
std::wstring GetParentDirectoryFromPath(const std::wstring & path)
{
    if( path.empty() )
    {
        return std::wstring();
    }

    // Remove any trailing slashes
    std::wstring cleanPath(path);

    if( cleanPath.back() == '\\' ||
        cleanPath.back() == '/' )
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
}

//----------------------------------------------------------------------------
const std::string GetFileExtensionFromPath(const std::string & path)
{
    std::string extension;

    // Check for a dot
    std::string::size_type lastSlash = path.find_last_of('.');

    if( lastSlash != std::string::npos )
    {
        extension = path.substr(lastSlash + 1);
        return extension;
    }

    // There was no dot
    return extension;
}

//----------------------------------------------------------------------------
const std::wstring GetFileExtensionFromPath(const std::wstring & path)
{
    std::wstring extension;

    // Check for a dot
    std::wstring::size_type lastSlash = path.find_last_of('.');

    if( lastSlash != std::wstring::npos )
    {
        extension = path.substr(lastSlash + 1);
        return extension;
    }

    // There was no dot
    return extension;
}

//--------------------------------------------------------------------------------------------------
} // End namespace