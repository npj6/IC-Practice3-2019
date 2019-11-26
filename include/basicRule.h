#ifndef BASIC_RULE_H
#define BASIC_RULE_H
  #include <iostream>
  #include "rule.h"

  class BasicRule : public Rule {
    protected:
      void kernel1(State &from, State &to, int i_from, int j_from);
      static int around[8][2];
    public:
      void apply(State &from, State &to);
  };
#endif
