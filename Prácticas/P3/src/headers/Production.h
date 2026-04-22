#ifndef PRODUCTION_H
#define PRODUCTION_H

#include <vector>
using namespace std;
#include "Symbols.hpp"

/**
 * Clase para representar una producción
 */
class Production
{
private:
  int head; //identificador del símbolo del encabezado de la producción (syms)
  vector<int> body; //arreglo de enteros para representar el cuerpo de la producción (syms)
  
public:
  Production(/* args */); //constructor por omisión
  Production(int head, vector<int> body); //constructor con encabezado y cuerpo 
  ~Production(); //destructor
  
  int getHead(); //obtener encabezado de la producción
  vector<int> getBody(); //obtener cuerpo de la producción
};
#endif // PRODUCTION_H
