#include "Translator.hpp"

#include <iostream>
#include <string>
#include <vector>

Translator::Translator(iLogger &a_roLogger ) : m_roLogger( a_roLogger )
{

}

std::vector<utils::CommandStandardize> Translator::translateCommand(std::vector<std::vector<std::string>> comandsSplitByWord)
{
    utils::CommandStandardize oCommand;
    std::vector<utils::CommandStandardize> vectorWithCommand;
    utils::dbCommand command;
    std::string tableName = "";
    std::vector<std::string> param = {};

    for( uint16_t iter = 0; iter < comandsSplitByWord.size(); ++iter )
    {
        //std::cout << iter;
        param.clear();
        tableName = "";
        command = checkFirstWord(comandsSplitByWord.at(iter).at(0));
        std::string word = "";
        switch( command )
        {
            case utils::dbCommand::CREATE:
                if( 2 > (comandsSplitByWord.at(iter).size()-1) )
                {
                    param.push_back("ERROR");
                    m_roLogger.logError("Undefined table name");
                    continue;
                }
                else
                {
                    tableName = comandsSplitByWord.at(iter).at(1);
                }
                for( size_t i = 2; i < comandsSplitByWord.at(iter).size(); ++i )
                {
                    word += comandsSplitByWord.at(iter).at(i);

                }
                word = word.substr(word.find_first_of('(')+1,word.find_last_of(')')-1);
                std::cout << word << std::endl;
                param = makeParamCreate(word);

            break;

            case utils::dbCommand::INSERT_INTO:
                if( 2 > (comandsSplitByWord.at(iter).size()-1) )
                {
                    param.push_back("ERROR");
                    m_roLogger.logError("Expected INTO");
                    continue;
                }
                else if( "INTO" == comandsSplitByWord.at(iter).at(1) )
                {
                    if( 3 > (comandsSplitByWord.at(iter).size()-1) )
                    {
                        param.push_back("ERROR");
                        m_roLogger.logError("Undefined table name");
                        continue;
                    }
                    else
                    {
                        tableName = comandsSplitByWord.at(iter).at(2);
                    }
                    for( size_t i = 2; i < comandsSplitByWord.at(iter).size(); ++i )
                    {
                        word += comandsSplitByWord.at(iter).at(i);

                    }
                    word = word.substr(word.find_first_of("(")+1,word.find_last_of(")")-1);
                    if( word.back() == ';' )
                    {
                        word = word.substr(0,word.length()-1);
                    }
                    if( word.back() == ')' )
                    {
                        word = word.substr(0,word.length()-1);
                    }

                    std::cout << word << std::endl;
                    param = makeParamInsert(word);

                }
                else
                {
                    param.push_back("ERROR");
                    m_roLogger.logError("Expected INTO");
                }
            break;

            case utils::dbCommand::DROP:

                if( 1 > (comandsSplitByWord.at(iter).size()-1) )
                {
                    param.push_back("ERROR");
                    m_roLogger.logError("Undefined table name");
                    continue;
                }
                else
                {
                    tableName = comandsSplitByWord.at(iter).at(1);
                }
                if( tableName.back() == ';' )
                {
                    tableName = tableName.substr(0,tableName.length()-1);
                }
                if( tableName.size() == 0 )
                {
                    param.push_back("ERROR");
                    m_roLogger.logError("Undefined table name");
                }

            break;

            case utils::dbCommand::DELETE_FROM:
                if( 1 > (comandsSplitByWord.at(iter).size()-1) )
                {
                    param.push_back("ERROR");
                    m_roLogger.logError("Expected FROM");
                    continue;
                }
                else if( "FROM" == comandsSplitByWord.at(iter).at(1) )
                {
                    if( 2 > (comandsSplitByWord.at(iter).size()-1) )
                    {
                        param.push_back("ERROR");
                        m_roLogger.logError("Undefined table name");
                        continue;
                    }
                    else
                    {
                        tableName = comandsSplitByWord.at(iter).at(2);
                    }

                    if( tableName.back() == ';' )
                    {
                        tableName = tableName.substr(0,tableName.length()-1);
                    }
                    if( tableName.size() == 0 )
                    {
                        param.push_back("ERROR");
                        m_roLogger.logError("Expected table name");
                        continue;
                    }

                    if( 3 < (comandsSplitByWord.at(iter).size()-1) )
                    {
                        if( "WHERE" == comandsSplitByWord.at(iter).at(3) )
                        {
                            word = "";
                            for(size_t i = 3; i < comandsSplitByWord.at(iter).size(); ++i)
                            {
                                word += comandsSplitByWord.at(iter).at(i);
                            }
                            word = makeParamWhere(word);
                            param.push_back(word);
                        }
                        else
                        {
                            param.push_back("ERROR");
                            m_roLogger.logError("Expection WHERE");
                        }
                    }




                }

            break;

            case utils::dbCommand::SELECT:
                if( 2 > (comandsSplitByWord.at(iter).size()-1) )
                {
                    param.push_back("ERROR");
                    m_roLogger.logError("Undefined column name");
                    continue;
                }

                if( comandsSplitByWord.at(iter).end() != std::find( comandsSplitByWord.at(iter).begin(), comandsSplitByWord.at(iter).end(), "FROM" ))
                {
                    for(size_t i = 1; i < comandsSplitByWord.at(iter).size(); ++i)
                    {
                        if( "FROM" == comandsSplitByWord.at(iter).at(i) )
                        {
                            break;
                        }
                        word += comandsSplitByWord.at(iter).at(i);
                    }
                    param.push_back(word);

                    for(size_t i = 0; i < comandsSplitByWord.at(iter).size(); ++i)
                    {
                        if( "FROM" != comandsSplitByWord.at(iter).at(i) )
                        {
                            continue;

                        }
                        tableName += comandsSplitByWord.at(iter).at(++i);
                        break;

                    }
                    tableName = tableName.substr(0,tableName.size());
                    if( tableName.back() == ';' )
                    {
                        tableName = tableName.substr(0,tableName.length()-1);
                    }
                    if( tableName.size() == 0 || tableName == ";" )
                    {
                        param.push_back("ERROR");
                        m_roLogger.logError("Expection table name");
                        continue;
                    }
                    else
                    {
                        word = "";
                        bool isWhere = false;
                        for(size_t i = 0; i < comandsSplitByWord.at(iter).size(); ++i)
                        {
                            if( true == isWhere  )
                            {
                                word += comandsSplitByWord.at(iter).at(i);
                            }
                            if( tableName == comandsSplitByWord.at(iter).at(i) )
                            {
                                isWhere = true;
                            }

                        }
                        if( word.size() > 0 && word != ";" )
                        {
                            if( std::string::npos != word.find("WHERE") )
                            {
                               std::string wordWithWhere = "";

                               for( size_t i = word.find("WHERE")+5; i < tableName.size(); ++i )
                               {
                                   wordWithWhere += tableName.at(i);
                               }
                               wordWithWhere = makeParamWhere(word);
                               param.push_back(wordWithWhere);
                            }
                            else
                            {
                                param.push_back("ERROR");
                                m_roLogger.logError("Expected WHERE");
                            }
                        }
                    }

                }
                else
                {
                  param.push_back("ERROR");
                  m_roLogger.logError("Expection FROM");
                }
            break;

            case utils::dbCommand::UNDEFINED:
            break;

        }
        oCommand.command = command;
        oCommand.tableName = tableName;
        oCommand.params = param;

        vectorWithCommand.push_back(oCommand);
    }
    return vectorWithCommand;

}

utils::dbCommand Translator::checkFirstWord(std::string word)
{
    utils::dbCommand command = utils::dbCommand::UNDEFINED;

    if( "CREATE" == word )
    {
        command = utils::dbCommand::CREATE;
    }
    else if( "INSERT" == word )
    {
        command = utils::dbCommand::INSERT_INTO;
    }
    else if( "DROP" == word )
    {
        command = utils::dbCommand::DROP;
    }
    else if( "SELECT" == word )
    {
        command = utils::dbCommand::SELECT;
    }
    else if( "DELETE" == word )
    {
        command = utils::dbCommand::DELETE_FROM;
    }
    else
    {
        command = utils::dbCommand::UNDEFINED;
    }

    return command;
}

std::vector<std::string> Translator::makeParamInsert(std::string word)
{
    std::string param = "";
    std::vector<std::string> vectorOfParam;
    bool isQuoted = false;
    for( size_t i = 0; i < word.length(); ++i )
    {
        if( '"' == word.at(i) )
        {
            isQuoted = !isQuoted;
        }
        if( ',' == word.at(i) && false == isQuoted )
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
            param += word.at(i);
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

std::string Translator::makeParamWhere(std::string word)
{
    std::string column = "";
    std::string value = "";
    std::string whereParam = "";

    if( std::string::npos != word.find("=") )
    {
        bool isColumn = true;
        for( size_t iter = 0; iter < word.size(); ++iter )
        {
            if( '=' == word.at(iter) )
            {
                isColumn = false;
                continue;

            }
            if( true == isColumn )
            {
                column += word.at(iter);
            }
            else
            {
                value += word.at(iter);
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

std::vector<std::string> Translator::makeParamCreate(std::string word)
{
    std::string param = "";
    std::vector<std::string> vectorOfParam;
    bool isFieldName = true;
    for( size_t i = 0; i < word.length(); ++i )
    {
        if( true == isFieldName )
        {
            if( ':' == word.at(i) )
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
               param += word.at(i);
            }
        }
        else
        {
           if( ',' == word.at(i) )
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
               param += word.at(i);
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
