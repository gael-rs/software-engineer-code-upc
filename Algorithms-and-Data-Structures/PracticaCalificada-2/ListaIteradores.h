#pragma once

#include <functional>
#include <string>
#include "CProducto.h" // Asegurarnos de que la definición de Producto esté disponible

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
    Lista() : ini(nullptr), lon(0), comparar([](T a, T b) { return 0; }) {} // Comparador por defecto que no hace nada
    Lista(Comp comparar) : ini(nullptr), lon(0), comparar(comparar) {}
    ~Lista();

    uint longitud();

    bool esVacia();

    void agregaInicial(T elem);
    void agregaPos(T elem, uint pos);
    void agregaFinal(T elem);

    void modificarInicial(T elem);
    void modificarPos(T elem, uint pos);

    void borrarTodo();

    T obtenerInicial();
    T obtenerPos(uint pos);
    T obtenerFinal();
    T getPrimero();

    T buscar(T elem);


    class Iterator {
        unsigned int pos;
        Nodo* aux;
    public:
        Iterator(unsigned int pos, Nodo* aux) : pos(pos), aux(aux) {}
        void operator++() { pos++; aux = aux->sig; }
        bool operator!=(Iterator x) { return pos != x.pos; }
        T operator*() { return aux->elem; }

    };

    Iterator begin() {
        return Iterator(0, ini);
    }

    Iterator end() {
        return Iterator(lon, nullptr);
    }
};

template <typename T>
struct Lista<T>::Nodo {
    T elem;
    Nodo* sig;
    Nodo* ant;

    Nodo(T elem = T(), Nodo* ant = nullptr, Nodo* sig = nullptr) : elem(elem), ant(ant), sig(sig) {}

    T getDato() {
        return elem;
    }

    Nodo* getAnterior() {
        return ant;
    }

    Nodo* getSiguiente() {
        return sig;
    }
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
void Lista<T>::agregaFinal(T elem) {
    uint pos = longitud();
    agregaPos(elem, pos);
}

template <typename T>
void Lista<T>::borrarTodo() {
    Nodo* aux = ini;
    while (ini != nullptr) {
        aux = ini;
        ini = ini->sig;
        delete aux;
    }
    lon = 0;
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
        return T();
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
    return T();
}
template<typename T>
T Lista<T>::getPrimero() {
    return obtenerInicial();
}
