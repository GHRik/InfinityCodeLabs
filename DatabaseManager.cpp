#include "DatabaseManager.hpp"


DatabaseManager::DatabaseManager
(
  const iLogger &a_roLogger,
  iValidate &a_roValidate,
  iFileManager &a_roFileManager,
  iSplitter &a_roSplitter,
  iTranslator &a_roTranslator
)
    : m_roLogger( a_roLogger ),
      m_roValidate( a_roValidate ),
      m_roFileManager( a_roFileManager ),
      m_roSplitter( a_roSplitter ),
      m_roTranslator( a_roTranslator )
{

}

DatabaseManager::~DatabaseManager()
{

}

void DatabaseManager::run() const
{

    std::string commandsOneLine = "CREATE table (price : Integer, Author: varchar(30)); ";
    //getline( std::cin, commandsOneLine );
    std::vector<std::vector<std::string>> astrComandInOneWord;
    std::vector<std::string> astrCommand;
    astrCommand = m_roSplitter.splitCommand(commandsOneLine);
    for( uint16_t u16Iter = 0; u16Iter < astrCommand.size(); ++u16Iter )
    {
        m_roValidate.prepareToValidate( astrCommand.at( u16Iter ) );
    }
    for( uint16_t u16Iter = 0; u16Iter < astrCommand.size(); ++u16Iter )
    {
        std::cout << astrCommand.at( u16Iter ) << std::endl;
        if( utils::ErrorsCode::OK != m_roValidate.validateCommand( astrCommand.at( u16Iter )) )
        {
            astrCommand.erase( astrCommand.begin() + u16Iter );
        }
    }
    astrComandInOneWord = m_roSplitter.splitCommandByWord( astrCommand );

    std::vector<utils::CommandStandardize> aoCommandStandard = m_roTranslator.translateCommand( astrComandInOneWord );

    for( uint16_t u16Iter = 0; u16Iter < aoCommandStandard.size(); ++u16Iter )
    {
        callCommand( aoCommandStandard.at( u16Iter) );
    }
}

void DatabaseManager::callCommand( const utils::CommandStandardize &a_roCommand ) const
{


    if( true == m_roValidate.isWithoutError( a_roCommand.params ) )
    {
        switch( a_roCommand.command )
        {
            case utils::dbCommand::CREATE :
                m_roLogger.logInfo("CREATE called");
                m_roLogger.logInfo("TableName: ");
                m_roLogger.logInfo(a_roCommand.tableName);
                m_roLogger.logInfo("Params: ");
                for(size_t i = 0; i < a_roCommand.params.size();++i)
                {
                    m_roLogger.logInfo(a_roCommand.params.at(i));
                }
            break;
            case utils::dbCommand::DELETE_FROM :
                m_roLogger.logInfo("DELETE FROM called");
                m_roLogger.logInfo("TableName: ");
                m_roLogger.logInfo(a_roCommand.tableName);
                m_roLogger.logInfo("Params: ");
                for(size_t i = 0; i < a_roCommand.params.size();++i)
                {
                    m_roLogger.logInfo(a_roCommand.params.at(i));
                }
            break;
            case utils::dbCommand::INSERT_INTO :
                m_roLogger.logInfo("INSERT INTO called");
                m_roLogger.logInfo("TableName: ");
                m_roLogger.logInfo(a_roCommand.tableName);
                m_roLogger.logInfo("Params: ");
                for(size_t i = 0; i < a_roCommand.params.size();++i)
                {
                    m_roLogger.logInfo(a_roCommand.params.at(i));
                }
            break;
            case utils::dbCommand::SELECT :
                m_roLogger.logInfo("SELECT called");
                m_roLogger.logInfo("TableName: ");
                m_roLogger.logInfo(a_roCommand.tableName);
                m_roLogger.logInfo("Params: ");
                for(size_t i = 0; i < a_roCommand.params.size();++i)
                {
                    m_roLogger.logInfo(a_roCommand.params.at(i));
                }
            break;
            case utils::dbCommand::DROP :
                m_roLogger.logInfo("DROP called");
            break;
            case utils::dbCommand::UNDEFINED :
                m_roLogger.logError("Undefined command");
            break;
        }
    }
}
