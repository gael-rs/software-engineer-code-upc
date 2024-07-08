#pragma once
#include <iostream>
#include "CVehiculo.h"

using namespace std;

template <class T>
int particion(T* A, int p, int r) {
    int x = A[r].getColor(); //el pivote
    int i = p - 1; //indice de los menores
    for (int j = p; j < r; j++) {
        if (A[j].getColor() <= x) {
            i++;
            swap(A[i], A[j]);
        }
    }
    swap(A[i + 1], A[r]);
    return i + 1;
}

template <class T>
void quicksort(T* A, int p, int r) {
    int q; //para almacenar el indice del pivote
    if (p < r) {
        q = particion(A, p, r); //devuelve el indice del pivote
        quicksort(A, p, q - 1);
        quicksort(A, q + 1, r);
    }
}