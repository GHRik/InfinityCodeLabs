#ifndef DATABASE_HPP
#define DATABASE_HPP


#include "Utils/ErrorsCode.hpp"
#include "Utils/DataBaseCommand.hpp"
#include "Interface/iFileManager.hpp"
#include "Interface/iValidate.hpp"
#include "Interface/iLogger.hpp"
#include "Interface/iSplitter.hpp"
#include "Helper/Logger.hpp"
#include "Helper/FileManager.hpp"
#include "Helper/Validator.hpp"
#include "Interface/iTranslator.hpp"


#include <iostream>
#include <vector>

struct CommandQueue;

class DatabaseManager
{
public:
    DatabaseManager
    (
      const iLogger &a_roLogger,
      iValidate &a_roValidate,
      iFileManager &a_roFileManager,
      iSplitter &a_roSplitter,
      iTranslator &a_roTranslator
    );
    ~DatabaseManager();
    void run() const;
private:
    const iLogger &m_roLogger;
    iValidate &m_roValidate;
    iFileManager &m_roFileManager;
    iSplitter &m_roSplitter;
    iTranslator &m_roTranslator;
    void callCommand( const utils::CommandStandardize &a_roCommand  ) const;
    DatabaseManager();
    DatabaseManager( const DatabaseManager& );
    DatabaseManager& operator=( const DatabaseManager& a_oDatabaseManager );

};

#endif // DATABASE_HPP
