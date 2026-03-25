#pragma once

// Librerías
#include <iostream>
#include "Estatus.h"
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

        // ----------------------------------------------------------------------
        // Funciones auxiliares
        // ----------------------------------------------------------------------
        // Permite cargar en memoria las instrucciones del archivo
        StatusCode LeerArchivo(string filepath);

        // Ejecuta las instrucciones de la memoria
        StatusCode EjecutarInstrucciones();

        // Permite mostrar códigos de error
        bool MostrarError(StatusCode estatus);

    public:
        // Constructor (inicializa la memoria con el tamaño seleccionado)
        MaquinaEjecucion();

        // Inicia la lectura sobre el archivo seleccionado
        StatusCode EjecutarArchivo(string filepath);
};
