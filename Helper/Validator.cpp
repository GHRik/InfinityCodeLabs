#include "Helper/Validator.hpp"

#include <iostream>

helper::Validator::Validator(const iLogger &a_roLogger )
    : m_roLogger( a_roLogger )
{
}

utils::ErrorsCode helper::Validator::validateCommand( std::string &a_rstrCommand ) const
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
                a_rstrCommand.at(u16Iter) = ' ';
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
            if( 2 <= a_rastrCommands.size() )
            {
                std::string strMessage = "Unexpected expression after "+a_rastrCommands.at(u16Iter-1);
                m_roLogger.logError( strMessage );
            }
            break;
        }
    }
    return isFreeError;
}

utils::ErrorsCode helper::Validator::validateStandarizeCommand( utils::CommandStandardize &a_roCommand ) const
{
    utils::ErrorsCode oError = utils::ErrorsCode::OK;

    if( false == isValidTableName( a_roCommand.tableName ) )
    {
        const std::string strTempMessage = "Table "+a_roCommand.tableName+" is not valid";
        m_roLogger.logError(strTempMessage);
    }
    switch( a_roCommand.command )
    {
    case utils::dbCommand::CREATE:
        if( 0 != a_roCommand.params.size() )
        {
            bool isFieldName = true;
            for( uint16_t u16Iter = 0; u16Iter < a_roCommand.params.size(); ++u16Iter )
            {

                if( true == isFieldName && false == isValidFieldName( a_roCommand.params.at(u16Iter) ) )
                {
                    oError = utils::ErrorsCode::BAD_COMMAND;
                    break;
                }
                else if ( false == isFieldName
                          && utils::DbFieldType::UNKNOWN == isRecognizedType( a_roCommand.params.at(u16Iter) ) )
                {
                    oError = utils::ErrorsCode::BAD_COMMAND;
                    break;
                }
                isFieldName = !isFieldName;
            }
        }
        else
        {
            oError = utils::ErrorsCode::BAD_COMMAND;
            m_roLogger.logError("CREATE call without params or unexpected expression after )");
        }

    break;

    case utils::dbCommand::SELECT:
        if( 0 == a_roCommand.params.size() )
        {
            oError = utils::ErrorsCode::BAD_COMMAND;
        }
        else
        {
            makeVectorUnique( a_roCommand.params );
        }
        break;

    case utils::dbCommand::DELETE_FROM:

        break;

    case utils::dbCommand::INSERT_INTO:
        if( 0 == a_roCommand.params.size() )
        {
            oError = utils::ErrorsCode::BAD_COMMAND;
            m_roLogger.logError("INSER call without param");
        }
        break;

    case utils::dbCommand::DROP:
        if( 0 != a_roCommand.params.size() )
        {
            oError = utils::ErrorsCode::BAD_COMMAND;
            m_roLogger.logError("Unecessary param in DROP");
        }

        break;

    case utils::dbCommand::UNDEFINED:
        oError = utils::ErrorsCode::BAD_COMMAND;
        break;
    }

    return oError;
}

void helper::Validator::deleteRedundantSpace( std::string &a_rstrWord ) const
{
    while( ' ' == *(a_rstrWord.begin()) )
    {
        a_rstrWord = a_rstrWord.substr(1, a_rstrWord.size());
    }

    while( ' ' == *(a_rstrWord.end()-2) )
    {
        a_rstrWord.erase(a_rstrWord.end()-2);
    }
     a_rstrWord.erase(std::remove(a_rstrWord.begin(), a_rstrWord.end(), '\n'), a_rstrWord.end());

}

utils::DbFieldType helper::Validator::isRecognizedType(std::string &a_roType) const
{
    utils::DbFieldType oFieldType = utils::DbFieldType::UNKNOWN;
    std::transform(a_roType.begin(), a_roType.end(), a_roType.begin(), toupper);

    if( "INTEGER" == a_roType )
    {
        oFieldType = utils::DbFieldType::INTEGER;
    }
    else if( "FLOAT" == a_roType )
    {
        oFieldType = utils::DbFieldType::FLOAT;
    }
    else if( "BOOL" == a_roType )
    {
        oFieldType = utils::DbFieldType::BOOL;
    }
    else if( true == isVarcharType( a_roType ) )
    {
        oFieldType = utils::DbFieldType::VARCHAR;
    }
    else
    {
        const std::string strTempMessage = "Type "+a_roType+" is undefined";
        m_roLogger.logError(strTempMessage);
        oFieldType = utils::DbFieldType::UNKNOWN;
    }

    return oFieldType;
}

bool helper::Validator::isVarcharType( const std::string &a_roTypeName ) const
{
    bool isVarchar = true;
    const std::string strVarchar = "VARCHAR";
    for( uint8_t u8Iter = 0; u8Iter < strVarchar.length(); ++u8Iter )
    {
        if( a_roTypeName.at(u8Iter) != strVarchar.at(u8Iter) )
        {
            isVarchar = false;
            break;
        }
    }
    if(  true == isVarchar && a_roTypeName.size() > strVarchar.size() )
    {
        std::string strTemp = "";
        for( size_t sizeIter = strVarchar.size(); sizeIter < a_roTypeName.size(); ++sizeIter )
        {
            strTemp += a_roTypeName.at(sizeIter);
        }
        if( '(' == *strTemp.begin() && ')' == *(strTemp.end()-1) )
        {
            strTemp = strTemp.substr(1,strTemp.length());
            strTemp = strTemp.substr(0,strTemp.length()-1);
            if( true == isNumber(strTemp) )
            {
                int iVarcharSize = stoi(strTemp);
                if( utils::Standarize::MAX_VARCHAR_SIZE >= iVarcharSize
                        && utils::Standarize::MIN_VARCHAR_SIZE <= iVarcharSize  )
                {
                    isVarchar = true;
                }
                else
                {
                    isVarchar = false;
                    m_roLogger.logError("Varchar array must be <1,255>");
                }
            }
            else
            {
                isVarchar = false;
                m_roLogger.logError("Expected number in ( ) after varchar");
            }
        }
        else
        {
            isVarchar = false;
            m_roLogger.logError("Expected (number) after varchar");
        }
    }
    return isVarchar;
}

//Definition From: https://stackoverflow.com/questions/4654636/how-to-determine-if-a-string-is-a-number-with-c
bool helper::Validator::isNumber( const std::string &a_rstrWord ) const
{
    return !a_rstrWord.empty() && std::find_if(a_rstrWord.begin(), a_rstrWord.end(),
                                               [](char c) { return !std::isdigit(c); }) == a_rstrWord.end();
}

bool helper::Validator::isAlNum( const std::string &a_rstrWord ) const
{
    return !a_rstrWord.empty() && std::find_if(a_rstrWord.begin(), a_rstrWord.end(),
                                               [](char c) { return !std::isalnum(c); }) == a_rstrWord.end();
}

bool helper::Validator::isValidTableName( const std::string &a_rstrTableName ) const
{
    bool isValid = true;

    if( 0 < a_rstrTableName.size() )
    {
        if( false == isAlNum( a_rstrTableName ) )
        {
            const std::string strTempMessage = "Table "+a_rstrTableName+" must be alpanumeric";
            m_roLogger.logError(strTempMessage);
            isValid = false;
        }
        if( true == isValid  )
        {
            for( uint8_t u8Iter = 0; u8Iter < utils::astrKeyWord.size(); ++u8Iter )
            {
                if( a_rstrTableName == utils::astrKeyWord.at(u8Iter) )
                {
                    m_roLogger.logError("Table is key word");
                    isValid = false;
                    break;
                }
            }
        }
    }
    else
    {
        isValid = false;
        m_roLogger.logError("Name of the table is empty");
    }

    return isValid;

}
bool helper::Validator::isValidFieldName(const std::string &a_rstrFieldeName) const
{
    bool isValid = true;

    if( 0 < a_rstrFieldeName.size() )
    {
        if( false == isAlNum( a_rstrFieldeName ) )
        {
            const std::string strTempMessage = "Field "+a_rstrFieldeName+" must be alpanumeric";
            m_roLogger.logError(strTempMessage);
            isValid = false;
        }
        if( true == isValid  && true == isFieldNameKeyWord(a_rstrFieldeName) )
        {
            const std::string strTempMessage = "Field "+a_rstrFieldeName+" is key word";
            m_roLogger.logError(strTempMessage);
            isValid = false;
        }
    }
    else
    {
        isValid = false;
        m_roLogger.logError("Name of the field is empty");
    }
    return isValid;
}

bool helper::Validator::isFieldNameKeyWord(const std::string &a_rstrWord ) const
{
    bool isKeyWord = false;
    for( uint8_t u8Iter = 0; u8Iter < utils::astrKeyWord.size(); ++u8Iter )
    {
        if( utils::astrKeyWord.at(u8Iter) == a_rstrWord )
        {
            isKeyWord = true;
            break;
        }
    }
    return isKeyWord;
}



bool helper::Validator::isValidateParam( std::string a_strParamInBase, std::string &a_rstrParamInCommand )
{
    bool isValid = true;
    switch( isRecognizedType(a_strParamInBase)  )
    {
        case utils::DbFieldType::INTEGER:
            if( false == isInt(a_rstrParamInCommand) )
            {
                isValid = false;
            }
        break;

        case utils::DbFieldType::FLOAT:
            if( false == isFloat(a_rstrParamInCommand) )
            {
                isValid = false;
            }
        break;

        case utils::DbFieldType::VARCHAR:
        {
            const std::string strVarchar = "VARCHAR";
            std::string strTemp = "";
            uint16_t u16VarcharSize = 0;
            for( size_t sizeIter = strVarchar.size(); sizeIter < a_strParamInBase.size(); ++sizeIter )
            {
                strTemp += a_strParamInBase.at(sizeIter);
            }
            if( '(' == *strTemp.begin() && ')' == *(strTemp.end()-1) )
            {
                strTemp = strTemp.substr(1,strTemp.length());
                strTemp = strTemp.substr(0,strTemp.length()-1);
                std::istringstream(strTemp) >> u16VarcharSize;
            }

            if( false == isVarcharValid(a_rstrParamInCommand, u16VarcharSize) )
            {
                isValid = false;
            }
        }
        break;

        case utils::DbFieldType::BOOL:
            std::transform(a_rstrParamInCommand.begin(), a_rstrParamInCommand.end(), a_rstrParamInCommand.begin(), toupper);
            bool b;

            if( "TRUE" == a_rstrParamInCommand )
            {
                a_rstrParamInCommand = "1";
            }
            else if ("FALSE" == a_rstrParamInCommand)
            {
                a_rstrParamInCommand = "0";
            }
            else
            {

                if(  !(std::istringstream(a_rstrParamInCommand) >> b) ) //returns false on bad input
                {
                    const std::string strTempMessage = a_rstrParamInCommand+" is not BOOL";
                    m_roLogger.logError(strTempMessage);
                    isValid = false;
                }
            }
        break;

        case utils::DbFieldType::UNKNOWN:
            isValid = false;
        break;


    }
    return isValid;


}

bool helper::Validator::isValidateFieldName(const std::string &a_strFieldNameBase, const std::string &a_strNameInCommand)
{
    bool isValide = false;
    if( a_strFieldNameBase == a_strNameInCommand )
    {
        isValide = true;
    }

    return isValide;
}

bool helper::Validator::isFloat( std::string &a_rstrWord) const
{
    bool isFloat = true;

    bool wasDecimalPoint = false;
    for( uint16_t u16Iter = 0; u16Iter < a_rstrWord.size(); ++u16Iter )
    {
        if( 0 == u16Iter )
        {
            if( '-' == a_rstrWord.at(u16Iter) )
            {
                continue;
            }
        }
        if( '.' == a_rstrWord.at(u16Iter) )
        {
                wasDecimalPoint = true;
                if( u16Iter == a_rstrWord.size()-1)
                {
                    a_rstrWord += "0";
                }
                continue;
        }
        if( false == isdigit(a_rstrWord.at(u16Iter)) )
        {
            isFloat = false;
            break;
        }
    }
    if( true == isFloat && true == wasDecimalPoint )
    {
        float fTemp = 0;
        if(  !(std::istringstream(a_rstrWord) >> fTemp) ) //returns false on bad input
        {
            const std::string strTempMessage = a_rstrWord+" is not FLOAT";
            m_roLogger.logError(strTempMessage);
            isFloat = false;
        }
    }
    else
    {
        const std::string strTempMessage = a_rstrWord+" is not FLOAT";
        m_roLogger.logError(strTempMessage);
        isFloat = false;
    }
    return isFloat;

}

bool helper::Validator::isInt( std::string &a_rstrWord) const
{
    bool isInt = true;
    for( uint16_t u16Iter = 0; u16Iter < a_rstrWord.size(); ++u16Iter )
    {
        if( 0 == u16Iter )
        {
            if( '-' == a_rstrWord.at(u16Iter) )
            {
                continue;
            }
        }
        if( false == isdigit(a_rstrWord.at(u16Iter)) )
        {
            isInt = false;
            break;
        }
    }
    if( true == isInt )
    {
        int iTemp = 0;
        if(  !(std::istringstream(a_rstrWord) >> iTemp) ) //returns false on bad input
        {
            const std::string strTempMessage = a_rstrWord+" is not INTEGER";
            m_roLogger.logError(strTempMessage);
            isInt = false;
        }
    }
    return isInt;

}

bool helper::Validator::isVarcharValid(std::string &a_rstrWord, const uint16_t sizeOfVarchar ) const
{
    bool isValid = true;
    if( '"' != *a_rstrWord.begin() || '"' != *(a_rstrWord.end()-1) )
    {
        m_roLogger.logError("Varchar must be in quote marks");
        isValid = false;
    }
    else
    {
        std::string strTemp = a_rstrWord;
        strTemp = strTemp.substr(1,strTemp.length());
        strTemp = strTemp.substr(0,strTemp.length()-1);

        if( strTemp.length() > sizeOfVarchar )
        {
            const std::string strTempMessage = "Param is too long ";
            m_roLogger.logError(strTempMessage);
            isValid = false;
        }
    }
    return isValid;

}

void helper::Validator::makeVectorUnique(std::vector<std::string> &a_rastrVector) const
{
    std::sort( a_rastrVector.begin(), a_rastrVector.end() );
    a_rastrVector.erase( unique( a_rastrVector.begin(), a_rastrVector.end() ), a_rastrVector.end() );
}
