//Librerias
#include <iostream>
#include "MaquinaEjecucion.h"
using namespace std;

//Programa principal
int main(int argc, char* argv[]) {

    argc--; //Se resta uno para que no cuente el nombre del archivo
    argv++; //Se mueve el puntero para que apunte al primer argumento

    //Ruta del archivo que se va a ajecutar, puede ser un parametro del usuario
    string archivoInstrucciones = "D:/ejemplo de prueba.cod";
    if (argc) {
        archivoInstrucciones = argv[0];
    }
    else {
        archivoInstrucciones = "./instrucciones.txt";
    }

    //Crea la maquina de ejecucion
    MaquinaEjecucion ejecucion;

    //Retorna el codigo de estado de la maquina de ejecucion
    return ejecucion.EjecutarArchivo(archivoInstrucciones);

}