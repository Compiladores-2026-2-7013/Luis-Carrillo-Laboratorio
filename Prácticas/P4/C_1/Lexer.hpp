#ifndef __SCANNER_HPP__
#define __SCANNER_HPP__ 1

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

namespace C_1
{

    class Lexer : public yyFlexLexer
    {
    public:
        Lexer(std::istream *in) : yyFlexLexer(in)
        {
        };

        using FlexLexer::yylex;
        virtual int yylex();

    private:
        const int ERROR = -1;        
    };

}

#endif /* END __SCANNER_H__ */
