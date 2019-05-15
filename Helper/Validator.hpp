#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include "Interface/iLogger.hpp"
#include "Interface/iValidate.hpp"
#include <string>
#include "Utils/ErrorsCode.hpp"
#include <cctype>
#include <algorithm>

namespace helper
{
    class Validator : public iValidate
    {
    public:
        Validator( const iLogger &a_roLogger );
        utils::ErrorsCode validateCommand( const std::string &a_rstrCommand ) const;
        void prepareToValidate(std::string &a_rstrCommand);
        bool isWithoutError( const std::vector<std::string> &a_rastrCommands ) const;
    private:
        const iLogger &m_roLogger;
        void deleteRedundantSpace(std::string &a_rstrWord);
        Validator();
        Validator( const Validator& );
        Validator& operator=( const Validator& a_oValidate );

    };
}


#endif // VALIDATOR_HPP
