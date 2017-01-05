#pragma once

//--------------------------------------------------------------------------------------------------
#ifdef COMMON_LIBRARY_EXPORTS
#define COMMON_API __declspec(dllexport)
#else
#define COMMON_API __declspec(dllimport)
// Specify the import library to link in for the DLL.
   #pragma comment(lib, "CommonLib.lib")
#endif

