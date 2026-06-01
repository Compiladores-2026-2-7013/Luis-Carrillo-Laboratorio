#ifndef ATTRIBUTES_HPP
#define ATTRIBUTES_HPP

#include <string>
#include <vector>

using namespace std;

// Atributo para los no-terminales T, B y A
// Almacena el tipo resultante de la producción
struct AttrType {
    int tipo;   // ID del tipo en la tabla de tipos
    int base;   // Tipo base (usado como atributo heredado en A)
};

#endif
