#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "Instruction.h"
using namespace std;

// Clase para leer instrucciones desde un archivo
class InstructionsFileReader {

public:
    // Método para leer las instrucciones desde un archivo
    int leerInstrucciones(string filepath, Instruction* memoria, unsigned int maximo, vector<string>& instruccionesValidas);

private:
    // Método privado para separar una cadena por un delimitador
    vector<string> split(string input, string delimiter);
};
