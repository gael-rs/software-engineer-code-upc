#pragma once
#include "Arbol BB.h"
#include <iostream>

using namespace std;

class MiArbolBinario : public ArbolBB<int> {
public:
    MiArbolBinario() : ArbolBB<int>([](int e) { cout << e << " "; }) {}

    // Función para insertar solo números de 2 o 3 dígitos
    bool insertar(int e) {
        if (e < 10 || e > 999) {
            cout << "Numero fuera de rango. Solo se aceptan numeros de 2 o 3 digitos.\n";
            return false;
        }
        return ArbolBB<int>::insertar(e);
    }

    // Función para calcular el promedio de elementos en el rango
    double promedio_rango(int valor) {
        double suma = 0;
        int cuenta = 0;
        promedio_rango_recursivo(this->obtenerRaiz(), valor, suma, cuenta);
        return cuenta == 0 ? 0.0 : suma / cuenta;
    }

    // Función para calcular el producto de los dígitos del mayor valor
    int producto_digitos() {
        int maximo = this->maximo();
        int producto = 1;
        while (maximo > 0) {
            producto *= (maximo % 10);
            maximo /= 10;
        }
        return producto;
    }

private:
    // Recorrido en orden para sumar y contar elementos en el rango
    void promedio_rango_recursivo(Nodo<int>* nodo, int valor, double& suma, int& cuenta) {
        if (nodo == nullptr) return;
        promedio_rango_recursivo(nodo->izq, valor, suma, cuenta);
        if (nodo->elemento <= valor) {
            suma += nodo->elemento;
            cuenta++;
        }
        promedio_rango_recursivo(nodo->der, valor, suma, cuenta);
    }
};
