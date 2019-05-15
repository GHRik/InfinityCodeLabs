#include "Translator.hpp"

#include <iostream>

Translator::Translator(iLogger &a_roLogger ) : m_roLogger( a_roLogger )
{

}

std::vector<utils::CommandStandardize> Translator::translateCommand(std::vector<std::vector<std::string> > comandsSplitByWord)
{
    utils::CommandStandardize oCommand;
    std::vector<utils::CommandStandardize> vectorWithCommand;
    utils::dbCommand command;
    std::string tableName = "";
    std::vector<std::string> param = {};

    for( uint16_t iter = 0; iter < comandsSplitByWord.size(); ++iter )
    {
        param.clear();
        command = checkFirstWord(comandsSplitByWord.at(iter).at(0));
        std::string word = "";
        switch( command )
        {
            case utils::dbCommand::CREATE:
                if( 2 > (comandsSplitByWord.at(iter).size()-1) )
                {
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
                    m_roLogger.logError("Expected INTO");
                    continue;
                }
                else if( "INTO" == comandsSplitByWord.at(iter).at(1) )
                {
                    if( 3 > (comandsSplitByWord.at(iter).size()-1) )
                    {
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
                    word = word.substr(word.find_first_of('(')+1,word.find_last_of(')')-1);
                    std::cout << word << std::endl;
                    param = makeParamInsert(word);

                }
                else
                {
                    m_roLogger.logError("Expected INTO");
                }
            break;

            case utils::dbCommand::DROP:

                if( 2 > (comandsSplitByWord.at(iter).size()-1) )
                {
                    m_roLogger.logError("Undefined table name");
                    continue;
                }
                else
                {
                    tableName = comandsSplitByWord.at(iter).at(1);
                }
            break;

            case utils::dbCommand::DELETE_FROM:

            break;

            case utils::dbCommand::SELECT:


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
