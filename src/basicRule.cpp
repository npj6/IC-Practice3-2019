#include "basicRule.h"

int BasicRule::around[8][2] = {
    {-1, -1},
    {-1, 0},
    {-1, 1},
    {0, -1},
    {0, 1},
    {1, -1},
    {1, 0},
    {1, 1}
  };


void BasicRule::apply(State &from, State &to) const {
  for(int i=0; i<from.getSize(); i++) {
    for (int j=0; j<from.getSize(); j++) {
      kernel1(from, to, i, j);
    }
  }
}

//i & j of from state
void BasicRule::kernel1(State &from, State &to, int i, int j) const {
  int around_alive = 0;
  //counts alive neighbours
  for(int n=0; n<8; n++) {
    around_alive += from.getCelda(i+around[n][0], j+around[n][1]);
  }

  if(from.getCelda(i, j) == 0) {
    //if dead and 3 alive, is born
    if (around_alive == 3) {
      to.setCelda(i, j);
    } else {
      to.unsetCelda(i, j);
    }
  } else {
    //if alive and 2 or 3 alive, keeps living
    if (around_alive==2 || around_alive==3) {
      to.setCelda(i, j);
    } else {
      to.unsetCelda(i, j);
    }
  }
}
