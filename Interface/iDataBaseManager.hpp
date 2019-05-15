#ifndef IDATAMANAGER_HPP
#define IDATAMANAGER_HPP

#include "Utils/ErrorsCode.hpp"
#include "Utils/DataBaseCommand.hpp"
#include <string>
#include <vector>

class iDataManager
{
public:
    virtual ~iDataManager();
    virtual utils::ErrorsCode addToCommandQueue( utils::dbCommand command, std::string tableName = "", std::vector<std::string> params = {} ) = 0;
};

#endif // IDATAMANAGER_HPP
