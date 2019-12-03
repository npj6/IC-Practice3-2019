
#include "arguments.h"
#include "state.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <cstdlib> //RAND_MAX, rand, srand
#include <ctime> //time
#include <cmath> //pow

#define TIME_MEASURE std::chrono::milliseconds
const std::string TIME_UNIT = "ms";
const std::string DEF_FOLDER = "pat/";

const std::string REPORT_FILE = "patterns_report";

std::string write_file(State* p, int id, int pnum, std::string carpeta);
void append_file(std::string name, std::string content);
void escribirPatterns(std::vector<State*> v, int id, std::string carpeta);

int main (int argc, char *argv[])  {
	Arguments args = Arguments(argc, argv);

	int num, size;

	try{
		num = std::stoi(args.get("n"));
		size = std::stoi(args.get("s"));

		if(num < 1){
			std::cout << "The number of patterns must be positive" << std::endl;
			return 1;
		}
		if(size < 1){
			std::cout << "The size of the pattern must be positive" << std::endl;
			return 1;
		}
	} catch (std::exception &e) {
			std::cout << std::endl << "  Usage: " << std::endl
				<< std::endl
				<< "  " << argv[0] << " --n pattern_num --s pattern_size" << std::endl
				<< std::endl
				<< "  default folder is " << DEF_FOLDER << std::endl
				<< std::endl;
				return 1;
	}

	srand(time(NULL));
	int id = rand();
	std::string carpeta = DEF_FOLDER;
	State* state;
	std::vector<State*> patterns;

	std::vector<double> times;

  for(int i = 0; i < num; i++){
	  auto start = std::chrono::steady_clock::now();
    state = new State(size);
	  auto end = std::chrono::steady_clock::now();
    patterns.push_back(state);
		times.push_back(std::chrono::duration_cast<TIME_MEASURE>(end - start).count());
  }

	int total_time = 0;
	int total_celulas = 0;

	std::ofstream output (REPORT_FILE);
	std::string line;

	std::cout << "num patron\tvalor N\t\tnum celulas\ttiempo ("+TIME_UNIT+")" << std::endl;
	for(int i = 0; i < patterns.size(); i++){
		int celulas = pow(patterns[i]->getSize(), 2);
		line = std::to_string(i)+"\t\t"
				+ std::to_string(patterns[i]->getSize()) + "\t\t"
				+ std::to_string(celulas) + "\t\t"
				+ std::to_string((int) times[i]) + "\n";

		output << line;
		std::cout << line;

		total_time += times[i];
		total_celulas += celulas;
	}

	output << std::endl;
	std::cout << std::endl;

	std::cout << "patrones\tcelulas\t\ttiempo ("+TIME_UNIT+")\ttiempo por patron ("+TIME_UNIT+")" << std::endl;
	line = std::to_string(patterns.size()) + "\t\t"
			+ std::to_string(total_celulas) + "\t\t"
			+ std::to_string((int) total_time) + "\t\t"
			+ std::to_string(total_time / patterns.size()) + "\n";
	output << line;
	std::cout << line;
	output.close();

	std::cout << "Escribiendo los patrones." << std::endl;
  //escribirPatterns(patterns, id, carpeta);

	return 0;
}

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

void escribirPatterns(std::vector<State*> v, int id, std::string carpeta){
	std::string state_index;
  for(int i = 0; i < v.size(); i++){
    std::string name = write_file(v[i], id, i, carpeta);
		state_index = state_index + name + "\n";
    delete v[i];
    v[i] = nullptr;
  }
  append_file(carpeta, state_index);
}
