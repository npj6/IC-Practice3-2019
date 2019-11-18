#ifndef STATE_H
#define STATE_H
  #include <iostream>
  #include <vector>

  using namespace std;
  class State{
    private:
      int estado[][];

    public:
      State(int size);
      int getCelda(int i, int j);
  };
#endif
