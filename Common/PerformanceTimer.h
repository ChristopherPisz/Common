#pragma once

// Project Includes
#include "CommonLib.h"

// Windows Includes
#include <windows.h>

//-----------------------------------------------------------------------------
namespace Common
{

//-----------------------------------------------------------------------------
/// This class is capable of high resolution performance timing
/// Intended for usage such as timing how long a method call takes to return
class COMMON_API PerformanceTimer
{
public:

    /// <summary>
    /// Constructor
    /// </summary>
    PerformanceTimer();

    /// <summary>
    /// Deconstructor
    /// </summary>
    ~PerformanceTimer();

    /// <summary>
    /// Starts Timing
    /// </summary>
    void Start();

    /// <summary>
    /// Ends Timing
    /// </summary>
    /// <returns>
    /// Time since <c>PerformanceTimer::Start</c> was called, in seconds.
    /// If PerformanceTimer::Start was never called, then time since construction
    /// </returns>
    double Stop();

private:

    /// <summary>
    /// Convert large int representing a performance timer value to a double representing seconds
    /// </summary>
    double LargeIntToSeconds(const LARGE_INTEGER & value) const;

    LARGE_INTEGER m_start;
    LARGE_INTEGER m_stop;
    LARGE_INTEGER m_frequency;

};

//-----------------------------------------------------------------------------
} // end namespace

