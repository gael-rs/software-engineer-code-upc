#pragma once
#include <functional>

using namespace std;
template <class T>
class NodoArbol {
public:
	T elemento;
	NodoArbol* izq;
	NodoArbol* der;
};

template <class T>
class Arbol {
public:
	typedef function<int(T, T)> Comp; //Lambda

	NodoArbol<T>* raiz;
	function<void(T)> procesar; //Puntero a funcion
	
	Comp comparar; // lambda de criterio de comparación

private:
	bool _buscar(NodoArbol<T>* nodo, T e) {
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
	NodoArbol<T>* _obtener(NodoArbol<T>* nodo, T e) {
		if (nodo == nullptr) return nullptr;
		else {
			int r = comparar(nodo->elemento, e);
			if (r == 0) return nodo;
			else if (r < 0) {
				return _buscar(nodo->der, e);
			}
			else {
				return _buscar(nodo->izq, e);
			}
		}
	}
	bool _insertar(NodoArbol<T>*&nodo, T e) {
		if (nodo == nullptr) {
			nodo = new NodoArbol<T>();
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
	void _enOrden(NodoArbol<T>* nodo) {
		if (nodo == nullptr) return;
		_enOrden(nodo->izq);
		procesar(nodo->elemento);
		_enOrden(nodo->der);
	}
	bool _vacio() {
		return raiz == nullptr;
	}
	int _cantidad(NodoArbol<T>* nodo) {
		//La cantidad de nodos del árbol es:
		//	0 si es vacío
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
	int _altura(NodoArbol<T>* nodo) {
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

	T _minimo(NodoArbol<T>* nodo) {
		if (nodo->izq == nullptr) return nodo->elemento;
		else
			return _minimo(nodo->izq);		
	}
	T _maximo(NodoArbol<T>* nodo) {
		if (nodo->der == nullptr) return nodo->elemento;
		else
			return _maximo(nodo->der);
	}
	bool _eliminar(NodoArbol<T>*& nodo, T e) {
		if (nodo == nullptr) return false;
		else {
 			int r = comparar(nodo->elemento, e);
			if (r < 0) {
				return _eliminar(nodo->der, e);
			}
			else if (r > 0) {
				return _eliminar(nodo->izq, e);
			}else { // r==0 es porque se encontró el elemento e en el arbol
				if (nodo->der == nullptr && nodo->izq == nullptr) {//caso 1
					nodo = nullptr;
					delete nodo;		
					return true;
				}
				else if (nodo->izq == nullptr) { //caso 2
					nodo = nodo->der;	
					return true;
				}
				else if (nodo->der == nullptr) { //caso 3
					nodo = nodo->izq;	
					return true;
				}
				else {
					NodoArbol<T> *aux = nodo->der;
					while (aux->izq != nullptr)
					{
						aux = aux->izq; //Se obtiene la hoja menor
					}
					nodo->elemento = aux->elemento; //Se actualiza el elemento en el nodo raiz y
					return _eliminar(nodo->der,aux->elemento); //se envía a eliminar el elemento en el arbol por la derecha
				}				
			}
		}
	}
public:
	Arbol(function<void(T)> otroPunteroAFuncion) {
		this->procesar = otroPunteroAFuncion;
		this->comparar=[](T a, T b)->int {return a.getVecesVendido() - b.getVecesVendido(); };
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
	bool Buscar(T e) {
		return _buscar(raiz, e);
	}
	T Minimo() {
		return _minimo(raiz);
	}
	T Maximo() {
		return _maximo(raiz);
	}
	bool Eliminar(T e) {
		return _eliminar(raiz, e);
	}
	bool esVacio() {
		return raiz == nullptr;
	}
};
