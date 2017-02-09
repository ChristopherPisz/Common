#pragma once

// Project Includes
#include "CommonLib.h"
#include "Exception.h"

// Standard Includes
#include <string>
#include <shared_mutex>

//--------------------------------------------------------------------------------------------------
namespace Common
{

//--------------------------------------------------------------------------------------------------
/// <summary>
/// A simple filestream based logger
///
/// This class is a singleton.
/// Be aware of the Static Initialization Fiasco when using this class in another's constructor 
/// or deconstructor.
/// </summary>
class COMMON_API Logger
{
public:

    /// <summary>
    /// Severity of a log message
    /// The logger can be configured to ignore all messages below a specified severity level
    /// Each log message can be set with a specified severity level
    /// </summary>
    enum Severity : unsigned
    {
        TRACE = 0,
        DEBUG,
        INFO,
        WARNING,
        MINOR,
        MAJOR,
        CRITICAL,
        UNKNOWN
    };

    /// <summary>
    /// Converts a Logger::Severity enumeration to a string
    /// </summary>
    static const std::string SeverityToString(const Logger::Severity severity);

    /// <summary>
    /// Converts a string to a LoggingLevel enumeration
    /// </summary>
    static const Logger::Severity StringToSeverity(const std::string & severity);


    /// <summary>
    /// Gets the one and only instance of this class
    /// </summary>
    static Logger & GetInstance();

    /// <summary>
    /// Deconstructor
    /// </summary>
    ~Logger();

    /// <summary>
    /// Gets the current file path of the log file this class is using.
    /// The log will rotate log files based on a time interval adding a _# suffix to each file.
    /// </summary>
    const std::string GetFilePath() const;

    /// <summary>
    /// Sets the file path of the log file this class will use.
    /// The log will rotate log files based on a time interval adding a _# suffix to each file.
    /// </summary>
    void SetFilePath(const std::string & filePath);

    /// <summary>
    /// Gets minimum severity required for a message to be logged
    /// </summary>
    Logger::Severity GetSeverity() const;

    /// <summary>
    /// Sets the minimum severity required for a message to be logged
    /// </summary>
    void SetSeverity(const Logger::Severity severity);

    boost::posix_time::time_duration GetTimeBetweenRotations() const;
    void SetTimeBetweenRotations(const boost::posix_time::time_duration & timeBetweenRotations);

    size_t GetMaxFileSize() const;
    void SetMaxFileSize(const size_t maxFileSize);

    /// <summary>
    /// Logs a message to the current log file
    /// </summary>
    void Log(const std::string & message
           , const std::string & fileName = std::string()
           , const unsigned lineNumber = 0
           , const boost::posix_time::ptime & time = boost::posix_time::microsec_clock::local_time()
           , const Logger::Severity severity = Logger::Severity::UNKNOWN);

    /// <summary>
    /// Logs a Common::Exception to the current log file
    /// </summary>
    void Log(const Common::Exception & exception, const Logger::Severity severity = Logger::Severity::UNKNOWN);

    /// <summary>
    /// Logs a std::exception to the current log file
    /// </summary>
    void Log(const std::exception & exception
           , const std::string & fileName = std::string()
           , const unsigned lineNumber = 0
           , const boost::posix_time::ptime & time = boost::posix_time::microsec_clock::local_time()
           , const Logger::Severity severity = Logger::Severity::UNKNOWN);

private:

    mutable std::shared_mutex m_mutex;
    Logger::Severity          m_severity;
    std::string               m_directoryPath;
    std::string               m_filenamePrefix;
    std::string               m_filenameExtension;

    boost::posix_time::ptime         m_lastRotationTime;
    boost::posix_time::time_duration m_timeBetweenRotations;
    size_t                           m_maxFileSize;
    unsigned                         m_maxFiles;


    /// <summary>
    /// Private constructor to enforce singleton pattern
    /// </summary>
    Logger();

    /// <summary>
    /// Rotates log files
    ///
    /// If the number of log files has reached m_maxFiles, then the oldest log file is deleted,
    /// and all log files are renamed with a _# suffix that is incremented by 1.
    /// The current log filename will contain no _# suffix.
    /// </summary>
    void RotateLogFiles();
};

//--------------------------------------------------------------------------------------------------

} // End namespace
