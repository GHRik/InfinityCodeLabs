#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include "Interface/iTranslator.hpp"
#include "Interface/iLogger.hpp"
#include "Utils/DataBaseCommand.hpp"
#include <algorithm>


class Translator : public iTranslator
{
public:
    Translator( iLogger &a_roLogger );
    std::vector<utils::CommandStandardize> translateCommand(std::vector<std::vector<std::string> > comandsSplitByWord);
private:
    iLogger &m_roLogger;
    utils::dbCommand checkFirstWord( std::string word );
    std::vector<std::string> makeParamCreate( std::string word );
    std::vector<std::string> makeParamInsert( std::string word );
    std::vector<std::string> makeParamSelect( std::string word);
    std::string makeParamWhere( std::string word );
};

#endif // TRANSLATOR_HPP
