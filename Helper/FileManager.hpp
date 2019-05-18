#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include "Utils/ErrorsCode.hpp"
#include "Interface/iLogger.hpp"
#include "Interface/iFileManager.hpp"
#include <string>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

namespace helper
{
    class FileManager : public iFileManager
    {
    public:
        FileManager( const iLogger &a_roLogger );
        ~FileManager();
    private:
        const iLogger &m_roLogger;
        std::fstream m_oFile;
        std::string m_strFileName;
        const std::string m_strFileExtension;
        FileManager();
        FileManager( const FileManager& );
        FileManager& operator=( const FileManager& a_oFileManager );
        bool isFileOpen();
        uint16_t countLine();

        // iFileManager interface
    public:
        utils::ErrorsCode create(const std::string &a_rstrFileName);
        utils::ErrorsCode open( const std::string &a_rstrFileName );
        void closeFile();
        utils::ErrorsCode deleteFile(const std::string &a_rstrFileName) const;
        utils::ErrorsCode write(const std::string &a_rstrWord , const bool bNewLine);
        bool isFileExist( const std::string &a_rstrFileName) const;
        utils::ErrorsCode readLine(std::string &a_rastrWords , const uint8_t a_u8NumberLine);
        utils::ErrorsCode deleteLine(uint16_t a_u16LineNumber );
        std::string readAll();
        utils::ErrorsCode readLine(std::string &a_rastrWord);
        utils::ErrorsCode deleteAllLine(const std::string &a_rstrFileName);
    };
}


#endif // FILEMANAGER_HPP
