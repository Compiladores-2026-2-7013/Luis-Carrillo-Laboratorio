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
%define api.namespace {C_1}
%define parse.error verbose
%parse-param {Lexer* lexer}

%code requires
{
    namespace C_1 {
        class Lexer;
    } // namespace C_1
} // %code requires
 
%code
{
 #include "Lexer.hpp"
 #define yylex(x) lexer->lex(x) // Referencia a 1 en Lexer.hpp
}

%union {
    struct {
        int ival;
        float fval;
        int tipo; /* 1 para int, 2 para float */
    } numero;
    char* cadena;
}

%token <numero> NUM
%token <cadena> ID
%token INT FLOAT_KW IF ELSE WHILE
%token PYC COMA IGUAL
%token MAS MIN MUL DIV PARIZQ PARDER

%start programa

%%

programa:
    declaraciones sentencias 
    { cout << "Regla: programa -> declaraciones sentencias" << endl; }
    ;

declaraciones:
    declaracion declaraciones_p
    { cout << "Regla: declaraciones -> declaracion declaraciones'" << endl; }
    ;

declaraciones_p:
    declaracion declaraciones_p
    | /* epsilon */
    ;

declaracion:
    tipo lista_var PYC
    { cout << "Regla: declaracion -> tipo lista_var ;" << endl; }
    ;

tipo:
    INT      { cout << "Regla: tipo -> int" << endl; }
    | FLOAT_KW { cout << "Regla: tipo -> float" << endl; }
    ;

lista_var:
    ID lista_var_p
    { cout << "Regla: lista_var -> identificador lista_var'" << endl; }
    ;

lista_var_p:
    COMA ID lista_var_p
    | /* epsilon */
    ;

sentencias:
    sentencia sentencias_p
    { cout << "Regla: sentencias -> sentencia sentencias'" << endl; }
    ;

sentencias_p:
    sentencia sentencias_p
    | /* epsilon */
    ;

sentencia:
    ID IGUAL suma_exp PYC
    { cout << "Regla: sentencia -> identificador = expresion ;" << endl; }
    | IF PARIZQ suma_exp PARDER sentencias ELSE sentencias
    { cout << "Regla: sentencia -> if ( expresion ) sentencias else sentencias" << endl; }
    | WHILE PARIZQ suma_exp PARDER sentencias
    { cout << "Regla: sentencia -> while ( expresion ) sentencias" << endl; }
    ;

suma_exp:
    mult_exp suma_exp_p
    ;

suma_exp_p:
    MAS mult_exp suma_exp_p
    | MIN mult_exp suma_exp_p
    | /* epsilon */
    ;

mult_exp:
    atom_exp mult_exp_p
    ;

mult_exp_p:
    MUL atom_exp mult_exp_p
    | DIV atom_exp mult_exp_p
    | /* epsilon */
    ;

atom_exp:
    ID
    { cout << "Regla: ()expresion -> identificador" << endl; }
    | NUM
    { cout << "Regla: ()expresion -> numero" << endl; }
    | PARIZQ suma_exp PARDER
    { cout << "Regla: ()expresion -> ( expresion )" << endl; }
    ;

%%

void C_1::Parser::error(const std::string& msg) {
    std::cerr << "Error de sintaxis en la línea " << lexer->lineno() << ": " << msg << '\n';
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
    C_1::Lexer lexer(&in);
    C_1::Parser parser(&lexer);
    parser.parse();
    fb.close();
    return 0;
}