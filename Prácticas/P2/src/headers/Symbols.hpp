#ifndef __SYMBOLS_HPP__
#define __SYMBOLS_HPP__

/** * 1. Definir en un comentario la gramática G(N, T, P, S)
 * G = (N, T, P, S)
 * N = { programa, declaraciones, declaraciones', declaracion, tipo, lista_var, lista_var', sentencias, sentencias', sentencia, +expresion, +expresion', *expresion, *expresion', ()expresion }
 * T = { int, float, identificador, numero, if, else, while, ;, ,, =, (, ), +, -, *, / }
 * P = {
 * programa -> declaraciones sentencias
 * declaraciones -> declaracion declaraciones'
 * declaraciones' -> declaracion declaraciones' | epsilon
 * declaracion -> tipo lista_var ;
 * tipo -> int | float
 * lista_var -> identificador lista_var'
 * lista_var' -> , identificador lista_var' | epsilon
 * sentencias -> sentencia sentencias'
 * sentencias' -> sentencia sentencias' | epsilon
 * sentencia -> identificador = +expresion ;
 *              | if ( +expresion ) sentencia else sentencia
 *              | while ( +expresion ) sentencia
 * +expresion -> *expresion +expresion'
 * +expresion' -> + *expresion +expresion' | - *expresion +expresion' | epsilon
 * *expresion -> ()expresion *expresion'
 * *expresion' -> * ()expresion *expresion' | / ()expresion *expresion' | epsilon
 * ()expresion -> identificador | numero | ( +expresion )
 * }
 * S = programa
 */

/**
 * 2. Determinar la enumeración para el conjunto T
 */
enum Token { 
    primero, t_eof, t_int, t_float, t_if, t_else, t_while, 
    t_id, t_num, t_pto_coma, t_coma, t_asignacion, t_par_izq, 
    t_par_der, t_suma, t_resta, t_mult, t_div 
};

/**
 * 3. Determinar la enumeración para el conjunto N
 */
enum NoTerm { 
    strEmpty, n_programa, n_declaraciones, n_declaraciones_prima, 
    n_declaracion, n_tipo, n_lista_var, n_lista_var_prima, 
    n_sentencias, n_sentencias_prima, n_sentencia, 
    n_mas_expresion, n_mas_expresion_prima, n_mult_expresion, 
    n_mult_expresion_prima, n_par_expresion 
};

#endif // !__SYMBOLS_HPP__