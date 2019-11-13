#include "state.h"
#include <iostream> //cout
#include <cstdlib> //RAND_MAX
#include <cmath> //log2

int State::RAND_BOOLS_PER_INT = (int) log2(1+(unsigned int) RAND_MAX);

int& State::state(int i, int j) {
  return st[i*size + j];
}

State::State(int size, bool parallel) {
  this->size = size;
  if (parallel) {

  } else {
    for(int i=0; i<size; i++) {
      for (int j=0; j<size; j++) {      }
    }
  }
}

State::State(std::string state) {
  size = 0;
}

int State::getCelda(int i, int j) {
  return 0;
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


std::string State::toString() {
  return "";
}


