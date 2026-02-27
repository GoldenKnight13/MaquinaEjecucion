#pragma once

// Librerías
#include <iostream>
#include "Ram.h"
#include "Instruction.h"
#include "Instructions_FileReader.h"
#include "Instruction_Executor.h"
#include <vector>

using namespace std;

// Variables globales de la máquina
#define INSTRUCCIONES_MAXIMO 256
#define DATOS_MAXIMO 256
#define NUMERO_REGISTROS 8
#define PC_REGISTRO 7   // Ubicación del registro de ejecución

class MaquinaEjecucion {

    private:
        // ----------------------------------------------------------------------
        // Variables internas
        // ----------------------------------------------------------------------
        RAM memoria;                // Memoria RAM de la máquina
        int* registros;             // Registros de ejecución
        Instruction instrucciones[INSTRUCCIONES_MAXIMO];    // Memoria de instrucciones
        vector<string> instruccionesValidas; // Instrucciones válidas

        // ----------------------------------------------------------------------
        // Funciones auxiliares
        // ----------------------------------------------------------------------
        // Permite cargar en memoria las instrucciones del archivo
        int LeerArchivo(string filepath);

        // Ejecuta las instrucciones de la memoria
        int EjecutarInstrucciones();

        // Permite mostrar códigos de error
        bool MostrarError(int estatus);

    public:
        // Constructor (inicializa la memoria con el tamaño seleccionado)
        MaquinaEjecucion();

        // Inicia la lectura sobre el archivo seleccionado
        int EjecutarArchivo(string filepath);
};
