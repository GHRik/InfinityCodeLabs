#ifndef DATABASECOMMAND_HPP
#define DATABASECOMMAND_HPP

#include <vector>
#include <string>

namespace utils
{
///
/// \brief The dbCommand enum - stored all comand who can be used in input.
///
    enum dbCommand
    {
        CREATE,
        SELECT,
        DROP,
        INSERT_INTO,
        DELETE_FROM,
        UNDEFINED
    };

    ///
    /// \brief The CommandStandardize struct is used to change command from input on this standard.
    /// \details For example: strInput = "CREATE table (a:INTEGER);"
    /// \n in during program a CommandStandarize will be stored:
    /// \n command = CREATE
    /// \n tableName = table
    /// \n param = { a,INTEGER }
    ///
    struct CommandStandardize
    {
        ///
        /// \brief command - command to manage table from input
        ///
        utils::dbCommand command;

        ///
        /// \brief tableName - name of the table from input command
        ///
        std::string tableName;

        ///
        /// \brief params - for example field type and field name( in CREATE ) or value( in insert ), or WHERE param = param
        /// \warning WHERE param is stored as WHEREparam=param, but is not supported
        ///
        std::vector<std::string> params;
    };

    static std::vector<std::string> astrKeyWord =
                                                {
                                                 "CREATE",
                                                 "SELECT",
                                                 "DROP",
                                                 "INSERT",
                                                 "INTO",
                                                 "DELETE",
                                                 "FROM",
                                                 "TEMPORARY"
                                                };

}

#endif // DATABASECOMMAND_HPP
