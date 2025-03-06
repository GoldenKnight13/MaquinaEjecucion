#pragma once

// Librerías
#include <iostream>
using namespace std;

// Variables globales
#define TAMANIO_DEFAULT 256

// Clase que simula la memoria RAM
class RAM {

private:
    // Variables internas
    int tamanio; // Tamaño de la memoria
    int* ram;    // Puntero a la memoria RAM

public:
    // Constructores
    RAM();
    RAM(unsigned int DATOS_MAXIMO);

    // Métodos
    void insert(int index, int value);
    int get(int index) const;
    int size() const;


};
