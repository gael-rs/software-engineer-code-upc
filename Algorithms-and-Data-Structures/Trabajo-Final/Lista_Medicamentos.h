#pragma once
#include "Medicamento.h"
#include "Merge.h"

enum CriterioDeOrdenamiento {
	Ascendente,
	Descendente
};

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
	void agregaInicial(T medicina);
	void eliminaInicial();
	void eliminarPos(int pos);
	void coutLista();
	int get_lon();
	void forEach(function<void(T)> callback);
	void forEach(function<void(T, int)> callback);
	T obtenerPos(int pos);
	void actualizarArchivo();
	void agregarPos(T medicina, int pos);
	void agregaPos(T elem, int pos);
	void agregaFinal(T elem);

	void ordenarNombre(CriterioDeOrdenamiento co);
	void ordenarCantidad(CriterioDeOrdenamiento co);
	void ordenarPrecio(CriterioDeOrdenamiento co);
	void borrarTodo();

	class Iterator {
		unsigned int pos;
		Nodo* aux;
	public:
		Iterator(unsigned int pos, Nodo* aux) : pos(pos), aux(aux) {}
		void operator++() { pos++; aux = aux->sig; }
		bool operator!=(Iterator x) { return pos != x.pos; }
		T operator*() { return aux->medicina; }
	};

	Iterator begin() {
		return Iterator(0, ini);
	}

	Iterator end() {
		return Iterator(lon, nullptr);
	}

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

	while (auxAux != nullptr) {
		auxAux->medicina.mostrar(9, ConsoleColor::Yellow, ++pos);
		auxAux = auxAux->sig;
	}

	delete auxLista;
	delete auxAux;
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
		char categoria[17]{};

		strcpy(envio, medicina.getNombre().c_str());
		strcpy(categoria, medicina.getCategoria().c_str());

		Medicamento<const char*, int, float>::MedicamentoStruct medicamentoStruct(envio,
			int(medicina.getCantidad()), float(medicina.getPrecio()), 
			categoria,
			medicina.getSucursalIdx(),
			int(medicina.getVecesVendido()));


		if (archivo->is_open()) {
			archivo->write((char*)&medicamentoStruct,
				sizeof(Medicamento<string, int, float>::MedicamentoStruct));
		}
		});

	archivo->close();

	delete archivo;

}

template<class T>
inline void Lista_Medicamentos<T>::agregarPos(T medicina, int pos)
{
	if (pos > lon) return;
	if (pos == 0) {
		agregaInicial(medicina);
	}
	else {
		Nodo* aux = ini;
		for (int i = 1; i < pos; i++) {
			aux = aux->sig;
		}
		Nodo* nuevo = new Nodo(medicina, aux->sig);
		if (nuevo != nullptr) {
			aux->sig = nuevo;
			lon++;
		}
	}
}

template <typename T>
void Lista_Medicamentos<T>::agregaPos(T elem, int pos) {
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

template<class T>
inline void Lista_Medicamentos<T>::agregaFinal(T elem)
{
	int pos = get_lon();
	agregaPos(elem, pos);
}



template<class T>
inline void Lista_Medicamentos<T>::ordenarNombre(CriterioDeOrdenamiento co)
{
	mergeSort<Lista_Medicamentos<T>, T>(this, [co](T a, T b) {
		if (co == Ascendente) return a.getNombre() < b.getNombre();
		return a.getNombre() > b.getNombre();
		});
}

template<class T>
inline void Lista_Medicamentos<T>::ordenarCantidad(CriterioDeOrdenamiento co)
{
	mergeSort<Lista_Medicamentos<T>, T>(this, [co](T a, T b) {
		if (co == Ascendente) return a.getCantidad() > b.getCantidad();
		return a.getCantidad() < b.getCantidad();
		});

}

template<class T>
inline void Lista_Medicamentos<T>::ordenarPrecio(CriterioDeOrdenamiento co)
{
	mergeSort<Lista_Medicamentos<T>, T>(this, [co](T a, T b) {
		if (co == Ascendente) return a.getPrecio() > b.getPrecio();
		return a.getPrecio() < b.getPrecio();
		});
}

template<class T>
inline void Lista_Medicamentos<T>::borrarTodo()
{
	Nodo* aux = ini;
	while (ini != nullptr) {
		aux = ini;
		ini = ini->sig;
		delete aux;
	}
	lon = 0; // Restablecemos la longitud de la lista a cero
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

template<class T>
inline void Lista_Medicamentos<T>::forEach(function<void(T, int)> callback)
{
	int pos = 0;
	Nodo* aux = ini;
	while (aux != nullptr) {
		callback(aux->medicina, pos++);
		aux = aux->sig;
	}
}
