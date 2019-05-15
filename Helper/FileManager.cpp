#include "Helper/FileManager.hpp"



helper::FileManager::FileManager(iLogger *a_poLogger) : m_poLogger( a_poLogger )
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
