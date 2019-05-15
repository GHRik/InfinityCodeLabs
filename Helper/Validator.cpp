#include "Helper/Validator.hpp"

#include <iostream>

helper::Validator::Validator( const iLogger &a_roLogger ) : m_roLogger( a_roLogger )
{
}

utils::ErrorsCode helper::Validator::validateCommand( const std::string &a_rstrCommand ) const
{
    utils::ErrorsCode oError = utils::ErrorsCode::OK;

    if( "ERROR" == a_rstrCommand ) //missing semicoln
    {
        oError = utils::ErrorsCode::BAD_COMMAND;
        m_roLogger.logError("Missing ;");
    }

    if( utils::ErrorsCode::OK == oError )
    {
        for( uint16_t u16Iter = 0; u16Iter < a_rstrCommand.length(); ++u16Iter)
        {
            bool isDigitNumberSign = !(a_rstrCommand.at(u16Iter) < 32 && a_rstrCommand.at(u16Iter) > 126);
            if( false == isDigitNumberSign )
            {
                oError = utils::ErrorsCode::BAD_COMMAND;
                break;
            }
        }
    }
    if( utils::ErrorsCode::OK == oError )
    {
        uint8_t counterQuotationMarks = 0;
        uint8_t counterLeftParenthesis = 0;
        uint8_t counterRightParenthesis = 0;
        for( uint16_t i = 0; i < a_rstrCommand.length(); ++i )
        {
            if( a_rstrCommand.at(i) == '"')
            {
                ++counterQuotationMarks;
            }
            if( a_rstrCommand.at(i) == '(')
            {
                ++counterLeftParenthesis;
            }
            if( a_rstrCommand.at(i) == ')')
            {
                ++counterRightParenthesis;
            }
        }
        if( ( counterQuotationMarks & 1 ) != 0 ) //is odd
        {
            m_roLogger.logError("Missing \"");
            oError = utils::ErrorsCode::BAD_COMMAND;
        }
        if( oError == utils::ErrorsCode::OK && ( counterLeftParenthesis != counterRightParenthesis ) )
        {
            m_roLogger.logError("Missing ( or ) ");
            oError = utils::ErrorsCode::BAD_COMMAND;
        }
        const char lastSign = *( a_rstrCommand.end() - 1 );
        if( oError == utils::ErrorsCode::OK && lastSign != ';' )
        {
            m_roLogger.logError("Missing ; ");
            oError = utils::ErrorsCode::BAD_COMMAND;
        }
    }

    return oError;
}

void helper::Validator::prepareToValidate( std::string &a_rstrCommand )
{
    deleteRedundantSpace(a_rstrCommand);
}

bool helper::Validator::isWithoutError( const std::vector<std::string> &a_rastrCommands ) const
{
    bool isFreeError = true;
    for( uint16_t u16Iter = 0; u16Iter < a_rastrCommands.size(); ++u16Iter )
    {
        if( "ERROR" == a_rastrCommands.at(u16Iter) )
        {
            isFreeError = false;
            break;
        }
    }
    return isFreeError;
}

void helper::Validator::deleteRedundantSpace( std::string &a_rstrWord )
{
    while( ' ' == *(a_rstrWord.begin()) )
    {
        a_rstrWord = a_rstrWord.substr(1, a_rstrWord.size());
    }

    while( ' ' == *(a_rstrWord.end()-2) )
    {
        a_rstrWord.erase(a_rstrWord.end()-2);
    }

}
