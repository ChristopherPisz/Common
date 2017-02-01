
// GTest Includes
#include <gtest/gtest.h>

// Common Library Includes
#include "Threads.h"

//--------------------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
    Common::SetCurrentThreadName("Main");

    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

//--------------------------------------------------------------------------------------------------