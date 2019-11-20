#include <iostream>
#include <string>
#include <vector>
#include "arguments.h"

Arguments::Arguments(int argc, char *argv[]){
    if(argc > 11){
        cout << "WRONG NUMBER OF ARGUMENTS" << endl;
    }
    else{
        
        nombre = argv[0];
        
        string d;
        for(int i = 1; i < argc; i++){
            if(argv[i].find("-")){
                d = argv[i] + " " + argv[i + 1);
            }    
        }
    }

}

string Arguments::get(string patt){
    string s = "-" + patt;
    for(int i = 0; i < datos.size(); i++){
        if(datos[i].find(s)){
            string aux = datos[i];
            return aux.erase(0, 2);
        }
    }
    
}

