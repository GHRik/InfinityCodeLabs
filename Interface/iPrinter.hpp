#ifndef IPRINTER_HPP
#define IPRINTER_HPP


#include <vector>
#include <string>

class iPrinter
{
public:
    virtual ~iPrinter();
    virtual void printFields( const std::vector<std::string> a_astrFields ) const = 0;
    virtual void printRecord( const std::vector<std::string> a_astr ) const = 0;
    virtual void printDataBase( const std::string &a_rstrWord ) const = 0;
};

#endif // IPRINTER_HPP
