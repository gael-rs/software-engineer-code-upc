#pragma once
#include "Encabezados.h"

template<class T>
class Nodo
{
public:
	T dato;
	Nodo<T>* siguiente;

	//Contructor sin parametros

	Nodo();

	//Constructor con parametros
	Nodo(T v, Nodo<T>* sig = nullptr);

};

template<class T>
inline Nodo<T>::Nodo()
{
	dato = 0;
	siguiente = nullptrptr;
}

template<class T>
inline Nodo<T>::Nodo(T v, Nodo<T>* sig = nullptr)
{
	dato = v;
	siguiente = sig;
}
