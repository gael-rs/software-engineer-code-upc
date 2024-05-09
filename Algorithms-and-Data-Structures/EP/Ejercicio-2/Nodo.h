#pragma once

template<class T>
class Nodo {
public:
    T dato;
    Nodo<T>* siguiente;

    Nodo(T v, Nodo<T>* sig = nullptr) {
        dato = v;
        siguiente = sig;
    }

    T getDato() {
        return dato;
    }

    Nodo<T>* getSiguiente() {
        return siguiente;
    }

    void setDato(T dato) {
        this->dato = dato;
    }

    void setSiguiente(Nodo<T>* siguiente) {
        this->siguiente = siguiente;
    }

};
