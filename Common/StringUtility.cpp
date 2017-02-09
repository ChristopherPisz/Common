
// Project Includes
#include "Exception.h"
#include "StringUtility.h"

// Boost Includes
#include <boost/locale.hpp>

//--------------------------------------------------------------------------------------------------
namespace Common
{

//--------------------------------------------------------------------------------------------------
std::wstring MultibyteToWide(const std::string & source)
{
    try
    {
        // Create locale generator
        // "" is the system default locale
        const boost::locale::generator gen;
        const std::locale locale = gen("");

        return boost::locale::conv::to_utf<wchar_t>(source, locale, boost::locale::conv::stop);
    }
    catch (boost::locale::conv::conversion_error &)
    {
        // AFAIK the boost::locale::conv::conversion_error doesn't contain any information at all
        // I assume that the only reason it can be thrown is because
        // Error - The source string contained at least once character that could not be converted using the default locale
        const std::string msg("The source string contained at least once character that could not be converted using the default locale");
        throw Common::Exception(__FILE__, __LINE__, msg);
    }
}

//--------------------------------------------------------------------------------------------------
std::string WideToMultibyte(const std::wstring & source)
{
    try
    {
        // Create locale generator
        // "" is the system default locale
        const boost::locale::generator gen;
        const std::locale locale = gen("");

        return boost::locale::conv::from_utf(source, locale, boost::locale::conv::stop);
    }
    catch (boost::locale::conv::conversion_error &)
    {
        // AFAIK the boost::locale::conv::conversion_error doesn't contain any information at all
        // I assume that the only reason it can be thrown is because
        // Error - The source string contained at least once character that could not be converted using the default locale
        const std::string msg("The source string contained at least once character that could not be converted using the default locale");
        throw Common::Exception(__FILE__, __LINE__, msg);
    }
}

//--------------------------------------------------------------------------------------------------
std::string ReplaceAllOccurances(const std::string & source, const std::string & a, const std::string & b)
{
    std::string result = source;
    size_t index = 0;

    while ( (index = result.find(a, index)) != std::string::npos)
    {
        result.replace(index, a.size(), b);
        index += b.size();
    }

    return result;
}

//--------------------------------------------------------------------------------------------------
std::wstring ReplaceAllOccurances(const std::wstring & source, const std::wstring & a, const std::wstring & b)
{
    std::wstring result = source;
    size_t index = 0;

    while ( (index = result.find(a, index)) != std::wstring::npos)
    {
        result.replace(index, a.size(), b);
        index += b.size();
    }

    return result;
}

//--------------------------------------------------------------------------------------------------
} // End namespace
