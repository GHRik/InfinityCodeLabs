#include "DatabaseManager.hpp"
#include <string>
#include <iostream>
#include <vector>
#include "Helper/FileManager.hpp"
#include "Helper/Logger.hpp"
#include "Helper/Validator.hpp"
#include "Helper/Translator.hpp"
#include "Helper/Printer.hpp"

using namespace std;

int main()
{

    helper::Validator oValidator( helper::Logger::getInstance() );
    helper::FileManager oFileManager( helper::Logger::getInstance() );
    helper::Translator oTranslator( helper::Logger::getInstance(), oFileManager );
    const helper::Printer oPrinter;
    DatabaseManager dbManager( helper::Logger::getInstance(), oValidator, oFileManager, oTranslator, oPrinter );
    dbManager.run();
}
