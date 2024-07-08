#pragma once

#include <functional>

using namespace std;

typedef unsigned int uint;

template <typename T>
class Lista {
    struct Nodo;
    typedef function<int(T, T)> Comp;

    Nodo* ini;
    uint lon; // número de elementos en la lista

    Comp comparar; // lambda de criterio de comparación

public:
    Lista() : ini(nullptr), lon(0), comparar([](T a, T b) {return a - b; }) {}
    Lista(Comp comparar) : ini(nullptr), lon(0), comparar(comparar) {}
    ~Lista();

    uint longitud();

    bool esVacia();

    void agregaInicial(T elem);
    void agregaPos(T elem, uint pos);

    void modificarInicial(T elem);
    void modificarPos(T elem, uint pos);

    T obtenerInicial();
    T obtenerPos(uint pos);
    T obtenerFinal();

    T buscar(T elem);
};

template <typename T>
struct Lista<T>::Nodo {
    T elem;
    Nodo* sig; // puntero apunta al siguiente nodo

    Nodo(T elem = NULL, Nodo* sig = nullptr) : elem(elem), sig(sig) {}
};

template <typename T>
Lista<T>::~Lista() {
    Nodo* aux = ini;
    while (ini != nullptr) {
        aux = ini;
        ini = ini->sig;
        delete aux;
    }
}

template <typename T>
uint Lista<T>::longitud() {
    return lon;
}

template <typename T>
bool Lista<T>::esVacia() {
    return lon == 0;
}

template <typename T>
void Lista<T>::agregaInicial(T elem) {
    Nodo* nuevo = new Nodo(elem, ini);
    if (nuevo != nullptr) {
        ini = nuevo;
        lon++;
    }
}

template <typename T>
void Lista<T>::agregaPos(T elem, uint pos) {
    if (pos > lon) return;
    if (pos == 0) {
        agregaInicial(elem);
    }
    else {
        Nodo* aux = ini;
        for (int i = 1; i < pos; i++) {
            aux = aux->sig;
        }
        Nodo* nuevo = new Nodo(elem, aux->sig);
        if (nuevo != nullptr) {
            aux->sig = nuevo;
            lon++;
        }
    }
}

template <typename T>
void Lista<T>::modificarInicial(T elem) {
    if (lon > 0) {
        ini->elem = elem;
    }
}
template <typename T>
void Lista<T>::modificarPos(T elem, uint pos) {
    if (pos >= 0 && pos < lon) {
        Nodo* aux = ini;
        for (int i = 0; i < pos; i++) {
            aux = aux->sig;
        }
        aux->elem = elem;
    }
}


template <typename T>
T Lista<T>::obtenerInicial() {
    return obtenerPos(0);
}

template <typename T>
T Lista<T>::obtenerPos(uint pos) { 
    if (pos >= 0 && pos < lon) {
        Nodo* aux = ini;
        for (int i = 0; i < pos; i++) {
            aux = aux->sig;
        }
        return aux->elem;
    }
    else {
        return NULL;
    }
}
template <typename T>
T Lista<T>::obtenerFinal() {
    return obtenerPos(lon - 1);
}

template <typename T>
T Lista<T>::buscar(T elem) {
    Nodo* aux = ini;
    while (aux != nullptr) {
        if (comparar(aux->elem, elem) == 0) {
            return aux->elem;
        }
        aux = aux->sig;
    }
    return NULL;
}
