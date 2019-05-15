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
    virtual void prepareToValidate( std::string a_strCommand ) = 0;
    virtual utils::ErrorsCode validateCommand( std::string a_strCommand ) = 0;
    virtual bool isWithoutError( std::vector<std::string> a_astrCommands ) = 0;
};

#endif // IVALIDATE_HPP
