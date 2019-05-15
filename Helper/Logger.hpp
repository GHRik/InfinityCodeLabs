#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "Interface/iLogger.hpp"

namespace helper
{
    class Logger : public iLogger
    {
    public:
        static Logger &getInstance();
        utils::ErrorsCode logError( std::string a_pcErrorMessage );
        utils::ErrorsCode logWarrning( std::string a_pcWarrningMessage );
        utils::ErrorsCode logInfo( std::string a_pcInfoMessage );
    private:
        Logger();
        virtual ~Logger();


    };
}


#endif // LOGGER_HPP
