#include <stdio.h>

#define CALOR 90
#define DESCANSO 1

//Si no hay un modo definido lo definimos como activo
#ifndef MODO_TRABAJO
    #define MODO_TRABAJO "ACTIVO"
#endif

//Deshabilitamos el modo descanso 
#undef DESCANSO

//Si el calor supera los 100 grados, se define la alerta
#if (CALOR > 100)
    #define ALERTA
#endif

int main() {
    printf("Modo de trabajo: %s\n", MODO_TRABAJO);

    //Si la alerta está definida, se muestra un mensaje de advertencia
    #if defined(ALERTA)
        printf("¡ALERTA! El nivel de calor supera las condiciones óptimas.\n");
    #endif

    //Si el modo descanso no está definido, se muestra un mensaje de aviso
    #ifndef DESCANSO
        printf("AVISO: El modo descanso está deshabilitado.\n");
    #endif

    //Si el calor supera los 150 grados, se detiene el programa con un error
    #if (CALOR > 150)
        #error "Calor demasiado alto. Deteniendo el programa."
    #endif

    return 0;
}