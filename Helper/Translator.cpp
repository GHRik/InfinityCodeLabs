#include "Translator.hpp"

#include <iostream>
#include <string>
#include <vector>

Translator::Translator( const iLogger &a_roLogger ) : m_roLogger( a_roLogger )
{

}

std::vector<utils::CommandStandardize> Translator::translateCommand
                                       ( const std::vector<std::vector<std::string>> &a_rastrComandsSplitByWord)
{
    utils::CommandStandardize oCommand = {};
    std::vector<utils::CommandStandardize> aoStandarizeCommand;
    utils::dbCommand oDbCommand = utils::dbCommand::UNDEFINED;
    std::string strTableName = "";
    std::vector<std::string> astrCommandParam = {};

    for( uint16_t u16Iter = 0; u16Iter < a_rastrComandsSplitByWord.size(); ++u16Iter )
    {
        //std::cout << iter;
        astrCommandParam.clear();
        strTableName = "";
        oDbCommand = checkFirstWord(a_rastrComandsSplitByWord.at(u16Iter).at(0));
        std::string strTempWord = "";
        switch( oDbCommand )
        {
            case utils::dbCommand::CREATE:
                if( 2 > (a_rastrComandsSplitByWord.at(u16Iter).size()-1) )
                {
                    astrCommandParam.push_back("ERROR");
                    m_roLogger.logError("Undefined table name");
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
                strTempWord = strTempWord.substr(strTempWord.find_first_of('(')+1,strTempWord.find_last_of(')')-1);
                std::cout << strTempWord << std::endl;
                astrCommandParam = makeParamCreate(strTempWord);
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

                    std::cout << strTempWord << std::endl;
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
                    astrCommandParam.push_back(strTempWord);

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

                               for( size_t i = strTempWord.find("WHERE")+5; i < strTableName.size(); ++i )
                               {
                                   wordWithWhere += strTableName.at(i);
                               }
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

utils::dbCommand Translator::checkFirstWord( const std::string &a_rstrWord ) const
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
    else
    {
        oDbCommand = utils::dbCommand::UNDEFINED;
    }

    return oDbCommand;
}

std::vector<std::string> Translator::makeParamInsert( const std::string &a_rstrWord ) const
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

std::string Translator::makeParamWhere( const std::string &a_rstrWord ) const
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



std::vector<std::string> Translator::makeParamCreate( const std::string &a_rstrWord) const
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
