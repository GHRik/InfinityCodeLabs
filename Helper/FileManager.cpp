#include "Helper/FileManager.hpp"

helper::FileManager::FileManager( const iLogger &a_roLogger ) : m_roLogger( a_roLogger ), m_strFileExtension( "txt" )
{

}

helper::FileManager::~FileManager()
{
    if( true == isFileOpen() )
    {
        closeFile();
    }
}

void helper::FileManager::closeFile()
{
    if( true == isFileOpen() )
    {
        m_oFile.close();
    }
}

bool helper::FileManager::isFileOpen()
{
    return m_oFile.is_open();
}


utils::ErrorsCode helper::FileManager::create( const std::string &a_rstrFileName )
{
    utils::ErrorsCode oError = utils::ErrorsCode::OK;
    const std::string strTemp = a_rstrFileName+"."+m_strFileExtension;
    if( false == isFileExist(strTemp ) )
    {
        std::ofstream oTempDescriptor( strTemp );
        oTempDescriptor.close();

        m_oFile.open( strTemp,  std::ios::out | std::ios::in | std::ios::app );

        if( !m_oFile )
        {
            oError = utils::ErrorsCode::FILE_ERROR;
            m_roLogger.logError("Can not create file");
        }
        else
        {
            m_strFileName = a_rstrFileName;
        }
    }
    else
    {
        oError = utils::ErrorsCode::FILE_ERROR;
        m_roLogger.logError("Table exist");
    }
    return oError;
}

utils::ErrorsCode helper::FileManager::open( const std::string &a_rstrFileName )
{
    utils::ErrorsCode oError = utils::ErrorsCode::OK;
    const std::string strTemp = a_rstrFileName+"."+m_strFileExtension;
    if( true == isFileExist(strTemp ) )
    {
        m_oFile.open( strTemp,  std::ios::out | std::ios::in | std::ios::app );

        if( !m_oFile )
        {
            oError = utils::ErrorsCode::FILE_ERROR;
            m_roLogger.logError("Can not open file");
        }
        else
        {
            m_strFileName = a_rstrFileName;
        }
    }
    else
    {
        oError = utils::ErrorsCode::FILE_ERROR;
        m_roLogger.logError("Table dont exist");
    }
    return oError;
}

utils::ErrorsCode helper::FileManager::deleteFile( const std::string &a_rstrFileName ) const
{
    utils::ErrorsCode oError = utils::ErrorsCode::OK;

    std::string strTemp = a_rstrFileName+"."+m_strFileExtension;
    if( true == isFileExist(strTemp) )
    {
        if( remove( strTemp.c_str() ) != 0 )
        {
          oError = utils::ErrorsCode::FILE_ERROR;
          m_roLogger.logError("Can not delete file");
        }
    }
    else
    {
         oError = utils::ErrorsCode::FILE_ERROR;
         m_roLogger.logError("Can not DROP table because dont exist");
    }
    return oError;
}

utils::ErrorsCode helper::FileManager::write( const std::string &a_rstrWord, const bool bNewLine = false )
{
    utils::ErrorsCode oError = utils::ErrorsCode::FILE_ERROR;
    if( utils::ErrorsCode::OK != isFileOpen() )
    {
        std::string strTemp = a_rstrWord+" ";

        m_oFile.sync();
        m_oFile.flush();
        if( true == bNewLine )
        {
            m_oFile << "\n";
        }
        m_oFile.write( strTemp.c_str(), static_cast<uint16_t>(strTemp.size()) );

        oError = utils::ErrorsCode::OK;
    }
    return oError;
}

uint16_t helper::FileManager::countLine()
{
    uint16_t u16CountLine = 0;
        if( true == isFileOpen() )
        {
            std::string strTemp = "";
            while( std::getline( m_oFile, strTemp ) )
            {
                ++u16CountLine;
            }
        }
        closeFile();
        if( utils::ErrorsCode::OK != open(m_strFileName) )
        {
            u16CountLine = 0;
        }
        return u16CountLine;
}


bool helper::FileManager::isFileExist(const std::string &a_rstrFileName) const
{
    bool isExist = true;  
    std::fstream oDescriptor(a_rstrFileName);

    if( !oDescriptor )
    {
        isExist = false;
    }

    return isExist;
}

utils::ErrorsCode helper::FileManager::readLine( std::string &a_rastrWord, const uint8_t a_u8NumberLine )
{
    utils::ErrorsCode oError = utils::ErrorsCode::OK;
    if( true == isFileOpen() )
    {
        uint16_t u16LineCounter = countLine();
        if( u16LineCounter != 0 )
        {
            for( uint16_t u16Iter = 0; u16Iter < u16LineCounter; ++u16Iter )
            {
                if( a_u8NumberLine == u16Iter )
                {
                    getline(m_oFile, a_rastrWord);
                    break;
                }

                getline(m_oFile, a_rastrWord);
            }
        }
        else
        {
            oError = utils::ErrorsCode::FILE_ERROR;
            m_roLogger.logError("File is empty");
        }
    }
    else
    {
        oError = utils::ErrorsCode::FILE_ERROR;
        m_roLogger.logError("Can not read from file");

    }
    return oError;

}

utils::ErrorsCode helper::FileManager::deleteLine(uint16_t a_u16LineNumber)
{
//    utils::ErrorsCode oError = utils::ErrorsCode::OK;
//    if( true == isFileOpen() )
//    {
//        uint16_t u16LineCounter = countLine();
//        if( u16LineCounter != 0 )
//        {
//            for( uint16_t u16Iter = 0; u16Iter < u16LineCounter; ++u16Iter )
//            {
//                std::string strTemp;
//                for( uint16_t u16Iter = 0; u16Iter < u16LineCounter; ++u16Iter )
//                {
//                    getline( m_oFile, strTemp );
//                    if( a_u16LineNumber == u16Iter )
//                    {

//                        break;
//                    }
//                }
//            }
//        }
//        else
//        {
//            m_roLogger.logError("File is empty");
//        }
//    }
//    else
//    {
//        oError = utils::ErrorsCode::FILE_ERROR;
//        m_roLogger.logError("Can not read from file");

    //    }
}

std::string helper::FileManager::readAll()
{
    std::string strResult = "";
    std::string strTemp = "";
    closeFile();
    if( utils::ErrorsCode::OK == open( m_strFileName ) )
    {
        getline( m_oFile, strTemp ); //skip first line
        while(getline( m_oFile, strTemp ))
        {
            strResult += strTemp;
            strResult += '\n';
        }
    }


    return strResult;

}

utils::ErrorsCode helper::FileManager::readLine(std::string &a_rastrWord)
{
    utils::ErrorsCode oError = utils::ErrorsCode::OK;
    if( true == isFileOpen() )
    {
        if( getline( m_oFile,a_rastrWord ) )
        {
            oError = utils::ErrorsCode::EMPTY_STRING;
        }
    }
    else
    {
        oError = utils::ErrorsCode::FILE_ERROR;
    }
    return oError;
}
