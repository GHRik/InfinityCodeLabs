#include "Helper/Logger.hpp"
#include <iostream>

helper::Logger::Logger()
{

}

helper::Logger::~Logger()
{
}


const helper::Logger &helper::Logger::getInstance()
{
    static helper::Logger oInstance;
    return oInstance;
}

void helper::Logger::logError( const std::string a_rstrErrorMessage ) const
{
    std::cout <<"ERROR: " << a_rstrErrorMessage << std::endl;
}

void helper::Logger::logWarrning( const std::string a_strWarrningMessage ) const
{
    std::cout <<"WARRNING: " << a_strWarrningMessage << std::endl;
}

void helper::Logger::logInfo( const std::string a_strInfoMessage ) const
{
    std::cout <<"INFO: " << a_strInfoMessage << std::endl;
}
