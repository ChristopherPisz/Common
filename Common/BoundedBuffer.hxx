
#pragma once

// Project Includes
#include "CommonLib.h"

// Standard Includes
#include <mutex>
#include <condition_variable>

//-----------------------------------------------------------------------------
namespace Common
{
    namespace DataStructures
    {

//-----------------------------------------------------------------------------
template <class T>
class BoundedBuffer
{
public:

    BoundedBuffer(size_t capacity) 
        :
        m_capacity(capacity)
      , m_front(0)
      , m_rear(0)
      , m_count(0)
    {
        m_buffer = new T[m_capacity];
    }

    ~BoundedBuffer()
    {
        delete[] m_buffer;
    }

    void Push(T data)
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        m_notFull.wait(lock,
            [this]()
            {
                return m_count != m_capacity;
            });

        m_buffer[m_rear] = data;
        m_rear = (m_rear + 1) % m_capacity;
        ++m_count;

        m_notEmpty.notify_one();
    }

    T Pop()
    {
        std::unique_lock<std::mutex> lock(m_mutex);

        m_notEmpty.wait(lock, 
            [this]()
            {
                return m_count != 0;
            });

        T result = m_buffer[m_front];
        m_front = (m_front + 1) % m_capacity;
        --m_count;

        m_notFull.notify_one();

        return result;
    }

protected:

    T *    m_buffer;
    size_t m_capacity;
    size_t m_front;
    size_t m_rear;
    size_t m_count;

private:

    mutable std::mutex              m_mutex;
    mutable std::condition_variable m_notFull;
    mutable std::condition_variable m_notEmpty;
};

//-----------------------------------------------------------------------------
    } // End namespace
} // End namespace

