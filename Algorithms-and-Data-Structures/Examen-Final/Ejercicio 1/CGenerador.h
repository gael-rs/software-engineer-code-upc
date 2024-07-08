#pragma once
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "CVehiculo.h"

using namespace std;

class Generador {
private:
    static const int MAX_DATOS = 350;
    Data* datos;
    int num_datos;

    static const int NUM_MARCAS = 10;

    const string marcas[NUM_MARCAS] = {
        "Toyota", "Ford", "Honda", "Chevrolet", "Nissan",
        "Volkswagen", "BMW", "Mercedes", "Audi", "Hyundai"
    };

public:
    Generador() : num_datos(0) {

        datos = new Data[MAX_DATOS];
        srand(time(nullptr));
    }

    ~Generador() {
        delete[] datos;
    }

    void generar_datos(int num_datos);
    int obtenerNumDatos() const;
    Data obtenerDato(int indice) const;

};

void Generador::generar_datos(int num_datos) {
    if (num_datos > MAX_DATOS) {
        num_datos = MAX_DATOS;
    }

    for (int i = 0; i < num_datos; ++i) {
        Data dato;

        dato.IDVehiculo = rand() % 90000000 + 10000000; // 8 dígitos
        dato.marca = marcas[rand() % NUM_MARCAS];         // 2 dígitos, entre 10 y 99
        dato.modelo = rand() % 90 + 10; // 'M' o 'F'
        dato.color = rand() % 5 + 1 ;          // 0 o 1
        dato.asiento = rand() % 6; // 8 dígitos



        datos[i] = dato;
    }

    this->num_datos = num_datos;

    cout << "Registros generados: " << this->num_datos << endl;
}

int Generador::obtenerNumDatos() const {
    return num_datos;
}

Data Generador::obtenerDato(int indice) const {
    if (indice >= 0 && indice < num_datos) {
        return datos[indice];
    }
    else {
        return Data();
    }
}

