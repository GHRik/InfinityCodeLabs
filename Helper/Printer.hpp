#ifndef PRINTER_HPP
#define PRINTER_HPP

#include "Interface/iPrinter.hpp"
#include <iostream>

namespace helper
{
///
/// \brief The Printer class is used to print DataBase table a specific way
///
    class Printer : public iPrinter
    {
    public:
        explicit Printer();
        ~Printer();

        ///
        /// \brief printDataBase - print table from data base
        /// \param a_rstrWord - data to print
        ///
        void printDataBase( const std::string &a_rstrWord) const;

    private:
        explicit Printer( const Printer& );
        Printer& operator=( const Printer& Translator );
    };
}

#endif // PRINTER_HPP
