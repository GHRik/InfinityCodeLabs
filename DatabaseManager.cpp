#include "DatabaseManager.hpp"


DatabaseManager::DatabaseManager( iLogger *a_poLogger, iValidate *a_poValidate, iFileManager *a_poFileManager, iSplitter *a_poSplitter, iTranslator *a_poTranslator)
    : m_poLogger( a_poLogger ),
      m_poValidate( a_poValidate ),
      m_poFileManager( a_poFileManager ),
      m_poSplitter( a_poSplitter ),
      m_poTranslator( a_poTranslator )
{

}

DatabaseManager::~DatabaseManager()
{

}

void DatabaseManager::run()
{

    std::string commandsOneLine = "CREATE table (price : Integer, Author: varchar(30)); INSERT INTO table (1, \"Ja\"); SELECT price FROM table WHERE Author=\"Ja\"; DELETE FROM table WHERE a=b; DROP table; ";
    //getline( std::cin, commandsOneLine );
    std::vector<std::vector<std::string>> comandInOneWord;
    std::vector<std::string> commands;
    if( nullptr != m_poSplitter )
    {
       commands = m_poSplitter->splitCommand(commandsOneLine);
       if( nullptr != m_poValidate )
       {
           for( uint16_t iter = 0; iter < commands.size(); ++iter )
           {
                m_poValidate->prepareToValidate( commands.at(iter) );
           }
          for( uint16_t iter = 0; iter < commands.size(); ++iter)
          {
             std::cout << commands.at(iter) << std::endl;
             if( utils::ErrorsCode::OK != m_poValidate->validateCommand(commands.at(iter)) )
             {
                 commands.erase(commands.begin()+iter);
             }
          }
       }
       comandInOneWord = m_poSplitter->splitCommandByWord(commands);
    }

    std::vector<utils::CommandStandardize> Queue = m_poTranslator->translateCommand( comandInOneWord );

    for( size_t iter = 0; iter < Queue.size(); ++iter )
    {
        callCommand( Queue.at(iter) );
    }
}

utils::ErrorsCode DatabaseManager::callCommand( utils::CommandStandardize Queue )
{
    if( true == m_poValidate->isWithoutError( Queue.params ) )
    {

        switch( Queue.command )
        {
            case utils::dbCommand::CREATE :
                m_poLogger->logInfo("CREATE called");
                m_poLogger->logInfo("TableName: ");
                m_poLogger->logInfo(Queue.tableName);
                m_poLogger->logInfo("Params: ");
                for(size_t i = 0; i < Queue.params.size();++i)
                {
                    m_poLogger->logInfo(Queue.params.at(i));
                }
            break;
            case utils::dbCommand::DELETE_FROM :
                m_poLogger->logInfo("DELETE FROM called");
                m_poLogger->logInfo("TableName: ");
                m_poLogger->logInfo(Queue.tableName);
                m_poLogger->logInfo("Params: ");
                for(size_t i = 0; i < Queue.params.size();++i)
                {
                    m_poLogger->logInfo(Queue.params.at(i));
                }
            break;
            case utils::dbCommand::INSERT_INTO :
                m_poLogger->logInfo("INSERT INTO called");
                m_poLogger->logInfo("TableName: ");
                m_poLogger->logInfo(Queue.tableName);
                m_poLogger->logInfo("Params: ");
                for(size_t i = 0; i < Queue.params.size();++i)
                {
                    m_poLogger->logInfo(Queue.params.at(i));
                }
            break;
            case utils::dbCommand::SELECT :
                m_poLogger->logInfo("SELECT called");
                m_poLogger->logInfo("TableName: ");
                m_poLogger->logInfo(Queue.tableName);
                m_poLogger->logInfo("Params: ");
                for(size_t i = 0; i < Queue.params.size();++i)
                {
                    m_poLogger->logInfo(Queue.params.at(i));
                }
            break;
            case utils::dbCommand::DROP :
                m_poLogger->logInfo("DROP called");
            break;
            case utils::dbCommand::UNDEFINED :
                m_poLogger->logError("Undefined command");
            break;
        }
    }
}
