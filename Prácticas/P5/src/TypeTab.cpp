#include "headers/TypeTab.hpp"

// Constructor: pre-carga los tipos primitivos
TypeTab::TypeTab() {
    // Tipo 0: int (4 bytes)
    types[0] = Type("int", 4);
    // Tipo 1: float (4 bytes)
    types[1] = Type("float", 4);
    // El siguiente ID disponible es 2
    nextId = 2;
}

// Obtiene el ID de un tipo por nombre
int TypeTab::getId(string name) {
    for (auto& par : types) {
        if (par.second.name == name) {
            return par.first;
        }
    }
    return -1;  // No encontrado
}

// ============================================================
// EJERCICIO 1: Implementar addArrayType
// ============================================================
// Agrega un tipo arreglo a la tabla de tipos
// Parámetros:
//   numElems: número de elementos del arreglo
//   tipoBase: ID del tipo base (ej: si es int[5], tipoBase = 0)
// Retorna: el ID del nuevo tipo creado
// Fórmula para tamaño: tam = numElems * getTam(tipoBase)
//
// Hint: Crear un Type con name="array", calcular tam, y guardarlo en types[nextId]
int TypeTab::addArrayType(int numElems, int tipoBase) {
    // TODO: Implementar
    int tamaño = numElems * getTam(tipoBase);  // 1. Calcular el tamaño: numElems * getTam(tipoBase)
    Type array("array", tamaño, numElems, tipoBase);  // 2. Crear un Type("array", tam, numElems, tipoBase)
    types[nextId] = array;  // 3. Almacenarlo en types[nextId]
    nextId++;  // 4. Incrementar nextId
    // 5. Retornar el ID asignado (nextId - 1)
    return nextId - 1; // Placeholder
}

// ============================================================
// EJERCICIO 1: Implementar addStructType
// ============================================================
// Agrega un tipo struct a la tabla de tipos
// Parámetros:
//   tam: tamaño total del struct (suma de tamaños de sus campos)
// Retorna: el ID del nuevo tipo creado
//
// Hint: Crear un Type con name="struct" y el tamaño dado
int TypeTab::addStructType(int tam) {
    // TODO: Implementar
    Type structType("struct", tam);  // 1. Crear un Type("struct", tam)
    types[nextId] = structType;  // 2. Almacenarlo en types[nextId]
    nextId++;  // 3. Incrementar nextId
    // 4. Retornar el ID asignado (nextId - 1)
    return nextId - 1; // Placeholder
}

// Obtiene el tamaño de un tipo dado su ID
int TypeTab::getTam(int id) {
    if (types.find(id) != types.end()) {
        return types[id].tam;
    }
    cerr << "Error: tipo con ID " << id << " no encontrado en tabla de tipos." << endl;
    return 0;
}

// Obtiene el nombre de un tipo dado su ID
string TypeTab::getName(int id) {
    if (types.find(id) != types.end()) {
        return types[id].name;
    }
    return "desconocido";
}

// Imprime la tabla de tipos
void TypeTab::print() {
    cout << "========== TABLA DE TIPOS ==========" << endl;
    cout << "ID\tNombre\t\tTam\tElems\tBase" << endl;
    cout << "----\t------\t\t---\t-----\t----" << endl;
    for (auto& par : types) {
        cout << par.first << "\t"
             << par.second.name << "\t\t"
             << par.second.tam << "\t"
             << par.second.numElems << "\t"
             << par.second.tipoBase << endl;
    }
    cout << "====================================" << endl;
}
