#ifndef GRAMMAR_H
#define GRAMMAR_H

#include <string>
#include <vector>
#include <map>
using namespace std;

#include "Symbol.h"
#include "Production.h"

/**
 * Clase para representar una gramática
 */
class Grammar
{
public:
  map<int, Symbol> syms; //conjunto de símbolos N U T 
  int term, noTerm; //número terminales y no terminales 
  int start; //start es la llave para el símbolo inicial en syms S 
  map<int, Production>  prods; //conjunto de producciones P

public:
  Grammar(/* args */);
  ~Grammar();
  void setNum(int term, int noTerm); //asigna los miembros term y noTerm
  void addSymbol(int i, Symbol s); //añade símbolo a la gramática (llave, valor) en syms
  void addProd(int i, Production p); //agrega una producción a la gramática (llave, valor) en prods
  Symbol getSym(int i); //obtener un símbolo de syms
  Production getProd(int i); //obtener una producción de prods
};




#endif // !GRAMMAR_H
