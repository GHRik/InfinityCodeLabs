#ifndef VALIDATOR_HPP
#define VALIDATOR_HPP

#include "Interface/iLogger.hpp"
#include "Interface/iValidate.hpp"
#include <string>
#include "Utils/ErrorsCode.hpp"
#include "Utils/UsedType.hpp"
#include <cctype>
#include <algorithm>
#include <sstream>


namespace helper
{
    ///
    /// \brief The Validator class is used to validate table name, param, field name etc.
    ///
    class Validator : public iValidate
    {
    public:

        ///
        /// \brief Validator
        /// \param a_roLogger - reference on iLogger to enable logging
        ///
        explicit Validator( const iLogger &a_roLogger );

        ///
        /// \brief validateCommand - checking ; " ( )
        /// \param a_rstrCommand - if is problem with command , a_rstrCommand = "ERROR"
        /// \return ErrorCode OK if command is valid
        ///
        utils::ErrorsCode validateCommand(std::string &a_rstrCommand ) const;

        ///
        /// \brief prepareToValidate - delete redundant space or other redundant sign
        /// \param a_rstrCommand - entry command , out - clear command without redundant sign
        ///
        void prepareToValidate(std::string &a_rstrCommand);

        ///
        /// \brief isWithoutError - check if param dont have any ERROR.
        /// \param a_rastrCommands - vector of command
        /// \return false if is any ERROR in vector
        /// \see validateCommand
        ///
        bool isWithoutError( const std::vector<std::string> &a_rastrCommands ) const;

        ///
        /// \brief validateStandarizeCommand - check if all field in CommandStandarize if valid like tableName,
        /// number of param, is param is valid etc.
        /// \param a_roCommand
        /// \return ErrorCode OK if command is validate
        /// \see CommandStandardize
        ///
        utils::ErrorsCode validateStandarizeCommand(utils::CommandStandardize &a_roCommand ) const;


        ///
        /// \brief isValidateParam - check if inserting param is same type as param from table.
        /// \param a_strParamInBase - param read from table
        /// \param a_rstrParamInCommand - param who want be insert in table
        /// \return true if param is valid
        ///
        bool isValidateParam(std::string a_strParamInBase, std::string &a_rstrParamInCommand);


        ///
        /// \brief isValidateFieldName - checking if selected param from table can be selected
        /// \param a_strFieldNameBase - name in table
        /// \param a_strNameInCommand - name who want be selected
        /// \return true if field name is valid
        ///
        bool isValidateFieldName( const std::string &a_strFieldNameBase, const std::string &a_strNameInCommand );

    private:
        const iLogger &m_roLogger;
        void deleteRedundantSpace(std::string &a_rstrWord) const;
        utils::DbFieldType isRecognizedType(std::string &a_roType ) const;
        bool isVarcharType(const std::string &a_roTypeName) const;
        bool isNumber( const std::string &a_rstrWord ) const;
        bool isAlNum( const std::string &a_rstrWord ) const;
        bool isValidTableName( const std::string &a_rstrTableName ) const;
        bool isValidFieldName ( const std::string &a_rstrFieldeName ) const;
        bool isFieldNameKeyWord( const std::string &a_rstrWord) const;
        bool isFloat( std::string &a_rstrWord ) const;
        bool isInt( std::string &a_rstrWord ) const;
        bool isVarcharValid( std::string &a_rstrWord , const uint16_t u16SizeOfVarchar ) const;
        void makeVectorUnique( std::vector<std::string> &a_rastrVector ) const;

        explicit Validator();
        explicit Validator( const Validator& );
        Validator& operator=( const Validator& a_oValidate );

    };
}


#endif // VALIDATOR_HPP
