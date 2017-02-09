// Project Includes

// Common Library
#include "BoundedBuffer.hxx"
#include "Exception.h"
#include "FilesAndDirectories.h"
#include "Logger.h"

// GTest Includes
#include <gtest/gtest.h>


//--------------------------------------------------------------------------------------------------
class LoggerTests : public ::testing::Test
{

protected:

    //--------------------------------------------------------------------------------------------------
    void SetUp()
    {
    }

    //--------------------------------------------------------------------------------------------------
    static void SetUpTestCase()
    {
    }

    //--------------------------------------------------------------------------------------------------
    void TearDown()
    {
    }

    //--------------------------------------------------------------------------------------------------
    static void TearDownTestCase()
    {
    }

    //--------------------------------------------------------------------------------------------------
    static void ConsumerProc(int id, Common::DataStructures::BoundedBuffer<int> & buffer)
    {
        for( int i = 0; i < 100; ++i )
        {
            int value = buffer.Pop();

            std::ostringstream msg;
            msg << "Consumer " << id << " popped " << value;
            Common::Logger::GetInstance().Log(msg.str(), __FILE__, __LINE__);

            std::this_thread::sleep_for(std::chrono::milliseconds(250));
        }
    }

    //--------------------------------------------------------------------------------------------------
    static void ProducerProc(int id, Common::DataStructures::BoundedBuffer<int> & buffer)
    {
        for( int i = 0; i < 200; ++i )
        {
            buffer.Push(i);
            std::ostringstream msg;
            msg << "Producer " << id << " pushed " << i;
            Common::Logger::GetInstance().Log(msg.str(), __FILE__, __LINE__);

            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }
};

//--------------------------------------------------------------------------------------------------
TEST_F(LoggerTests, LoggerThreadedTest)
{
    std::string directoryPath = Common::GetModuleDirectoryA();

    // Travel up two directories
    // We assume the orginal project settings for output directory and source locations
    directoryPath = Common::GetParentDirectoryFromPath(directoryPath);
    directoryPath = Common::GetParentDirectoryFromPath(directoryPath);

    // Make the directory
    directoryPath = directoryPath + "\\Unit Tests\\Temp";
    Common::MakeDirectory(directoryPath);

    EXPECT_TRUE(Common::IsDirectory(directoryPath));

    // Append the filename
    std::string filePath = directoryPath + "\\LoggerTests.log";

    // Configure the logger
    Common::Logger::GetInstance().SetFilePath(filePath);
    Common::Logger::GetInstance().SetMaxFileSize(1024 * 50); // 50 kilobytes

    // Run a threaded test
    Common::DataStructures::BoundedBuffer<int> buffer(100);

    std::thread consumer1(ConsumerProc, 0, std::ref(buffer));
    std::thread consumer2(ConsumerProc, 1, std::ref(buffer));
    std::thread consumer3(ConsumerProc, 2, std::ref(buffer));
    std::thread producer1(ProducerProc, 0, std::ref(buffer));
    std::thread producer2(ProducerProc, 1, std::ref(buffer));

    consumer1.join();
    consumer2.join();
    consumer3.join();
    producer1.join();
    producer2.join();
}

//--------------------------------------------------------------------------------------------------
