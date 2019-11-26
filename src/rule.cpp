#include "rule.h"

Rule* Rule::RULE = nullptr;

/* getRule() example:

const Rule& Rule::getRule() {
  if (RULE == nullptr) {
    RULE = new Rule();
  }

  return *RULE;
}

*/
