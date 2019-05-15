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
    DatabaseManager( iLogger *a_poLogger, iValidate *a_poValidate, iFileManager *a_poFileManager, iSplitter *a_poSplitter, iTranslator *a_poTranslator );
    ~DatabaseManager();
    void run();
private:
    utils::ErrorsCode callCommand(utils::CommandStandardize Queue  );
    iLogger *m_poLogger;
    iValidate *m_poValidate;
    iFileManager *m_poFileManager;
    iSplitter *m_poSplitter;
    iTranslator *m_poTranslator;
};

#endif // DATABASE_HPP
