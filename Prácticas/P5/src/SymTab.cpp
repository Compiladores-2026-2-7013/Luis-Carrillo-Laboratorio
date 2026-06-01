#include "headers/SymTab.hpp"

SymTab::SymTab() {}

// ============================================================
// EJERCICIO 2: Implementar addSym
// ============================================================
// Agrega un símbolo a la tabla de símbolos
// Parámetros:
//   id:   nombre del identificador
//   dir:  dirección de memoria asignada
//   tipo: ID del tipo (referencia a TypeTab)
//   cat:  categoría ("var", "func", "param")
// Retorna: true si se agregó, false si ya existía
//
// Hint: Verificar primero con existe(id), si no existe, insertar en el mapa
bool SymTab::addSym(string id, int dir, int tipo, string cat) {
    // TODO: Implementar
    if(existe(id)) {
        return false; // 2. Si ya existe, retornar false
    } else {
        Sym nuevoSimbolo(dir, tipo, cat); // 3. Si no existe, crear un Sym(dir, tipo, cat)
        syms[id] = nuevoSimbolo; // e insertarlo en syms[id]
        return true; // 4. Retornar true
    }
    return false; // Placeholder
}

// Versión para funciones (incluye lista de parámetros)
bool SymTab::addSym(string id, int dir, int tipo, string cat, vector<int> params) {
    // TODO: Implementar (similar al anterior pero usando el constructor con params)
    if(existe(id)) {
        return false; 
    } else {
        Sym nuevoSimbolo(dir, tipo, cat, params);
        syms[id] = nuevoSimbolo; 
        return true; 
    }
    return false; // Placeholder
}

// ============================================================
// EJERCICIO 2: Implementar existe
// ============================================================
// Verifica si un identificador ya existe en esta tabla de símbolos
// Parámetros:
//   id: nombre del identificador a buscar
// Retorna: true si existe, false si no
//
// Hint: Usar find() del map y comparar con syms.end()
bool SymTab::existe(string id) {
    // TODO: Implementar
    if(syms.find(id) != syms.end()) {
        return true; 
    }
    // Usar: syms.find(id) != syms.end()
    return false; // Placeholder
}

// Obtiene la dirección de un símbolo
int SymTab::getDir(string id) {
    if (existe(id)) {
        return syms[id].dir;
    }
    cerr << "Error: símbolo '" << id << "' no encontrado." << endl;
    return -1;
}

// Obtiene el tipo de un símbolo
int SymTab::getType(string id) {
    if (existe(id)) {
        return syms[id].tipo;
    }
    cerr << "Error: símbolo '" << id << "' no encontrado." << endl;
    return -1;
}

// Obtiene la categoría de un símbolo
string SymTab::getCat(string id) {
    if (existe(id)) {
        return syms[id].cat;
    }
    return "";
}

// Retorna el mapa completo
map<string, Sym> SymTab::getSyms() {
    return syms;
}

// Imprime la tabla de símbolos
void SymTab::print() {
    cout << "========== TABLA DE SIMBOLOS ==========" << endl;
    cout << "Nombre\t\tDir\tTipo\tCat" << endl;
    cout << "------\t\t---\t----\t---" << endl;
    for (auto& par : syms) {
        cout << par.first << "\t\t"
             << par.second.dir << "\t"
             << par.second.tipo << "\t"
             << par.second.cat << endl;
    }
    cout << "========================================" << endl;
}
