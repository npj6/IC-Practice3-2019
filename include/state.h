#ifndef STATE_H
#define STATE_H
  #include <vector>
  #include <string>

  class State {
    private:
      int size;
      int st[];
      int& state(int i, int j);

    public:
      
      static int RAND_BOOLS_PER_INT;

      State(int size, bool parallel);
      State(std::string state);

      int getCelda(int i, int j);

      //CRITICAL
      void setCelda(int i, int j);
      void upCelda(int i, int j);
      void unsetCelda(int i, int j);

      void unsetAll();

      std::string toString();

  };
#endif
