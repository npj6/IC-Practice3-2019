#ifndef ARGUMENTS_H
#define ARGUMENTS_H
  #include <iostream>
  #include <vector>
  #include <string>

    class Arguments{
        private:
            std::string nombre;
            std::vector<std::string> datos;

        public: 
            Arguments(int argc, char *argv[]);
            std::string get(std::string patt);
            bool exist(std::string patt);
    };


#endif