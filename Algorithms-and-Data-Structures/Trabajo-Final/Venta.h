#pragma once
#include "Lista_Medicamentos.h"

template<class T>
class Venta
{
public:
	Venta();
	Venta(string n, int c);
	~Venta();

	string nombre;
	int cantidad;

private:

};

template<class T>
inline Venta<T>::Venta(){

}

template<class T>
inline Venta<T>::Venta(string n, int c){
}

template<class T>
inline Venta<T>::~Venta()
{
}
