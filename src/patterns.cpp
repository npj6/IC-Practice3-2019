#include <iostream>
#include "state.h"

int main(void) {
  for(int i=0; i<5; i++) {
    State* estado = new State(6+i, false);
    std::cout << estado->toString() << std::endl;
    estado->writeFile("estado.txt");
    State* estado2 = new State("estado.txt");
    std::cout << estado2->toString() << std::endl;
    delete estado, estado2;
  }
  return 0;

} 

