#include "DatabaseManager.hpp"


DatabaseManager::DatabaseManager
(
        const iLogger &a_roLogger,
        iValidate &a_roValidate,
        iFileManager &a_roFileManager,
        iTranslator &a_roTranslator,
        const iPrinter &a_roPrinter
        )
    : m_roLogger( a_roLogger ),
      m_roValidate( a_roValidate ),
      m_roFileManager( a_roFileManager ),
      m_roTranslator( a_roTranslator ),
      m_roPrinter( a_roPrinter )
{

}

DatabaseManager::~DatabaseManager()
{

}

void DatabaseManager::run() const
{

    std::string commandsOneLine = "" ;//"CREATE BookInventory ( Title:varchar(60),Price:Float,Amount:Integer,isAv:Bool ); INSERT INTO BookInventory ( \"60\", 2.5 , 2 , true ) ; SELECT * FROM BookInventory; DROP BookInventory;  ";
    getline( std::cin, commandsOneLine );
    std::vector<std::vector<std::string>> astrComandInOneWord;
    std::vector<std::string> astrCommand;
    astrCommand = m_roTranslator.splitCommand(commandsOneLine);
    for( uint16_t u16Iter = 0; u16Iter < astrCommand.size(); ++u16Iter )
    {
        m_roValidate.prepareToValidate( astrCommand.at( u16Iter ) );
    }
    for( uint16_t u16Iter = 0; u16Iter < astrCommand.size(); ++u16Iter )
    {
        //std::cout << astrCommand.at( u16Iter ) << std::endl;
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
        std::cout << astrCommand.at( u16Iter ) << std::endl;
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
            m_roLogger.logWarrning("DELETE FROM called , but not supported");
            m_roLogger.logInfo("TableName: ");
            m_roLogger.logInfo(a_roCommand.tableName);
            m_roLogger.logInfo("Params: ");
            for(size_t i = 0; i < a_roCommand.params.size();++i)
            {
                m_roLogger.logInfo(a_roCommand.params.at(i));
                if( std::string::npos != a_roCommand.params.at(i).find("WHERE"))
                {
                    m_roLogger.logInfo("DELETE call with WHERE but not supported");
                    break;
                }
            }
            break;

        case utils::dbCommand::INSERT_INTO :
            m_roFileManager.closeFile();
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
            m_roFileManager.closeFile();

            break;

        case utils::dbCommand::SELECT :
            for(size_t i = 0; i < a_roCommand.params.size();++i)
            {
                if( std::string::npos != a_roCommand.params.at(i).find("WHERE"))
                {
                    m_roLogger.logInfo("SELECT call with WHERE but not supported");
                    break;
                }
            }

            if( utils::ErrorsCode::OK == ( m_roFileManager.open( a_roCommand.tableName ) ) )
            {
                std::vector<std::string> astrMyField = m_roTranslator.takeField();
                if(  a_roCommand.params.size() <= astrMyField.size() )
                {
                    bool isParamGood = true;
                    bool isFieldExist = false;
                    std::vector<uint16_t> au16FieldNumberToPrint;
                    for( uint16_t u16It = 0; u16It < a_roCommand.params.size(); ++u16It )
                    {
                        if(  1 == a_roCommand.params.size() && "*" == a_roCommand.params.at(0)  )
                        {
                            isFieldExist = true;
                            isParamGood = true;
                            au16FieldNumberToPrint.resize(astrMyField.size());
                            std::iota( au16FieldNumberToPrint.begin(),au16FieldNumberToPrint.end(),0 );
                            break;
                        }

                        for( uint16_t u16Iter = 0; u16Iter < astrMyField.size(); ++u16Iter )
                        {
                            isFieldExist = false;
                            if( true == m_roValidate.isValidateFieldName(a_roCommand.params.at(u16It),astrMyField.at(u16Iter) ) )
                            {
                                isFieldExist = true;
                                au16FieldNumberToPrint.push_back(u16Iter);
                                break;
                            }
                        }
                        if( false == isFieldExist )
                        {
                            m_roLogger.logError( " Use param in SELECT is not field name " );
                            isParamGood = false;
                            break;
                        }
                    }
                    if( true == isParamGood )
                    {
                        std::string strTemp = "";
                        strTemp += a_roCommand.tableName +'\n';
                        for( uint16_t u16Iter = 0; u16Iter < au16FieldNumberToPrint.size(); ++u16Iter  )
                        {
                            strTemp += astrMyField.at(au16FieldNumberToPrint.at(u16Iter)) + " ";
                            strTemp += '\t';

                        }
                        strTemp += '\n';
                        std::string strLineFromFile = "";
                        while( m_roFileManager.readLine(strLineFromFile) )
                        {
                            strTemp += m_roTranslator.splitByExpectedField( au16FieldNumberToPrint, strLineFromFile );
                        }

                        m_roPrinter.printDataBase(strTemp); //SELECT param,parm
                    }
                }
                else
                {
                    m_roLogger.logError("Too much arguments");
                }
            }
            m_roFileManager.closeFile();
            break;

        case utils::dbCommand::DROP :
            m_roFileManager.deleteFile( a_roCommand.tableName );
            break;
        case utils::dbCommand::UNDEFINED :
            m_roLogger.logError("Undefined command");
            break;
        }
        m_roFileManager.closeFile();
    }
}
