#include "DatabaseManager.hpp"
#include <string>
#include <iostream>
#include <vector>
#include "Helper/FileManager.hpp"
#include "Helper/Logger.hpp"
#include "Helper/Splitter.hpp"
#include "Helper/Validator.hpp"
#include "Helper/Translator.hpp"

using namespace std;

int main()
{

    helper::Validator oValidator( helper::Logger::getInstance() );
    helper::FileManager oFileManager( helper::Logger::getInstance() );
    helper::Splitter oSplitter;
    Translator oTranslator( helper::Logger::getInstance() );
    DatabaseManager dbManager( helper::Logger::getInstance(), oValidator, oFileManager, oSplitter, oTranslator );
    dbManager.run();
}
