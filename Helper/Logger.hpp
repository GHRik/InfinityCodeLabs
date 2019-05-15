#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "Interface/iLogger.hpp"

namespace helper
{
    class Logger : public iLogger
    {
    public:
        static Logger const &getInstance();
        void logError( const std::string a_rstrErrorMessage ) const;
        void logWarrning( const std::string a_strWarrningMessage ) const;
        void logInfo( const std::string a_strInfoMessage ) const;
    private:
        Logger();
        virtual ~Logger();
        Logger( const Logger& );
        Logger& operator=( const Logger& a_oLogger );


    };
}


#endif // LOGGER_HPP
