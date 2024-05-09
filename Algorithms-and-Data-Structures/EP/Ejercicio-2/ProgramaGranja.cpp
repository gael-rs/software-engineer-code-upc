#include <iostream>
#include "ListaIteradores.h"
#include "CCerdo.h"
#include "Cola.h"
#include "Nodo.h"
#include <cstdlib> //incluidos para el uso de rand()
#include <ctime> //incluidos para le uso de rand() 

using namespace std;

void generarDatosCerdos(Lista<CCerdo*>* lst) {
	srand(time(nullptr)); // Semilla para el rand()

	// Número de cerdos a generar (500 < n < 800)
	int n = rand() % 301 + 500; // Número aleatorio entre 500 y 800

	for (int i = 0; i < n; ++i) {
		int codigo = rand() % 301 + 500;  // Código entre 500 y 800
		int edad = rand() % 100;          // Edad entre 0 y 99
		float peso = static_cast<float>(rand() % 10000) / 10; // Peso entre 0.0 y 999.9
		float altura = static_cast<float>(rand() % 10000) / 100;        // Altura entre 0.00 y 99.99
		float temperatura = static_cast<float>(rand() % 10000) / 100;   // Temperatura entre 0.00 y 99.99

		CCerdo* cerdo = new CCerdo();
		cerdo->codigoCerdo = to_string(codigo);
		cerdo->edad = edad;
		cerdo->peso = peso;
		cerdo->altura = altura;
		cerdo->temperatura = temperatura;

		lst->agregaFinal(cerdo);
	}
}

void mostrarDatosCerdos(Lista<CCerdo*>* lst) {
	cout << "===========================" << endl;
	cout << "    DATOS DE LOS CERDOS    " << endl;
	cout << "===========================" << endl;

	for (auto it = lst->begin(); it != lst->end(); ++it) {
		CCerdo* cerdo = *it; 

		cout << "===========================" << endl;
		cout << "Cerdo #" << cerdo->codigoCerdo << endl;
		cout << "======" << endl;
		cout << "Edad: " << cerdo->edad << endl;
		cout << "Peso: " << cerdo->peso << " kg" << endl;
		cout << "Altura: " << cerdo->altura << endl;
		cout << "Temperatura: " << cerdo->temperatura << endl;
		cout << "===========================" << endl;

	}
}
float promedioEdades(Lista<CCerdo*>* lst) {
	if (lst->esVacia()) return 0;

	float suma = 0;
	uint cantidad = 0;

	for (auto it = lst->begin(); it != lst->end(); ++it) {
		suma += (*it)->edad;
		cantidad++;
	}

	return suma / cantidad;
}

float promedioPesos(Lista<CCerdo*>* lst) {
	if (lst->esVacia()) return 0;

	float suma = 0;
	uint cantidad = 0;

	for (auto it = lst->begin(); it != lst->end(); ++it) {
		suma += (*it)->peso;
		cantidad++;
	}

	return suma / cantidad;
}

float promedioAlturas(Lista<CCerdo*>* lst) {
	if (lst->esVacia()) return 0; 

	float suma = 0;
	uint cantidad = 0;

	for (auto it = lst->begin(); it != lst->end(); ++it) {
		suma += (*it)->altura;
		cantidad++;
	}

	return suma / cantidad;
}

void mostrarEdades(Lista<CCerdo*>* lst) {
	Cola<int> colaEdades;

	for (auto it = lst->begin(); it != lst->end(); ++it) {
		colaEdades.enqueue((*it)->edad);
	}

	cout << "Edades de los cerdos (COLA): ";
	while (!colaEdades.esVacia()) {
		cout << colaEdades.dequeue() << " <- ";
	}
	cout << endl;
}

void ordenarPorEdades(Lista<CCerdo*>* lst) {
	if (lst->esVacia()) return;

	int n = lst->longitud();
	CCerdo** cerdos = new CCerdo * [n];

	int i = 0;
	for (auto it = lst->begin(); it != lst->end(); ++it) {
		cerdos[i++] = *it;
	}

	// Ordenar por edades
	for (int i = 1; i < n; i++) {
		CCerdo* aux = cerdos[i];
		int k = i - 1;
		while (k >= 0 && aux->edad < cerdos[k]->edad) {
			cerdos[k + 1] = cerdos[k];
			k--;
		}
		cerdos[k + 1] = aux;
	}

	lst->borrarTodo();
	for (int i = 0; i < n; i++) {
		lst->agregaFinal(cerdos[i]);
	}

	delete[] cerdos;


	
}

void mostrarListaOrdenada(Lista<CCerdo*>* lst) {
	cout << "=================================" << endl;
	cout << "  DATOS DE LOS CERDOS ORDENADOS    " << endl;
	cout << "=================================" << endl;

	for (auto it = lst->begin(); it != lst->end(); ++it) {
		CCerdo* cerdo = *it;

		cout << "===========================" << endl;
		cout << "Cerdo #" << cerdo->codigoCerdo << endl;
		cout << "======" << endl;
		cout << "Edad: " << cerdo->edad << endl;
		cout << "Peso: " << cerdo->peso << " kg" << endl;
		cout << "Altura: " << cerdo->altura << endl;
		cout << "Temperatura: " << cerdo->temperatura << endl;
		cout << "===========================" << endl;
	}
}



void menu(Lista<CCerdo*>* lst) {
	int opcion;
	do {
		cout << "===========================" << endl;
		cout << "          M E N U          " << endl;
		cout << "===========================" << endl;
		cout << "1. Generar datos de cerdos (datos aleatorios)" << endl;
		cout << "2. Mostrar datos de los cerdos (Esperar a que se muestren todos los datos)" << endl;
		cout << "3. Promedio de los pesos de los cerdos" << endl;
		cout << "4. Promedio de las edades de los cerdos" << endl;
		cout << "5. Promedio de las alturas de los cerdos" << endl;
		cout << "6. Mostrar edad de los cerdos (COLA)"<< endl;
		cout << "7. Ordenar la edad de los cerdos (INSERCION)" << endl;
		cout << "8. Salir" << endl;
		cout << "===========================" << endl;
		cout << "Ingrese la opcion que desea realizar: ";
		cin >> opcion;
		switch (opcion)
		{
		case 1:
			generarDatosCerdos(lst);
			cout << "Datos generados correctamente..." << endl;
			break;
		case 2:
			mostrarDatosCerdos(lst);
			break;
		case 3:
			cout << "Promedio de TODOs los pesos de los cerdos: " << promedioPesos(lst) << " kg" << endl;
			break;
		case 4:
			cout << "Promedio de TODAS las edades de los cerdos: " << promedioEdades(lst) << " años" << endl;
			break;
		case 5:
			cout << "Promedio de TODAS las alturas de los cerdos: " << promedioAlturas(lst) << " m" << endl;
			break;
		case 6:
			mostrarEdades(lst);
			break;
		case 7:
			ordenarPorEdades(lst);
			mostrarListaOrdenada(lst);
			break;
		case 8:
			cout << "Gracias por usar el programa...";
			exit(0);
		default:
			cout << "Opcion no valida...";
			break;
		}
	} while (opcion != 6);
}

int main() {

	Lista<CCerdo*>* lst = new Lista<CCerdo*>(
		[](CCerdo* a1, CCerdo* a2) {
			return a1->ToString().compare(a2->ToString());
		});

	menu(lst);

	delete lst;
	cin.get();
	cin.ignore();
	return 0;
}
