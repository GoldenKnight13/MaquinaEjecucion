#include "RAM.h"

// Constructor por defecto
RAM::RAM() : tamanio(TAMANIO_DEFAULT) {
    ram = new int[TAMANIO_DEFAULT];
}

// Constructor con tamaño definido
RAM::RAM(unsigned int DATOS_MAXIMO) : tamanio(DATOS_MAXIMO) {
    ram = new int[DATOS_MAXIMO];
}

//Inserta un dato en la memoria RAM, devolviendo un codigo de estatus para saber si fue posible insertar el valor
StatusCode RAM::insert(int index, int value) {
    if (index >= 0 && index < tamanio) {
        ram[index] = value;
        return CONTINUE;
    }
    else {
        cerr << "Error: Intento de acceso fuera de los límites de la memoria en insert()." << endl;
        return MEMORY_OVERFLOW_ERROR;
    }
}

// Método para obtener un valor de la memoria
StatusCode RAM::get(int index, int& returnValue) const {
    if (index >= 0 && index < tamanio) {
        returnValue = ram[index];
        return CONTINUE;
    }
    else {
        cerr << "Error: Intento de acceso fuera de los límites de la memoria en get()." << endl;
        return MEMORY_OVERFLOW_ERROR;
    }
}

// Método para obtener el tamaño de la memoria
int RAM::size() const {
    return tamanio;
}

