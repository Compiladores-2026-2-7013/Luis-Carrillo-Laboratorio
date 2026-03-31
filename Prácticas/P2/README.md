<p  align="center">
  <img  width="200"  src="https://www.fciencias.unam.mx/sites/default/files/logoFC_2.png"  alt="">  <br>Compiladores  2026-2 <br>
  Práctica 1: Analizadores léxicos con Lex (Flex) <br> Profesora: Ariel Adara Mercado Martínez
</p>


# Análisis sintáctico descendente

## Objetivo:
Que el alumno conozca e implemente los principios del análisis sintáctico descendente recursivo, aplicando técnicas de transformación de gramáticas —eliminación de ambigüedad, eliminación de recursividad izquierda y 
factorización izquierda— para construir un analizador sintáctico predictivo que, junto con el analizador léxico desarrollado con Flex, permita reconocer programas válidos del lenguaje C_1.


### Estructura del directorio
```c++
p3
├── README.md
└── src //carpeta de código
    ├── headers
    │   ├── Lexer.hpp   //header de la clase Lexer
    │   ├── Parser.hpp  //header de la clase Parser
    │   └── Symbols.hpp //definición de símbolos
    ├── lexer.ll        //definición del an. léxico
    ├── main.cpp        //contiene la función principal del programa
    ├── Makefile        //boceto de Makefile (no funciona aún)
    ├── Parser.cpp      //código fuente de la clase Parser
    └── prueba          ////archivo de entrada para el analizador (léxico y sintáctico)
```

### Uso

#### Compilación

```bash
$ cd src/
$ flex++ lexer.ll
$ g++ Lexer.cpp Parser.cpp main.cpp -o analyzer
```

#### Ejecución

```bash
$ ./analyzer prueba
```

#### Ejercicios
Para la gramática G = ( N, Σ, P, S), descrita por las siguientes producciones: 
> P = {
>> programa → declaraciones sentencias <br>
>> declaraciones → declaraciones declaracion | declaracion <br>
>> declaracion → tipo lista-var **;** <br>
>> tipo → **int** | **float** <br>
>> lista_var → lista_var **,** _**identificador**_ | _**identificador**_ <br>
>> sentencias → sentencias sentencia | sentencia <br>
>> sentencia → _**identificador**_ **=** expresion **;** | **if** **(** expresion **)** sentencias **else** sentencias | **while** **(** expresión **)** sentencias <br>
>> expresion → expresion **+** expresion | expresion **-** expresion | expresion __\*__ expresion | expresion **\/** expresión | _**identificador**_ | **_numero_** <br>
>> expresion → **(** expresion **)** <br>
}


1. Determinar en un archivo Readme, en formato Markdown (.md) o LaTeX (.tex) -- con su respectivo PDF, para este último -- , los conjuntos _N_, _Σ_ y el símbolo inicial _S_.  (0.5 pts.)
2. Mostrar en el archivo el proceso de eliminación de ambigüedad o justificar, en caso de no ser necesario. (1 pts.).
3. Mostrar en el archivo el proceso de eliminación de la recursividad izquierda o justificar, en caso de no ser necesario. (1 pts.)
4. Mostrar en el archivo el proceso de factorización izquierda o justificar, en caso de no ser necesario. (1 pts.)
5. Mostrar en el archivo los nuevos conjuntos _N_ y _P_. (0.5 pts.)
6. Definir el Analizador Léxico (lexer.ll) con las acciones léxicas correspondientes. (2 pts.)
7. Implementar el Analizador Sintáctico (Parser.cpp) de descenso recursivo, documentando las funciones de cada No-Terminal, de forma que el programa descrito en el archivo _prueba_ sea reconocido y aceptado por el analizador resultante. (4 pts.)

---
#### Extras

8. Documentar el código. (0.25pts)
9. Proponer 4 archivos de prueba nuevos, 2 válidos y 2 inválidos. (0.25pts)
10. Modificar el Makefile para poder simplificar el proceso de compilación de la práctica. (1pt)
