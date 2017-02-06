
// Project Includes
#include "Exception.h"

//------------------------------------------------------------------------------
namespace Common
{

//------------------------------------------------------------------------------
Exception::Exception(const char * filePath
                   , unsigned int line
                   , const std::string & what_arg
                   , boost::posix_time::ptime when /*= boost::posix_time::microsec_clock::local_time()*/)
    :
    std::runtime_error(what_arg)
  , m_filePath        (filePath)
  , m_line            (line)
  , m_when            (when)
{
}

//------------------------------------------------------------------------------
Exception::Exception(const Exception & rhs)
    :
    std::runtime_error(rhs)
  , m_filePath        (rhs.m_filePath)
  , m_line            (rhs.m_line)
  , m_when            (rhs.m_when)
{
}

//------------------------------------------------------------------------------
Exception::~Exception()
{
}

//------------------------------------------------------------------------------
const std::string & Exception::GetFilePath() const
{
    return m_filePath;
}

//------------------------------------------------------------------------------
unsigned int Exception::GetLine() const
{
    return m_line;
}

//------------------------------------------------------------------------------
std::string Exception::GetReason() const
{
    return std::string(what());
}

//------------------------------------------------------------------------------
const boost::posix_time::ptime & Exception::GetWhen() const
{
    return m_when;
}

//------------------------------------------------------------------------------
} // End namespace
