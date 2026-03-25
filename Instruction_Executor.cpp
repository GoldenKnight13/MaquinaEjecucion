#include "Instruction_Executor.h"

// Constructor de la clase InstructionExecutor
InstructionExecutor::InstructionExecutor(RAM& ram, int* reg, int numReg, int regExec)
    : memoria(ram), registros(reg), NUMERO_REGISTROS(numReg), registroEjecucion(regExec) {
}

// Método para saber el índice de la instrucción que se está ejecutando
int InstructionExecutor::num_instruccion() {
    return registros[registroEjecucion];
}

// Método que permite mostrar los valores que hay almacenados en todos los registros (inclyendo el PC)
void InstructionExecutor::getValoresRegistros() {

    std::cout << "Arreglo de registros: ";
    for (unsigned int i = 0; i < registroEjecucion; i++) {

        if (i == registroEjecucion) std::cout << "(PC: " << registros[i]  << ") ";
        else std::cout << registros[i] << " ";
    }

    std::cout << endl;

    return;

}

// Método para ejecutar una instrucción
StatusCode InstructionExecutor::ejecutar(const Instruction& instruction) {

    std::cout << "Comando: " << instruction.comando
        << " ,r: " << instruction.r
        << " ,s: " << instruction.s
        << " ,t: " << instruction.t
        << " ,d: " << instruction.d
        << std::endl;

    /*
    //Intruccion de final del programa (Maxima prioridad)
    if (instruction.comando == "HALT") {
        getValoresRegistros();
        system("pause");
        return ENDED;  // Salir del programa
    }

    //Verifica que se acceda solo a los registros existentes
    if ((instruction.r < 0 || instruction.r >= NUMERO_REGISTROS) ||
        (instruction.s < 0 || instruction.s >= NUMERO_REGISTROS) ||
        (instruction.t < 0 || instruction.t >= NUMERO_REGISTROS)) {
        return REGISTER_INDEX_ERROR;
    }

    //Calcula la direccion de memoria
    int a = instruction.d + registros[instruction.s];
    std::cout << "Direccion de memoria calculada (a): " << a << endl;
    getValoresRegistros();

    //Manipulacion directa de registros
    if (instruction.comando == "IN") {
        std::cout << "Ingrese un valor para el registro " << instruction.r << ": ";
        std::cin >> registros[instruction.r];
        std::cout << std::endl;
    }
    if (instruction.comando == "OUT"){ 
      std::cout << "Valor del registro " << instruction.r << ": " << registros[instruction.r] << std::endl << std::endl;
    }

    //Operaciones aritmeticas
    if (instruction.comando == "ADD") {
        registros[instruction.r] = registros[instruction.s] + registros[instruction.t];
    }
    if (instruction.comando == "SUB") {
        registros[instruction.r] = registros[instruction.s] - registros[instruction.t];
    }
    if (instruction.comando == "MUL") {
        registros[instruction.r] = registros[instruction.s] * registros[instruction.t];

    }
    if (instruction.comando == "DIV") {
        if (registros[instruction.t] != 0) {
            registros[instruction.r] = registros[instruction.s] / registros[instruction.t];
        }
        else {
            std::cout << "Error: Division por cero no permitida." << std::endl;
			return ARITH_ERROR;  // Error aritmetico
        }
    }

    //Instrucciones de memoria
    if (instruction.comando == "LD") {
        registros[instruction.r] = memoria.get(a);
    }
    if (instruction.comando == "LDA") {
        registros[instruction.r] = a;
    }
    if (instruction.comando == "LDC") {
        registros[instruction.r] = instruction.d;
    }
    if (instruction.comando == "ST") {
        if (a >= 0 && a < memoria.size()) {
            memoria.insert(a, registros[instruction.r]);
        }
        else {
            return MEMORY_OVERFLOW_ERROR;
        }
    }

    // Instrucciones de salto condicional
    else if (instruction.comando == "JLT") {  // Salta si registros[r] < 0
        if (registros[instruction.r] < 0) {
            if (a >= 0 && a < memoria.size()) {  // Validación del rango de la dirección de salto
                registros[registroEjecucion] = a;  // Actualiza el registro de ejecución
            }
            else {
                std::cerr << "Error: Dirección de salto fuera de rango en JLT: " << a << std::endl;
                return ENDED;  // Error en la instrucción
            }
        }
    }
    else if (instruction.comando == "JLE") {  // Salta si registros[r] <= 0
        if (registros[instruction.r] <= 0) {
            if (a >= 0 && a < memoria.size()) {
                registros[registroEjecucion] = a;
            }
            else {
                std::cerr << "Error: Dirección de salto fuera de rango en JLE: " << a << std::endl;
                return ENDED;
            }
        }
    }
    else if (instruction.comando == "JGE") {  // Salta si registros[r] >= 0
        if (registros[instruction.r] >= 0) {
            if (a >= 0 && a < memoria.size()) {
                registros[registroEjecucion] = a;
            }
            else {
                std::cerr << "Error: Dirección de salto fuera de rango en JGE: " << a << std::endl;
                return SYNTAX_ERROR;
            }
        }
    }
    else if (instruction.comando == "JGT") {  // Salta si registros[r] > 0
        if (registros[instruction.r] > 0) {
            if (a >= 0 && a < memoria.size()) {
                registros[registroEjecucion] = a;
            }
            else {
                std::cerr << "Error: Dirección de salto fuera de rango en JGT: " << a << std::endl;
                return SYNTAX_ERROR;
            }
        }
    }
    else if (instruction.comando == "JEQ") {  // Salta si registros[r] == 0
        if (registros[instruction.r] == 0) {
            if (a >= 0 && a < memoria.size()) {
                registros[registroEjecucion] = a;
            }
            else {
                std::cerr << "Error: Dirección de salto fuera de rango en JEQ: " << a << std::endl;
                return SYNTAX_ERROR;
            }
        }
    }
    else if (instruction.comando == "JNE") {  // Salta si registros[r] != 0
        if (registros[instruction.r] != 0) {
            if (a >= 0 && a < memoria.size()) {
                registros[registroEjecucion] = a;
            }
            else {
                std::cerr << "Error: Dirección de salto fuera de rango en JNE: " << a << std::endl;
                return SYNTAX_ERROR;
            }
        }
    }


    else {
        return SYNTAX_ERROR; // Si no hay una instrucción válida
    }
    */

    registros[registroEjecucion]++;
    return CONTINUE;  // Retorno para continuar ejecutando
}
