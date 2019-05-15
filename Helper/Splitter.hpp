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
        std::vector<std::string> splitCommand(std::string &str);
        std::vector<std::vector<std::string> > splitCommandByWord(std::vector<std::string> &sequence);
    };
}

#endif // SPLITTER_HPP
