#include "RAM.h"
#include <iostream>

// Constructor por defecto
RAM::RAM() : tamanio(TAMANIO_DEFAULT) {
    ram = new int[TAMANIO_DEFAULT];
}

// Constructor con tamaño definido
RAM::RAM(unsigned int DATOS_MAXIMO) : tamanio(DATOS_MAXIMO) {
    ram = new int[DATOS_MAXIMO];
}

// Método para insertar valor en la memoria
void RAM::insert(int index, int value) {
    if (index >= 0 && index < tamanio) {
        ram[index] = value;
    }
    else {
        cerr << "Error: Intento de acceso fuera de los límites de la memoria en insert()." << endl;
    }
}

// Método para obtener un valor de la memoria
int RAM::get(int index) const {
    if (index >= 0 && index < tamanio) {
        return ram[index];
    }
    else {
        cerr << "Error: Intento de acceso fuera de los límites de la memoria en get()." << endl;
        return -1;
    }
}

// Método para obtener el tamaño de la memoria
int RAM::size() const {
    return tamanio;
}

