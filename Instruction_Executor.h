#pragma once
#include "Ram.h"
#include "Instruction.h"
#include <vector>
#include <string>
#include <iostream>

// Clase que maneja la ejecución de instrucciones
class InstructionExecutor {
private:
    RAM memoria;
    int* registros;
    unsigned int registroEjecucion;
    unsigned int NUMERO_REGISTROS;

    // Instrucciones que se pueden ejecutar
    std::vector<std::string> instrucciones;

public:
    // Constructor de la clase InstructionExecutor
    InstructionExecutor(RAM& ram, int* reg, int numReg, int regExec);

    // Método para saber el índice de la instrucción que se está ejecutando
    int num_instruccion();

    // Método para ejecutar una instrucción
    int ejecutar(const Instruction& instruction);
};
