#ifndef STATE_H
#define STATE_H
  #include <vector>
  #include <string>

  class State {
    private:
      int size;
      int* st;
      int& state(int i, int j);

      std::vector<std::string> split(std::string str, char pattern);

      static int RAND_BOOLS_PER_INT;
      static bool SEEDED;

      static void SEED();

    public:

      State(int size, bool parallel);
      State(std::string s); //recibe el archivo 
      ~State();

      int getCelda(int i, int j);

      //CRITICAL
      void setCelda(int i, int j);
      void upCelda(int i, int j);
      void unsetCelda(int i, int j);

      void unsetAll();

      std::string toString();
      void writeFile(std::string name);
  };
#endif
