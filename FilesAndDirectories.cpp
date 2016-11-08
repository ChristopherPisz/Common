
// Project Includes
#include "Exception.h"
#include "FilesAndDirectories.h"

// Windows Includes
#include <windows.h>
#include <shellapi.h>

//--------------------------------------------------------------------------------------------------
namespace Common
{

//--------------------------------------------------------------------------------------------------
std::string GetModuleDirectory()
{
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
} // End namespace