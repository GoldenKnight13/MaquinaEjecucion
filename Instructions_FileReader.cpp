#include "Instructions_FileReader.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

// Método para leer las instrucciones desde un archivo
int InstructionsFileReader::leerInstrucciones(string filepath, Instruction* memoria, unsigned int maximo, vector<string>& instruccionesValidas) {

    unsigned int posicion = 0;
    ifstream archivo(filepath);          // Crear un objeto ifstream para abrir el archivo
    string linea;                        // Variable para almacenar cada línea del archivo

    // Verificar si el archivo se abrió correctamente
    if (!archivo.is_open()) {
        return 0;
    }

    // Leer el archivo línea por línea
    while (getline(archivo, linea)) {
        

        // Ignorar líneas vacías o que comienzan con un asterisco (comentarios)
        if (linea.empty() || linea[0] == '*') continue;

        std::stringstream ss(linea);  // Crear un stringstream para procesar la línea

        // Descompone la línea en sus componentes
        string linea, instruccion, parametros;
        ss >>linea >> instruccion >> parametros;

        memoria[posicion].comando = instruccion;

        // Diferencia entre los parámetros de las instrucciones de operación y memoria
        if (parametros.find('(') != string::npos) {
            // r,d(s)
            vector<string> val1 = split(parametros, ",");   // r d(s)
            vector<string> val2 = split(val1.at(1), "(");
            memoria[posicion].r = stoi(val1.at(0));
            memoria[posicion].d = stoi(val2.at(0));
            memoria[posicion].s = stoi(val2.at(1).substr(0, val2.at(1).length() - 1));
        }
        else {  // r,s,t
            vector<string> values = split(parametros, ",");
            memoria[posicion].r = stoi(values.at(0));
            memoria[posicion].s = stoi(values.at(1));
            memoria[posicion].t = stoi(values.at(2));
        }

        // Agregar la instrucción leída al vector de instrucciones
        posicion++;

        // Si hay más comandos de los máximos que se pueden almacenar en memoria
        if (posicion >= maximo) {
            return 2;
        }
    }

    archivo.close();  // Cerrar el archivo después de leer todas las líneas
    return 1;  // Retornar el vector de instrucciones
}

// Método privado para separar una cadena por un delimitador
vector<string> InstructionsFileReader::split(string input, string delimiter) {
    size_t pos;                 // Para el control de la división
    vector<string> tokens;      // Valores de retorno

    // Mientras pueda separar la entrada (guarda el valor en la variable pos)
    while ((pos = input.find(delimiter)) != string::npos) {
        tokens.push_back(input.substr(0, pos));
        input.erase(0, pos + delimiter.length());
    }
    tokens.push_back(input);

    return tokens;
}
