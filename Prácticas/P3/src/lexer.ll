%{
#include <iostream>
#include <string>
using namespace std;

#include "headers/Symbols.hpp"
#include "headers/Lexer.hpp"

int line=1;
%}

%option c++
%option outfile="Lexer.cpp"
%option yyclass="Lexer"

%%

[ \t\r]+                 { /* Ignorar espacios, tabulaciones y retornos */ }
"\n"                     { line++; }

"int"                    { return t_int; }
"float"                  { return t_float; }
"if"                     { return t_if; }
"else"                   { return t_else; }
"while"                  { return t_while; }

[a-zA-Z_][a-zA-Z0-9_]* { return t_id; }
[0-9]+(\.[0-9]+)?        { return t_num; }

";"                      { return t_pto_coma; }
","                      { return t_coma; }
"="                      { return t_asignacion; }
"("                      { return t_par_izq; }
")"                      { return t_par_der; }
"+"                      { return t_suma; }
"-"                      { return t_resta; }
"*"                      { return t_mult; }
"/"                      { return t_div; }

<<EOF>>                  { return t_eof; }
.                        { cout << "ERROR LEXICO " << yytext << endl;}

%%

int yyFlexLexer::yywrap(){
    return 1;
}

int Lexer::getLine()
{
    return line;
}