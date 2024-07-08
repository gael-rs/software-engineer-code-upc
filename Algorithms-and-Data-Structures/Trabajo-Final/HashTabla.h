#pragma once
#include <vector>
#include <list>
#include <string>
#include "Entidad.h"

#include <iostream>
using namespace std;

template <typename Key, typename Value>
class HashTabla {
private:
	vector<list<Entidad<Key, Value>>> listas;   // Tabla
	int  tamanoActual;

public:
	explicit HashTabla(int size = 150) : tamanoActual{ 0 }
	{
		listas.resize(150);
	}

	void makeEmpty()
	{
		for (auto& thisList : listas)
			thisList.clear();
	}

	bool insert(Entidad<Key, Value>&& x)
	{
		int hash = myhash(x.getKey());
		auto& whichList = listas[hash]; //Obtenemos la lista de elementos segun el hash obtenido

		/*
			Cambio de lugar
		*/
		for (auto& it : whichList) {
			if (myhash(it.getKey()) == myhash(x.getKey())) {
				hash += rand() % listas.size() - hash;
				hash = max(0, min(hash, (int)listas.size() - 1));

				break;
			}
		}

		listas[hash].push_back(x); //Agregamos el nuevo elemento a la lista

		return true;
	}


	void DispAll(function<void(list<Entidad<Key, Value>>)> cb) {
		int pos = 0;
		for (auto& thisList : listas) {
			cb(listas[pos]);
			pos++;
		}
	}

private:

	int myhash(Key key) const {
		int hash = 0;

		for (int i = 0; i < key.length(); i++) {
			hash += short(key[i]);
		}

		hash %= listas.size();
		return(hash);
	}
};


