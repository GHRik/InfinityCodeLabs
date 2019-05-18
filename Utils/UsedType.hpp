#ifndef USEDTYPE_HPP
#define USEDTYPE_HPP

namespace utils
{

///
/// \brief The DbFieldType enum - store all type which can by used in table
///
    enum DbFieldType
    {  
        INTEGER,
        FLOAT,
        BOOL,
        VARCHAR,
        UNKNOWN,
    };

    enum Standarize
    {
        MIN_VARCHAR_SIZE = 1,
        MAX_VARCHAR_SIZE = 255
    };

}


#endif // USEDTYPE_HPP
