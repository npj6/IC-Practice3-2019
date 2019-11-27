#include <iostream>
#include <string>
#include <dirent.h>
#include <chrono>
#include "state.h"
#include "basicRule.h"
#include "arguments.h"

int main(int argc, char *argv[]) {
/*
	State* from = new State(4);
	State* to = new State(*from);

	std::cout << "ESTADO FROM" << std::endl;
	std::cout << from->toString() << std::endl << std::endl;
	std::cout << "ESTADO TO" << std::endl;
	std::cout << to->toString() << std::endl;
	std::cout << "------------------------------------------------" << std::endl;

	BasicRule r;

	r.apply(*from, *to);


	std::cout << "ESTADO FROM" << std::endl;
	std::cout << from->toString() << std::endl << std::endl;
	std::cout << "ESTADO TO" << std::endl;
	std::cout << to->toString() << std::endl;

	delete from, to;
*/

	Arguments args = Arguments(argc, argv);

	int iteraciones = std::stoi(args.get("i"));
	std::string carpeta = args.get("f");


	std::vector<std::string> archivos;
	if( DIR* pDIR = opendir(carpeta.c_str()) )
	{
		while(dirent* entry = readdir(pDIR))
		{
			std::string fileName = entry->d_name;

			if( fileName != "." && fileName != ".." && fileName[0] != '.'){
				archivos.push_back(fileName);
			}
		}
		closedir(pDIR);
	}
	for(int i = 0; i < archivos.size(); i++){
		archivos[i] = carpeta + archivos[i];
	}

	std::vector<std::vector<State*>> posiciones(archivos.size());
	for(int i = 0; i < posiciones.size(); i++){
		posiciones[i].push_back(NULL);
		posiciones[i].push_back(NULL);
	}
	BasicRule r;

	auto start = std::chrono::steady_clock::now();
	for(int i = 0; i < archivos.size(); i++){
		for(int j = 0; j < iteraciones; j++){
			

			if(j == 0){
				posiciones[i][0] = new State((std::string)archivos[i]);
				posiciones[i][1] = new State(*posiciones[i][0]);
			}
			

			r.apply(*posiciones[i][j%2], *posiciones[i][(j+1)%2]);
		}
	}
	auto end = std::chrono::steady_clock::now();
    std::string time = std::to_string(std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());

	int total_celulas = 0;
	int total_tiempo = 0;
	for(int i = 0; i < posiciones.size(); i++){

		std::cout << "Num_simulacion: " << i << " Patrón: " + (std::string)archivos[i] << " Num_celulas: " + posiciones[i][0]->getSize()
		 << " Num_generaciones: " + iteraciones << " Tiempo: " + time << std::endl;

		
		total_celulas += (int)posiciones[i][0]->getSize();
		total_tiempo += (int)std::stoi(time);
	}
	std::cout << std::endl;
	std::cout << "Total_Soluciones: " << posiciones.size() << "  total_celulas * generaciones: " << (total_celulas * (iteraciones*archivos.size()))
	 << "  T_total: " << total_tiempo << "  total_celulas / T_total: " << (total_celulas / total_tiempo)<< std::endl;
	return 0;

}
