#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include "Utils/ErrorsCode.hpp"
#include "Interface/iLogger.hpp"
#include "Interface/iFileManager.hpp"
#include <string>

namespace helper
{
    class FileManager : public iFileManager
    {
    public:
        FileManager( iLogger *a_poLogger );
        ~FileManager();
        utils::ErrorsCode openFile( const std::string a_strFileName );
        utils::ErrorsCode closeFile();
        utils::ErrorsCode writeToFile( const std::string a_strText );
        utils::ErrorsCode removeLineFromFile( const uint16_t a_u16LineNumber );
        utils::ErrorsCode clearFile();
        utils::ErrorsCode printFile( const std::string a_strFileName );
    private:
        iLogger *m_poLogger;
        std::string *m_strOpenFileName;


        // iFileManager interface
    public:
        utils::ErrorsCode createFile(std::string a_strFileName);
        utils::ErrorsCode deleteFile(std::string a_strFileName);
        utils::ErrorsCode addRecordToFile(std::string a_strFileName, std::string a_strColumnName, std::string a_strValue);
        utils::ErrorsCode printRecordFromFile(std::string a_strFileName);
        utils::ErrorsCode printRecordFromFile(std::string a_strFileName, std::string a_strColumnName);
        utils::ErrorsCode printRecordFromFile(std::string a_strFileName, std::string a_strColumnName, std::string a_strValue);
        utils::ErrorsCode removeRecordFromFile(std::string a_strFileName);
        utils::ErrorsCode removeRecordFromFile(std::string a_strFileName, std::string a_strColumnName, std::string a_strValue);
    };
}


#endif // FILEMANAGER_HPP
