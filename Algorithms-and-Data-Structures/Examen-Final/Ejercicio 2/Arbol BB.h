#pragma once
#include <functional>

using namespace std;

template <class T>
class Nodo {
public:
    T elemento;
    Nodo* izq;
    Nodo* der;

    Nodo() : izq(nullptr), der(nullptr) {}
};

template <class T>
class ArbolBB {
    typedef function<int(T, T)> Comp; 

    Nodo<T>* raiz;
    void(*procesar)(T); 

    Comp comparar; 

protected:
    Nodo<T>* obtenerRaiz() const {
        return raiz;
    }

private:
    bool _buscar(Nodo<T>* nodo, T e) {
        if (nodo == nullptr) return false;
        else {
            int r = comparar(nodo->elemento, e);
            if (r == 0) return true;
            else if (r < 0) {
                return _buscar(nodo->der, e);
            }
            else {
                return _buscar(nodo->izq, e);
            }
        }
    }

    Nodo<T>* _obtener(Nodo<T>* nodo, T e) {
        if (nodo == nullptr) return nullptr;
        else {
            int r = comparar(nodo->elemento, e);
            if (r == 0) return nodo;
            else if (r < 0) {
                return _obtener(nodo->der, e);
            }
            else {
                return _obtener(nodo->izq, e);
            }
        }
    }

    bool _insertar(Nodo<T>*& nodo, T e) {
        if (nodo == nullptr) {
            nodo = new Nodo<T>();
            nodo->elemento = e;
            return true;
        }
        else {
            int r = comparar(nodo->elemento, e);
            if (r == 0) return false;
            else if (r < 0) {
                return _insertar(nodo->der, e);
            }
            else {
                return _insertar(nodo->izq, e);
            }
        }
    }

    void _enOrden(Nodo<T>* nodo) {
        if (nodo == nullptr) return;
        _enOrden(nodo->izq);
        procesar(nodo->elemento);
        _enOrden(nodo->der);
    }

    bool _vacio() {
        return raiz == nullptr;
    }

    int _cantidad(Nodo<T>* nodo) {
        if (nodo == nullptr)
            return 0;
        else
        {
            int ci, cd;
            ci = _cantidad(nodo->izq);
            cd = _cantidad(nodo->der);
            return 1 + ci + cd;
        }
    }

    int _altura(Nodo<T>* nodo) {
        if (nodo == nullptr)
            return 0;
        else
        {
            int ai, ad;
            ai = 1 + _altura(nodo->izq);
            ad = 1 + _altura(nodo->der);
            return ai > ad ? ai : ad;
        }
    }

    T _minimo(Nodo<T>* nodo) {
        if (nodo->izq == nullptr) return nodo->elemento;
        else
            return _minimo(nodo->izq);
    }

    T _maximo(Nodo<T>* nodo) {
        if (nodo->der == nullptr) return nodo->elemento;
        else
            return _maximo(nodo->der);
    }

    bool _eliminar(Nodo<T>*& nodo, T e) {
        if (nodo == nullptr) return false;
        else {
            int r = comparar(nodo->elemento, e);
            if (r < 0) {
                return _eliminar(nodo->der, e);
            }
            else if (r > 0) {
                return _eliminar(nodo->izq, e);
            }
            else {
                if (nodo->der == nullptr && nodo->izq == nullptr) {
                    delete nodo;
                    nodo = nullptr;
                    return true;
                }
                else if (nodo->izq == nullptr) {
                    Nodo<T>* der = nodo->der;
                    delete nodo;
                    nodo = der;
                    return true;
                }
                else if (nodo->der == nullptr) {
                    Nodo<T>* izq = nodo->izq;
                    delete nodo;
                    nodo = izq;
                    return true;
                }
                else {
                    Nodo<T>* aux = nodo->der;
                    while (aux->izq != nullptr)
                    {
                        aux = aux->izq;
                    }
                    nodo->elemento = aux->elemento;
                    return _eliminar(nodo->der, aux->elemento);
                }
            }
        }
    }

public:
    ArbolBB(void(*otroPunteroAFuncion)(T)) {
        this->procesar = otroPunteroAFuncion;
        this->comparar = [](T a, T b)->int { return a - b; };
        raiz = nullptr;
    }

    ArbolBB(void(*otroPunteroAFuncion)(T), Comp comparar) {
        this->procesar = otroPunteroAFuncion;
        this->comparar = comparar;
        raiz = nullptr;
    }

    bool insertar(T e) {
        return _insertar(raiz, e);
    }

    void enOrden() {
        _enOrden(raiz);
    }

    int cantidad() {
        return _cantidad(raiz);
    }

    int altura() {
        return _altura(raiz);
    }

    bool buscar(T e) {
        return _buscar(raiz, e);
    }

    T minimo() {
        return _minimo(raiz);
    }

    T maximo() {
        return _maximo(raiz);
    }

    bool eliminar(T e) {
        return _eliminar(raiz, e);
    }
};
