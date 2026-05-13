%{
#include <iostream>
#include <string>
#include "Lexer.hpp"

#undef yylex
#define yylex lexer.lex

// Prototipo de la función de error
void yyerror(const char *s);

using namespace std;
%}

/* Configuración para generar una clase C++ */
%skeleton "lalr1.cc"
%require "3.2"
%defines
%define api.parser.class {Parser}
%define api.namespace {calc}
%parse-param { calc::Lexer& lexer }
%define parse.error detailed
%expect 6

/* Definición de los valores semánticos (yylval) */
%union {
    struct {
        int ival;
        float fval;
        int tipo; /* 1 para int, 2 para float */
    } numero;
    char* cadena;
}

/* Declaración de Terminales (Tokens) */
%token <numero> NUM
%token <cadena> ID
%token INT FLOAT_KW IF ELSE WHILE
%token PYC COMA IGUAL
%token MAS MIN MUL DIV PARIZQ PARDER

/* Símbolo inicial */
%start programa

%%

/* REGLAS DE LA GRAMÁTICA */

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

/* +expresion en tu gramática */
suma_exp:
    mult_exp suma_exp_p
    ;

/* +expresion' en tu gramática */
suma_exp_p:
    MAS mult_exp suma_exp_p
    | MIN mult_exp suma_exp_p
    | /* epsilon */
    ;

/* *expresion en tu gramática */
mult_exp:
    atom_exp mult_exp_p
    ;

/* *expresion' en tu gramática */
mult_exp_p:
    MUL atom_exp mult_exp_p
    | DIV atom_exp mult_exp_p
    | /* epsilon */
    ;

/* ()expresion en tu gramática */
atom_exp:
    ID
    { cout << "Regla: ()expresion -> identificador" << endl; }
    | NUM
    { cout << "Regla: ()expresion -> numero" << endl; }
    | PARIZQ suma_exp PARDER
    { cout << "Regla: ()expresion -> ( expresion )" << endl; }
    ;

%%

/* Definición de la función de error requerida por Bison */
void calc::Parser::error(const std::string& msg) {
    cerr << "Error sintáctico detectado: " << msg << endl;
}