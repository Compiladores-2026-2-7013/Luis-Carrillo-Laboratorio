#include "headers/ParserLL.hpp"


ParserLL::ParserLL(Lexer *lexer)
{
    this->lexer = lexer;
}

ParserLL::~ParserLL()
{
}


void ParserLL::loadSyms()
{
  /*********************************************
   * 4. Agregar todos los símbolos (N'∪T) de G'*
   *********************************************/
   grammar.addSymbol(primero, Symbol(primero));
   grammar.addSymbol(t_eof, Symbol(t_eof));
   grammar.addSymbol(t_int, Symbol(t_int));
   grammar.addSymbol(t_float, Symbol(t_float));
   grammar.addSymbol(t_if, Symbol(t_if));
   grammar.addSymbol(t_else, Symbol(t_else));
   grammar.addSymbol(t_while, Symbol(t_while));
   grammar.addSymbol(t_id, Symbol(t_id));
   grammar.addSymbol(t_num, Symbol(t_num));
   grammar.addSymbol(t_pto_coma, Symbol(t_pto_coma));
   grammar.addSymbol(t_coma, Symbol(t_coma));
   grammar.addSymbol(t_asignacion, Symbol(t_asignacion));
   grammar.addSymbol(t_par_izq, Symbol(t_par_izq));
   grammar.addSymbol(t_par_der, Symbol(t_par_der));
   grammar.addSymbol(t_suma, Symbol(t_suma));
   grammar.addSymbol(t_resta, Symbol(t_resta));
   grammar.addSymbol(t_mult, Symbol(t_mult));
   grammar.addSymbol(t_div, Symbol(t_div));

   int offset = 100; 

   grammar.addSymbol(n_programa + offset, Symbol(n_programa));
   grammar.addSymbol(n_declaraciones + offset, Symbol(n_declaraciones));
   grammar.addSymbol(n_declaraciones_prima + offset, Symbol(n_declaraciones_prima));
   grammar.addSymbol(n_declaracion + offset, Symbol(n_declaracion));
   grammar.addSymbol(n_tipo + offset, Symbol(n_tipo));
   grammar.addSymbol(n_lista_var + offset, Symbol(n_lista_var));
   grammar.addSymbol(n_lista_var_prima + offset, Symbol(n_lista_var_prima));
   grammar.addSymbol(n_sentencias + offset, Symbol(n_sentencias));
   grammar.addSymbol(n_sentencias_prima + offset, Symbol(n_sentencias_prima));
   grammar.addSymbol(n_sentencia + offset, Symbol(n_sentencia));
   grammar.addSymbol(n_mas_expresion + offset, Symbol(n_mas_expresion));      
   grammar.addSymbol(n_mas_expresion_prima + offset, Symbol(n_mas_expresion_prima));   
   grammar.addSymbol(n_mult_expresion + offset, Symbol(n_mult_expresion));      
   grammar.addSymbol(n_mult_expresion_prima + offset, Symbol(n_mult_expresion_prima));   
   grammar.addSymbol(n_par_expresion + offset, Symbol(n_par_expresion)); 
   grammar.start = n_programa + offset; 
   grammar.setNum(17, 15);           
}

void ParserLL::loadProds()
{
  /************************************************
   * 5. Agregar todas las producciones (P') de G' *
   ************************************************/  
    int offset = 100;

    // programa -> declaraciones sentencias
    grammar.addProd(1, Production(n_programa + offset, {n_declaraciones + offset, n_sentencias + offset}));

    // declaraciones -> declaracion declaraciones'
    grammar.addProd(2, Production(n_declaraciones + offset, {n_declaracion + offset, n_declaraciones_prima + offset}));
    // declaraciones' -> declaracion declaraciones'
    grammar.addProd(3, Production(n_declaraciones_prima + offset, {n_declaracion + offset, n_declaraciones_prima + offset}));
    // declaraciones' -> epsilon
    grammar.addProd(4, Production(n_declaraciones_prima + offset, {}));

    // declaracion -> tipo lista_var ;
    grammar.addProd(5, Production(n_declaracion + offset, {n_tipo + offset, n_lista_var + offset, t_pto_coma}));

    // tipo -> int
    grammar.addProd(6, Production(n_tipo + offset, {t_int}));
    // tipo -> float
    grammar.addProd(7, Production(n_tipo + offset, {t_float}));

    // lista_var -> identificador lista_var'
    grammar.addProd(8, Production(n_lista_var + offset, {t_id, n_lista_var_prima + offset}));
    // lista_var' -> , identificador lista_var'
    grammar.addProd(9, Production(n_lista_var_prima + offset, {t_coma, t_id, n_lista_var_prima + offset}));
    // lista_var' -> epsilon
    grammar.addProd(10, Production(n_lista_var_prima + offset, {}));

    // sentencias -> sentencia sentencias'
    grammar.addProd(11, Production(n_sentencias + offset, {n_sentencia + offset, n_sentencias_prima + offset}));
    // sentencias' -> sentencia sentencias'
    grammar.addProd(12, Production(n_sentencias_prima + offset, {n_sentencia + offset, n_sentencias_prima + offset}));
    // sentencias' -> epsilon
    grammar.addProd(13, Production(n_sentencias_prima + offset, {}));

    // sentencia -> identificador = +expresion ;
    grammar.addProd(14, Production(n_sentencia + offset, {t_id, t_asignacion, n_mas_expresion + offset, t_pto_coma}));
    // sentencia -> if ( +expresion ) sentencias else sentencias
    grammar.addProd(15, Production(n_sentencia + offset, {t_if, t_par_izq, n_mas_expresion + offset, t_par_der, n_sentencias + offset, t_else, n_sentencias + offset}));
    // sentencia -> while ( +expresion ) sentencias
    grammar.addProd(16, Production(n_sentencia + offset, {t_while, t_par_izq, n_mas_expresion + offset, t_par_der, n_sentencias + offset}));

    // +expresion -> *expresion +expresion'
    grammar.addProd(17, Production(n_mas_expresion + offset, {n_mult_expresion + offset, n_mas_expresion_prima + offset}));
    // +expresion' -> + *expresion +expresion'
    grammar.addProd(18, Production(n_mas_expresion_prima + offset, {t_suma, n_mult_expresion + offset, n_mas_expresion_prima + offset}));
    // +expresion' -> - *expresion +expresion'
    grammar.addProd(19, Production(n_mas_expresion_prima + offset, {t_resta, n_mult_expresion + offset, n_mas_expresion_prima + offset}));
    // +expresion' -> epsilon
    grammar.addProd(20, Production(n_mas_expresion_prima + offset, {}));

    // *expresion -> ()expresion *expresion'
    grammar.addProd(21, Production(n_mult_expresion + offset, {n_par_expresion + offset, n_mult_expresion_prima + offset}));
    // *expresion' -> * ()expresion *expresion'
    grammar.addProd(22, Production(n_mult_expresion_prima + offset, {t_mult, n_par_expresion + offset, n_mult_expresion_prima + offset}));
    // *expresion' -> / ()expresion *expresion'
    grammar.addProd(23, Production(n_mult_expresion_prima + offset, {t_div, n_par_expresion + offset, n_mult_expresion_prima + offset}));
    // *expresion' -> epsilon
    grammar.addProd(24, Production(n_mult_expresion_prima + offset, {}));

    // ()expresion -> identificador
    grammar.addProd(25, Production(n_par_expresion + offset, {t_id}));
    // ()expresion -> numero
    grammar.addProd(26, Production(n_par_expresion + offset, {t_num}));
    // ()expresion -> ( +expresion )
    grammar.addProd(27, Production(n_par_expresion + offset, {t_par_izq, n_mas_expresion + offset, t_par_der}));
}

void ParserLL::loadTable()
{
  /*************************************************
   ** 6.Cargar la tabla de AS predictivo      **
   *************************************************/
  
  // --- programa ---
    table[n_programa][t_int] = 1;
    table[n_programa][t_float] = 1;

  // --- declaraciones ---
    table[n_declaraciones][t_int] = 2;
    table[n_declaraciones][t_float] = 2;

  // --- declaraciones' ---
    table[n_declaraciones_prima][t_int] = 3;
    table[n_declaraciones_prima][t_float] = 3;
  // FOLLOW(declaraciones') = {t_id, t_if, t_while}
    table[n_declaraciones_prima][t_id] = 4;
    table[n_declaraciones_prima][t_if] = 4;
    table[n_declaraciones_prima][t_while] = 4;
  // --- declaracion ---
    table[n_declaracion][t_int] = 5;
    table[n_declaracion][t_float] = 5;

  // --- tipo ---
    table[n_tipo][t_int] = 6;
    table[n_tipo][t_float] = 7;
  // --- lista_var ---
    table[n_lista_var][t_id] = 8;

  // --- lista_var' ---
    table[n_lista_var_prima][t_coma] = 9;
    table[n_lista_var_prima][t_pto_coma] = 10; // epsilon

  // --- sentencias ---
    table[n_sentencias][t_id] = 11;
    table[n_sentencias][t_if] = 11;
    table[n_sentencias][t_while] = 11;

  // --- sentencias' ---
  // Resolución de colisión: Prioridad a la producción recursiva (12)
    table[n_sentencias_prima][t_id] = 12;
    table[n_sentencias_prima][t_if] = 12;
    table[n_sentencias_prima][t_while] = 12;
  // Producción epsilon (13) para los casos de salida
    table[n_sentencias_prima][t_eof] = 13;
    table[n_sentencias_prima][t_else] = 13;

  // --- sentencia ---
    table[n_sentencia][t_id] = 14;
    table[n_sentencia][t_if] = 15;
    table[n_sentencia][t_while] = 16;

  // --- +expresion (+expresion) ---
    table[n_mas_expresion][t_id] = 17;
    table[n_mas_expresion][t_num] = 17;
    table[n_mas_expresion][t_par_izq] = 17;

  // --- +expresion' (+expresion') ---
    table[n_mas_expresion_prima][t_suma] = 18;
    table[n_mas_expresion_prima][t_resta] = 19;
    table[n_mas_expresion_prima][t_pto_coma] = 20; // epsilon
    table[n_mas_expresion_prima][t_par_der] = 20;  // epsilon

  // --- *expresion (*expresion) ---
    table[n_mult_expresion][t_id] = 21;
    table[n_mult_expresion][t_num] = 21;
    table[n_mult_expresion][t_par_izq] = 21;

  // --- *expresion' (*expresion') ---
    table[n_mult_expresion_prima][t_mult] = 22;
    table[n_mult_expresion_prima][t_div] = 23;
    table[n_mult_expresion_prima][t_suma] = 24;      // epsilon
    table[n_mult_expresion_prima][t_resta] = 24;     // epsilon
    table[n_mult_expresion_prima][t_pto_coma] = 24;  // epsilon
    table[n_mult_expresion_prima][t_par_der] = 24;   // epsilon
  // --- ()expresion (()expresion) ---
    table[n_par_expresion][t_id] = 25;
    table[n_par_expresion][t_num] = 26;
    table[n_par_expresion][t_par_izq] = 27;
}

int ParserLL::parse()
{
  /**************************************************
   ** 7. Implementar el algoritmo de AS predictivo **
   **************************************************/

  loadSyms();
  loadProds();
  loadTable();

  stack<Symbol> pila;    
  
  // Apilamos el símbolo de fin de cadena ($) y luego el símbolo inicial (S)
  pila.push(grammar.getSym(t_eof));         
  pila.push(grammar.getSym(grammar.start));  

  // Obtenemos el primer token de la entrada (Lookahead)
  token = eat();

  // Ciclo principal del algoritmo hasta que la pila esté vacía
  while (!pila.empty()) 
  {
      Symbol X = pila.top();
      pila.pop();

      if (X.getType() == terminal) 
      {
          if (X.getToken() == token) 
          {
              // Si el token esperado coincide con la entrada
              if (token != t_eof) 
              {
                  token = eat(); // Consumimos el token y avanzamos el lexer
              }
          } 
          else 
          {
              error("Error sintáctico: Se esperaba un terminal diferente en la entrada.");
          }
      } 
      else 
      {
          NoTerm A = X.getNoTerm();

          if (table.count(A) && table[A].count(token)) 
          {
              int prodId = table[A][token];
              Production p = grammar.getProd(prodId);
              vector<int> body = p.getBody();

              for (int i = (int)body.size() - 1; i >= 0; --i) 
              {
                  pila.push(grammar.getSym(body[i]));
              }
          } 
          else 
          {
            // No se encontró una producción válida
              error("Error de sintaxis.");
          }
      }
  }

  aceptar("Cadena aceptada.");
  return 0;
}

void ParserLL::error(string msg)
{
    cout<<msg<<endl;
    exit(EXIT_FAILURE);
}

Token ParserLL::eat()
{
    return (Token) lexer->yylex();    
}

void ParserLL::aceptar(string msg)
{
    cout<<msg<<endl;
}
