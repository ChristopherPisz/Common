# Common
A common library for utility functions and common things I run across in C++

This library should have _no dependencies_, aside from standard C++ libraries, Boost, and Windows.
If you find yourself needing some dependency other than those three, it belongs somewhere else.


Dependecies:

) C++ runtime
All projects were compiled with the DLL versions of the runtime. That is /MD and MDd

) Boost
The projects are expecting to find the boost 1.62 headers installed at
$(SolutionDir)../../Third Party/boost_1_62_0/boost

The projects are expecting to find the boost 1.62 libraries installed at
$(SolutionDir)../../Third Party/boost_1_62_0/lib32-msvc-14.0
$(SolutionDir)../../Third Party/boost_1_62_0/lib64-msvc-14.0

Feel free to alter the project settings for additional header directories and/or additional library directories to point to your boost installation.
It doesn't necessariy need 1.62, but that's what I developed and tested with.

) GTest
The projects are expecting to find the gtest 1.8.0 headers installed at
$(SolutionDir)../../Third Party/googletest-release-1.8.0/googletest/include

The projects are expecting to find the gtest 1.8.0 libraries installed at
$(SolutionDir)../../Third Party/googletest-release-1.8.0/$(Platform)/$(Configuration)

Feel free to alter the project settings for additional header directories and/or additional library directories to point to your gtest installation.
It doesn't necessariy need 1.8, but that's what I developed and tested with.