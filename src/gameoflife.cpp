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

void iterate_patterns(const std::vector<std::string> &archivos, int iteraciones, const Rule &r);

int main(int argc, char *argv[]) {

	//Comunication test
	MPI_Init(&argc, &argv);

	int node, nodeNum;
	MPI_Comm_rank(MPI_COMM_WORLD, &node);
	MPI_Comm_size(MPI_COMM_WORLD, &nodeNum);

	if (node == 0) {
		State* prueba = new State(7);
		send_pattern(prueba, 0);
		std::cout << prueba->toString() << std::endl << std::endl;
		delete prueba;
	} else {
		State* prueba = recv_pattern(1);
		std::cout << prueba->toString() << std::endl << std::endl;
		delete prueba;
	}

	MPI_Finalize();


	return 0;
}

void send_pattern(State* pat, int node_to) {
	int size_nums[2];
	size_nums[0] = pat->getSize();
	size_nums[1] = State::getBoolsPerInt();

	//std::cout << "1: enviando 2 ints" << std::endl;

	MPI_Send(size_nums, 2, MPI_INT, node_to, 0, MPI_COMM_WORLD);
	std::vector<int> value_vector = pat->getComprimido();
	int* values = new int[value_vector.size()];

	for(int i=0; i<value_vector.size(); i++) {
		values[i] = value_vector[i];
	}
/*
	std::cout << "1: esperando señal de vuelta" << std::endl;

	int num;
	MPI_Recv(&num, 1, MPI_INT, node_to, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	std::cout << "2: enviando " << value_vector.size() << " ints" << std::endl;

	MPI_Send(values, value_vector.size(), MPI_INT, node_to, 0, MPI_COMM_WORLD);

	std::cout << "envio terminado" << std::endl;

	delete[] values;
	*/
}

State* recv_pattern(int node_from) {
	int size_nums[2];

	//std::cout << "1: \trecibiendo 2 ints" << std::endl;

	MPI_Recv(size_nums, 2, MPI_INT, node_from, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	int size = (int) ceil(size_nums[0] * size_nums[0]/(double) size_nums[1]);

	int* values = new int[size];
/*
	std::cout << "1: \tenviando señal de vuelta" << std::endl;

	int num;
	MPI_Send(&num, 1, MPI_INT, node_from, 1, MPI_COMM_WORLD);

	std::cout << "2: \recibiendo " << size << " ints" << std::endl;

	MPI_Recv(size_nums, size, MPI_INT, node_from, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

	std::cout << "\trecibo terminado" << std::endl;

	std::vector<int> value_vector;
	for(int i=0; i<size; i++) {
		value_vector.push_back(values[i]);
	}

	delete[] values;

	return new State(value_vector, size_nums[0], size_nums[1]);
*/
	return NULL;
}

int main2(int argc, char *argv[]) {

	Arguments args = Arguments(argc, argv);

	int iteraciones;
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
					archivos.push_back(fileName);
				}
			}
			closedir(pDIR);
		}

		for(int i = 0; i < archivos.size(); i++){
			archivos[i] = carpeta + archivos[i];
		}
	} catch (std::exception &e) {
		std::cout << std::endl << "  Usage: " << std::endl
			<< std::endl
			<< "  " << argv[0] << " --i iterations [--f folder]" << std::endl
			<< std::endl
			<< "  default folder is " << DEF_FOLDER << std::endl
			<< std::endl;
			return 1;
	}

	BasicRule r;

	iterate_patterns(archivos, iteraciones, r);

	return 0;

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
