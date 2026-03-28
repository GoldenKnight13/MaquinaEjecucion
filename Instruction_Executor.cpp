#include "Instruction_Executor.h"

//Permite inicializar el mapa hash que trnaforma instrucciones en acciones
void InstructionExecutor::iniciarMapaInstrucciones() {

    //Finalizacion de programa
    OPERACIONES[InstructionSet::KEYWORD::HALT] = [this](const Instruction& instruction) -> StatusCode {
        return ENDED;
    };

    //Funciones de IO
    OPERACIONES[InstructionSet::KEYWORD::IN] = [this](const Instruction& instruction) -> StatusCode {

        //Valida que se intente acceder a un registro valido
        const int registroDestino = instruction.r;
        if (!esRegistroValido(registroDestino)) return REGISTER_INDEX_ERROR;

        //Intenta obtener el valor del usuario
        int entrada;
        std::cout << "Ingrese un valor para el registro " << instruction.r << ": ";

        if ( !(std::cin >> entrada) ) {

            //En caso de que se cierre la terminal o haya un error en el flujo de entrada
            if (std::cin.eof()) return ENDED; 

            std::cin.clear();   //Se limpian las banderas 
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //Limpieza del buffer

            //Retorno del error
            return INPUT_ERROR;
        }
        
        //Ingresa el valor en el registro solicitado
        registros[registroDestino] = entrada;
        std::cout << std::endl;

        registros[registroEjecucion]++;
        return CONTINUE;
    };
    OPERACIONES[InstructionSet::KEYWORD::OUT] = [this](const Instruction& instruction) -> StatusCode {

        //Verifica si el registro es valido
        const int registroDestino = instruction.r;
        if (!esRegistroValido(registroDestino)) return REGISTER_INDEX_ERROR;

        //Muestra la informacion solicitada
        std::cout << "Valor del registro " << instruction.r << ": " << registros[instruction.r] << std::endl << std::endl;

        registros[registroEjecucion]++;
        return CONTINUE;
    };
    
    //Funciones aritmeticas
    OPERACIONES[InstructionSet::KEYWORD::ADD] = [this](const Instruction& instruction) -> StatusCode {

        const int destino = instruction.r, operando1 = instruction.s, operando2 = instruction.t;

        if ( !esRegistroValido(destino) || !esRegistroValido(operando1) || !esRegistroValido(operando2) )
            return REGISTER_INDEX_ERROR;

        registros[destino] = registros[operando1] + registros[operando2];

        registros[registroEjecucion]++;
        return CONTINUE;
    };
    OPERACIONES[InstructionSet::KEYWORD::SUB] = [this](const Instruction& instruction) -> StatusCode {

        const int destino = instruction.r, operando1 = instruction.s, operando2 = instruction.t;

        if (!esRegistroValido(destino) || !esRegistroValido(operando1) || !esRegistroValido(operando2))
            return REGISTER_INDEX_ERROR;

        registros[destino] = registros[operando1] - registros[operando2];

        registros[registroEjecucion]++;
        return CONTINUE;
    };
    OPERACIONES[InstructionSet::KEYWORD::MUL] = [this](const Instruction& instruction) -> StatusCode {

        const int destino = instruction.r, operando1 = instruction.s, operando2 = instruction.t;

        if (!esRegistroValido(destino) || !esRegistroValido(operando1) || !esRegistroValido(operando2))
            return REGISTER_INDEX_ERROR;

        registros[destino] = registros[operando1] * registros[operando2];

        registros[registroEjecucion]++;
        return CONTINUE;
    };
    OPERACIONES[InstructionSet::KEYWORD::DIV] = [this](const Instruction& instruction) -> StatusCode {

        const int destino = instruction.r, operando1 = instruction.s, operando2 = instruction.t;

        if (!esRegistroValido(destino) || !esRegistroValido(operando1) || !esRegistroValido(operando2))
            return REGISTER_INDEX_ERROR;

        const int divisor = registros[operando2];
        if (divisor == 0) return ARITH_ERROR;

        registros[destino] = registros[operando1] / registros[operando2];

        registros[registroEjecucion]++;
        return CONTINUE;
    };

    //Funciones de memoria
    OPERACIONES[InstructionSet::KEYWORD::LD] = [this](const Instruction& instruction) -> StatusCode {

        const int direccion = calcularDireccionMemoria(instruction);
        const int destino = instruction.r;

        //Valida que se pueda tenga una direccion de memoria y regsitro validos
        if (direccion < 0 || direccion >= memoria.size() ) return MEMORY_OVERFLOW_ERROR;
        if ( !esRegistroValido( destino ) ) return REGISTER_INDEX_ERROR; 

        //Realiza una verificacion de que se obtuvo la informacion de forma correcta
        int valor;
        StatusCode estatus = memoria.get(direccion, valor);
        if (estatus == CONTINUE) registros[destino] = valor;

        registros[registroEjecucion]++;
        return estatus;
    };
    OPERACIONES[InstructionSet::KEYWORD::LDA] = [this](const Instruction& instruction) -> StatusCode {

        const int direccion = calcularDireccionMemoria(instruction);
        const int destino = instruction.r;

        //Valida que se pueda tenga una direccion de memoria y regsitro validos
        if (direccion < 0 || direccion >= memoria.size()) return MEMORY_OVERFLOW_ERROR;
        if (!esRegistroValido(destino)) return REGISTER_INDEX_ERROR;

        registros[destino] = direccion;

        registros[registroEjecucion]++;
        return CONTINUE;
    };
    OPERACIONES[InstructionSet::KEYWORD::LDC] = [this](const Instruction& instruction) -> StatusCode {

        const int origen = instruction.d;
        const int destino = instruction.r;

        //Valida que se acceda a registros existentes
        if ( !esRegistroValido(origen) || !esRegistroValido(destino) ) return REGISTER_INDEX_ERROR;

        registros[destino] = origen;

        registros[registroEjecucion]++;
        return CONTINUE;
    };
    OPERACIONES[InstructionSet::KEYWORD::ST] = [this](const Instruction& instruction) -> StatusCode {
        
        const int direccion = calcularDireccionMemoria(instruction);
        const int origen = instruction.r;

        //Valida que se pueda tenga una direccion de memoria y regsitro validos
        if (direccion < 0 || direccion >= memoria.size()) return MEMORY_OVERFLOW_ERROR;
        if (!esRegistroValido(origen) ) return REGISTER_INDEX_ERROR;

        //Verifica que se haya insertado correctamente la informacion en la memoria
        const StatusCode estatusMemoria = memoria.insert(direccion, registros[origen] );

        registros[registroEjecucion]++;
        return estatusMemoria;
    };

    //Funciones de salto
    OPERACIONES[InstructionSet::KEYWORD::JLT] = [this](const Instruction& instruction) -> StatusCode {

        //Valida que se pueda tenga una direccion de regsitro valida
        const int origen = instruction.r;
        if (!esRegistroValido(origen)) return REGISTER_INDEX_ERROR;

        //Salta de instruccion si es que el registro tiene un valor menor que 0
        if (registros[origen] < 0) {

            const int direccion = calcularDireccionMemoria(instruction);
            if (direccion < 0 || direccion >= memoria.size()) return MEMORY_OVERFLOW_ERROR;

            registros[registroEjecucion] = direccion;

        }
        else registros[ registroEjecucion ]++;

        return CONTINUE;
    };
    OPERACIONES[InstructionSet::KEYWORD::JLE] = [this](const Instruction& instruction) -> StatusCode {

        //Valida que se pueda tenga una direccion de regsitro valida
        const int origen = instruction.r;
        if (!esRegistroValido(origen)) return REGISTER_INDEX_ERROR;

        //Salta de instruccion si es que el registro tiene un valor menor o igual que 0
        if (registros[origen] <= 0) {

            const int direccion = calcularDireccionMemoria(instruction);
            if (direccion < 0 || direccion >= memoria.size()) return MEMORY_OVERFLOW_ERROR;

            registros[registroEjecucion] = direccion;

        }
        else registros[registroEjecucion]++;

        return CONTINUE;

    };
    OPERACIONES[InstructionSet::KEYWORD::JGT] = [this](const Instruction& instruction) -> StatusCode {

        //Valida que se pueda tenga una direccion de regsitro valida
        const int origen = instruction.r;
        if (!esRegistroValido(origen)) return REGISTER_INDEX_ERROR;

        //Salta de instruccion si es que el registro tiene un valor mayor que 0
        if (registros[origen] > 0) {

            const int direccion = calcularDireccionMemoria(instruction);
            if (direccion < 0 || direccion >= memoria.size()) return MEMORY_OVERFLOW_ERROR;

            registros[registroEjecucion] = direccion;

        }
        else registros[registroEjecucion]++;

        return CONTINUE;

    };
    OPERACIONES[InstructionSet::KEYWORD::JGE] = [this](const Instruction& instruction) -> StatusCode {

        //Valida que se pueda tenga una direccion de regsitro valida
        const int origen = instruction.r;
        if (!esRegistroValido(origen)) return REGISTER_INDEX_ERROR;

        //Salta de instruccion si es que el registro tiene un valor mayor o igual que 0
        if (registros[origen] >= 0) {

            const int direccion = calcularDireccionMemoria(instruction);
            if (direccion < 0 || direccion >= memoria.size()) return MEMORY_OVERFLOW_ERROR;

            registros[registroEjecucion] = direccion;

        }
        else registros[registroEjecucion]++;

        return CONTINUE;
    };
    OPERACIONES[InstructionSet::KEYWORD::JEQ] = [this](const Instruction& instruction) -> StatusCode {

        //Valida que se pueda tenga una direccion de regsitro valida
        const int origen = instruction.r;
        if (!esRegistroValido(origen)) return REGISTER_INDEX_ERROR;

        //Salta de instruccion si es que el registro tiene un valor igual a 0
        if (registros[origen] == 0) {

            const int direccion = calcularDireccionMemoria(instruction);
            if (direccion < 0 || direccion >= memoria.size()) return MEMORY_OVERFLOW_ERROR;

            registros[registroEjecucion] = direccion;

        }
        else registros[registroEjecucion]++;

        return CONTINUE;
    };
    OPERACIONES[InstructionSet::KEYWORD::JNE] = [this](const Instruction& instruction) -> StatusCode {

        //Valida que se pueda tenga una direccion de regsitro valida
        const int origen = instruction.r;
        if (!esRegistroValido(origen)) return REGISTER_INDEX_ERROR;

        //Salta de instruccion si es que el registro tiene un valor distinto de 0
        if (registros[origen] != 0) {

            const int direccion = calcularDireccionMemoria(instruction);
            if (direccion < 0 || direccion >= memoria.size()) return MEMORY_OVERFLOW_ERROR;

            registros[registroEjecucion] = direccion;

        }
        else registros[registroEjecucion]++;

        return CONTINUE;
    };

}

//Permite saber si se puede acceder a los registros seleccionados
bool InstructionExecutor::esRegistroValido(int seleccion) {
    return (seleccion > 0) && (seleccion < NUMERO_REGISTROS);
};

//Calcula la direccion de memoria deseada
int InstructionExecutor::calcularDireccionMemoria(const Instruction& instruction) {
    int registroAccedido = instruction.s;
    if (!esRegistroValido(registroAccedido)) return -1;
    else return instruction.d + registros[registroAccedido];
}

// Constructor de la clase InstructionExecutor
InstructionExecutor::InstructionExecutor(RAM& ram, int* reg, int numReg, int regExec)
    : memoria(ram), registros(reg), NUMERO_REGISTROS(numReg), registroEjecucion(regExec) {

    iniciarMapaInstrucciones();
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

    //Muestra la informacion de la instruccion
    std::cout << "Comando: " << instruction.comando
        << " ,r: " << instruction.r
        << " ,s: " << instruction.s
        << " ,t: " << instruction.t
        << " ,d: " << instruction.d
        << std::endl;

    //Muestra el estado actual de la maquina de ejecucion
    getValoresRegistros();

    //Busca la instruccion solicitada, si puede la ejecuta y retorna el estado de la maquina
    auto it = OPERACIONES.find( instruction.comando );
    if (it != OPERACIONES.end()) return it->second(instruction);
    else return SYNTAX_ERROR;

}
