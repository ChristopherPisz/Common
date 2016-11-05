
// Project Includes
#include "Exception.h"

//------------------------------------------------------------------------------
namespace Common
{

//------------------------------------------------------------------------------
Exception::Exception(const char * filePath, unsigned int line, const std::string & what_arg)
    :
    std::runtime_error(what_arg),
    m_filePath        (filePath),
    m_line            (line),
    m_when            (boost::posix_time::microsec_clock::local_time())
{
}

//------------------------------------------------------------------------------
Exception::Exception(const Exception & rhs)
    :
    std::runtime_error(rhs),
    m_filePath        (rhs.m_filePath),
    m_line            (rhs.m_line),
    m_when            (rhs.m_when)
{
}

//------------------------------------------------------------------------------
const Exception & Exception::operator = (const Exception & rhs)
{
    if (this == &rhs)
    {
        return *this;
    }

    std::runtime_error::operator=(rhs);
    m_filePath = rhs.m_filePath;
    m_line     = rhs.m_line;
    m_when     = rhs.m_when;

    return *this;
}

//------------------------------------------------------------------------------
Exception::~Exception()
{

}

//------------------------------------------------------------------------------
const std::string & Exception::GetFilePath()
{
    return m_filePath;
}

//------------------------------------------------------------------------------
unsigned int Exception::GetLine()
{
    return m_line;
}

//------------------------------------------------------------------------------
std::string Exception::GetReason()
{
    return std::string(what());
}

//------------------------------------------------------------------------------
const boost::posix_time::ptime & Exception::GetWhen()
{
    return m_when;
}

//------------------------------------------------------------------------------
} // End namespace
