
#include "arguments.h"
#include "state.h"
#include <iostream>
#include <fstream>
#include <chrono>

std::string write_file(State* p, int id, int pnum, std::string carpeta) {
	std::string name = carpeta + std::to_string(id) + "_pattern" + std::to_string(pnum)+".pat";
	std::ofstream output (name);
	output << p->toString() << std::endl;
	output.close();
	return name;
}

void append_file(std::string name, std::string content) {
	std::ofstream output (name, std::fstream::out | std::fstream::app);
	output << content << std::endl;
	output.close();
}

std::vector<State*> generarPatterns(State* state, Arguments args){
  std::vector<State*> sol;
  for(int i = 0; i < std::stoi(args.get("n")); i++){
    state = new State(std::stoi(args.get("s")));
    sol.push_back(state);
  }

  return sol;
}

void escribirPatterns(std::vector<State*> v, int id, std::string carpeta, std::string state_index){
  for(int i = 0; i < v.size(); i++){
    std::string name = write_file(v[i], id, i, carpeta);
		state_index = state_index + name + "\n";
    delete v[i];
    v[i] = nullptr;
  }
  append_file(carpeta, state_index);
}

int main (int argc, char *argv[])  {
	std::cout << "SOY GAME OF LIFE" << std::endl;
	Arguments args = Arguments(argc, argv);
	
	if(args.exist("n") && args.exist("s") || args.exist("n") && args.exist("s")){
		if(std::stoi(args.get("n")) < 1){
			std::cout << "The number of patterns must be positive" << std::endl;
			return 1;
		}
		if(std::stoi(args.get("s")) < 1){
			std::cout << "The size of the pattern must be positive" << std::endl;
			return 1;
		}

  
		int id = rand();
		std::string carpeta = "pat/";
		std::string state_index = "";
		State* state;
		
    auto start = std::chrono::steady_clock::now();
    std::vector<State*> patterns = generarPatterns(state, args);
    auto end = std::chrono::steady_clock::now();
    std::string time = std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());

    escribirPatterns(patterns, id, carpeta, state_index);

    std::cout << "Time: " << time << " µs" << std::endl;
	}
	else{
		std::cout << "Some arguments are missing" << std::endl;
		std::cout << "At least you should have --n (number of patterns) --s (size of the patterns)" << std::endl;
	}

	int id = rand(); 
	
	return 0;
}



