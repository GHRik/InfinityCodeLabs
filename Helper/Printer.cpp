#include "Printer.hpp"

helper::Printer::~Printer()
{

}

helper::Printer::Printer()
{

}

void helper::Printer::printDataBase( const std::string &a_rstrWord) const
{
    std::cout << a_rstrWord;
}
