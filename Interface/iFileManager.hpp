#ifndef IFILEMANAGER_H
#define IFILEMANAGER_H

#include "Utils/ErrorsCode.hpp"
#include <string>
#include <vector>

class iFileManager
{
public:
    virtual ~iFileManager();
    virtual utils::ErrorsCode create( const std::string &a_rstrFileName ) = 0;
    virtual utils::ErrorsCode open( const std::string &a_rstrFileName ) = 0;
    virtual void closeFile() = 0;
    virtual utils::ErrorsCode readLine( std::string &a_rastrWord, const uint8_t a_u8NumberLine  ) = 0;
    virtual std::string readAll() = 0;
    virtual utils::ErrorsCode deleteFile( const std::string &a_rstrFileName ) const = 0;
    virtual utils::ErrorsCode deleteLine( uint16_t a_u8LineNumber ) = 0;
    virtual utils::ErrorsCode write( const std::string &a_rstrWord, const bool bNewline = false ) = 0;


};

#endif // IFILEMANAGER_H
