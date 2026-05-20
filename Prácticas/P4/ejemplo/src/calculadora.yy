%{
#include <iostream>
#include <fstream>
#include <string>
#include <FlexLexer.h>
using namespace std;
%}

%language "C++"
%require "3.2"
%defines "Parser.hpp"
%output "Parser.cpp"
 
%define api.parser.class {Parser}
%define api.namespace {calc}
%parse-param {Lexer* lexer}

%code requires
{
    namespace calc {
        class Lexer;
    } // namespace calc
} // %code requires
 
%code
{
 #include "Lexer.hpp"
 #define yylex(x) lexer->lex(x) // Referencia a 1 en Lexer.hpp
}

%union {
  struct { //declarado para manejar los tipos de número posibles: 1.- entero, 2.- flotante.
    int ival; //valor entero
    double fval; //valor flotante
    int tipo;
  } numero;
}

%token<numero> NUM
%token EOL

%left MAS
%left MIN
%left MUL
%left DIV
%right NEG

%nonassoc PARIZQ
%nonassoc PARDER

%type<numero> expresion

%start input

%%

input:
      /* vacío */
    | input linea
    ;

linea:
      expresion EOL {
          cout << "El valor de la expresión ya evaluada es: ";
          if($1.tipo == 1) {
              cout << $1.ival << endl;
          } else {
              cout << $1.fval << endl;
          }
      }
    | EOL
    ;

expresion:
      expresion MAS expresion {
        if($1.tipo == 2 || $3.tipo == 2) {
            $$.fval = ($1.tipo == 2 ? $1.fval : $1.ival) + ($3.tipo == 2 ? $3.fval : $3.ival);
            $$.tipo = 2;
        } else {
            $$.ival = $1.ival + $3.ival;
            $$.tipo = 1;
        }
      }
	  | expresion MIN expresion {
        if($1.tipo == 2 || $3.tipo == 2) {
            $$.fval = ($1.tipo == 2 ? $1.fval : $1.ival) - ($3.tipo == 2 ? $3.fval : $3.ival);
            $$.tipo = 2;
        } else {
            $$.ival = $1.ival - $3.ival;
            $$.tipo = 1;
        }
      }
	  | expresion MUL expresion {
        if($1.tipo == 2 || $3.tipo == 2) {
            $$.fval = ($1.tipo == 2 ? $1.fval : $1.ival) * ($3.tipo == 2 ? $3.fval : $3.ival);
            $$.tipo = 2;
        } else {
            $$.ival = $1.ival * $3.ival;
            $$.tipo = 1;
        }
      }
	  | expresion DIV expresion {
        $$.fval = ($1.tipo == 2 ? $1.fval : $1.ival) / ($3.tipo == 2 ? $3.fval : $3.ival);
        $$.tipo = 2;
      }
	  | MIN expresion %prec NEG {
                if($2.tipo == 2) {
                        $$.fval = -$2.fval;
                        $$.tipo = 2;
                } else {
                        $$.ival = -$2.ival;
                        $$.tipo = 1;
                }
            }
	  | PARIZQ expresion PARDER { $$ = $2; }
	  | NUM { $$ = $1; }
    ;

%%

void calc::Parser::error(const std::string& msg) {
    std::cerr << msg << '\n';
}


#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char *argv[]){
    if(argc < 2){
        cout<<"Faltan argumentos "<<endl;
        return EXIT_FAILURE;
    }
    filebuf fb;
    fb.open(string(argv[1]), ios::in);
    istream in(&fb);
    calc::Lexer lexer(&in);
    calc::Parser parser(&lexer);
    parser.parse();
    fb.close();
    return 0;
    /*
    calc::Lexer scanner{ std::cin, std::cerr };
    calc::Parser parser{ &scanner };
    //std::cout.precision(10);
    parser.parse();*/
}
