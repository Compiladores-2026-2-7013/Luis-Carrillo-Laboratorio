#ifndef TYPETAB_HPP
#define TYPETAB_HPP

#include <string>
#include <map>
#include <iostream>

using namespace std;

// Estructura que representa un tipo en la tabla de tipos
struct Type {
    string name;       // Nombre del tipo (ej: "int", "float", "array", "struct")
    int tam;           // Tamaño en bytes
    int numElems;      // Número de elementos (para arreglos), -1 si no aplica
    int tipoBase;      // ID del tipo base (para arreglos), -1 si no aplica

    Type() : name(""), tam(0), numElems(-1), tipoBase(-1) {}
    Type(string name, int tam) : name(name), tam(tam), numElems(-1), tipoBase(-1) {}
    Type(string name, int tam, int numElems, int tipoBase)
        : name(name), tam(tam), numElems(numElems), tipoBase(tipoBase) {}
};

class TypeTab {
private:
    map<int, Type> types;   // Mapa de ID → Type
    int nextId;             // Siguiente ID disponible

public:
    // Constructor: pre-carga los tipos primitivos (int=0, float=1)
    TypeTab();

    // Obtiene el ID de un tipo por nombre (ej: "int" → 0, "float" → 1)
    // Retorna -1 si no se encuentra
    int getId(string name);

    // Agrega un tipo arreglo: arreglo de 'numElems' elementos de tipo 'tipoBase'
    // Retorna el ID asignado al nuevo tipo
    // tam = numElems * getTam(tipoBase)
    int addArrayType(int numElems, int tipoBase);

    // Agrega un tipo struct con su tamaño total
    // Retorna el ID asignado al nuevo tipo
    int addStructType(int tam);

    // Obtiene el tamaño de un tipo dado su ID
    int getTam(int id);

    // Obtiene el nombre de un tipo dado su ID
    string getName(int id);

    // Imprime la tabla de tipos (para depuración)
    void print();
};

#endif
