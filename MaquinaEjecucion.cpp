#include "MaquinaEjecucion.h"

// Constructor (inicializa la memoria con el tamaño seleccionado)
MaquinaEjecucion::MaquinaEjecucion() : memoria(DATOS_MAXIMO) {
    registros = new int[NUMERO_REGISTROS];      // Crea los registros

    // Inicializa los registros
    for (int i = 0; i < NUMERO_REGISTROS; i++) {
        registros[i] = 0;
    }

}



// Permite cargar en memoria las instrucciones del archivo
StatusCode MaquinaEjecucion::LeerArchivo(string filepath) {

    InstructionsFileReader reader;  // Crear una instancia de InstructionsFileReader
    return reader.leerInstrucciones(filepath, instrucciones, INSTRUCCIONES_MAXIMO);   // Carga las instrucciones en memoria

}



// Ejecuta las instrucciones de la memoria
StatusCode MaquinaEjecucion::EjecutarInstrucciones() {
    
    InstructionExecutor cpu(memoria, registros, NUMERO_REGISTROS, PC_REGISTRO);
    StatusCode estatus;

    for (unsigned int i = 0; i < INSTRUCCIONES_MAXIMO; i++) {
        const Instruction& instruccion = instrucciones[i];
        cout << instruccion.comando << endl;
    }

    return ENDED;
}



// Permite mostrar códigos de error
bool MaquinaEjecucion::MostrarError(StatusCode estatus) {

    if (estatus == ENDED || estatus == CONTINUE ) return false;


    std::cerr << ">>> [ERROR]: ";
    switch (estatus) {
        case LECTURE_ERROR:
            cerr << "Error leyendo el archivo";
            break;
        case PROGRAM_SIZE_LIMIT_ERROR:
            cerr << "El archivo es muy grande";
            break;
        case SYNTAX_ERROR:
            cerr << "Error en la sintaxis del programa";
            break;
        case REGISTER_INDEX_ERROR :
            cerr << "Resgistro fuera de los limites";
            break;
        case MEMORY_OVERFLOW_ERROR:
            cerr << "Memoria fuera de los limites";
            break;
        case ARITH_ERROR:
            cerr << "Error aritmetico";
            break;
        default:
            cerr << "Error desconocido";
            break;
    }

    std::cerr << endl;
    return true;

}



// Inicia la lectura sobre el archivo seleccionado
StatusCode MaquinaEjecucion::EjecutarArchivo(string filepath) {

    // Lee el archivo y retorna un código de estatus
    StatusCode estatus = LeerArchivo(filepath);

    // Si hay error interrumpe la ejecución
    if ( MostrarError(estatus) ) {
        return estatus;
    }

    // Ejecuta las instrucciones
    estatus = EjecutarInstrucciones();

    // Si hay error interrumpe la ejecución
    //MostrarError(estatus);
    return estatus;

}
