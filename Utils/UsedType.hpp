#ifndef USEDTYPE_HPP
#define USEDTYPE_HPP

namespace utils
{

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
