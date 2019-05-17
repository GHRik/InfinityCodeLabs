#ifndef IPRINTER_HPP
#define IPRINTER_HPP


#include <vector>
#include <string>

class iPrinter
{
public:
    virtual ~iPrinter();
    virtual void printFields( std::vector<std::string> a_astrFields ) = 0;
    virtual void printRecord( std::vector<std::string> a_astr ) = 0;
};

#endif // IPRINTER_HPP
