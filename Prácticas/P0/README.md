<p  align="center">
  <img  width="200"  src="https://www.fciencias.unam.mx/sites/default/files/logoFC_2.png"  alt="">  <br>Compiladores  2026-2 <br>
  Práctica 0: Sistema de procesamiento de Lenguaje <br> Profesora: Ariel Adara Mercado Martínez
</p>

### Sistema de procesamiento de Lenguaje
### Objetivo:
Comprender y analizar el funcionamiento de los diferentes programas que intervienen en el proceso de traducción de un programa fuente a un programa ejecutable.

### Introducción
Un compilador es un programa que traduce un programa fuente escrito en un lenguaje de alto nivel a un
programa en lenguaje objeto, usualmente de bajo nivel. Este proceso no se realiza de manera aislada; el
compilador colabora con otros programas como el preprocesador, ensamblador y enlazador.
El preprocesador recopila y expande macros y otros fragmentos de código abreviado en el programa
fuente. Luego, el compilador transforma el código preprocesado en un programa objeto en lenguaje ensamblador, que es posteriormente convertido en código máquina por el ensamblador. Finalmente, el enlazador combina los archivos de código máquina y bibliotecas necesarias para producir un programa ejecutable. El cargador lleva este programa ejecutable a la memoria para su ejecución.

```mermaid
flowchart TD
subgraph 1
id1([Programa fuente]) --> Preprocesador  -- Programa Fuente modificado -->  Compilador  -- Programa objeto en lenguaje ensamblador -->  Ensamblador  -- Código máquina relocalizable --> Enlazador/Cargador --> id2([Código máquina destino])
end
subgraph  2  
id3[/Archivos de biblioteca y archivos objeto/] --> Enlazador/Cargador  
end  
 ```

### Desarrollo:

1. Deberá tener instalado el compilador _gcc_ y trabajar en un ámbiente _Linux_.
2. Escriba el siguiente programa en lenguaje **_C_** (sin copiar y pegar) y nómbrelo *programa.c*
```c
#include <stdio .h>
#include <stdlib.h>
//# define PI 3.1415926535897

# ifdef PI
# define area (r) (PI * r * r)
# else
# define area (r) (3.1416 * r * r)
# endif


/**
* Compiladores 2025-2
*
*/
int main ( void ) {
printf ("Hola Mundo !\n"); //Función para imprimir hola mundo
float mi_area = area (3) ; //soy un comentario... hasta donde llegaré ?
printf ("Resultado : %f\n", mi_area);
return 0;
}
```

3. Use el siguiente comando: `cpp programa.c programa.i`
Revise el contenido de _programa.i_ y conteste lo siguiente:
<ol type="a">
  <li>¿Qué ocurre cuando se invoca el comando <i>cpp</i> con esos argumentos?</li>
  <li>¿Qué similitudes encuentra entre los archivos <i>programa.c</i> y <i>programa.i</i>?</li>
  <li>¿Qué pasa con las macros y los comentarios del código fuente original en <i>programa.i</i>?</li>
  <li>Compare el contenido de <i>programa.i</i> con el de <i>stdio.h</i> e indique de forma general las similitudes entre ambos
  archivos.</li>
  <li>¿A qué etapa corresponde este proceso?</li>
</ol>

---

4. Ejecute la siguiente instrucción: ``gcc -Wall -S programa.i``
<ol type="a">
  <li>¿Para qué sirve la opción <i>-Wall</i>?</li>
  <li>¿Qué le indica a gcc la opción <i>-S</i>?</li>
  <li>¿Qué contiene el archivo de salida y cuál es su extensión?</li>
  <li>¿A qué etapa corresponde este comando?</li>
</ol>

---

5. Ejecute la siguiente instrucción: `as programa.s -o programa.o`
<ol type="a">
  <li> Antes de revisarlo, indique cuál es su hipótesis sobre lo que debe contener el archivo con extensión  <i>.o</i>. </li>
  <li> Diga de forma general qué contiene el archivo <i>programa.o</i> y por qué se visualiza de esa manera. </li>
  <li> ¿Qué programa se invoca con  <i>as</i>? </li>
  <li> ¿A qué etapa corresponde la llamada a este programa? </li>
</ol>

---

6. Encuentre la ruta de los siguientes archivos en el equipo de trabajo:
* ld-linux-x86-64.so.2
* Scrt1.o (o bien, crt1.o)
* crti.o
* crtbeginS.o
* crtendS.o
* crtn.o

---

7. Ejecute el siguiente comando, sustituyendo las rutas que encontró en el paso anterior:
```bash
ld -o ejecutable -dynamic-linker /lib/ld-linux-x86-64.so.2 /usr/lib/Scrt1.o /usr/lib/crti.o programa.o -lc /usr/lib/crtn.o
```

<ol type="a">
  <li> En caso de que el comando ld mande errores, investigue como enlazar un programa utilizando el comando <i>ld</i>. Y proponga una posible solución para llevar a cabo este proceso con éxito. </li>
  <li> Describa el resultado obtenido al ejecutar el comando anterior. </li>
</ol>

---
8. Una vez que se enlazó el código máquina relocalizable, podemos ejecutar el programa con la siguiente
instrucción en la terminal: ```./ejecutable```
---

9. Quite el comentario de la macro _#define PI_ en el código fuente original y conteste lo siguiente:
<ol type="a">
  <li> Genere nuevamente el archivo.i. De preferencia asigne un nuevo nombre.</li>
  <li> ¿Cambia en algo la ejecución final? </li>
</ol>

---

10. Escribe un segundo programa en lenguaje **_C_** en el que agregue 4 directivas del preprocesador
de _**C**_ (_cpp_)[^1]. Las directivas elegidas deben jugar algún papel en el significado del programa, ser distintas entre sí y
diferentes de las utilizadas en el primer programa (aunque no están prohibidas si las requieren). 
<ol type="a">
    <li>Explique su utilidad
general y su función en particular para su programa.</li>
</ol>

---

11. Redacte un informe detallado con sus resultados y conclusiones.


[^1]: Pueden consultar la lista de directivas en su documentación en línea: [CPP - Index of directives](https://gcc.gnu.org/onlinedocs/cpp/Index-of-Directives.html##Index-of-Directives). O bien, revisar la entrada para este preprocesador en la herramienta man en Linux: `$ man cpp`
