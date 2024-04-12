#include <iostream>
#include "Lista.h"
#include "CCliente.h"

using namespace::std;

void ingresarTransaccion(Lista<CCliente*>* lst) {
	CCliente* cliente = new CCliente();
	cout << "Ingresar Nombre: ";
	cin.ignore();
	getline(cin, cliente->nombre);
	cout << "Ingresar DNI: ";
	cin >> cliente->dni;
	cout << "Ingresar numero de celular: ";
	cin >> cliente->numeroCelular;
	cout << "Ingresar numero de destino: ";
	cin >> cliente->numeroDestino;
	cout << "Ingresar monto: ";
	cin >> cliente->monto;
	lst->agregaInicial(cliente);
	cout << endl << endl;
}

void mostrarCliente(Lista<CCliente*>* lst) {
	cout << "--------- Lista de Transacciones ---------" << endl;
	for (int i = 0; i < lst->longitud(); i++)
	{
		CCliente* alumno = lst->obtenerPos(i);
		cout << alumno->ToString() << endl;
	}
}

void imprimir3MontosAltos(Lista<CCliente*>* lst) {
	/*
	CCliente** arrayCliente = new CCliente* [lst->longitud()];
	
	
	for (int i = 0; i < lst->longitud(); i++){
		arrayCliente[i] = lst->obtenerPos(i);
	}
	*/
}

void menu(Lista<CCliente*>* lst) {
	int opcion;
	do {
		cout << "===========================" << endl;
		cout << "          M E N U          " << endl;
		cout << "===========================" << endl;
		cout << "1. Ingresar una Transaccion" << endl;
		cout << "2. Mostrar cliente por DNI" << endl;
		cout << "3. Mostrar transaccion mas alta y mas baja" << endl;
		cout << "Ingrese la opcion que desea realizar: ";
		cin >> opcion;
		switch (opcion)
		{
		case 1:
			ingresarTransaccion(lst);
			break;
		case 2:
			mostrarCliente(lst);
			break;
		case 3:
			imprimir3MontosAltos(lst);
			break;
		case 4:
			cout << "Gracias por ingresar...";
			exit(0);
		default:
			cout << "Opcion no valida...";
			break;
		}
	} while (opcion != 4);
}

int main(){
	Lista<CCliente*>* lst = new Lista<CCliente*>(
		[](CCliente* a1, CCliente* a2) {
			return a1->ToString().compare(a2->ToString());
		});

	menu(lst);

	delete lst;
	
	cin.get();
	cin.ignore();
	return 0;
}

