#ifndef SYMTAB_HPP
#define SYMTAB_HPP

#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

// Estructura que representa un símbolo en la tabla de símbolos
struct Sym {
    int dir;           // Dirección de memoria (offset)
    int tipo;          // ID del tipo (referencia a TypeTab)
    string cat;        // Categoría: "var", "func", "param"
    vector<int> params; // Lista de tipos de parámetros (solo para funciones)

    Sym() : dir(0), tipo(0), cat("") {}
    Sym(int dir, int tipo, string cat) : dir(dir), tipo(tipo), cat(cat) {}
    Sym(int dir, int tipo, string cat, vector<int> params)
        : dir(dir), tipo(tipo), cat(cat), params(params) {}
};

class SymTab {
private:
    map<string, Sym> syms;  // Mapa de nombre → Sym

public:
    SymTab();

    // Agrega un símbolo a la tabla
    // Retorna true si se agregó exitosamente, false si ya existía
    bool addSym(string id, int dir, int tipo, string cat);

    // Versión para funciones (incluye lista de parámetros)
    bool addSym(string id, int dir, int tipo, string cat, vector<int> params);

    // Verifica si un identificador ya existe en la tabla
    bool existe(string id);

    // Obtiene la dirección de un símbolo
    int getDir(string id);

    // Obtiene el tipo de un símbolo
    int getType(string id);

    // Obtiene la categoría de un símbolo
    string getCat(string id);

    // Retorna el mapa completo de símbolos (para depuración/impresión)
    map<string, Sym> getSyms();

    // Imprime la tabla de símbolos (para depuración)
    void print();
};

#endif
