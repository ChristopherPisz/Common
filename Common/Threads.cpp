
// Project Includes
#include "stdafx.h"
#include "Threads.h"

// Windows Includes
#include <windows.h>

//--------------------------------------------------------------------------------------------------
namespace Common
{

    //--------------------------------------------------------------------------------------------------
void SetCurrentThreadName(const std::string & name)
{
    // See https://msdn.microsoft.com/en-us/library/xcb2z8hs.aspx?f=255&MSPPError=-2147217396
    // The Win32-specific way of setting the name on a thread for debugging.

    const DWORD MS_VC_EXCEPTION = 0x406D1388;

#pragma pack(push,8)
    typedef struct tagTHREADNAME_INFO
    {
        DWORD  dwType;     // Must be 0x1000
        LPCSTR szName;     // Pointer to name (in user addr space)
        DWORD  dwThreadID; // Thread ID (-1 = caller thread)
        DWORD  dwFlags;    // Reserved for future use, must be zero
    } THREADNAME_INFO;
#pragma pack(pop)

    THREADNAME_INFO info;
    info.dwType     = 0x1000;
    info.szName     = name.c_str();
    info.dwThreadID = -1;
    info.dwFlags    = 0;

#pragma warning(push)  
#pragma warning(disable: 6320 6322)
    __try
    {
        RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR *)&info);
    }
    __except( EXCEPTION_EXECUTE_HANDLER )
    {
    }
#pragma warning(pop)
}

//--------------------------------------------------------------------------------------------------
} // End namespace

