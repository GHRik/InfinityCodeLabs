#ifndef ISPLITTER_HPP
#define ISPLITTER_HPP


#include "Utils/ErrorsCode.hpp"
#include <string>
#include <vector>

class iSplitter
{
public:
    virtual ~iSplitter();
    virtual std::vector<std::string> splitCommand( std::string &a_rstrCommand ) const = 0;
    virtual std::vector<std::vector<std::string>> splitCommandByWord
                                                  ( const std::vector<std::string> &a_rstrCommandSequence ) const = 0;
};

#endif // ISPLITTER_HPP
