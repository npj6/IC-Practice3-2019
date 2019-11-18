#ifndef STATE_H
#define STATE_H
  #include <iostream>
  #include <vector>

  using namespace std;
  class State{
    private:
      vector<vector<int>> estado;
      int size;

    public:
      State(int size);
      State(string s);
      int getCelda(int i, int j){return estado[i][j];};
      string toString();
      vector<string> split(string str, char pattern);
  };
#endif
