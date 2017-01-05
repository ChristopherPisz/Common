
// Project Includes
#include "stdafx.h"
#include "PerformanceTimer.h"


//-----------------------------------------------------------------------------
namespace Common
{

//-----------------------------------------------------------------------------
PerformanceTimer::PerformanceTimer()
{
    QueryPerformanceFrequency(&m_frequency);
    Start();
}

//-----------------------------------------------------------------------------
PerformanceTimer::~PerformanceTimer()
{
}

//-----------------------------------------------------------------------------
void PerformanceTimer::Start()
{
    QueryPerformanceCounter(&m_start);
}

//-----------------------------------------------------------------------------
double PerformanceTimer::Stop()
{
    QueryPerformanceCounter(&m_stop);

    LARGE_INTEGER elapsed;
    elapsed.QuadPart = m_stop.QuadPart - m_start.QuadPart;

    return LargeIntToSeconds(elapsed);
}

//-----------------------------------------------------------------------------
double PerformanceTimer::LargeIntToSeconds(const LARGE_INTEGER & value) const
{
    return (static_cast<double>(value.QuadPart) / static_cast<double>(m_frequency.QuadPart));
}

//-----------------------------------------------------------------------------
} // End namespace

