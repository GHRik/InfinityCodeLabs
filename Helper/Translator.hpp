#ifndef TRANSLATOR_HPP
#define TRANSLATOR_HPP

#include "Interface/iTranslator.hpp"
#include "Interface/iLogger.hpp"
#include "Interface/iFileManager.hpp"
#include "Utils/DataBaseCommand.hpp"
#include <algorithm>

namespace helper {
    ///
    /// \brief The Translator class is used to parse string. Translate means,
    /// this class translate a string to CommandStandarize. Class Can parse field name and param from string.
    /// \see CommandStandarize
    ///
    class Translator : public iTranslator
    {
    public:
        ///
        /// \brief Translator
        /// \param a_roLogger - const reference on iLogger to unable logging in class
        /// \param a_roFileManager - reference on iFileManager to unable use file with class.
        ///
        Translator( const iLogger &a_roLogger, iFileManager &a_roFileManager );

        ///
        /// \brief translateCommand - Make vector
        /// \param a_rastrComandsSplitByWord - vector of vector string. First diemension means a command number.
        /// Secound means a command splited by word( ready to translate to CommandStandarize )
        /// \return vector CommandStandarize to properly call callCommand
        /// \see callCommand
        ///
        std::vector<utils::CommandStandardize> translateCommand
                                            ( const std::vector<std::vector<std::string> > &a_rastrComandsSplitByWord );

        ///
        /// \brief splitCommand - used to split sequence from std::cin by command
        ///
        /// \details Example: std::string strCommand = "First comand; Secound Command;"
        /// \n splitCommand( strCommand  ).at(0) =  "First comand"
        /// \n splitCommand( strCommand  ).at(1) =  "Secound Command"
        ///
        /// \param a_rstrCommand - string with command from std::cin
        /// \return vector of command
        ///
        std::vector<std::string> splitCommand( std::string &a_rstrCommand ) const;

        ///
        /// \brief splitCommandByWord - used to split sequence splitCommand by command
        /// \param a_rstrCommandSequence - string with ONE command ready to be splited by word
        /// \details Example: std::string strSequence = "One command;"
        /// \n splitComandByWord( strSequence ).at(0) = "One"
        /// \n splitComandByWord( strSequence ).at(0) = "command"
        /// \return vector of vector string. First diemension means a command number.
        /// Secound means a command splited by word( ready to translate to CommandStandarize )
        /// \see splitCommand
        ///
        std::vector<std::vector<std::string> > splitCommandByWord
                                                ( const std::vector<std::string> &a_rstrCommandSequence ) const;

        ///
        /// \brief takeParam - used to take param from first line in file
        /// \return vector of param from table
        ///
        std::vector<std::string> takeParam( );

        ///
        /// \brief takeField - used to take field name from first line in file
        /// \return vector of field name from table
        ///
        std::vector<std::string> takeField( );

        ///
        /// \brief splitByExpectedField - read file by expected column
        ///
        /// \details Example: strFromFile = "1 2 3.5 "Test"" <- string readed from file
        /// \n whichParam = {0,3} <- expected field to print
        /// \n splitByExpectedField( whichParam, strFromFile ) = "1 "Test"" <- result
        ///
        ///
        /// \param a_rau16Line - number of which column will be taken from file
        /// \param a_rstrToSplit - a line from file to split by expected column
        /// \return string with expected param to print
        ///
        std::string splitByExpectedField( const std::vector<uint16_t> &a_rau16Line, const std::string &a_rstrToSplit );

    private:
        const iLogger &m_roLogger;
        iFileManager &m_roFileManager;

        Translator();
        explicit Translator( const Translator& a_roTranslator );
        Translator& operator=( const Translator& a_roTranslator );

        utils::dbCommand checkFirstWord( const std::string &a_rstrWord ) const;
        size_t splitByDelimeter(
                                const std::string &a_strTextToSplit,
                                std::vector<std::string> &a_rastrResult,
                                char a_chDelimeter
                                );
        std::vector<std::string> makeParamCreate( const std::string &a_rstrWord ) const;
        std::vector<std::string> makeParamInsert( const std::string &a_rstrWord ) const;
        std::string makeParamWhere( const std::string &a_strWord ) const;
        std::string splitByExpectedField( const std::vector<uint16_t> &a_rau16Line );
    };
}

#endif // TRANSLATOR_HPP
