#ifndef SPLITTER_HPP
#define SPLITTER_HPP

#include "Interface/iSplitter.hpp"
#include <iostream>

namespace helper
{
    class Splitter : public iSplitter
    {
    public:
        Splitter();
        virtual ~Splitter();
        std::vector<std::string> splitCommand(std::string &a_rstrCommand ) const;
        std::vector<std::vector<std::string>> splitCommandByWord
                                              ( const std::vector<std::string> &a_rstrCommandSequence ) const;
    private:
        Splitter( const Splitter& );
        Splitter& operator=( const Splitter& a_oSplitter );

    };
}

#endif // SPLITTER_HPP
