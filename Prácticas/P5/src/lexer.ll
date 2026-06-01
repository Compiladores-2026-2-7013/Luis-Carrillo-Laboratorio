%{
    #include "Parser.hpp"
    #include "headers/Lexer.hpp"

    #define YY_DECL int C1::Lexer::lex(C1::Parser::semantic_type *yylval)
%}

%option c++ noyywrap outfile="Lexer.cpp" yyclass="Lexer"

DIG     [0-9]
LETTER  [a-zA-Z_]
ID      {LETTER}({LETTER}|{DIG})*
NUM     {DIG}+
WSPC    [ \t\r]+

%%

"def"       { return Parser::token::DEF; }
"int"       { return Parser::token::INT; }
"float"     { return Parser::token::FLOAT; }
"register"  { return Parser::token::REGISTER; }
";"         { return Parser::token::SEMICOLON; }
","         { return Parser::token::COMMA; }
"["         { return Parser::token::LBRACKET; }
"]"         { return Parser::token::RBRACKET; }
"{"         { return Parser::token::LBRACE; }
"}"         { return Parser::token::RBRACE; }
"("         { return Parser::token::LPAREN; }
")"         { return Parser::token::RPAREN; }

{NUM}       {
                yylval->ival = atoi(yytext);
                return Parser::token::NUM;
            }

{ID}        {
                yylval->sval = strdup(yytext);
                return Parser::token::ID;
            }

{WSPC}      { /* Ignorar espacios en blanco */ }
"\n"        { line++; }
.           { std::cerr << "Error léxico: carácter inesperado '" << yytext << "' en línea " << line << std::endl; }

<<EOF>>     { yyterminate(); }

%%


