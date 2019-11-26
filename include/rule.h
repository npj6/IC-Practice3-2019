#ifndef RULE_H
#define RULE_H
  #include <iostream>
  #include "state.h"
  class Rule {
    private:
      static Rule* RULE;
      //Empty Constructor Rule() should be private;

    public:
      virtual const Rule& getRule() = 0;
      virtual void apply(State &from, State &to) = 0;
  };
#endif
