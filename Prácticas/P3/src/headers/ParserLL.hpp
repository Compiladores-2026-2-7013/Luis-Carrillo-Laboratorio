#ifndef __PARSER_LL_HPP__
#define __PARSER_LL_HPP__
#include "Grammar.h"
#include "Symbols.hpp"
#include "Lexer.hpp"

#include <string>
#include <vector>
#include <map>
#include <stack>
using namespace std;

class ParserLL
{
private:
  Grammar grammar; //la gramática que debe reconocer nuestro analizador sintáctico
  Token token; //token actual 
  Lexer *lexer; //analizador léxico 
  map<NoTerm, map<Token, int>> table;//tabla de análisis sintáctico predictivo
  
public:
  ParserLL(Lexer *lexer); //constructor
  ~ParserLL(); //destructor
  
  void loadSyms(); //función para agregar todos los símbolos a la gramática (en grammar)
  void loadProds(); //función para cargar todas las producciones (en grammar)
  void loadTable(); //función para definir la tabla de análisis predictivo
  int parse(); //función con la implementación del algoritmo de análisis sintáctico
  
  void error(string msg); //función para impresión de errores sintácticos
  Token eat(); //consumo de entrada
  void aceptar(string msg); //función para impresión de mensaje de aceptación
};




#endif // !__PARSER_LL_HPP__
