#include "Helper/Validator.hpp"

#include <iostream>

helper::Validator::Validator( iLogger *a_poLogger ) : m_poLogger( a_poLogger )
{
}

utils::ErrorsCode helper::Validator::validateCommand(std::string a_strCommand)
{

    utils::ErrorsCode oError = utils::ErrorsCode::OK;

    //Asci from <0,32> & (126,255>

    if( a_strCommand == "ERROR" ) //missing semicoln
    {
        oError = utils::ErrorsCode::BAD_COMMAND;
        m_poLogger->logError("Missing ;");
    }

    if( utils::ErrorsCode::OK == oError )
    {
        for(size_t i = 0; i < a_strCommand.length(); ++i)
        {
            if( a_strCommand.at(i) < 32 && a_strCommand.at(i) > 126 )
            {
                oError = utils::ErrorsCode::BAD_COMMAND;
                break;
            }
        }
    }
    if( utils::ErrorsCode::OK == oError )
    {
        int counterCudzyslow = 0;
        int counterNawiasOpen = 0;
        int counterNawiasClose = 0;
        for(uint16_t i = 0; i < a_strCommand.length(); ++i)
        {

            if( a_strCommand.at(i) == '"')
            {
                ++counterCudzyslow;
            }
            if( a_strCommand.at(i) == '(')
            {
                ++counterNawiasOpen;
            }
            if( a_strCommand.at(i) == ')')
            {
                ++counterNawiasClose;
            }
        }
        if( ( counterCudzyslow & 1 ) != 0 ) //is odd
        {
            oError = utils::ErrorsCode::BAD_COMMAND;
        }
        if( oError == utils::ErrorsCode::OK && (counterNawiasClose != counterNawiasOpen) )
        {
            oError = utils::ErrorsCode::BAD_COMMAND;
        }
        const char lastSign = *(a_strCommand.end() - 1);
        if( oError == utils::ErrorsCode::OK && lastSign != ';' )
        {
            oError = utils::ErrorsCode::BAD_COMMAND;
        }
    }

    return oError;
}

void helper::Validator::prepareToValidate(std::string a_strCommand)
{
    deleteRedundantSpace(a_strCommand);
}

void helper::Validator::deleteRedundantSpace(std::string &str)
{
    while( ' ' == *(str.begin()) )
    {
        str = str.substr(1, str.size());
    }

//    while( ';' != *(str.end()-1) )
//    {
//        str = str.substr(0, str.size()-1);
//    }

    while( ' ' == *(str.end()-2) )
    {
        str.erase(str.end()-2);
    }

    //std::cout << str << std::endl;

}
