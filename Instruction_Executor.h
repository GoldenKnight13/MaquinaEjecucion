#pragma once
#include "Ram.h"
#include "Instruction.h"
#include "Estatus.h"
#include <vector>
#include <string>
#include <iostream>
#include <cstdlib> // Para usar system("pause")
#include <functional>

// Clase que maneja la ejecución de instrucciones
class InstructionExecutor {
private:
    RAM memoria;
    int* registros;
    unsigned int registroEjecucion;
    unsigned int NUMERO_REGISTROS;

    //Mapa de instrucciones, permite ejecutarlas de forma rapida y separada
    std::unordered_map<
        InstructionSet::KEYWORD,
        std::function<StatusCode(const Instruction&)>
    > OPERACIONES;

    void iniciarMapaInstrucciones();

    int calcularDireccionMemoria(const Instruction&);
    bool esRegistroValido(int seleccion);

public:
    // Constructor de la clase InstructionExecutor
    InstructionExecutor(RAM& ram, int* reg, int numReg, int regExec);

    // Método para saber el índice de la instrucción que se está ejecutando
    int num_instruccion();

    //Metodo para obtener el estado de lso registros
    void getValoresRegistros();

    // Método para ejecutar una instrucción
    StatusCode ejecutar(const Instruction& instruction);
};
