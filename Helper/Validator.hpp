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
    class Validator : public iValidate
    {
    public:
        Validator( const iLogger &a_roLogger );
        utils::ErrorsCode validateCommand(std::string &a_rstrCommand ) const;
        void prepareToValidate(std::string &a_rstrCommand);
        bool isWithoutError( const std::vector<std::string> &a_rastrCommands ) const;
        utils::ErrorsCode validateStandarizeCommand(utils::CommandStandardize &a_roCommand ) const;
    private:
        const iLogger &m_roLogger;
        void deleteRedundantSpace(std::string &a_rstrWord) const;
        utils::DbFieldType isRecognizedType(std::string &a_roType ) const;
        bool isVarcharType(const std::string &a_roTypeName) const;
        bool isNumber( const std::string &a_rstrWord ) const;
        bool isAlNum(const std::string &a_rstrWord) const;
        bool isValidTableName( const std::string &a_rstrTableName ) const;
        bool isValidFieldName (const std::string &a_rstrFieldeName ) const;
        bool isFieldNameKeyWord( const std::string &a_rstrWord) const;
        bool isFloat(std::string &a_rstrWord ) const;
        bool isInt(std::string &a_rstrWord ) const;
        bool isVarcharValid(std::string &a_rstrWord , const uint16_t sizeOfVarchar) const;

        Validator();
        Validator( const Validator& );
        Validator& operator=( const Validator& a_oValidate );

    public:
        bool isValidateParam(std::string a_strParamInBase, std::string &a_rstrParamInCommand);
    };
}


#endif // VALIDATOR_HPP
