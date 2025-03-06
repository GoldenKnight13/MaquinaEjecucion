#pragma once

// Librerías
#include <string>
#include <vector>
#include <iostream>
#include "Instruction.h"
#include "Instruction_Executor.h"

// Clase que maneja la lectura y ejecución de instrucciones
class InstructionsReader {

public:
    // Constructor que recibe una referencia al ejecutor de instrucciones
    InstructionsReader(InstructionExecutor& executor);

    // Función para procesar y ejecutar las instrucciones
    void procesarInstrucciones(const std::vector<Instruction>& instrucciones);

private:
    // Método para validar la estructura de una instrucción
    bool validarInstruccion(const Instruction& instruccion);

    static const int NUMERO_REGISTROS = 8;  // Número de registros permitidos
    InstructionExecutor& executor;  // Referencia al ejecutor de instrucciones para delegar la ejecución
};
