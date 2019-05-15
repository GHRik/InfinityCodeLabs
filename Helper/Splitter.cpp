#include "Splitter.hpp"

helper::Splitter::Splitter()
{

}

helper::Splitter::~Splitter()
{

}

std::vector<std::string> helper::Splitter::splitCommand( std::string &a_rstrCommand ) const
{
    std::vector<std::string> aResult;
    std::string strSequence = "";
    while( ' ' == *( a_rstrCommand.begin() ) )
    {
        a_rstrCommand = a_rstrCommand.substr( 1, a_rstrCommand.size() );
    }

    while( ' ' == *( a_rstrCommand.rbegin() ) )
    {
        a_rstrCommand = a_rstrCommand.substr( 0, a_rstrCommand.size()-1 );
    }

    for( uint16_t iter = 0; iter < a_rstrCommand.length(); ++iter)
    {

        strSequence += a_rstrCommand.at(iter);
        if( ';' == a_rstrCommand.at(iter) )
        {
            aResult.push_back( strSequence );
            strSequence = "";
        }
    }
    if( strSequence.length() > 0 )
    {
        aResult.push_back("ERROR");
    }

    return aResult;
}

std::vector<std::vector<std::string> > helper::Splitter::splitCommandByWord
                                                         ( const std::vector<std::string> &a_rstrCommandSequence ) const
{
    std::vector<std::string> strSeparateWords;
    std::vector<std::vector<std::string>> astrResult;
    std::string strTempWord = "";
    bool quoteState = false;
    for( size_t u16IterAllSequence = 0; u16IterAllSequence < a_rstrCommandSequence.size(); ++u16IterAllSequence)
    {
        for( uint16_t u16Iter = 0; u16Iter < a_rstrCommandSequence.at( u16IterAllSequence ).length(); ++u16Iter )
        {

            if( a_rstrCommandSequence.at( u16IterAllSequence ).at( u16Iter ) == '"' )
            {
                quoteState = !quoteState;
            }
            if( a_rstrCommandSequence.at( u16IterAllSequence ).at( u16Iter ) == ' ' && false == quoteState )
            {
                if( 0 < strTempWord.length() )
                {
                    strSeparateWords.push_back( strTempWord );
                }
                strTempWord = "";
            }
            else
            {
                strTempWord += a_rstrCommandSequence.at( u16IterAllSequence ).at( u16Iter );
            }

        }
        if( 0 < strTempWord.length() )
        {
            strSeparateWords.push_back( strTempWord );
            strTempWord = "";
        }

        astrResult.push_back( strSeparateWords );
        strSeparateWords.clear();

    }

    return astrResult;
}
