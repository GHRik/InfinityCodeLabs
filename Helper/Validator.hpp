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
        Validator( iLogger *a_poLogger );
        utils::ErrorsCode validateCommand( std::string a_strCommand );
        void prepareToValidate(std::string a_strCommand);
        bool isWithoutError( std::vector<std::string> a_astrCommands );
    private:
        iLogger *m_poLogger;
        void deleteRedundantSpace(std::string &str);

    };
}


#endif // VALIDATOR_HPP
