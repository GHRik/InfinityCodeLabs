#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include "Interface/iTranslator.hpp"
#include "Interface/iLogger.hpp"
#include "Utils/DataBaseCommand.hpp"
#include <algorithm>


class Translator : public iTranslator
{
public:
    Translator( const iLogger &a_roLogger );
    std::vector<utils::CommandStandardize> translateCommand
                                           (const std::vector<std::vector<std::string> > &a_rastrComandsSplitByWord);
private:
    const iLogger &m_roLogger;
    utils::dbCommand checkFirstWord( const std::string &a_rstrWord ) const;
    std::vector<std::string> makeParamCreate( const std::string &a_rstrWord ) const;
    std::vector<std::string> makeParamInsert( const std::string &a_rstrWord ) const;
    std::string makeParamWhere( const std::string &a_strWord ) const;
    Translator();
    Translator( const Translator& );
    Translator& operator=( const Translator& Translator );
};

#endif // TRANSLATOR_HPP
