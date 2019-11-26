#include <iostream>
#include "state.h"
#include "basicRule.h"

int main(void) {
  State* from = new State(4);
  State* to = new State(*from);

  std::cout << "ESTADO FROM" << std::endl;
  std::cout << from->toString() << std::endl << std::endl;
  std::cout << "ESTADO TO" << std::endl;
  std::cout << to->toString() << std::endl;
  std::cout << "------------------------------------------------" << std::endl;

  BasicRule r;

  r.apply(*from, *to);


  std::cout << "ESTADO FROM" << std::endl;
  std::cout << from->toString() << std::endl << std::endl;
  std::cout << "ESTADO TO" << std::endl;
  std::cout << to->toString() << std::endl;

  delete from, to;

  return 0;

}
