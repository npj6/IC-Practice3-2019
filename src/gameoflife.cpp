#include <iostream>
#include <string>
#include <dirent.h>
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

	std::vector<std::vector<State*>> posiciones(archivos.size());
	for(int i = 0; i < posiciones.size(); i++){
		posiciones[i].push_back(NULL);
		posiciones[i].push_back(NULL);
	}
	BasicRule r;

	for(int i = 0; i < archivos.size(); i++){
		for(int j = 0; j < iteraciones; j++){
			State* from;
			State* to;
			posiciones[i][0] = from;
			posiciones[i][1] = to;
			if(j == 0){
				posiciones[i][0] = new State(archivos[i]);
				posiciones[i][1] = new State(*posiciones[i][0]);
			}
			else{
				posiciones[i][0] = new State(*posiciones[i][1]);
				posiciones[i][1] = new State(*posiciones[i][0]);
			}

			r.apply(*posiciones[i][0], *posiciones[i][1]);
		}
	}
	
	for(int i = 0; i < posiciones.size(); i++){
		std::cout << posiciones[i][1]->toString() << std::endl;
	}

	return 0;

}
