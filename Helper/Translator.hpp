#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include "Interface/iTranslator.hpp"
#include "Interface/iLogger.hpp"
#include "Interface/iFileManager.hpp"
#include "Utils/DataBaseCommand.hpp"
#include <algorithm>

namespace helper {

    class Translator : public iTranslator
    {
    public:
        explicit Translator( const iLogger &a_roLogger, iFileManager &a_roFileManager );
        std::vector<utils::CommandStandardize> translateCommand
        (const std::vector<std::vector<std::string> > &a_rastrComandsSplitByWord);
        std::vector<std::string> splitCommand(std::string &a_rstrCommand) const;
        std::vector<std::vector<std::string> > splitCommandByWord(const std::vector<std::string> &a_rstrCommandSequence) const;
        std::vector<std::string> takeParam( );
        std::vector<std::string> takeField( );
        std::string splitByExpectedField(const std::vector<uint16_t> &a_rau16Line, const std::string &a_rstrToSplit);
    private:
        const iLogger &m_roLogger;
        iFileManager &m_roFileManager;
        utils::dbCommand checkFirstWord( const std::string &a_rstrWord ) const;
        size_t splitByDelimeter(
                                const std::string &a_strTextToSplit,
                                std::vector<std::string> &a_rastrResult,
                                char a_chDelimeter
                                );
        std::vector<std::string> makeParamCreate( const std::string &a_rstrWord ) const;
        std::vector<std::string> makeParamInsert( const std::string &a_rstrWord ) const;
        std::string makeParamWhere( const std::string &a_strWord ) const;
        explicit Translator();
        explicit Translator( const Translator& );
        Translator& operator=( const Translator& Translator );

        std::string splitByExpectedField(const std::vector<uint16_t> &a_rau16Line);
    };
}

#endif // TRANSLATOR_HPP
