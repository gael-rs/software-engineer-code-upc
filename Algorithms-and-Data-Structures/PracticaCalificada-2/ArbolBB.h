#pragma once
#include "CProducto.h"
#include <functional>

using namespace std;

template <class T>
class Nodo {
public:
	T elemento;
	Nodo* izq;
	Nodo* der;

	Nodo() : izq(nullptr), der(nullptr){}
};

template <class T>
class ArbolBB {
	typedef function<int(T, T)> Comp; //Lambda

	Nodo<T>* raiz;
	void(*procesar)(T); //Puntero a funcion

	Comp comparar; // lambda de criterio de comparaci�n


private:
	bool _buscar(Nodo<T>* nodo, T e) {
		if (nodo == nullptr) return false;
		else {
			int r = comparar(nodo->elemento.stock, e.stock);
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

	void _preOrden(Nodo<T>* nodo) {
		if (nodo == nullptr) return;
		procesar(nodo->elemento);
		_preOrden(nodo->izq);
		_preOrden(nodo->der);
	}

	void _postOrden(Nodo<T>* nodo) {
		if (nodo == nullptr) return;
		_postOrden(nodo->izq);
		_postOrden(nodo->der);
		procesar(nodo->elemento);
	}
	bool _vacio() {
		return raiz == nullptr;
	}
	int _cantidad(Nodo<T>* nodo) {
		//La cantidad de nodos del arbol es:
		//	0 si es vacio
		//	1 + la cantidad de nodos por la izquierda + la cantidad de nodos por la derecha

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
		//La altura del �rbol es:
		//	0 si es vac�o
		//	la mayor de las alturas por la izquierda y por la derecha, las cu�les son 0 si son vac�as � 1 + la altura por la izq(o der) en caso contrario

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
			else { // r==0 es porque se encontr� el elemento e en el arbol
				if (nodo->der == nullptr && nodo->izq == nullptr) {//caso 1
					delete nodo;
					nodo = nullptr;
					return true;
				}
				else if (nodo->izq == nullptr) { //caso 2
					Nodo<T>* der = nodo->der;
					delete nodo;
					nodo = der;
					return true;
				}
				else if (nodo->der == nullptr) { //caso 3
					Nodo<T>* izq = nodo->izq;
					delete nodo;
					nodo = izq;
					return true;
				}
				else { //caso 4
					Nodo<T>* aux = nodo->der; //Se establece buscar el menor elemento por la derecha
					while (aux->izq != nullptr)
					{
						aux = aux->izq; //Se obtiene la hoja menor
					}
					nodo->elemento = aux->elemento; //Se actualiza el elemento en el nodo raiz y
					return _eliminar(nodo->der, aux->elemento); //se env�a a eliminar el elemento en el arbol por la derecha
				}
			}
		}
	}
public:
	Nodo<T>* obtenerRaiz() const {
		return raiz;
	}
	ArbolBB(void(*otroPunteroAFuncion)(T)) {
		this->procesar = otroPunteroAFuncion;
		this->comparar = [](T a, T b)->int {return a.stock - b.stock; };
		raiz = nullptr;
	}
	ArbolBB(void(*otroPunteroAFuncion)(T), Comp comparar) {
		this->procesar = otroPunteroAFuncion;
		this->comparar = comparar;
		raiz = nullptr;
	}
	bool eliminar(const T& elemento) {
		return eliminarNodo(raiz, elemento);
	}

	bool eliminarNodo(Nodo<T>*& nodo, const T& elemento) {
		if (nodo == nullptr) {
			return false;
		}

		if (elemento < nodo->elemento) {
			return eliminarNodo(nodo->izq, elemento);
		}
		else if (elemento > nodo->elemento) {
			return eliminarNodo(nodo->der, elemento);
		}
		else {
			// Nodo encontrado, realizar la eliminación
			eliminarNodoEncontrado(nodo);
			return true;
		}
	}

	void eliminarNodoEncontrado(Nodo<T>*& nodo) {
		if (nodo->izq == nullptr && nodo->der == nullptr) {
			// Caso 1: Nodo sin hijos
			delete nodo;
			nodo = nullptr;
		}
		else if (nodo->izq == nullptr) {
			// Caso 2: Nodo con un hijo derecho
			Nodo<T>* temp = nodo;
			nodo = nodo->der;
			delete temp;
		}
		else if (nodo->der == nullptr) {
			// Caso 2: Nodo con un hijo izquierdo
			Nodo<T>* temp = nodo;
			nodo = nodo->izq;
			delete temp;
		}
		else {
			// Caso 3: Nodo con dos hijos
			Nodo<T>* temp = obtenerMinimo(nodo->der);
			nodo->elemento = temp->elemento;
			eliminarNodo(nodo->der, temp->elemento);
		}
	}

	Nodo<T>* obtenerMinimo(Nodo<T>* nodo) {
		while (nodo->izq != nullptr) {
			nodo = nodo->izq;
		}
		return nodo;
	}

	bool insertar(T e) {
		return _insertar(raiz, e);
	}
	void enOrden() {
		_enOrden(raiz);
	}
	void preOrden() {
		_preOrden(raiz);
	}
	void postOrden() {
		_postOrden(raiz);
	}
	int cantidad() {
		return _cantidad(raiz);
	}
	int altura() {
		return _altura(raiz);
	}
	bool Buscar(T e) {
		return _buscar(raiz, e);
	}
	int Minimo() {
		return _minimo(raiz);
	}
	int Maximo() {
		return _maximo(raiz);
	}
	bool Eliminar(T e) {
		return _eliminar(raiz, e);
	}
	T minimo() {
		return _minimo(raiz);
	}
	T maximo() {
		return _maximo(raiz);
	}
	bool eliminarPorStock(int stock) {
		return _eliminarPorStock(raiz, stock);
	}

	bool _eliminarPorStock(Nodo<T>*& nodo, int stock) {
		if (nodo == nullptr) {
			return false;
		}

		if (stock < nodo->elemento.stock) {
			return _eliminarPorStock(nodo->izq, stock);
		}
		else if (stock > nodo->elemento.stock) {
			return _eliminarPorStock(nodo->der, stock);
		}
		else {
			// Nodo encontrado, realizar la eliminación
			eliminarNodoEncontrado(nodo);
			return true;
		}
	}

};

