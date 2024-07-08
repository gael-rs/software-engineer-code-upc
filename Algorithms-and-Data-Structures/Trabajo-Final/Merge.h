#pragma once
#include <functional>

using namespace std;

template<class T, class T2>
inline void Merge(T* listaIzquierda, 
           T* listaDerecha,
           T* listaFinal,
           function<bool(T2, T2)> cb)
    {
    auto it1 = listaIzquierda->begin();
    auto it2 = listaDerecha->begin();

    while (it1 != listaIzquierda->end() && it2 != listaDerecha->end()) {
        auto temp1 = it1;
        auto temp2 = it2;

        if (cb(*temp1, *temp2)) {
            listaFinal->agregaFinal(*temp1);
            ++it1;
        }
        else {
            listaFinal->agregaFinal(*temp2);
            ++it2;
        }
    }

    while (it1 != listaIzquierda->end()) {
        listaFinal->agregaFinal(*it1);
        ++it1;
    }

    while (it2 != listaDerecha->end()) {
        listaFinal->agregaFinal(*it2);
        ++it2;
    }
}

template<class T, class T2>
inline void mergeSort(T* lst, function<bool(T2, T2)> cb) {
    // Caso base: si la lista tiene 0 o 1 elemento, está ordenada
    if (lst->get_lon() <= 1) {
        return;
    }

    // Dividir la lista en mitades
    int mitad = lst->get_lon() / 2;
    T* listaIzquierda = new T;
    T* listaDerecha = new T;

    auto it = lst->begin();
    for (int i = 0; i < mitad; ++i) {
        listaIzquierda->agregaFinal(*it);
        ++it;
    }

    for (int i = mitad; i < lst->get_lon(); ++i) {
        listaDerecha->agregaFinal(*it);
        ++it;
    }

    // Llamar recursivamente a mergeSort para ordenar las sublistas
    mergeSort<T, T2>(listaIzquierda, cb);
    mergeSort<T, T2>(listaDerecha, cb);

    // Fusionar las sublistas ordenadas para formar la lista final ordenada
    lst->borrarTodo();
    Merge<T, T2>(listaIzquierda, listaDerecha, lst, cb);

    // Liberar memoria
    delete listaIzquierda;
    delete listaDerecha;
}