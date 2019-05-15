#ifndef ILOGGER_HPP
#define ILOGGER_HPP

#include <string>

class iLogger
{
public:
    virtual ~iLogger();
    virtual void logError( std::string a_strErrorMessage ) const = 0;
    virtual void logWarrning( std::string a_strErrorMessage ) const = 0;
    virtual void logInfo( std::string a_strErrorMessage ) const = 0;
};

#endif // ILOGGER_HPP
