#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include "Utils/ErrorsCode.hpp"
#include "Interface/iLogger.hpp"
#include "Interface/iFileManager.hpp"
#include "Utils/FileConfig.hpp"
#include <string>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <iostream>
#include <vector>

namespace helper
{
    ///
    /// \brief The FileManager class is used to operate on file
    ///
    class FileManager : public iFileManager
    {
    public:
        ///
        /// \brief FileManager - constructor
        /// \param a_roLogger - reference on iLogger
        ///
        explicit FileManager( const iLogger &a_roLogger );
        ~FileManager();

        ///
        /// \brief create - create file if is not exist, if exist FILE_ERROR will be return.
        /// \param a_rstrFileName  file name to create without extension. For example:
        /// if you want to create x.extension, x should be a parameter.
        /// \return ErrorCode OK or FILE_ERROR if is problem with create file (or file exist)
        ///
        utils::ErrorsCode create( const std::string &a_rstrFileName);

        ///
        /// \brief open - open file if exist
        /// \param a_rstrFileName - file name to open without extension. For example:
        /// if you want to open x.extension, x should be a parameter.
        /// \return ErrorCode OK or FILE_ERROR if is problem with open file ( or file dont exist )
        ///
        utils::ErrorsCode open( const std::string &a_rstrFileName );

        ///
        /// \brief closeFile - close file whos was open last
        ///
        void closeFile();

        ///
        /// \brief deleteFile - if file exist delete this file.
        /// \param a_rstrFileName - file name to delete without extension. For example:
        /// if you want to delete x.extension, x should be a parameter.
        /// \return  ErrorCode OK or FILE_ERROR if is problem with delete file ( or file dont exist )
        ///
        utils::ErrorsCode deleteFile( const std::string &a_rstrFileName ) const;

        ///
        /// \brief write
        /// \param a_rstrWord
        /// \param bNewLine
        /// \return same as open
        /// \see open
        ///
        utils::ErrorsCode write( const std::string &a_rstrWord , const bool bNewLine );

        ///
        /// \brief isFileExist - check existing file in project directory
        /// \param a_rstrFileName -
        /// \return true if exist, false if not exist
        ///
        bool isFileExist( const std::string &a_rstrFileName) const;

        ///
        /// \brief readLine - reads exactly one line with the given number and writes it to a_rastrWords
        /// \param a_rastrWords - reference on string. This string will be contain a line from file
        /// \param a_u8NumberLine - line number to read
        /// \return same as open
        /// \see open
        ///
        utils::ErrorsCode readLine( std::string &a_rastrWords , const uint8_t a_u8NumberLine );

        ///
        /// \brief deleteLine - delete exactly one line with the given number and writes it to a_rastrWords
        /// \param a_u16LineNumber - line number to delete
        /// \return
        /// \todo This function now is empty. Function is neccesary to support
        /// DELETE FROM table_name WHERE param=param.
        /// \todo To implements: OpenFile, ReadAllLine to string , delete line from string,
        /// insert string to temporary file, remove old file, rename temporary file as old file.
        ///
        ///
        utils::ErrorsCode deleteLine( uint16_t a_u16LineNumber );

        ///
        /// \brief readAll - read all line( without first ) from last opened file.
        /// \return string with file content
        ///
        std::string readAll();

        ///
        /// \brief readLine - reads exactly one line and writes it to a_rastrWords
        /// \param a_rastrWords - reference on string. This string will be contain a line from file
        /// \return same as open
        /// \see open
        ///
        utils::ErrorsCode readLine( std::string &a_rastrWord );

        ///
        /// \brief deleteAllLine
        /// \param a_rstrFileName
        /// \return same as deleteFile and open
        /// \see deleteFile
        /// \see open
        ///
        utils::ErrorsCode deleteAllLine( const std::string &a_rstrFileName );

    private:
        const iLogger &m_roLogger;
        std::fstream m_oFile;
        std::string m_strFileName;
        const std::string m_strFileExtension;
        FileManager();
        explicit FileManager( const FileManager& a_roFileManager );
        FileManager& operator=( const FileManager& a_roFileManager );
        bool isFileOpen();
        uint16_t countLine();




    };
}


#endif // FILEMANAGER_HPP
