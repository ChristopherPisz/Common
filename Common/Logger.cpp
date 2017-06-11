
// Project Includes
#include "stdafx.h"
#include "FilesAndDirectories.h"
#include "Logger.h"

// Standard Includes
#include <algorithm>
#include <fstream>

//--------------------------------------------------------------------------------------------------
namespace Common
{

//--------------------------------------------------------------------------------------------------
const std::string Logger::SeverityToString(const Logger::Severity severity)
{
    static char * strings[] =
    {
        "TRACE",
        "DEBUG",
        "INFO",
        "WARNING",
        "MINOR",
        "MAJOR",
        "CRITICAL",
        "UNKNOWN"
    };

    return strings[severity];
}

//--------------------------------------------------------------------------------------------------
const Logger::Severity Logger::StringToSeverity(const std::string & severity)
{
    std::string temp;
    std::transform(severity.begin(), severity.end(), std::back_inserter(temp), ::toupper);

    if( temp == "TRACE" )
    {
        return Logger::Severity::TRACE;
    }
    else if( temp == "DEBUG" )
    {
        return Logger::Severity::DEBUG;
    }
    else if( temp == "INFO" )
    {
        return Logger::Severity::INFO;
    }
    else if( temp == "WARNING" )
    {
        return Logger::Severity::WARNING;
    }
    else if( temp == "MINOR" )
    {
        return Logger::Severity::MINOR;
    }
    else if( temp == "MAJOR" )
    {
        return Logger::Severity::MAJOR;
    }
    else if( temp == "CRITICAL" )
    {
        return Logger::Severity::CRITICAL;
    }
    else
    {
        return Logger::Severity::UNKNOWN;
    }
}

//--------------------------------------------------------------------------------------------------
Logger::Logger()
    :
    m_severity            (Logger::Severity::TRACE)
  , m_directoryPath       ("")
  , m_filenamePrefix      ("default")
  , m_filenameExtension   ("log")
  , m_lastRotationTime    ()
  , m_timeBetweenRotations(24, 0, 0)
  , m_maxFileSize         (1024)
  , m_maxFiles            (20)
{
}

//--------------------------------------------------------------------------------------------------
Logger & Logger::GetInstance()
{
    static Logger instance;
    return instance;
}

//--------------------------------------------------------------------------------------------------
Logger::~Logger()
{

}

//--------------------------------------------------------------------------------------------------
const std::string Logger::GetFilePath() const
{
    std::ostringstream filePath;
    filePath << m_directoryPath << '\\' << m_filenamePrefix << '.' << m_filenameExtension;

    return filePath.str();
}

//--------------------------------------------------------------------------------------------------
void Logger::SetFilePath(const std::string & filePath)
{
    m_filenamePrefix = GetFileOrDirectoryNameFromPath(filePath);

    // Strip the extension
    std::wstring::size_type lastDot = m_filenamePrefix.find_last_of('.');

    if( lastDot != std::wstring::npos )
    {
        m_filenamePrefix = m_filenamePrefix.substr(0, lastDot);
    }

    m_directoryPath     = GetParentDirectoryFromPath(filePath);
    m_filenameExtension = GetFileExtensionFromPath(filePath);
}

//--------------------------------------------------------------------------------------------------
Logger::Severity Logger::GetSeverity() const
{
    std::shared_lock<std::shared_mutex> lock(m_mutex);
    return m_severity;
}

//--------------------------------------------------------------------------------------------------
void Logger::SetSeverity(const Logger::Severity severity)
{
    std::lock_guard<std::shared_mutex> lock(m_mutex);
    m_severity = severity;
}

//--------------------------------------------------------------------------------------------------
boost::posix_time::time_duration Logger::GetTimeBetweenRotations() const
{
    std::shared_lock<std::shared_mutex> lock(m_mutex);
    return m_timeBetweenRotations;
}

//--------------------------------------------------------------------------------------------------
void Logger::SetTimeBetweenRotations(const boost::posix_time::time_duration & timeBetweenRotations)
{
    std::lock_guard<std::shared_mutex> lock(m_mutex);
    m_timeBetweenRotations = timeBetweenRotations;
}

//--------------------------------------------------------------------------------------------------
size_t Logger::GetMaxFileSize() const
{
    std::shared_lock<std::shared_mutex> lock(m_mutex);
    return m_maxFileSize;
}

//--------------------------------------------------------------------------------------------------
void Logger::SetMaxFileSize(const size_t maxFileSize)
{
    std::lock_guard<std::shared_mutex> lock(m_mutex);
    m_maxFileSize = maxFileSize;
}

//--------------------------------------------------------------------------------------------------
void Logger::Log(const std::string & message
               , const std::string & fileName /*= std::string()*/
               , const unsigned lineNumber /*= 0*/
               , const boost::posix_time::ptime & time /*= boost::posix_time::microsec_clock::local_time()*/
               , const Logger::Severity severity /*= Logger::Severity::UNKNOWN*/)
{
    std::lock_guard<std::shared_mutex> lock(m_mutex);

    // Check if the log files are due for rotation and rotate them
    RotateLogFiles();

    if( severity < m_severity )
    {
        return;
    }

    // Attempt to open the log file
    std::ostringstream filePath;
    filePath << m_directoryPath << "\\" << m_filenamePrefix << "." << m_filenameExtension;

    std::ofstream file(filePath.str(), std::ios::app);
    if( !file )
    {
        // Error - Could not open log file
        //         Not much can be done here. It's not like we can log it
        //         Try to write to default log.
        std::ofstream defaultLog("default.log", std::ios::app);
        if( !defaultLog )
        {
            // Give up and ignore
            // We'd hate to shut down an important process because some dummy locked the log file up.
            return;
        }

        // We got the default log open, use it instead.
        defaultLog << "Error opening log file" << filePath.str() << ". Could not log: ";

        // std::ofstream has no assignment operator so we have to type all this twice
        defaultLog << std::this_thread::get_id()             << '|'
                   << boost::posix_time::to_iso_string(time) << '|'
                   << SeverityToString(severity)             << '|';

        if( !fileName.empty() )
        {
            defaultLog << fileName << '|';
        }
        else
        {
            defaultLog << "UKNOWN" << '|';
        }

        // Line numbers are indexed from 1 and not 0
        if( lineNumber )
        {
            defaultLog << lineNumber << '|';
        }
        else
        {
            defaultLog << "UKNOWN" << '|';
        }

        defaultLog << message << std::endl;
        defaultLog.close();

        return;
    }

    // We have the log open
    // Log the message
    file << std::this_thread::get_id()             << '|'
         << boost::posix_time::to_iso_string(time) << '|'
         << SeverityToString(severity)             << '|';

    if( !fileName.empty() )
    {
        file << fileName << '|';
    }
    else
    {
        file << "UKNOWN" << '|';
    }

    // Line numbers are indexed from 1 and not 0
    if( lineNumber )
    {
        file << lineNumber << '|';
    }
    else
    {
        file << "UKNOWN" << '|';
    }

    file << message << std::endl;
    file.close();
}

//--------------------------------------------------------------------------------------------------
void Logger::Log(const Common::Exception & exception, const Logger::Severity severity /*= Logger::Severity::UNKNOWN*/)
{
    Log(exception.GetReason()
      , exception.GetFilePath().c_str()
      , exception.GetLine()
      , exception.GetWhen()
      , severity);
}

//--------------------------------------------------------------------------------------------------
void Logger::Log(const std::exception & exception
               , const std::string & fileName /*= std::string()*/
               , const unsigned lineNumber /*= 0*/
               , const boost::posix_time::ptime & time /*= boost::posix_time::microsec_clock::local_time()*/
               , const Logger::Severity severity /*= Logger::Severity::UNKNOWN*/)
{
    Log(exception.what()
      , fileName
      , lineNumber
      , time
      , severity);
}

//--------------------------------------------------------------------------------------------------
void Logger::RotateLogFiles()
{
    // Check if it is time to rotate files
    std::ostringstream logFilePath;
    logFilePath << m_directoryPath << '\\' << m_filenamePrefix << '.' << m_filenameExtension;

    size_t fileSize = GetFileSize(logFilePath.str());

    if( m_lastRotationTime.is_not_a_date_time()                                                     ||
        m_lastRotationTime + m_timeBetweenRotations < boost::posix_time::second_clock::local_time() ||
        m_maxFileSize < fileSize )
    {
        // Delete the oldest log file
        logFilePath.str("");
        logFilePath.clear();
        logFilePath << m_directoryPath << '\\' << m_filenamePrefix << "_" << m_maxFiles << '.' << m_filenameExtension;

        if( IsFile(logFilePath.str()) )
        {
            RemoveFile(logFilePath.str());
        }

        // Rename all other log files
        for(unsigned index = m_maxFiles - 1; index > 0; --index )
        {
            logFilePath.str("");
            logFilePath.clear();
            logFilePath << m_directoryPath << '\\' << m_filenamePrefix << '_' << index << '.' << m_filenameExtension;

            if( IsFile(logFilePath.str()) )
            {
                std::ostringstream newLogFilePath;
                newLogFilePath << m_directoryPath << '\\' << m_filenamePrefix << '_' << index + 1 << '.' << m_filenameExtension;

                MoveFileOrDirectory(logFilePath.str(), newLogFilePath.str());
            }
        }

        // Rename the current log file
        logFilePath.str("");
        logFilePath.clear();
        logFilePath << m_directoryPath << '\\' << m_filenamePrefix << '.' << m_filenameExtension;

        if( IsFile(logFilePath.str()) )
        {
            std::ostringstream newLogFilePath;
            newLogFilePath << m_directoryPath << '\\' << m_filenamePrefix << '_' << 1 << '.' << m_filenameExtension;

            MoveFileOrDirectory(logFilePath.str(), newLogFilePath.str());
        }

        m_lastRotationTime = boost::posix_time::microsec_clock::local_time();
    }
}

//--------------------------------------------------------------------------------------------------
} // End namespace