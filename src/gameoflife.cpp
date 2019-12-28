#include <iostream>
#include <string>
#include <dirent.h>
#include <chrono>
#include <cmath> //pow ceil
#include <fstream> // ofstream

#include <mpi.h>

#include "state.h"
#include "basicRule.h"
#include "arguments.h"

#define TIME_MEASURE std::chrono::milliseconds
const std::string TIME_UNIT = "ms";
const std::string DEF_FOLDER = "pat/";

const std::string REPORT_FILE = "gameoflife_report";

void send_pattern(State* pat, int node_to);
State* recv_pattern(int node_from);

std::vector<State*> calculate_patterns(std::vector<State*> patterns,  int iteraciones, const Rule &r);


void iterate_patterns(const std::vector<std::string> &archivos, int iteraciones, const Rule &r);

void send_pattern(State* pat, int node_to) {
	int size_nums[2];
	size_nums[0] = pat->getSize();
	size_nums[1] = State::getBoolsPerInt();

	MPI_Ssend(size_nums, 2, MPI_INT, node_to, 0, MPI_COMM_WORLD);

	std::vector<int> value_vector = pat->getComprimido();

	int n = value_vector.size();
	int* values = new int[n];

	for(int i=0; i<n; i++) {
		values[i] = value_vector[i];
	}

	MPI_Ssend(values, n, MPI_INT, node_to, 0, MPI_COMM_WORLD);

	delete[] values;
}

State* recv_pattern(int node_from) {
	int size_nums[2];

	MPI_Recv(size_nums, 2, MPI_INT, node_from, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	int n = (int) ceil(size_nums[0] * size_nums[0]/(double) size_nums[1]);
	int* values = new int[n];

	MPI_Recv(values, n, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	std::vector<int> value_vector;
	for(int i=0; i<n; i++) {
		value_vector.push_back(values[i]);
	}

	delete[] values;
	return new State(value_vector, size_nums[0], size_nums[1]);
}

int main(int argc, char *argv[]) {

	//Comunication test
	MPI_Init(&argc, &argv);

	int node, nodeNum;
	MPI_Comm_rank(MPI_COMM_WORLD, &node);
	MPI_Comm_size(MPI_COMM_WORLD, &nodeNum);

	int iteraciones;
	std::vector<std::string> archivos;
	BasicRule r;

	if(node == 0) {
		Arguments args = Arguments(argc, argv);

		std::string carpeta;
		std::vector<std::string> archivos;
		try {
			iteraciones = std::stoi(args.get("i"));
			if (args.exist("f")) {
				carpeta = args.get("f");
			} else {
				carpeta = DEF_FOLDER;
			}


			if( DIR* pDIR = opendir(carpeta.c_str()) )
			{
				while(dirent* entry = readdir(pDIR))
				{
					std::string fileName = entry->d_name;

					if( fileName != "." && fileName != ".." && fileName[0] != '.'){
						archivos.push_back(carpeta + fileName);
					}
				}
				closedir(pDIR);
			}

		} catch (std::exception &e) {
			std::cout << std::endl << "  Usage: " << std::endl
				<< std::endl
				<< "  " << argv[0] << " --i iterations [--f folder]" << std::endl
				<< std::endl
				<< "  default folder is " << DEF_FOLDER << std::endl
				<< std::endl;
				MPI_Finalize();
				return 1;
		}
	}

	if(node==0) {
		/*
			el nodo 0 empieza a recorrer los archivos y crea los Pattern.
			Envia 2 patrones a cada nodo y se pone a hacer otros dos
			Despues haces MPI Barrier para esperar a que todos acaben sus 2 patrones
			Cuando todos acaben sus dos patrones, sigues recorriendo los archivos y repites
		*/
	} else {
		/*
			los demás nodos esperan los 2 patrones y los hacen

		*/
	}

	iterate_patterns(archivos, iteraciones, r);


	MPI_Finalize();

	return 0;

}


//LITERALMENTE SE CARGA LOS DATOS DE INPUT, CUIDADO
std::vector<State*> calculate_patterns(std::vector<State*> patterns,  int iteraciones, const Rule &r) {
	std::vector<State*> output;
	State* posiciones[2];

	for(int i = 0; i < patterns.size(); i++){

		//Carga el estado
		posiciones[0] = patterns[i];
		posiciones[1] = new State(*posiciones[0]);

		for(int j = 0; j < iteraciones; j++){
			r.apply(*posiciones[j%2], *posiciones[(j+1)%2]);
		}

		output.push_back(posiciones[iteraciones%2]);
		delete posiciones[(iteraciones-1)%2];
		patterns[i] = nullptr;
	}

	return output;

}

void iterate_patterns(const std::vector<std::string> &archivos, int iteraciones, const Rule &r) {


	State* posiciones[2];

	std::vector<double> times;


	for(int i = 0; i < archivos.size(); i++){
		auto start = std::chrono::steady_clock::now();

		for(int j = 0; j < iteraciones; j++){

			//Carga el estado
			if(j == 0){
				posiciones[0] = new State((std::string)archivos[i]);
				posiciones[1] = new State(*posiciones[0]);
			}


			r.apply(*posiciones[j%2], *posiciones[(j+1)%2]);
		}

		auto end = std::chrono::steady_clock::now();

		times.push_back(std::chrono::duration_cast<TIME_MEASURE>(end - start).count());
	}

	double total_time = 0;
	int total_celulas = 0;


	std::ofstream output (REPORT_FILE);
	std::string line;

	std::cout << "num simulacion\tpatron\t\t\t\tnum celulas\tgeneraciones\ttiempo ("+TIME_UNIT+")" << std::endl;
	for(int i = 0; i < archivos.size(); i++){
		int celulas = pow(posiciones[0]->getSize(), 2);
		line = std::to_string(i)+"\t\t"
			+ archivos[i] + "\t"
			+ std::to_string(celulas) + "\t\t"
			+ std::to_string(iteraciones) + "\t\t"
			+ std::to_string((int) times[i]) + "\n";
		output << line;
		std::cout << line;


		total_time += times[i];
		total_celulas += celulas;
	}

	output << std::endl;
	std::cout << std::endl;

	std::cout << "simulaciones\tcelulas computadas\t\ttiempo ("+TIME_UNIT+")\ttiempo por celula ("+TIME_UNIT+")" << std::endl;
	line = std::to_string(archivos.size()) + "\t\t"
		+ std::to_string(total_celulas * iteraciones) + "\t\t\t\t"
		+ std::to_string((int) total_time) + "\t\t"
		+ std::to_string(total_time / total_celulas) + "\n";
	output << line;
	std::cout << line;

	output.close();
}
