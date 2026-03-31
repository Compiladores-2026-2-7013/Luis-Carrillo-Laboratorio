#include "headers/Parser.hpp"
#include <iostream>

namespace C_1
{
  Parser::Parser(/* args */)
  {
  }

  Parser::Parser(Lexer *lexer)
  {
    this->lexer = lexer;
  }
    
  Parser::~Parser()
  {
  }

  void Parser::programa(){
    // Símbolo inicial
    declaraciones();
    sentencias();
  }

  /************************************************************************/
  /**                                                                    **/
  /**                       Funciones por cada NT                        **/
  /**                                                                    **/
  /************************************************************************/


  Token Parser::eat(){
    // Consume y devuelve el siguiente token del lexer
    return (Token) lexer->yylex();
  }

  void Parser::error(string msg){
    cout << "ERROR DE SINTAXIS: " << msg << " en la línea "<< lexer->getLine() <<endl;
  }   

  void Parser::parse(){
    // Punto de entrada del análisis sintáctico
    token = eat();
    programa();
    if(token == t_eof)
      cout << "La cadena es aceptada" << endl;
    else 
      cout << "La cadena no pertenece al lenguaje generado por la gramática" << endl;
  }

  void Parser::declaraciones(){
    // declaraciones -> declaracion declaraciones' | epsilon
    if(token == t_int || token == t_float){
      declaracion();
      declaraciones_prima();
    }
  }

  void Parser::declaraciones_prima(){
    // declaraciones' -> declaracion declaraciones' | epsilon
    if(token == t_int || token == t_float){
      declaracion();
      declaraciones_prima();
    }
  }

  void Parser::declaracion(){
    tipo();
    lista_var();
    if(token == t_pto_coma) token = eat();
    else error("Se esperaba ;");
  }

  void Parser::tipo(){
    if(token == t_int) token = eat();
    else if(token == t_float) token = eat();
    else error("Se esperaba un tipo de dato (int o float)");
  }

  void Parser::lista_var(){
    if(token == t_id) token = eat();
    else error("Se esperaba un identificador");
    lista_var_prima();
  }

  void Parser::lista_var_prima(){
    if(token == t_coma){
      token = eat();
      if(token == t_id) token = eat();
      else error("Se esperaba un identificador");
      lista_var_prima();
    }
  }

  void Parser::sentencias(){
    // sentencias -> sentencia sentencias' | epsilon
    if(token == t_id || token == t_if || token == t_while){
      sentencia();
      sentencias_prima();
    }
  }

  void Parser::sentencias_prima(){
    // sentencias' -> sentencia sentencias' | epsilon
    if(token == t_id || token == t_if || token == t_while){
      sentencia();
      sentencias_prima();
    }
  }

  void Parser::sentencia(){
    // sentencia -> asignación | if-else | while
    if(token == t_id){
      token = eat();
      if(token == t_asignacion) token = eat();
      else error("Se esperaba =");
      
      mas_expresion();
      
      if(token == t_pto_coma) token = eat();
      else error("Se esperaba ;");
    } 
    else if(token == t_if){
      token = eat();
      if(token == t_par_izq) token = eat();
      else error("Se esperaba (");
      
      mas_expresion();
      
      if(token == t_par_der) token = eat();
      else error("Se esperaba )");
      
      sentencia();
      
      if(token == t_else){
        token = eat();
        sentencia();
      } else {
        error("Se esperaba else");
      }
    } 
    else if(token == t_while){
      token = eat();
      if(token == t_par_izq) token = eat();
      else error("Se esperaba (");
      
      mas_expresion();
      
      if(token == t_par_der) token = eat();
      else error("Se esperaba )");
      
      sentencia();
    } 
    else {
      error("Error en la sentencia");
    }
  }

  void Parser::mas_expresion(){
    // +expresion -> *expresion +expresion'
    mult_expresion();
    mas_expresion_prima();
  }

  void Parser::mas_expresion_prima(){
    if(token == t_suma || token == t_resta){
      token = eat();
      mult_expresion();
      mas_expresion_prima();
    }
  }

  void Parser::mult_expresion(){
    // *expresion -> ()expresion *expresion'
    par_expresion();
    mult_expresion_prima();
  }

  void Parser::mult_expresion_prima(){
    if(token == t_mult || token == t_div){
      token = eat();
      par_expresion();
      mult_expresion_prima();
    }
  }

  void Parser::par_expresion(){
    // ()expresion -> identificador | numero | ( +expresion )
    if(token == t_id){
      token = eat();
    } else if(token == t_num){
      token = eat();
    } else if(token == t_par_izq){
      token = eat();
      mas_expresion();
      if(token == t_par_der) token = eat();
      else error("Se esperaba )");
    } else {
      error("Se esperaba un identificador, numero o (");
    }
  }

}
