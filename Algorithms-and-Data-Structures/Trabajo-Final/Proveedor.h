#pragma once
#include "Cola.h"
#define MAX 45
#define MIN 5

template <class T>
class Proveedor: public Cola<T>
{
private:
	int pos;

public:
	Proveedor();
	~Proveedor();

	void agregarPedido(string nombre, int cantidad);
	T recibirPedido();
	float generarPrecio(int cantidad);

};

template<class T>
inline Proveedor<T>::Proveedor(): Cola<T>()
{
}

template <class T>
Proveedor<T>::~Proveedor()
{
}

template<class T>
inline void Proveedor<T>::agregarPedido(string nombre, int cantidad)
{
	float precio = generarPrecio(cantidad);

	Medicamento<string, int, float>* medicamento = new Medicamento<string, int, float>(nombre, cantidad, precio);

	enqueue(*medicamento);
}



template<class T>
inline T Proveedor<T>::recibirPedido()
{	
	T primerPedido = peek().dato;
	dequeue();

	return primerPedido;
}

template<class T>
inline float Proveedor<T>::generarPrecio(int cantidad)
{
	float precio = ((float(rand()) / float(RAND_MAX)) * (MAX - MIN + 1) + MIN) * float(cantidad);
	return precio;
}
