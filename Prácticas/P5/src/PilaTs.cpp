#include "headers/PilaTs.hpp"

PilaTs::PilaTs() {}

PilaTs::~PilaTs() {
    // Liberar memoria de todas las tablas restantes en la pila
    while (!pila.empty()) {
        delete pila.top();
        pila.pop();
    }
}

// Empuja una nueva tabla de símbolos al tope
void PilaTs::push(SymTab* ts) {
    pila.push(ts);
}

// Retira y retorna la tabla del tope
SymTab* PilaTs::pop() {
    if (pila.empty()) {
        cerr << "Error: intentando pop en pila vacía." << endl;
        return nullptr;
    }
    SymTab* ts = pila.top();
    pila.pop();
    return ts;
}

// Obtiene la tabla del tope (alcance actual)
SymTab* PilaTs::top() {
    if (pila.empty()) {
        cerr << "Error: intentando top en pila vacía." << endl;
        return nullptr;
    }
    return pila.top();
}

// Obtiene la tabla del fondo (alcance global)
// Nota: stack no tiene acceso directo al fondo, usamos una técnica auxiliar
SymTab* PilaTs::bottom() {
    if (pila.empty()) {
        cerr << "Error: intentando bottom en pila vacía." << endl;
        return nullptr;
    }
    // Copiar temporalmente todos los elementos para acceder al fondo
    stack<SymTab*> aux;
    while (pila.size() > 1) {
        aux.push(pila.top());
        pila.pop();
    }
    SymTab* fondo = pila.top();
    // Restaurar la pila
    while (!aux.empty()) {
        pila.push(aux.top());
        aux.pop();
    }
    return fondo;
}

bool PilaTs::empty() {
    return pila.empty();
}

int PilaTs::size() {
    return pila.size();
}
