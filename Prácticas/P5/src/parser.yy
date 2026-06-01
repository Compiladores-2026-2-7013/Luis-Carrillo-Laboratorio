%language "C++"
%require "3.2"
%defines "headers/Parser.hpp"
%output "Parser.cpp"

%define api.parser.class {Parser}
%define api.namespace {C1}
%parse-param {Lexer* lexer}

%code requires {
    #include <string>
    #include <iostream>
    #include <vector>
    #include <stack>
    #include "Attributes.hpp"
    #include "TypeTab.hpp"
    #include "SymTab.hpp"
    #include "PilaTs.hpp"

    namespace C1 {
        class Lexer;
    }
}

%code {
    #include "headers/Lexer.hpp"

    // Definir yylex para que Bison llame a nuestro Lexer
    #define yylex(yylval) lexer->lex(yylval)

    // ========================================================
    // Variables globales del esquema de traducción
    // ========================================================
    TypeTab tablaTipos;         // Tabla de tipos global
    PilaTs pilaTs;             // Pila de tablas de símbolos
    std::stack<int> pilaDir;   // Pila de direcciones
    int dir = 0;               // Dirección actual de memoria

    // Variable auxiliar para propagar L.tipo (atributo heredado)
    int currentType = 0;

    // Variable para el tipo de retorno de funciones
    int tipoReturnFunc = 0;

    // Lista de tipos de parámetros (para F.lista)
    std::vector<int> listaParams;
}

// ========================================================
// Unión de valores semánticos
// ========================================================
%union {
    int ival;              // Para números enteros (NUM)
    char* sval;            // Para identificadores (ID)
    struct {
        int tipo;          // Tipo resultante
        int base;          // Tipo base (heredado en A)
    } attr;                // Para T, B, A
}

// ========================================================
// Tokens (terminales)
// ========================================================
%token <sval> ID
%token <ival> NUM
%token INT FLOAT REGISTER
%token DEF
%token SEMICOLON COMMA
%token LBRACKET RBRACKET LBRACE RBRACE LPAREN RPAREN

// ========================================================
// Tipos de los no-terminales
// ========================================================
%type <attr> T B A

// ========================================================
// Símbolo inicial
// ========================================================
%start P

%%

// ============================================================
// EJERCICIO 3: Implementar las acciones semánticas
// ============================================================

// P → D
// Regla semántica: dir ← 0, inicializar pila con tabla global
P : {
        // TODO: Implementar
        // 1. dir ← 0
        // 2. Crear nueva tabla de símbolos global: new SymTab()
        // 3. Empujarla en pilaTs: pilaTs.push(...)
        dir = 0;
        pilaTs.push(new SymTab());
    }
    D
    {
        // Al finalizar, imprimir resultados
        std::cout << std::endl;
        tablaTipos.print();
        std::cout << std::endl;
        std::cout << "Tabla de simbolos global:" << std::endl;
        pilaTs.top()->print();
    }
    ;

// D → T L ; D
//   | def T id ( F ) { S } D
//   | ε
D : T L SEMICOLON D
    {
        // Regla semántica: L.tipo = T.tipo
        // (ya se propagó vía currentType al reducir T)
    }
  // ----------------------------------------------------------------
  // D → def T id ( F ) { S } D
  // ----------------------------------------------------------------
  // Regla semántica:
  //   Si !PilaTs.bottom().existe(id):
  //     PilaTs.push(nuevaTs())
  //     PilaDir.push(dir)
  //     dir ← 0
  //     tipoReturnFunc ← T.tipo
  //     label(id)
  //     <ejecutar S>
  //     PilaTs.pop()
  //     PilaTs.bottom().add(id, -1, T.tipo, "func", F.lista)
  //   Sino: error("El id ya fue declarado anteriormente")
  | DEF T ID LPAREN F RPAREN
    {
        // TODO: Implementar (mid-rule action: antes de { S })
        string id = $3; // 1. Obtener id: string id = $3
       // 2. Verificar: if (!pilaTs.bottom()->existe(id))
        //    a) pilaTs.push(new SymTab())  ← nuevo alcance para la función
        //    b) pilaDir.push(dir)          ← guardar dir actual
        //    c) dir = 0                    ← reiniciar dir para la función
        //    d) tipoReturnFunc = $2.tipo   ← guardar tipo de retorno
        //    Nota: Aquí también se generaría label(id) si hubiera generación de código
        // 3. Sino: cerr << "Error: El id " << id << " ya fue declarado" << endl;

        id = $3;
        if (!pilaTs.bottom()->existe(id)) {
            pilaTs.push(new SymTab());
            pilaDir.push(dir);
            dir = 0;
            tipoReturnFunc = $2.tipo;
        } else {
            std::cerr << "Error: La función " << id << " ya fue declarada" << std::endl;
        }
    }
    LBRACE S RBRACE
    {
        // TODO: Implementar (después de { S })
        // 1. Obtener id: string id = $3
        // 2. SymTab* tsFunc = pilaTs.pop()   ← retirar tabla de la función
        //    (se podría guardar tsFunc para depuración)
        // 3. dir = pilaDir.top(); pilaDir.pop()  ← restaurar dir
        // 4. Registrar la función en alcance global:
        //    pilaTs.bottom()->addSym(id, -1, $2.tipo, "func", listaParams)
        // 5. listaParams.clear()             ← limpiar para la siguiente función

        std::string id = $3;
        // Solo registramos si no hubo error de colisión previa
        if (!pilaTs.bottom()->existe(id)) {
            pilaTs.pop(); // Retiramos la tabla de la función
            dir = pilaDir.top();
            pilaDir.pop(); // Restauramos el dir global
            
            // Registramos la función en el alcance global
            pilaTs.bottom()->addSym(id, -1, $2.tipo, "func", listaParams);
            listaParams.clear(); // Limpiamos la lista para futuras funciones
        }
        if ($3) free($3);
    }
    D
    {
        // Continuar con más declaraciones
    }
  | /* ε */
    {
        // Producción vacía, no hacer nada
    }
  ;

// T → B A
// Regla semántica: T.tipo = A.tipo, A.base = B.tipo
T : B A
    {
        // TODO: Implementar
        // 1. Propagar: $$.tipo = $2.tipo (A.tipo)
        // 2. Actualizar currentType para que L lo use
        //
        // Nota: A.base = B.tipo se propaga como atributo heredado.
        // En Bison, los heredados se manejan con variables globales
        // o acciones intermedias (mid-rule actions).
        $$.tipo = $2.tipo;
        currentType = $$.tipo;
    }
  // T → register { D }
  // Regla semántica:
  //   PilaTs.push(nuevaTs()), PilaDir.push(dir), dir ← 0
  //   <procesar D>
  //   ts* = PilaTs.pop()
  //   T.tipo = tablaTipos.add("struct", ts*)
  //   dir = PilaDir.top(); PilaDir.pop()
  | REGISTER LBRACE
    {
        // TODO: Implementar
        // 1. Empujar nueva tabla de símbolos: pilaTs.push(new SymTab())
        // 2. Guardar dir actual: pilaDir.push(dir)
        // 3. Reiniciar dir: dir ← 0
        pilaTs.push(new SymTab());
        pilaDir.push(dir);
        dir = 0;
    }
    D RBRACE
    {
        // TODO: Implementar
        // 1. El tamaño del struct es el valor actual de dir
        //    (dir acumuló los tamaños de los campos del struct)
        // 2. Retirar la tabla del struct: SymTab* tsStruct = pilaTs.pop()
        // 3. Registrar el struct en tablaTipos: tablaTipos.addStructType(dir)
        // 4. Restaurar dir: dir = pilaDir.top(); pilaDir.pop()
        // 5. Asignar $$.tipo con el ID del nuevo tipo struct
        // 6. Actualizar currentType
        pilaTs.pop(); // Retiramos la tabla del struct
        
        $$.tipo = tablaTipos.addStructType(dir);
        
        dir = pilaDir.top();
        pilaDir.pop(); 
        
        currentType = $$.tipo;
    }
  ;

// B → int
// Regla semántica: B.tipo = tablaTipos.getId("int")
B : INT
    {
        // TODO: Implementar
        // $$.tipo = tablaTipos.getId("int")
        // $$.base = $$.tipo (se usará como A.base)
        $$.tipo = tablaTipos.getId("int");
        $$.base = $$.tipo;
    }
  // B → float
  // Regla semántica: B.tipo = tablaTipos.getId("float")
  | FLOAT
    {
        // TODO: Implementar
        // $$.tipo = tablaTipos.getId("float")
        // $$.base = $$.tipo
        $$.tipo = tablaTipos.getId("float");
        $$.base = $$.tipo;
    }
  ;

// A → [ NUM ] A₁
// Regla semántica:
//   Si num.val > 0:
//     A.tipo = tablaTipos.addArrayType(num.val, A₁.tipo)
//     A₁.base = A.base
//   Sino: error
A : LBRACKET NUM RBRACKET A
    {
        // TODO: Implementar
        // 1. Verificar que $2 (NUM) > 0
        //    Si no: error("El índice debe ser mayor a cero")
        // 2. A₁.base ya se propagó (hereda de A.base → B.tipo)
        // 3. $$.tipo = tablaTipos.addArrayType($2, $4.tipo)
        //    donde $4.tipo es A₁.tipo
        // 4. $$.base = $1... (heredado, pero no se usa aquí)
        if ($2 > 0) {
            $$.tipo = tablaTipos.addArrayType($2, $4.tipo);
        } else {
            std::cerr << "Error: El índice del arreglo debe ser mayor a cero" << std::endl;
            $$.tipo = -1; 
        }
    }
  // A → ε
  // Regla semántica: A.tipo = A.base
  | /* ε */
    {
        // TODO: Implementar
        // A.tipo = A.base
        // Como A.base se hereda de B.tipo, y lo tenemos en la variable
        // global currentType (que se fijó en B), usamos:
        // $$.tipo = ??? (necesitamos el valor de B.tipo que llegó como heredado)
        //
        // Solución: Usar $0 o una variable global.
        // Aquí usamos $<attr>0.base (referencia al símbolo anterior en la pila)
        // O más simple: una variable global baseType
        $$.tipo = $<attr>0.base;
    }
  ;

// ----------------------------------------------------------------
// F → T id , F | T id | ε
// ----------------------------------------------------------------
// Regla semántica:
//   Agrega cada parámetro a la tabla de símbolos actual (la de la función)
//   y acumula los tipos en listaParams (F.lista)
F : T ID COMMA F
    {
        // TODO: Implementar
        // 1. string id = $2
        // 2. pilaTs.top()->addSym(id, dir, $1.tipo, "param")
        // 3. dir += tablaTipos.getTam($1.tipo)
        // 4. listaParams.push_back($1.tipo)
        std::string id = $2;
        pilaTs.top()->addSym(id, dir, $1.tipo, "param");
        dir += tablaTipos.getTam($1.tipo);
        listaParams.push_back($1.tipo);
        if ($2) free($2);
    }
  | T ID
    {
        // TODO: Implementar
        // 1. string id = $2
        // 2. pilaTs.top()->addSym(id, dir, $1.tipo, "param")
        // 3. dir += tablaTipos.getTam($1.tipo)
        // 4. listaParams.push_back($1.tipo)
        std::string id = $2;
        pilaTs.top()->addSym(id, dir, $1.tipo, "param");
        dir += tablaTipos.getTam($1.tipo);
        listaParams.push_back($1.tipo);
        if ($2) free($2);
    }
  | /* ε */
    {
        // Sin parámetros
    }
  ;

// ----------------------------------------------------------------
// S → (cuerpo de sentencias - simplificado para esta práctica)
// ----------------------------------------------------------------
// Nota: S es el cuerpo de la función. Para esta práctica se deja
// como producción vacía. En prácticas posteriores se expandirá
// con asignaciones, condicionales, ciclos, etc.
S : /* ε - placeholder para cuerpo de función */
    {
        // El cuerpo de sentencias se implementará en prácticas posteriores
    }
  ;

// L → L , id
// Regla semántica:
//   Si !PilaTs.top().existe(id):
//     PilaTs.top().add(id, dir, L.tipo, "var")
//     dir ← dir + tablaTipos.getTam(L.tipo)
//   Sino: error("La variable ya fue declarada")
L : L COMMA ID
    {
        // TODO: Implementar
        // 1. Obtener el id: string id = $3
        // 2. Verificar: if (!pilaTs.top()->existe(id))
        // 3. Si no existe: pilaTs.top()->addSym(id, dir, currentType, "var")
        //                   dir += tablaTipos.getTam(currentType)
        // 4. Si existe: cerr << "Error: La variable " << id << " ya fue declarada" << endl;
        //
        // Nota: L.tipo se propaga vía la variable global currentType
        std::string id = $3;
        if (!pilaTs.top()->existe(id)) {
            pilaTs.top()->addSym(id, dir, currentType, "var");
            dir += tablaTipos.getTam(currentType);
        } else {
            std::cerr << "Error: La variable " << id << " ya fue declarada" << std::endl;
        }
        if ($3) free($3);
    }
  // L → id
  // Regla semántica: (misma que arriba para un solo id)
  | ID
    {
        // TODO: Implementar
        // 1. Obtener el id: string id = $1
        // 2. Verificar: if (!pilaTs.top()->existe(id))
        // 3. Si no existe: pilaTs.top()->addSym(id, dir, currentType, "var")
        //                   dir += tablaTipos.getTam(currentType)
        // 4. Si existe: cerr << "Error: La variable " << id << " ya fue declarada" << endl;
        std::string id = $1;
        if (!pilaTs.top()->existe(id)) {
            pilaTs.top()->addSym(id, dir, currentType, "var");
            dir += tablaTipos.getTam(currentType);
        } else {
            std::cerr << "Error: La variable " << id << " ya fue declarada" << std::endl;
        }
        if ($1) free($1);
    }
  ;

%%

// Manejo de errores de Bison
void C1::Parser::error(const std::string& msg) {
    std::cerr << "Error de sintaxis: " << msg << std::endl;
}
