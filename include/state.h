#ifndef STATE_H
#define STATE_H
  #include <vector>
  #include <string>

  class State {
    private:
      int size;
      int* st;
      int& state(int i, int j) const;

      std::vector<std::string> split(std::string str, char pattern) const;

      static int RAND_BOOLS_PER_INT;
      static bool SEEDED;

      static void SEED();

    public:

      State(int size);
      State(std::string s); //recibe el archivo
      State(State &st); //Recibe el estado a ser continuado
      ~State();

      int getSize() const {return size;}
      int getCelda(int i, int j) const;

      //CRITICAL
      void setCelda(int i, int j);
      void upCelda(int i, int j);
      void unsetCelda(int i, int j);

      void unsetAll();

      std::string toString() const;
      void writeFile(std::string name) const;
  };
#endif
