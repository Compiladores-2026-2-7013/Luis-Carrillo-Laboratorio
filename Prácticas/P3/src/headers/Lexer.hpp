#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

class Lexer : public yyFlexLexer
{
public:
    Lexer(std::istream *in) : yyFlexLexer(in){};

    using FlexLexer::yylex;
    virtual int yylex();
    virtual int getLine();

private:
    const int ERROR = -1;
};

#endif /* __LEXER_HPP__ */