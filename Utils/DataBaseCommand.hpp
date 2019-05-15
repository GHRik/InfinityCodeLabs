#ifndef DATABASECOMMAND_HPP
#define DATABASECOMMAND_HPP

#include <vector>
#include <string>

namespace utils
{
    enum dbCommand
    {
        CREATE,
        SELECT,
        DROP,
        INSERT_INTO,
        DELETE_FROM,
        UNDEFINED
    };

    struct CommandStandardize
    {
        utils::dbCommand command;
        std::string tableName;
        std::vector<std::string> params;
    };

}

#endif // DATABASECOMMAND_HPP
