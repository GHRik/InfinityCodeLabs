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

};

#endif // ITRANSLATOR_HPP
