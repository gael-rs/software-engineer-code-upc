#pragma once
#include <cstdlib> // incluidos para el uso del random
#include <ctime> // incluidos para el uso del random
#include "CProducto.h"

using namespace std;

class Generador {
private:
    static const int MAX_PRODUCTOS = 400; // Tamaño máximo del arreglo
    Producto productos[MAX_PRODUCTOS]; // Arreglo de registros
    int num_productos; // Número actual de registros

public:
    Generador() : num_productos(0) {
        
        srand(time(0));

    }

    void generar_datos(int num_productos);
    int obtenerNumProductos() const; // Método para obtener el número de registros
    Producto obtenerProducto(int indice) const; // Método para obtener un registro específico
};

void Generador::generar_datos(int num_productos) {
    if (num_productos > MAX_PRODUCTOS) {
        // Si se solicita generar más registros de los que caben en el arreglo, ajustamos num_registros
        num_productos = MAX_PRODUCTOS;
    }

    string ids[] = { "UUU", "OOO", "III", "EEE", "AAA" };
    string nombres[] = { "Gael", "Eduardo" };

    for (int i = 0; i < num_productos; ++i) {
        string id = ids[rand() % 5];
        string nombre = nombres[rand() % 2];
        int categoria = rand() % 1000000 + 10000;
        int stock = rand() % 50000 + 100;
        int precio = rand () % 50000 + 100;
        int fecha_caducidad = rand() % 50000 + 100;

        Producto prod;
        prod.id = id;
        prod.nombre = nombre;
        prod.categoria = categoria;
        prod.stock = stock;
        prod.precio = precio;
        prod.fecha_caducidad = fecha_caducidad;

        productos[i] = prod;
    }

    // Actualizamos el número de registros generados
    this->num_productos = num_productos;

	cout << "Registros generados: " << this->num_productos << endl;
}

int Generador::obtenerNumProductos() const {
    return num_productos;
}

Producto Generador::obtenerProducto(int indice) const {
    if (indice >= 0 && indice < num_productos) {
        return productos[indice];
    }
}

