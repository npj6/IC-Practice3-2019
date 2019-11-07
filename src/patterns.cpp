#include <iostream>
#include "state.h"

int main(void) {
  State* estado = new State(6, false);
  std::cout << estado->toString() << std::endl;
  /*
  estado->writeFile("estado.txt");
  State* estado2 = new State("estado.txt");
  std::cout << estado2->toString() << std::endl;
  */
  estado->unsetAll();

  for(int i=0; i<6; i++) {
    for (int j=0; j<6; j++) {
      for (int i2=0; i2<(i*6 + j); i2++) {
        estado->upCelda(i, j);
      }
    }
  }

  //estado->setCelda(0,0);
  std::cout << estado->toString() << std::endl;
  std::cout << "Celda 5, 6: " << estado->getCelda(5, 6) << std::endl;
  std::cout << "Celda 6, 5: " << estado->getCelda(6, 5) << std::endl;
  std::cout << "Celda 5, -1: " << estado->getCelda(5, -1) << std::endl;
  std::cout << "Celda -1, 5: " << estado->getCelda(-1, 5) << std::endl;

  delete estado; //, estado2;
  return 0;

}
