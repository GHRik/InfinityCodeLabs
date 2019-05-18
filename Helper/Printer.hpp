#ifndef PRINTER_HPP
#define PRINTER_HPP

#include "Interface/iPrinter.hpp"
#include <iostream>

namespace helper
{
    class Printer : public iPrinter
    {
    public:
        Printer();
        ~Printer();

        // iPrinter interface
    public:
        void printFields( const std::vector<std::string> a_astrFields) const;
        void printRecord( const std::vector<std::string> a_astr) const;
        void printDataBase( const std::string &a_rstrWord) const;
    };
}

#endif // PRINTER_HPP
