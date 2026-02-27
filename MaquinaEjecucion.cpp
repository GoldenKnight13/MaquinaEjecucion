#include "MaquinaEjecucion.h"

// Constructor (inicializa la memoria con el tamaño seleccionado)
MaquinaEjecucion::MaquinaEjecucion() : memoria(DATOS_MAXIMO) {
    registros = new int[NUMERO_REGISTROS];      // Crea los registros

    // Inicializa los registros
    for (int i = 0; i < NUMERO_REGISTROS; i++) {
        registros[i] = 0;
    }

    instruccionesValidas = {
        "HALT", "IN", "OUT", "ADD", "SUB", "MUL", "DIV",
        "LD", "LDA", "LDC", "ST",
        "JLT", "JLE", "JGE", "JGT", "JEQ", "JNE"
    };
}



// Permite cargar en memoria las instrucciones del archivo
int MaquinaEjecucion::LeerArchivo(string filepath) {

    InstructionsFileReader reader;  // Crear una instancia de InstructionsFileReader
    return reader.leerInstrucciones(filepath, instrucciones, INSTRUCCIONES_MAXIMO, instruccionesValidas);   // Carga las instrucciones en memoria

}



// Ejecuta las instrucciones de la memoria
int MaquinaEjecucion::EjecutarInstrucciones() {
    InstructionExecutor cpu(memoria, registros, NUMERO_REGISTROS, PC_REGISTRO);
    int estatus;

    while (true) {
        unsigned int i = cpu.num_instruccion();
        const auto& instruccion = instrucciones[i];
        estatus = cpu.ejecutar(instruccion);
        if (estatus == 1) return 1;
        else if (estatus == 4) return 3;
        i++;
    }

    return 1;
}



// Permite mostrar códigos de error
bool MaquinaEjecucion::MostrarError(int estatus) {
    switch (estatus) {
    case 0:
        cerr << "Error leyendo el archivo" << endl;
        return true;
    case 2:
        cerr << "El archivo es muy grande" << endl;
        return true;
    case 3:
        cerr << "Error en la sintaxis del programa" << endl;
        return true;
    default:
        return false;
    }
}



// Inicia la lectura sobre el archivo seleccionado
int MaquinaEjecucion::EjecutarArchivo(string filepath) {

    // Lee el archivo y retorna un código de estatus
    int estatus = LeerArchivo(filepath);

    // Si hay error interrumpe la ejecución
    if ( MostrarError(estatus) ) {
        return 0;
    }

    // Ejecuta las instrucciones
    estatus = EjecutarInstrucciones();

    // Si hay error interrumpe la ejecución
    if ( MostrarError(estatus) ) {
        return 0;
    }

    return 1;
}
