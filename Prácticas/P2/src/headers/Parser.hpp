#ifndef PARSER_H
#define PARSER_H
#include <string>
#include "Lexer.hpp"
#include "Symbols.hpp"
using namespace std;

namespace C_1
{
  /**
   * Parser sintáctico descendente recursivo.
   * Consume tokens del `Lexer` según la gramática definida en `Symbols.hpp`.
   */
  class Parser
  {

  private:
    Lexer *lexer;
    int token; // token actual 
    
  public:
    Parser();
    Parser(Lexer *lexer);
    ~Parser();
    
    // Símbolo inicial
    void programa();
    
    // Funciones del resto de NTs 
    void declaraciones();
    void declaraciones_prima();
    void declaracion();
    void tipo();
    void lista_var();
    void lista_var_prima();
    void sentencias();
    void sentencias_prima();
    void sentencia();
    void mas_expresion();
    void mas_expresion_prima();
    void mult_expresion();
    void mult_expresion_prima();
    void par_expresion();
    
    Token eat();
    void error(string msg);
    void parse();
  };    
    
}

#endif