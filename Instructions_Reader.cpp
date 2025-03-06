#include "Instructions_Reader.h"
#include <algorithm>

// Constructor que recibe una referencia al ejecutor de instrucciones
InstructionsReader::InstructionsReader(InstructionExecutor& executor)
    : executor(executor) {}

// Función para procesar y ejecutar las instrucciones
void InstructionsReader::procesarInstrucciones(const std::vector<Instruction>& instrucciones) {
    for (const auto& instruccion : instrucciones) {
        // Validar la instrucción antes de ejecutarla
        if (validarInstruccion(instruccion)) {
            // Ejecutar la instrucción si es válida
            executor.ejecutar(instruccion);
        }
        else {
            // Imprimir un mensaje de error si la instrucción no es válida
            std::cerr << "Instrucción inválida: " << instruccion.comando << std::endl;
        }
    }
}

// Método para validar la estructura de una instrucción
bool InstructionsReader::validarInstruccion(const Instruction& instruccion) {
    // Lista de comandos válidos
    const std::vector<std::string> comandos_validos = { "IN", "OUT", "ADD", "SUB", "MUL", "DIV", "LD", "LDA", "LDC", "ST" };

    // Validar si el comando de la instrucción es uno de los comandos válidos
    if (std::find(comandos_validos.begin(), comandos_validos.end(), instruccion.comando) == comandos_validos.end()) {
        return false;  // Comando no válido
    }

    // Validar índices de registros
    // Verifica que los índices de registros (r, s, t) estén dentro del rango permitido
    if (instruccion.r >= NUMERO_REGISTROS || instruccion.s >= NUMERO_REGISTROS || instruccion.t >= NUMERO_REGISTROS) {
        return false;  // Índice de registro fuera de rango
    }

    // Validación adicional para el desplazamiento (d) si es necesario

    return true;  // Instrucción válida
}
