#include "Helper/FileManager.hpp"



helper::FileManager::FileManager( const iLogger &a_roLogger ) : m_roLogger( a_roLogger )
{

}

helper::FileManager::~FileManager()
{

}

utils::ErrorsCode helper::FileManager::createFile(std::string a_strFileName)
{

}

utils::ErrorsCode helper::FileManager::deleteFile(std::string a_strFileName)
{

}

utils::ErrorsCode helper::FileManager::addRecordToFile(std::string a_strFileName, std::string a_strColumnName, std::string a_strValue)
{

}

utils::ErrorsCode helper::FileManager::printRecordFromFile(std::string a_strFileName)
{

}

utils::ErrorsCode helper::FileManager::printRecordFromFile(std::string a_strFileName, std::string a_strColumnName)
{

}

utils::ErrorsCode helper::FileManager::printRecordFromFile(std::string a_strFileName, std::string a_strColumnName, std::string a_strValue)
{

}

utils::ErrorsCode helper::FileManager::removeRecordFromFile(std::string a_strFileName)
{

}

utils::ErrorsCode helper::FileManager::removeRecordFromFile(std::string a_strFileName, std::string a_strColumnName, std::string a_strValue)
{

}
