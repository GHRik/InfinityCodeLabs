#ifndef IPRINTER_HPP
#define IPRINTER_HPP


#include <vector>
#include <string>


class iPrinter
{
public:
    virtual ~iPrinter();
    virtual void printDataBase( const std::string &a_rstrWord ) const = 0;
};

#endif // IPRINTER_HPP
