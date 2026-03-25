#pragma once
#include "Instruction_Set.h"

// TIPOS DE INSTRUCCIONES DE LA MAQUINA VIRTUAL
struct Instruction {
    InstructionSet::KEYWORD comando;  // El comando de la instrucción (e.g., "ADD", "SUB")
    unsigned int r;       // Registro destino
    unsigned int d;       // Desplazamiento o constante (opcional)
    unsigned int s;       // Registro fuente 1
    unsigned int t;       // Registro fuente 2

    // Constructor para inicializar todos los valores (Cuenta con valores por defecto)
    Instruction(InstructionSet::KEYWORD cmd = InstructionSet::KEYWORD::UNKNOWN, unsigned int reg_r = 0, unsigned int reg_d = 0,
        unsigned int reg_s = 0, unsigned int reg_t = 0)
        : comando(cmd), r(reg_r), d(reg_d), s(reg_s), t(reg_t) {}
};
