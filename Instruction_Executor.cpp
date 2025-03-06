#include "Instruction_Executor.h"
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // Para usar system("pause")

// Constructor de la clase InstructionExecutor
InstructionExecutor::InstructionExecutor(RAM& ram, int* reg, int numReg, int regExec)
    : memoria(ram), registros(reg), NUMERO_REGISTROS(numReg), registroEjecucion(regExec) {
}

// Método para saber el índice de la instrucción que se está ejecutando
int InstructionExecutor::num_instruccion() {
    return registros[7];
}

// Método para ejecutar una instrucción
int InstructionExecutor::ejecutar(const Instruction& instruction) {
    int a = instruction.d + registros[instruction.s];

    std::cout << "Comando: " << instruction.comando
        << " ,r: " << instruction.r
        << " ,s: " << instruction.s
        << " ,t: " << instruction.t
        << " ,d: " << instruction.d
        << ", a: " << a
        << std::endl;

    std::cout << "Arreglo de registros: ";
    for (unsigned int i = 0; i < 8; i++) {
        std::cout << registros[i] << " ";
    }

    std::cout << std::endl << std::endl;

    if (instruction.comando == "HALT") {
        system("pause");
        return 1;  // Salir del programa
    }
    else if (instruction.comando == "IN") {
        if (instruction.r < NUMERO_REGISTROS) {
            std::cout << "Ingrese un valor para el registro " << instruction.r << ": ";
            std::cin >> registros[instruction.r];
        }
    }
    else if (instruction.comando == "OUT") {
        if (instruction.r < NUMERO_REGISTROS) {
            std::cout << registros[instruction.r] << std::endl;
        }
    }
    else if (instruction.comando == "ADD") {
        if (instruction.r < NUMERO_REGISTROS) {
            registros[instruction.r] = registros[instruction.s] + registros[instruction.t];
        }
    }
    else if (instruction.comando == "SUB") {
        if (instruction.r < NUMERO_REGISTROS) {
            registros[instruction.r] = registros[instruction.s] - registros[instruction.t];
        }
    }
    else if (instruction.comando == "MUL") {
        if (instruction.r < NUMERO_REGISTROS) {
            registros[instruction.r] = registros[instruction.s] * registros[instruction.t];
        }
    }
    else if (instruction.comando == "DIV") {
        if (instruction.r < NUMERO_REGISTROS) {
            if (registros[instruction.t] != 0) {
                registros[instruction.r] = registros[instruction.s] / registros[instruction.t];
            }
            else {
                std::cout << "Error: Division por cero no permitida." << std::endl;
				return 4;  // Error en la instrucción
            }
        }
    }
    else if (instruction.comando == "LD") {
        if (instruction.r < NUMERO_REGISTROS) {
            registros[instruction.r] = memoria.get(a);
        }
    }
    else if (instruction.comando == "LDA") {
        if (instruction.r < NUMERO_REGISTROS) {
            registros[instruction.r] = a;
        }
    }
    else if (instruction.comando == "LDC") {
        if (instruction.r < NUMERO_REGISTROS) {
            registros[instruction.r] = instruction.d;
        }
    }
    else if (instruction.comando == "ST") {
        if (instruction.r < NUMERO_REGISTROS) {
            if (a < memoria.size()) {
                memoria.insert(a, registros[instruction.r]);
            }
        }
    }
    // Instrucciones de salto condicional
    else if (instruction.comando == "JLT") {  // Salta si registros[r] < 0
        if (registros[instruction.r] < 0) {
            if (a >= 0 && a < memoria.size()) {  // Validación del rango de la dirección de salto
                registros[registroEjecucion] = a;  // Actualiza el registro de ejecución
                return 3;  // Indica que se debe continuar ejecutando
            }
            else {
                std::cerr << "Error: Dirección de salto fuera de rango en JLT: " << a << std::endl;
                return 4;  // Error en la instrucción
            }
        }
    }
    else if (instruction.comando == "JLE") {  // Salta si registros[r] <= 0
        if (registros[instruction.r] <= 0) {
            if (a >= 0 && a < memoria.size()) {
                registros[registroEjecucion] = a;
                return 3;
            }
            else {
                std::cerr << "Error: Dirección de salto fuera de rango en JLE: " << a << std::endl;
                return 4;
            }
        }
    }
    else if (instruction.comando == "JGE") {  // Salta si registros[r] >= 0
        if (registros[instruction.r] >= 0) {
            if (a >= 0 && a < memoria.size()) {
                registros[registroEjecucion] = a;
                return 3;
            }
            else {
                std::cerr << "Error: Dirección de salto fuera de rango en JGE: " << a << std::endl;
                return 4;
            }
        }
    }
    else if (instruction.comando == "JGT") {  // Salta si registros[r] > 0
        if (registros[instruction.r] > 0) {
            if (a >= 0 && a < memoria.size()) {
                registros[registroEjecucion] = a;
                return 3;
            }
            else {
                std::cerr << "Error: Dirección de salto fuera de rango en JGT: " << a << std::endl;
                return 4;
            }
        }
    }
    else if (instruction.comando == "JEQ") {  // Salta si registros[r] == 0
        if (registros[instruction.r] == 0) {
            if (a >= 0 && a < memoria.size()) {
                registros[registroEjecucion] = a;
                return 3;
            }
            else {
                std::cerr << "Error: Dirección de salto fuera de rango en JEQ: " << a << std::endl;
                return 4;
            }
        }
    }
    else if (instruction.comando == "JNE") {  // Salta si registros[r] != 0
        if (registros[instruction.r] != 0) {
            if (a >= 0 && a < memoria.size()) {
                registros[registroEjecucion] = a;
                return 3;
            }
            else {
                std::cerr << "Error: Dirección de salto fuera de rango en JNE: " << a << std::endl;
                return 4;
            }
        }
    }


    else {
        return 4; // Si no hay una instrucción válida
    }

    registros[7]++;
    return 3;  // Retorno para continuar ejecutando
}
