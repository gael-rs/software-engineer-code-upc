#pragma once
#include "Medicamento.h"

template<class T>
class Lista_Medicamentos
{
private:
	struct Nodo;
	Nodo* ini;
	int lon;

public:
	Lista_Medicamentos();
	~Lista_Medicamentos();
	void    agregaInicial(T medicina);
	void    eliminaInicial();
	void    eliminarPos(int pos);
	void	coutLista();
	int get_lon();
	void forEach(function<void(T)> callback);
	T       obtenerPos(int pos);
	void actualizarArchivo();
};

template <typename T>
struct Lista_Medicamentos<T>::Nodo {
	T       medicina;
	Nodo* sig;

	Nodo(T medicina = NULL, Nodo* sig = nullptr) : medicina(medicina), sig(sig) {}
};



template<class T>
Lista_Medicamentos<T>::Lista_Medicamentos()
{
	this->ini = nullptr;
	this->lon = 0;
}



template<class T>
Lista_Medicamentos<T>::~Lista_Medicamentos()
{
}

template <typename T>
void Lista_Medicamentos<T>::agregaInicial(T medicina) {
	Nodo* nuevo = new Nodo(medicina, ini);
	if (nuevo != nullptr) {
		ini = nuevo;
		lon++;
	}
}


template <typename T>
void Lista_Medicamentos<T>::eliminaInicial() {
	if (lon > 0) {
		Nodo* aux = ini;
		ini = ini->sig;
		delete aux;
		lon--;
	}
}


template<class T>
inline void Lista_Medicamentos<T>::eliminarPos(int pos)
{
	if (pos >= 0 && pos < lon) {
		Nodo* aux = ini;
		Nodo* anterior = nullptr;
		for (int i = 0; i < pos; i++) {
			anterior = aux;
			aux = aux->sig;
		}
		if (anterior != nullptr) {
			anterior->sig = aux->sig;
		}
		else {
			ini = aux->sig;
		}
		delete aux;
		lon--;
	}
}


template<class T>
inline void Lista_Medicamentos<T>::coutLista()
{
	int pos = 0;
	Nodo* aux = ini;

	Lista_Medicamentos<T>* auxLista = new Lista_Medicamentos<T>();

	while (aux != nullptr) {
		auxLista->agregaInicial(aux->medicina);
		aux = aux->sig;
	}

	Nodo* auxAux = auxLista->ini;

	if (ini != nullptr && ini->sig != nullptr) {
		int n = rand() % 3;

		switch (n)
		{
		case 0: {
			Nodo* temp1;
			Nodo* temp2;
			bool intercambiado;

			do {
				intercambiado = false;
				temp1 = auxLista->ini;
				temp2 = temp1->sig;

				while (temp2 != nullptr) {
					if (temp1->medicina.getNombre() > temp2->medicina.getNombre()) {
						// Intercambiar los datos de los nodos
						T temp = temp1->medicina;
						temp1->medicina = temp2->medicina;
						temp2->medicina = temp;
						intercambiado = true;
					}

					temp1 = temp1->sig;
					temp2 = temp2->sig;
				}
			} while (intercambiado);
			break;
		}
		case 1:
		{
			Nodo* listaOrdenada = nullptr; // Inicializamos una lista vacía
			Nodo* actual = auxLista->ini;

			while (actual != nullptr) {
				Nodo* sig = actual->sig;
				if (listaOrdenada == nullptr || actual->medicina.getNombre() < listaOrdenada->medicina.getNombre()) {
					actual->sig = listaOrdenada;
					listaOrdenada = actual;
				}
				else {
					Nodo* temp = listaOrdenada;
					while (temp->sig != nullptr && actual->medicina.getNombre() < temp->medicina.getNombre()) {
						temp = temp->sig;
					}
					actual->sig = temp->sig;
					temp->sig = actual;
				}
				actual = sig;
			}

			auxLista->ini = listaOrdenada;
			break;
		}
		case 2: {
			Nodo* actual = auxAux;

			while (actual != nullptr) {
				Nodo* minimo = auxAux;
				Nodo* temp = auxAux->sig;

				while (temp != nullptr) {
					if (temp->medicina.getNombre() < minimo->medicina.getNombre()) {
						minimo = temp;
					}
					temp = temp->sig;
				}


				T tempV = actual->medicina;
				actual->medicina = minimo->medicina;
				minimo->medicina = tempV;

				actual = actual->sig;
			}
		}
		default:
			break;
		}

	}


	while (auxAux != nullptr) {
		auxAux->medicina.mostrar(9, ConsoleColor::Yellow, ++pos);
		auxAux = auxAux->sig;
	}

	delete auxLista;
}

template<class T>
T Lista_Medicamentos<T>::obtenerPos(int pos) {

	if (pos >= 0 && pos < lon) {
		Nodo* aux = ini;
		for (int i = 0; i < pos; i++) {
			aux = aux->sig;
		}
		return aux->medicina;
	}
}

template<class T>
inline void Lista_Medicamentos<T>::actualizarArchivo()
{
	ofstream* archivo = new ofstream("Medicamentos.dat", ios::out);

	forEach([&archivo](T medicina) {
		char envio[50]{};

		strcpy(envio, medicina.getNombre().c_str());

		Medicamento<const char*, int, float>::MedicamentoStruct medicamentoStruct(envio,
			int(medicina.getCantidad()), float(medicina.getPrecio()));


		if (archivo->is_open()) {
			archivo->write((char*)&medicamentoStruct,
				sizeof(Medicamento<string, int, float>::MedicamentoStruct));
		}
		});

	archivo->close();

	delete archivo;

}

template<class T>
inline int Lista_Medicamentos<T>::get_lon()
{
	return this->lon;
}

template<class T>
inline void Lista_Medicamentos<T>::forEach(function<void(T)> callback)
{
	Nodo* aux = ini;
	while (aux != nullptr) {
		callback(aux->medicina);
		aux = aux->sig;
	}
}
