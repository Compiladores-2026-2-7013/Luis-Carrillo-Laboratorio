%{
#include <sstream>
#include <cstdlib>
#include <string>

#include "Parser.hpp"
#include "Lexer.hpp"

using namespace std;

#undef YY_DECL // Buena práctica
#define YY_DECL int calc::Lexer::lex(calc::Parser::semantic_type *yylval) // Asegúrate de que el namespace corresponda al de tu proyecto
%}

%option c++
%option noyywrap
%option outfile="Lexer.cpp"
%option yyclass="Lexer"
%option yylineno

/* Expresiones Regulares */
DIG     [0-9]
LETRA   [a-zA-Z_]
IDENT   {LETRA}({LETRA}|{DIG})*
WSPC    [ \t\r\n]+
FLOAT   {DIG}+"."{DIG}+

%%

"int"   {
         cout << "Terminal int detectado" << endl;
         return Parser::token::INT;
        }

"float" {
         cout << "Terminal float detectado" << endl;
         return Parser::token::FLOAT; 
        }

"if"    {
         cout << "Terminal if detectado" << endl;
         return Parser::token::IF;
        }

"else"  {
         cout << "Terminal else detectado" << endl;
         return Parser::token::ELSE;
        }

"while" {
         cout << "Terminal while detectado" << endl;
         return Parser::token::WHILE;
        }

";"     {
         cout << "Terminal ; detectado" << endl;
         return Parser::token::PYC;
        }

","     {
         cout << "Terminal , detectado" << endl;
         return Parser::token::COMA;
        }

"="     {
         cout << "Terminal = detectado" << endl;
         return Parser::token::IGUAL;
        }

"+"     {
         cout << "Terminal + detectado" << endl;    
         return Parser::token::MAS;
        }

"*"     {
         cout << "Terminal * detectado" << endl;    
         return Parser::token::MUL;
        }

"-"     {
         cout << "Terminal - detectado" << endl;
         return Parser::token::MIN;
        }

"/"     {
         cout << "Terminal / detectado" << endl;
         return Parser::token::DIV;
        }

"("     {
         cout << "Terminal ( detectado" << endl;    
         return Parser::token::PARIZQ;
        }

")"     {
         cout << "Terminal ) detectado" << endl;    
         return Parser::token::PARDER;
        }

{FLOAT} {
         cout << "Terminal flotante " << yytext << " detectado" << endl;
         yylval->numero.fval = atof(yytext);
         yylval->numero.tipo = 2; /* 1: Entero, 2: Flotante */
         return Parser::token::NUM;
        }

{DIG}+  {
         cout << "Terminal entero " << yytext << " detectado" << endl;
         yylval->numero.ival = atoi(yytext);
         yylval->numero.tipo = 1; /* 1: Entero, 2: Flotante */
         return Parser::token::NUM;
        }

{IDENT} {
         cout << "Terminal identificador " << yytext << " detectado" << endl;
         return Parser::token::ID;
        }

{WSPC}  { 
         /* Ignoramos espacios en blanco, tabuladores y saltos de línea */ 
        }

.       {
         cout << "Error léxico en la línea: " << yylineno << " Token no reconocido: " << yytext << endl;
        }

<<EOF>> {   
         yyterminate();
        }

%%