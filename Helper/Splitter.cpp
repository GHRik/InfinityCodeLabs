#include "Splitter.hpp"

helper::Splitter::Splitter()
{

}

helper::Splitter::~Splitter()
{

}

std::vector<std::string> helper::Splitter::splitCommand(std::string &str)
{
    std::vector<std::string> test;
    std::string sequence = "";
    while( ' ' == *(str.begin()) )
    {
        str = str.substr(1, str.size());
    }

    while( ' ' == *(str.rbegin()) )
    {
        str = str.substr(0, str.size()-1);
    }
    //std::cout << str << std::endl;

    for( uint16_t iter = 0; iter < str.length(); ++iter)
    {
        sequence += str.at(iter);
        if( ';' == str.at(iter) )
        {
            test.push_back(sequence);
            sequence = "";
        }
    }
    for( uint16_t i = 0; i < test.size(); ++i)
    {
        //std::cout << test.at(i) << std::endl;
    }
    if( sequence.length() > 0 )
    {
        test.push_back("ERROR");
    }

    return test;
}

std::vector<std::vector<std::string> > helper::Splitter::splitCommandByWord(std::vector<std::string> &sequence)
{
    std::vector<std::string> words;
    std::vector<std::vector<std::string>> separeting;
    std::string word = "";
    bool quoteState = false;
    for( size_t i = 0; i < sequence.size(); ++i)
    {
        for( size_t iter = 0; iter < sequence.at(i).length(); ++iter )
        {

            if( sequence.at(i).at(iter) == '"' )
            {
                quoteState = !quoteState;
            }
            if( sequence.at(i).at(iter) == ' ' && false == quoteState )
            {
                if( word.length() > 0 )
                {
                    words.push_back(word);
                }
                word = "";
            }
            else
            {
                word += sequence.at(i).at(iter);
            }

        }
        if( word.length() > 0 )
        {
            words.push_back(word);
            word = "";
        }

        separeting.push_back(words);
        words.clear();

    }

    return separeting;
}
