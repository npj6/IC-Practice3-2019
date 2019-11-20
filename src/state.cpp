#include "state.h"
#include <iostream> //cout
#include <cstdlib> //RAND_MAX, rand, srand
#include <cmath> //log2
#include <ctime> //time
#include <fstream>

int State::RAND_BOOLS_PER_INT = (int) log2(1+(unsigned int) RAND_MAX);
bool State::SEEDED = false;

void State::SEED() {
  srand(time(NULL));
}

int& State::state(int i, int j) {
  return st[i*size + j];
}

State::State(int size, bool parallel) {
  this->size = size;
  this->st = new int[size*size];
  //calculates the number of random needed
  int rand_nums = (size*size)/RAND_BOOLS_PER_INT + 1;
  if (!SEEDED) {
    SEED();
    SEEDED = true;
  }
  if (parallel) {

  } else {
    for(int i=0; i<rand_nums; i++) {
      int rand_value = rand();
      int mask = 1;
      for (int j=0; j<RAND_BOOLS_PER_INT; j++) {
	if (size*size <= i*RAND_BOOLS_PER_INT + j) {
	  break;
	}
	int bit = rand_value & mask;
	st[i*RAND_BOOLS_PER_INT + j] = (int) (bit != 0);
	mask = mask << 1;
      }
    }
  }
}

State::~State() {
  delete [] st;
}

int State::getCelda(int i, int j) {
  return 0;
}

State::State(std::string s){
  std::ifstream fe(s);
  std::string str = "";
  std::string num = "";

  while(!fe.eof()){
    fe >> num;
    str += num;
    str += '\t';
  }

  fe.close();

  std::vector<std::string> aux = split(str, '\t');
  size = std::stoi(aux[0]);
  int it = 1;
  for(int i = 0; i < size; i++){
    for(int j = 0; j < size; j++){
      state(i, j) = std::stoi(aux[it]);
      it++;
    }
  }
}

std::vector<std::string> State::split(std::string str, char pattern) {
  int posInit = 0;
  int posFound = 0;
  std::string splitted;
  std::vector<std::string> resultados;

  while(posFound >= 0){
    posFound = str.find(pattern, posInit);
    splitted = str.substr(posInit, posFound - posInit);
    posInit = posFound + 1;
    resultados.push_back(splitted);
  }

  return resultados;
}

std::string State::toString(){
  std::string result = "";
  result += std::to_string(size);

  for(int i = 0; i < size; i++){
    result += '\n';
    for(int j = 0; j < size; j++){
      result += std::to_string(state(i, j)) + " ";
    }
  }

  return result;
}


void State::writeFile(std::string name) {
  std::ofstream output (name);
  output << toString() << std::endl;
  output.close();
}

//CRITICAL
void State::setCelda(int i, int j) {

}
void State::upCelda(int i, int j) {

}
void State::unsetCelda(int i, int j) {

}

void State::unsetAll() {

}
