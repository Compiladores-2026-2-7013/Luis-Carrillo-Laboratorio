#include "headers/Grammar.h"

Grammar::Grammar(/* args */)
{
}

Grammar::~Grammar()
{
}

/*
 * Añade un símbolo a la gramática
 */
void Grammar::addSymbol(int i, Symbol s)
{
    syms[i] = s;
}

/*
 * Agrega una producción a la gramática
 * @param i indica el número de producción
 * @param p la producción para agregar
 */
void Grammar::addProd(int i, Production p)
{
    prods[i] = p;
}

/*
 * Devuelve un símbolo
 * @param i el número del símbolo a devolver
 * @return el símbolo i dentro del conjunto de símbolos
 */
Symbol Grammar::getSym(int i)
{
    return syms[i];
}

/*
 * Devuelve una producción
 * @param i el número de la producción a devolver
 * @return la producción i dentro del conjunto de producciones
 */
Production Grammar::getProd(int i)
{
    return prods[i];
}

/**
 * Asigna los atributos miembro term y noTerm.
 * @param term número de terminales
 * @param noTerm número de no-terminales
 */
void Grammar::setNum(int term, int noTerm)
{
    this->term = term;
    this->noTerm = noTerm;
}
