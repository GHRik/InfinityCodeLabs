#ifndef ILOGGER_HPP
#define ILOGGER_HPP

#include "utils/ErrorsCode.hpp"
#include <string>

class iLogger
{
public:
    virtual ~iLogger();
    virtual utils::ErrorsCode logError( std::string a_pcErrorMessage ) = 0;
    virtual utils::ErrorsCode logWarrning( std::string a_pcErrorMessage ) = 0;
    virtual utils::ErrorsCode logInfo( std::string a_pcErrorMessage ) = 0;
};

#endif // ILOGGER_HPP
