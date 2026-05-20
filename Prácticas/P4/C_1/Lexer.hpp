#ifndef __LEXER_HPP__
#define __LEXER_HPP__

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

namespace C_1 { 
 
  class Lexer : public yyFlexLexer {
  public:
    Lexer(std::istream& arg_yyin, std::ostream& arg_yyout):
      yyFlexLexer(arg_yyin, arg_yyout), emittedEolAtEof(false) {};
    
    Lexer(std::istream* arg_yyin = nullptr, std::ostream* arg_yyout = nullptr):
      yyFlexLexer(arg_yyin, arg_yyout), emittedEolAtEof(false) {};
    
    int lex(Parser::semantic_type *yylval);

    bool emittedEolAtEof;
  };
 
} 

#endif /* __LEXER_HPP__ */
