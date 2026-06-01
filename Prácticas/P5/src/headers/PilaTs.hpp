#ifndef PILATS_HPP
#define PILATS_HPP

#include <stack>
#include "SymTab.hpp"

using namespace std;

// Pila de tablas de símbolos para manejar alcances (scopes)
class PilaTs {
private:
    stack<SymTab*> pila;  // Pila de apuntadores a tablas de símbolos

public:
    PilaTs();
    ~PilaTs();

    // Empuja una nueva tabla de símbolos vacía (nuevo alcance)
    void push(SymTab* ts);

    // Retira la tabla del tope (salir de un alcance)
    // Retorna la tabla retirada (para poder usarla, ej: en struct)
    SymTab* pop();

    // Obtiene la tabla del tope (alcance actual)
    SymTab* top();

    // Obtiene la tabla del fondo (alcance global)
    SymTab* bottom();

    // Verifica si la pila está vacía
    bool empty();

    // Obtiene el tamaño de la pila
    int size();
};

#endif
