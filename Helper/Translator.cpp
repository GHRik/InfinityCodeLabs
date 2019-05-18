#include "Translator.hpp"

#include <iostream>
#include <string>
#include <vector>

helper::Translator::Translator(const iLogger &a_roLogger , iFileManager &a_roFileManager)
    : m_roLogger( a_roLogger ),
      m_roFileManager( a_roFileManager )
{

}

std::vector<utils::CommandStandardize> helper::Translator::translateCommand
                                       ( const std::vector<std::vector<std::string>> &a_rastrComandsSplitByWord)
{
    utils::CommandStandardize oCommand = {};
    std::vector<utils::CommandStandardize> aoStandarizeCommand;
    utils::dbCommand oDbCommand = utils::dbCommand::UNDEFINED;
    std::string strTableName = "" ;
    std::vector<std::string> astrCommandParam = {};

    for( uint16_t u16Iter = 0; u16Iter < a_rastrComandsSplitByWord.size(); ++u16Iter )
    {
        astrCommandParam.clear();
        strTableName = "";
        oDbCommand = checkFirstWord(a_rastrComandsSplitByWord.at(u16Iter).at(0));
        std::string strTempWord = "";
        switch( oDbCommand )
        {
            case utils::dbCommand::CREATE:
            {
                if( 2 > (a_rastrComandsSplitByWord.at(u16Iter).size()-1) )
                {
                    astrCommandParam.push_back("ERROR");
                    m_roLogger.logError("Undefined table name");
                    m_roLogger.logInfo("Maybe you miss space after table name?");
                    continue;
                }
                else
                {
                    strTableName = a_rastrComandsSplitByWord.at(u16Iter).at(1);
                }
                for( size_t i = 2; i < a_rastrComandsSplitByWord.at(u16Iter).size(); ++i )
                {
                    strTempWord += a_rastrComandsSplitByWord.at(u16Iter).at(i);

                }

                if( ';' == strTempWord.back() )
                {
                     strTempWord = strTempWord.substr( 0,strTempWord.length()-1 );
                }
                const std::string strTemp = strTempWord;
                strTempWord = strTempWord.substr(strTempWord.find_first_of('(')+1,strTempWord.find_last_of(')')-1);
                if( strTemp.length()-2 == strTempWord.length() )
                {

                    //std::cout << strTempWord << std::endl;
                    astrCommandParam = makeParamCreate(strTempWord);
                }
                else
                {
                    m_roLogger.logError("Unexpected expression after )");
                }
            }
            break;

            case utils::dbCommand::INSERT_INTO:
                if( 2 > (a_rastrComandsSplitByWord.at(u16Iter).size()-1) )
                {
                    astrCommandParam.push_back("ERROR");
                    m_roLogger.logError("Expected INTO");
                    continue;
                }
                else if( "INTO" == a_rastrComandsSplitByWord.at(u16Iter).at(1) )
                {
                    if( 3 > (a_rastrComandsSplitByWord.at(u16Iter).size()-1) )
                    {
                        astrCommandParam.push_back("ERROR");
                        m_roLogger.logError("Undefined table name");
                        continue;
                    }
                    else
                    {
                        strTableName = a_rastrComandsSplitByWord.at(u16Iter).at(2);
                    }
                    for( size_t i = 2; i < a_rastrComandsSplitByWord.at(u16Iter).size(); ++i )
                    {
                        strTempWord += a_rastrComandsSplitByWord.at(u16Iter).at(i);

                    }
                    strTempWord = strTempWord.substr(strTempWord.find_first_of("(")+1,strTempWord.find_last_of(")")-1);
                    if( strTempWord.back() == ';' )
                    {
                        strTempWord = strTempWord.substr(0,strTempWord.length()-1);
                    }
                    if( strTempWord.back() == ')' )
                    {
                        strTempWord = strTempWord.substr(0,strTempWord.length()-1);
                    }

                    //std::cout << strTempWord << std::endl;
                    astrCommandParam = makeParamInsert(strTempWord);

                }
                else
                {
                    astrCommandParam.push_back("ERROR");
                    m_roLogger.logError("Expected INTO");
                }
            break;

            case utils::dbCommand::DROP:

                if( 1 > (a_rastrComandsSplitByWord.at(u16Iter).size()-1) )
                {
                    astrCommandParam.push_back("ERROR");
                    m_roLogger.logError("Undefined table name");
                    continue;
                }
                else
                {
                    strTableName = a_rastrComandsSplitByWord.at(u16Iter).at(1);
                }
                if( strTableName.back() == ';' )
                {
                    strTableName = strTableName.substr(0,strTableName.length()-1);
                }
                if( strTableName.size() == 0 )
                {
                    astrCommandParam.push_back("ERROR");
                    m_roLogger.logError("Undefined table name");
                }

            break;

            case utils::dbCommand::DELETE_FROM:
                if( 1 > (a_rastrComandsSplitByWord.at(u16Iter).size()-1) )
                {
                    astrCommandParam.push_back("ERROR");
                    m_roLogger.logError("Expected FROM");
                    continue;
                }
                else if( "FROM" == a_rastrComandsSplitByWord.at(u16Iter).at(1) )
                {
                    if( 2 > (a_rastrComandsSplitByWord.at(u16Iter).size()-1) )
                    {
                        astrCommandParam.push_back("ERROR");
                        m_roLogger.logError("Undefined table name");
                        continue;
                    }
                    else
                    {
                        strTableName = a_rastrComandsSplitByWord.at(u16Iter).at(2);
                    }

                    if( strTableName.back() == ';' )
                    {
                        strTableName = strTableName.substr(0,strTableName.length()-1);
                    }
                    if( strTableName.size() == 0 )
                    {
                        astrCommandParam.push_back("ERROR");
                        m_roLogger.logError("Expected table name");
                        continue;
                    }

                    if( 3 < (a_rastrComandsSplitByWord.at(u16Iter).size()-1) )
                    {
                        if( "WHERE" == a_rastrComandsSplitByWord.at(u16Iter).at(3) )
                        {
                            strTempWord = "";
                            for(size_t i = 3; i < a_rastrComandsSplitByWord.at(u16Iter).size(); ++i)
                            {
                                strTempWord += a_rastrComandsSplitByWord.at(u16Iter).at(i);
                            }
                            strTempWord = makeParamWhere(strTempWord);
                            astrCommandParam.push_back(strTempWord);
                        }
                        else
                        {
                            astrCommandParam.push_back("ERROR");
                            m_roLogger.logError("Expection WHERE");
                        }
                    }
                }

            break;

            case utils::dbCommand::SELECT:
                if( 2 > (a_rastrComandsSplitByWord.at(u16Iter).size()-1) )
                {
                    astrCommandParam.push_back("ERROR");
                    m_roLogger.logError("Undefined column name");
                    continue;
                }

                if( a_rastrComandsSplitByWord.at(u16Iter).end() != std::find
                                                                   ( a_rastrComandsSplitByWord.at(u16Iter).begin(),
                                                                     a_rastrComandsSplitByWord.at(u16Iter).end(),
                                                                     "FROM"
                                                                    ))
                {
                    for( uint16_t u16IterByWord = 1;
                                                u16IterByWord < a_rastrComandsSplitByWord.at(u16Iter).size();
                                                ++u16IterByWord
                                                )
                    {
                        if( "FROM" == a_rastrComandsSplitByWord.at(u16Iter).at(u16IterByWord) )
                        {
                            break;
                        }
                        strTempWord += a_rastrComandsSplitByWord.at(u16Iter).at(u16IterByWord);
                    }
                    std::vector<std::string> astrTempBuff;
                    splitByDelimeter(strTempWord, astrTempBuff, ',' );
                    for( uint16_t u16It = 0; u16It < astrTempBuff.size(); ++u16It )
                    {
                        astrCommandParam.push_back(astrTempBuff.at(u16It));
                    }

                    for(size_t i = 0; i < a_rastrComandsSplitByWord.at(u16Iter).size(); ++i)
                    {
                        if( "FROM" != a_rastrComandsSplitByWord.at(u16Iter).at(i) )
                        {
                            continue;

                        }
                        strTableName += a_rastrComandsSplitByWord.at(u16Iter).at(++i);
                        break;

                    }
                    strTableName = strTableName.substr(0,strTableName.size());
                    if( strTableName.back() == ';' )
                    {
                        strTableName = strTableName.substr(0,strTableName.length()-1);
                    }
                    if( strTableName.size() == 0 || strTableName == ";" )
                    {
                        astrCommandParam.push_back("ERROR");
                        m_roLogger.logError("Expection table name");
                        continue;
                    }
                    else
                    {
                        strTempWord = "";
                        bool isWhere = false;
                        for(size_t i = 0; i < a_rastrComandsSplitByWord.at(u16Iter).size(); ++i)
                        {
                            if( true == isWhere  )
                            {
                                strTempWord += a_rastrComandsSplitByWord.at(u16Iter).at(i);
                            }
                            if( strTableName == a_rastrComandsSplitByWord.at(u16Iter).at(i) )
                            {
                                isWhere = true;
                            }

                        }
                        if( strTempWord.size() > 0 && strTempWord != ";" )
                        {
                            if( std::string::npos != strTempWord.find("WHERE") )
                            {
                               std::string wordWithWhere = "";

                               wordWithWhere = makeParamWhere(strTempWord);
                               astrCommandParam.push_back(wordWithWhere);
                            }
                            else
                            {
                                astrCommandParam.push_back("ERROR");
                                m_roLogger.logError("Expected WHERE");
                            }
                        }
                    }

                }
                else
                {
                  astrCommandParam.push_back("ERROR");
                  m_roLogger.logError("Expection FROM");
                }
            break;

            case utils::dbCommand::UNDEFINED:
            break;

        }
        oCommand.command = oDbCommand;
        oCommand.tableName = strTableName;
        oCommand.params = astrCommandParam;

        aoStandarizeCommand.push_back(oCommand);
    }
    return aoStandarizeCommand;

}

utils::dbCommand helper::Translator::checkFirstWord( const std::string &a_rstrWord ) const
{
    utils::dbCommand oDbCommand = utils::dbCommand::UNDEFINED;

    if( "CREATE" == a_rstrWord )
    {
        oDbCommand = utils::dbCommand::CREATE;
    }
    else if( "INSERT" == a_rstrWord )
    {
        oDbCommand = utils::dbCommand::INSERT_INTO;
    }
    else if( "DROP" == a_rstrWord )
    {
        oDbCommand = utils::dbCommand::DROP;
    }
    else if( "SELECT" == a_rstrWord )
    {
        oDbCommand = utils::dbCommand::SELECT;
    }
    else if( "DELETE" == a_rstrWord )
    {
        oDbCommand = utils::dbCommand::DELETE_FROM;
    }

    return oDbCommand;
}

std::vector<std::string> helper::Translator::makeParamInsert( const std::string &a_rstrWord ) const
{
    std::string param = "";
    std::vector<std::string> vectorOfParam;
    bool isQuoted = false;
    for( size_t i = 0; i < a_rstrWord.length(); ++i )
    {
        if( '"' == a_rstrWord.at(i) )
        {
            isQuoted = !isQuoted;
        }
        if( ',' == a_rstrWord.at(i) && false == isQuoted )
        {
            if( param.length() == 0 )
            {
                m_roLogger.logError("Expected field value before , ");
                break;
            }
            else
            {
                vectorOfParam.push_back(param);
            }
            param = "";
        }
        else
        {
            param += a_rstrWord.at(i);
        }
    }
    if( param.length() == 0 )
    {
        m_roLogger.logError("Expected field value after ,");
    }
    else
    {
       vectorOfParam.push_back(param);
    }

    return vectorOfParam;
}

std::string helper::Translator::makeParamWhere( const std::string &a_rstrWord ) const
{
    std::string column = "";
    std::string value = "";
    std::string whereParam = "";

    if( std::string::npos != a_rstrWord.find("=") )
    {
        bool isColumn = true;
        for( size_t iter = 0; iter < a_rstrWord.size(); ++iter )
        {
            if( '=' == a_rstrWord.at(iter) )
            {
                isColumn = false;
                continue;

            }
            if( true == isColumn )
            {
                column += a_rstrWord.at(iter);
            }
            else
            {
                value += a_rstrWord.at(iter);
            }
        }
        if( 0 == column.size() )
        {
            m_roLogger.logError("Expected column name");
        }

        if( 0 == value.size() )
        {
            m_roLogger.logError("Expected value after =");
        }
        if( column.size() > 0 && value.size() > 0 )
        {
            whereParam += column+"="+value;
        }
        if( whereParam.back() == ';' )
        {
            whereParam = whereParam.substr(0,whereParam.length()-1);
        }
    }
    else
    {
        m_roLogger.logError("Expected =");
    }
    return whereParam;

}



std::vector<std::string> helper::Translator::makeParamCreate( const std::string &a_rstrWord) const
{
    std::string param = "";
    std::vector<std::string> vectorOfParam;
    bool isFieldName = true;
    for( size_t i = 0; i < a_rstrWord.length(); ++i )
    {
        if( true == isFieldName )
        {
            if( ':' == a_rstrWord.at(i) )
            {
                if( param.length() == 0 )
                {
                    m_roLogger.logError("Expected field name befor : ");
                    break;
                }
                else
                {
                    vectorOfParam.push_back(param);
                    isFieldName = !isFieldName;
                }
                param = "";
            }
            else
            {
               param += a_rstrWord.at(i);
            }
        }
        else
        {
           if( ',' == a_rstrWord.at(i) )
           {
               if( param.length() == 0 )
               {
                   m_roLogger.logError("Expected type name after , ");
                   break;
               }
               else
               {
                   vectorOfParam.push_back(param);
                   isFieldName = !isFieldName;
               }
               param = "";
           }
           else
           {
               param += a_rstrWord.at(i);
           }
        }
    }
    if( param.length() == 0 )
    {
        if( false == isFieldName )
        {
            m_roLogger.logError("Expected type name ");
        }
        else
        {
            m_roLogger.logError("Expected field name ");
        }
    }
    else
    {
       vectorOfParam.push_back(param);
    }


    return vectorOfParam;
}

std::vector<std::string> helper::Translator::splitCommand( std::string &a_rstrCommand ) const
{
    std::vector<std::string> aResult;
    std::string strSequence = "";
    while( ' ' == *( a_rstrCommand.begin() ) )
    {
        a_rstrCommand = a_rstrCommand.substr( 1, a_rstrCommand.size() );
    }

    while( ' ' == *( a_rstrCommand.rbegin() ) )
    {
        a_rstrCommand = a_rstrCommand.substr( 0, a_rstrCommand.size()-1 );
    }

    for( uint16_t iter = 0; iter < a_rstrCommand.length(); ++iter)
    {

        strSequence += a_rstrCommand.at(iter);
        if( ';' == a_rstrCommand.at(iter) )
        {
            aResult.push_back( strSequence );
            strSequence = "";
        }
    }
    if( strSequence.length() > 0 )
    {
        aResult.push_back("ERROR");
    }

    return aResult;
}

std::vector<std::vector<std::string> > helper::Translator::splitCommandByWord
                                                         ( const std::vector<std::string> &a_rstrCommandSequence ) const
{
    std::vector<std::string> strSeparateWords;
    std::vector<std::vector<std::string>> astrResult;
    std::string strTempWord = "";
    bool isQuoteState = false;
    for( size_t u16IterAllSequence = 0; u16IterAllSequence < a_rstrCommandSequence.size(); ++u16IterAllSequence)
    {
        for( uint16_t u16Iter = 0; u16Iter < a_rstrCommandSequence.at( u16IterAllSequence ).length(); ++u16Iter )
        {

            if( a_rstrCommandSequence.at( u16IterAllSequence ).at( u16Iter ) == '"' )
            {
                isQuoteState = !isQuoteState;
            }
            if( a_rstrCommandSequence.at( u16IterAllSequence ).at( u16Iter ) == ' ' && false == isQuoteState )
            {
                if( 0 < strTempWord.length() )
                {
                    strSeparateWords.push_back( strTempWord );
                }
                strTempWord = "";
            }
            else
            {
                strTempWord += a_rstrCommandSequence.at( u16IterAllSequence ).at( u16Iter );
            }

        }
        if( 0 < strTempWord.length() )
        {
            strSeparateWords.push_back( strTempWord );
            strTempWord = "";
        }

        astrResult.push_back( strSeparateWords );
        strSeparateWords.clear();

    }

    return astrResult;
}

std::vector<std::string> helper::Translator::takeParam()
{
    std::string strMyParams;
    std::vector<std::string> astrMyParams;
    if(utils::ErrorsCode::OK == m_roFileManager.readLine(strMyParams, 0))
    {
        if( 0 != splitByDelimeter( strMyParams ,astrMyParams, ' ' ))
        {
            for( uint16_t u16Iter = 0; u16Iter < astrMyParams.size(); ++u16Iter )
            {
                if( (u16Iter % 2) ==  0 )
                {
                    astrMyParams.at(u16Iter) = "";
                }
            }
            for( uint16_t u16Iter = 0; u16Iter < astrMyParams.size(); ++u16Iter )
            {
                if( "" == astrMyParams.at(u16Iter) )
                {
                    astrMyParams.erase( astrMyParams.begin()+u16Iter );
                }
            }
            if( astrMyParams.back() == "" )
            {
                astrMyParams.pop_back();
            }
        }
    }
    return astrMyParams;

}

std::vector<std::string> helper::Translator::takeField()
{
    std::string strMyParams;
    std::vector<std::string> astrMyParams;
    if(utils::ErrorsCode::OK == m_roFileManager.readLine(strMyParams,0))
    {
        if( 0 != splitByDelimeter( strMyParams ,astrMyParams, ' ' ))
        {
            for( uint16_t u16Iter = 0; u16Iter < astrMyParams.size(); ++u16Iter )
            {
                if( (u16Iter % 2) !=  0 )
                {
                    astrMyParams.at(u16Iter) = "";
                }
            }
            for( uint16_t u16Iter = 0; u16Iter < astrMyParams.size(); ++u16Iter )
            {
                if( "" == astrMyParams.at(u16Iter) )
                {
                    astrMyParams.erase( astrMyParams.begin()+u16Iter );
                }
            }
            if( astrMyParams.back() == "" )
            {
                astrMyParams.pop_back();
            }
        }
    }
    return astrMyParams;
}

std::string helper::Translator::splitByExpectedField(const std::vector<uint16_t> &a_rau16Line, const std::string &a_rstrToSplit)
{
    std::string strTemp = "";
    std::vector<std::string> astrTempVec;
    bool isQuoteState = false;
    for( uint16_t u16Iter = 0; u16Iter < a_rstrToSplit.length(); ++u16Iter )
    {

        if( a_rstrToSplit.at( u16Iter ) == '"' )
        {
            isQuoteState = !isQuoteState;
        }
        if( a_rstrToSplit.at( u16Iter ) == ' ' && false == isQuoteState )
        {
            if( 0 < strTemp.length() )
            {
                astrTempVec.push_back( strTemp );
            }
            strTemp = "";
        }
        else
        {
            strTemp += a_rstrToSplit.at( u16Iter );
        }

    }
    strTemp = "";
    for( uint16_t u16Iter = 0; u16Iter < a_rau16Line.size(); ++u16Iter )
    {
        strTemp += astrTempVec.at(a_rau16Line.at(u16Iter))+ '\t';
    }
    strTemp += '\n';

    return strTemp;
}

//Implementation from https://stackoverflow.com/questions/5888022/split-string-by-single-spaces
size_t helper::Translator::splitByDelimeter(const std::string &a_strTextToSplit, std::vector<std::string> &a_rastrResult, char a_chDelimeter)
{
    size_t pos = a_strTextToSplit.find( a_chDelimeter );
    size_t initialPos = 0;
    a_rastrResult.clear();

    // Decompose statement
    while( pos != std::string::npos ) {
        a_rastrResult.push_back( a_strTextToSplit.substr( initialPos, pos - initialPos ) );
        initialPos = pos + 1;

        pos = a_strTextToSplit.find( a_chDelimeter, initialPos );
    }

    // Add the last one
    a_rastrResult.push_back( a_strTextToSplit.substr( initialPos,
                                                      std::min( pos, a_strTextToSplit.size() ) - initialPos + 1 ) );

    return a_rastrResult.size();
}
