#ifndef IFILEMANAGER_H
#define IFILEMANAGER_H

#include "Utils/ErrorsCode.hpp"
#include <string>

class iFileManager
{
public:
    virtual ~iFileManager();
    virtual utils::ErrorsCode createFile( std::string a_strFileName ) = 0;
    virtual utils::ErrorsCode deleteFile( std::string a_strFileName ) = 0;
    virtual utils::ErrorsCode addRecordToFile( std::string a_strFileName, std::string a_strColumnName, std::string a_strValue ) = 0;
    virtual utils::ErrorsCode printRecordFromFile( std::string a_strFileName ) = 0;
    virtual utils::ErrorsCode printRecordFromFile( std::string a_strFileName, std::string a_strColumnName ) = 0;
    virtual utils::ErrorsCode printRecordFromFile( std::string a_strFileName, std::string a_strColumnName, std::string a_strValue ) = 0;
    virtual utils::ErrorsCode removeRecordFromFile( std::string a_strFileName ) = 0;
    virtual utils::ErrorsCode removeRecordFromFile( std::string a_strFileName, std::string a_strColumnName, std::string a_strValue ) = 0;


};

#endif // IFILEMANAGER_H
