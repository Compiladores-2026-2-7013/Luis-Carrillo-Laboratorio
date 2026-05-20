%{
#include <sstream>
#include <cstdlib>

#include "Parser.hpp"
#include "Lexer.hpp"

using namespace std;

#undef YY_DECL // Buena práctica
#define YY_DECL int calc::Lexer::lex(calc::Parser::semantic_type *yylval) // Referencia a 1 en Lexer.hpp
%}

%option c++
%option noyywrap
%option outfile="Lexer.cpp"
%option yyclass="Lexer"


DIG [0-9]
WSPC [ \t\r]+
FLOAT {DIG}+"."{DIG}+

%%


"+"	{
	 cout << "Terminal + detectado" << endl;	
	 return Parser::token::MAS;
	}

"*"	{
	 cout << "Terminal * detectado" << endl;	
	 return Parser::token::MUL;
	}

"-"	{
	 cout << "Terminal - detectado" << endl;
	 return Parser::token::MIN;
	}

"/"	{
	 cout << "Terminal / detectado" << endl;
	 return Parser::token::DIV;
	}

"("	{
	 cout << "Terminal ( detectado" << endl;	
	 return Parser::token::PARIZQ;
	}

")"	{
	 cout << "Terminal ) detectado" << endl;	
	 return Parser::token::PARDER;
	}

\n	{
	 return Parser::token::EOL;
	}

{FLOAT}	{
	 cout << "Terminal flotante " << yytext << " detectado" << endl;
	 yylval->numero.fval = atof(yytext);
	 yylval->numero.tipo = 2; /* 1: Entero, 2: Flotante */
	 return Parser::token::NUM;
	}

{DIG}+	{
	 cout << "Terminal entero " << yytext << " detectado" << endl;
	 yylval->numero.ival = atoi(yytext);
	 yylval->numero.tipo = 1; /* 1: Entero, 2: Flotante */
	 return Parser::token::NUM;
	}

{WSPC}  { /* Ignoramos espacios en blanco */ }

.	{
	  cout << "Error léxico en la línea: " << yylineno << endl;
	}


<<EOF>> {	
		 if(!emittedEolAtEof) {
			 emittedEolAtEof = true;
			 return Parser::token::EOL;
		 }
		 yyterminate();
        }


%%

