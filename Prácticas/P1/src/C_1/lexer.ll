%{
#include <iostream>
#include <string>
using namespace std;

#include "tokens.hpp"
#include "Lexer.hpp"

%}

%option c++
%option outfile="Lexer.cpp"
%option yyclass="C_1::Lexer"
%option case-insensitive

/* Definiciones de expresiones regulares */
DIG     [0-9]
LETRA   [a-zA-Z_]
ID      {LETRA}({LETRA}|{DIG})*
NUM     {DIG}+("."{DIG}+)?(e[+-]?{DIG}+)?
ESPACIO [ \t\n\r]

%%

{ESPACIO}   { }

"if"        { return IF; }
"else"      { return ELSE; }
"while"     { return WHILE; }
"int"       { return INT; }
"float"     { return FLOAT; }

{ID}        { return ID; }
{NUM}       { return NUMERO; }

";"         { return PYC; }
","         { return COMA; }
"("         { return LPAR; }
")"         { return RPAR; }

"+"         { return MAS; }
"-"         { return MENOS; }
"*"         { return MUL; }
"/"         { return DIV; }
"="         { return ASIG; }

.           { cout << "Error lexico: " << yytext << endl; }

%%

int yyFlexLexer::yywrap(){
    return 1;
}