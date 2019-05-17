#ifndef ITRANSLATOR_HPP
#define ITRANSLATOR_HPP

#include "Utils/ErrorsCode.hpp"
#include "Utils/DataBaseCommand.hpp"
#include <vector>
#include <string>

class iTranslator
{
public:
    virtual ~iTranslator();
    virtual std::vector<utils::CommandStandardize> translateCommand
                                               ( const std::vector<std::vector<std::string>> &a_rastrcomandsSplitByWord ) = 0;
    virtual std::vector<std::string> splitCommand( std::string &a_rstrCommand ) const = 0;
    virtual std::vector<std::vector<std::string>> splitCommandByWord
                                                  ( const std::vector<std::string> &a_rstrCommandSequence ) const = 0;
    virtual std::vector<std::string> takeParam() = 0;
    virtual std::vector<std::string> takeField() = 0;

};

#endif // ITRANSLATOR_HPP
