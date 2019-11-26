#include <iostream>
#include <string>
#include <vector>
#include "arguments.h"


Arguments::Arguments(int argc, char *argv[]){
    if(argc > 11){
        std::cout << "WRONG NUMBER OF ARGUMENTS" << std::endl;
    }
    else{
        
        this->nombre = argv[0];
        
        std::string d;
        for(int i = 1; i < argc; i++){
            if(argv[i][0] == '-' && argv[i][1] == '-'){
                if(argv[i + 1] == NULL){
                    d = (std::string)argv[i];
                    this->datos.push_back(d);
                }
                else{
                    d = (std::string)argv[i] + ' ' + (std::string)argv[i + 1];
                    this->datos.push_back(d);
                }
                
            }    
        }
    }

}

std::string Arguments::get(std::string patt){
    for(int i = 0; i < this->datos.size(); i++){
        if(this->datos[i][2] == patt[0] && this->datos[i].size() < 5){
            return "";
        }
        if(this->datos[i][2] == patt[0]){
            std::string aux = this->datos[i];
            return aux.erase(0, 4);
        }
    }

    return "";
}

bool Arguments::exist(std::string patt){
    for(int i = 0; i < this->datos.size(); i++){
        if(this->datos[i][2] == patt[0]){
            return true;
        }
    }
    return false;
}

