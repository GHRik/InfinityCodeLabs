#ifndef IVALIDATE_HPP
#define IVALIDATE_HPP


#include "Utils/ErrorsCode.hpp"
#include "Utils/DataBaseCommand.hpp"
#include <string>
#include <vector>

class iValidate
{
public:
    virtual ~iValidate();
    virtual void prepareToValidate( std::string &a_rstrCommand ) = 0;
    virtual utils::ErrorsCode validateCommand( std::string &a_rstrCommand ) const = 0;
    virtual bool isWithoutError( const std::vector<std::string> &a_arstrCommands ) const = 0;
    virtual utils::ErrorsCode validateStandarizeCommand( utils::CommandStandardize &a_roCommand ) const = 0;
    virtual bool isValidateParam( std::string a_strParamInBase, std::string &a_rstrParamInCommand ) = 0;
};

#endif // IVALIDATE_HPP
