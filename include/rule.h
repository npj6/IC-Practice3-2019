#ifndef RULE_H
#define RULE_H
  #include <iostream>
  #include "state.h"
  class Rule {
    public:
      virtual void apply(State &from, State &to) const = 0;
  };
#endif
