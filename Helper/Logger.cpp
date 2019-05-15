#include "Helper/Logger.hpp"
#include <iostream>

helper::Logger::Logger()
{

}

helper::Logger::~Logger()
{
}


helper::Logger &helper::Logger::getInstance()
{
    static helper::Logger oInstance;
    return oInstance;
}

utils::ErrorsCode helper::Logger::logError( std::string a_pcErrorMessage )
{
    utils::ErrorsCode oError = utils::ErrorsCode::LOGGER_PROBLEM;
        oError = utils::ErrorsCode::OK;
        std::cout <<"ERROR: " << a_pcErrorMessage << std::endl;

    return oError;
}

utils::ErrorsCode helper::Logger::logWarrning(std::string a_pcWarrningMessage)
{
    utils::ErrorsCode oError = utils::ErrorsCode::LOGGER_PROBLEM;
        oError = utils::ErrorsCode::OK;
        std::cout <<"WARRNING: " << a_pcWarrningMessage << std::endl;
    return oError;
}

utils::ErrorsCode helper::Logger::logInfo( std::string a_pcInfoMessage )
{
    utils::ErrorsCode oError = utils::ErrorsCode::LOGGER_PROBLEM;
        oError = utils::ErrorsCode::OK;
        std::cout <<"INFO: " << a_pcInfoMessage << std::endl;
    return oError;
}
