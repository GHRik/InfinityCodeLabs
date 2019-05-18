#ifndef LOGGER_HPP
#define LOGGER_HPP

#include "Interface/iLogger.hpp"

namespace helper
{
///
/// \brief The Logger class is Singletoon. This class is used to log in any casy of error, warrning and info.
///
    class Logger : public iLogger
    {
    public:
        ///
        /// \brief getInstance - used to take Logger object
        /// \return const reference on Logger object
        ///
        static Logger const &getInstance();

        ///
        /// \brief logError - loggin ERROR: + a_rstrErrorMessage
        /// \param a_rstrErrorMessage - messege to log
        ///
        void logError( const std::string &a_rstrErrorMessage ) const;

        ///
        /// \brief logWarrning - loggin WARRNING: + a_strWarrningMessage
        /// \param a_strWarrningMessage - messege to log
        ///
        void logWarrning( const std::string &a_rstrWarrningMessage ) const;

        ///
        /// \brief logInfo - loggin INFO: + a_strInfoMessage
        /// \param a_strInfoMessage - messege to log
        ///
        void logInfo( const std::string &a_rstrInfoMessage ) const;
    private:
        explicit Logger();
        virtual ~Logger();
        explicit Logger( const Logger& );
        Logger& operator=( const Logger& a_oLogger );


    };
}


#endif // LOGGER_HPP
