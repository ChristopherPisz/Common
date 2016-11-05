#pragma once

// Project Includes
#include "CommonLib.h"

// Boost Library Includes
#include <boost/date_time/posix_time/posix_time.hpp>

// Standard Includes
#include <stdexcept>
#include <string>

//-----------------------------------------------------------------------------
// Disable compiler warning about exporting template instantiations from DLL
// See MSDN
// It is OK as long we are only suppressing warnings about template instances that have also been instantiated
// by clients of the DLL.
// For example: As long as the client uses std::vector<int> for example, we can too
// The same goes for the Boost Library
#pragma warning( push )
#pragma warning( disable: 4251 )
#pragma warning( disable: 4275 )

//------------------------------------------------------------------------------
namespace Common
{

//------------------------------------------------------------------------------
class COMMON_API Exception : public std::runtime_error
{
public:
    Exception(const char * filePath, unsigned int line, const std::string & what_arg);
    Exception(const Exception & rhs);
    const Exception & operator = (const Exception & rhs);
    ~Exception();

    const std::string & GetFilePath();
    unsigned int GetLine();
    std::string GetReason();
    const boost::posix_time::ptime & GetWhen();

protected:

    std::string              m_filePath;
    unsigned int             m_line;
    boost::posix_time::ptime m_when;

};

//------------------------------------------------------------------------------
} // End namespace
