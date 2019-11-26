#ifndef RULE_H
#define RULE_H
  #include <iostream>
  #include "state.h"
  class Rule {
    public:
      virtual void apply(State &from, State &to) = 0;
  };
#endif
