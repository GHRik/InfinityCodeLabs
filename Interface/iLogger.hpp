#ifndef ILOGGER_HPP
#define ILOGGER_HPP

#include <string>

class iLogger
{
public:
    virtual ~iLogger();
    virtual void logError( const std::string &a_rstrErrorMessage ) const = 0;
    virtual void logWarrning( const std::string &a_rstrErrorMessage ) const = 0;
    virtual void logInfo( const std::string &a_rstrErrorMessage ) const = 0;
};

#endif // ILOGGER_HPP
