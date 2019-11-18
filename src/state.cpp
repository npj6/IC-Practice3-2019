#include "state.h"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

State::State(int siz){
    size = siz;
   for(int i = 0; i < size; i++){
       for(int j = 0; j < size; j++){
           estado[i][j] = rand() % 1;
       }
   } 
}

State::State(string s){
    ifstream fe(s);
    string str = "";
    string num = "";

    while(!fe.eof()){
        fe >> num;
        str += num;
        str += '\t';
    }

    fe.close();

    vector<string> aux = split(str, '\t');
    size = stoi(aux[0]);
    int it = 1;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            estado[i][j] = stoi(aux[it]);
            it++;
        }
    }
}

vector<string> State::split(string str, char pattern) {
	int posInit = 0;
	int posFound = 0;
	string splitted;
	vector<string> resultados;

	while(posFound >= 0){
		posFound = str.find(pattern, posInit);
		splitted = str.substr(posInit, posFound - posInit);
		posInit = posFound + 1;
		resultados.push_back(splitted);
	}

	return resultados;
}
string
State::toString(){
    string result = "";
    result += size + '\n';

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            result += to_string(estado[i][j]);
        }
        result += '\n';
    }

    return result;
}

