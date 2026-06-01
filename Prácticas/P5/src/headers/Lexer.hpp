#ifndef LEXER_HPP
#define LEXER_HPP

#if !defined(yyFlexLexerOnce)
#include "FlexLexer.h"
#endif

#include "Parser.hpp"

namespace C1 {

class Lexer : public yyFlexLexer {
public:
    Lexer(std::istream& arg_yyin, std::ostream& arg_yyout)
        : yyFlexLexer(arg_yyin, arg_yyout) {};
    Lexer(std::istream* arg_yyin = nullptr, std::ostream* arg_yyout = nullptr)
        : yyFlexLexer(arg_yyin, arg_yyout) {};

    // Método lex que retorna tokens al parser Bison
    int lex(Parser::semantic_type *yylval);

private:
    int line = 1;
};

}

#endif
