#include "DatabaseManager.hpp"


DatabaseManager::DatabaseManager
(
        const iLogger &a_roLogger,
        iValidate &a_roValidate,
        iFileManager &a_roFileManager,
        iTranslator &a_roTranslator
        )
    : m_roLogger( a_roLogger ),
      m_roValidate( a_roValidate ),
      m_roFileManager( a_roFileManager ),
      m_roTranslator( a_roTranslator )
{

}

DatabaseManager::~DatabaseManager()
{

}

void DatabaseManager::run() const
{

    std::string commandsOneLine = " INSERT INTO BookInventory (\"600\", -2, -2, 0) ; INSERT INTO BookInventory (\"600\", 2, 20.5, 1); INSERT INTO BookInventory (\"600\", 2, 20.5, 1); INSERT INTO BookInventory (\"600\", 2, 20.5, 1); INSERT INTO BookInventory (\"600\", 2, 20.5, 1); INSERT INTO BookInventory (\"600\", 2, 20.5, 1);  ";
    //getline( std::cin, commandsOneLine );
    std::vector<std::vector<std::string>> astrComandInOneWord;
    std::vector<std::string> astrCommand;
    astrCommand = m_roTranslator.splitCommand(commandsOneLine);
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
    astrComandInOneWord = m_roTranslator.splitCommandByWord( astrCommand );

    std::vector<utils::CommandStandardize> aoCommandStandard = m_roTranslator.translateCommand( astrComandInOneWord );

    for( uint16_t u16Iter = 0; u16Iter < aoCommandStandard.size(); ++u16Iter )
    {
        if( utils::ErrorsCode::OK != m_roValidate.validateStandarizeCommand( aoCommandStandard.at(u16Iter) ) )
        {
            aoCommandStandard.erase( aoCommandStandard.begin()+u16Iter );
        }

    }

    for( uint16_t u16Iter = 0; u16Iter < aoCommandStandard.size(); ++u16Iter )
    {
        callCommand( aoCommandStandard.at( u16Iter) );
    }
}

void DatabaseManager::callCommand( utils::CommandStandardize &a_roCommand ) const
{
    if( true == m_roValidate.isWithoutError( a_roCommand.params ) )
    {
        switch( a_roCommand.command )
        {
        case utils::dbCommand::CREATE :

            if( utils::ErrorsCode::OK == ( m_roFileManager.create( a_roCommand.tableName ) ) )
            {

                for(size_t i = 0; i < a_roCommand.params.size();++i)
                {
                    m_roFileManager.write( a_roCommand.params.at(i) );
                }

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
            if( utils::ErrorsCode::OK == ( m_roFileManager.open( a_roCommand.tableName ) ) )
            {
                std::vector<std::string> astrMyParams = m_roTranslator.takeParam();
                if( astrMyParams.size() == a_roCommand.params.size() )
                {
                    bool isParamGood = true;
                    for ( uint16_t u16Iter = 0; u16Iter < a_roCommand.params.size(); ++u16Iter )
                    {
                        if( false == m_roValidate.isValidateParam(astrMyParams.at(u16Iter),a_roCommand.params.at(u16Iter)))
                        {
                            isParamGood = false;
                            break;
                        }

                    }

                    if( true == isParamGood )
                    {
                        m_roFileManager.closeFile();
                        if( utils::ErrorsCode::OK == m_roFileManager.open( a_roCommand.tableName ))
                        {
                            const bool bNewLine = true;
                            m_roFileManager.write( "", bNewLine );
                            for(size_t i = 0; i < a_roCommand.params.size(); ++i )
                            {

                                m_roFileManager.write( a_roCommand.params.at(i) );
                            }


                        }
                    }
                    else
                    {
                        m_roLogger.logError("Bad param");
                    }

                }
                else
                {
                    m_roLogger.logError("Incompatible number of arguments");
                }
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
            m_roLogger.logInfo("TableName: ");
            m_roLogger.logInfo(a_roCommand.tableName);
            m_roLogger.logInfo("Params: ");
            for(size_t i = 0; i < a_roCommand.params.size();++i)
            {
                m_roLogger.logInfo(a_roCommand.params.at(i));
            }
            break;

        case utils::dbCommand::UNDEFINED :
            m_roLogger.logError("Undefined command");
            break;
        }
        m_roFileManager.closeFile();
    }
}
