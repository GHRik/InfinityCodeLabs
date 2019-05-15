#ifndef ISPLITTER_HPP
#define ISPLITTER_HPP


#include "Utils/ErrorsCode.hpp"
#include <string>
#include <vector>

class iSplitter
{
public:
    virtual ~iSplitter();
    virtual std::vector<std::string> splitCommand(std::string &str) = 0;
    virtual std::vector<std::vector<std::string>> splitCommandByWord( std::vector<std::string> &sequence ) = 0;
};

#endif // ISPLITTER_HPP
