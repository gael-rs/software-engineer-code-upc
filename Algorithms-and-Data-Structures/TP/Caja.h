#pragma once
#include "Proveedor.h"
#include "Lista_Medicamentos.h"
#include "Pila.h"
#include "Medicamento.h"

template <class T>
class Caja
{
public:
	Caja(Lista_Medicamentos<T> unalista);
	~Caja();

	void registrarVenta();
	void mostrarHistorialVentas();
	void menu_caja();
	void actualizar_lista(Lista_Medicamentos<T> unalista);

private:
	Lista_Medicamentos<T> unalista;
	Pila<T> historialVentas;
};

template <class T>
Caja<T>::Caja(Lista_Medicamentos<T> unalista) {
	this->unalista = unalista;
}

template <class T>
Caja<T>::~Caja()
{
}

template<class T>
inline void Caja<T>::actualizar_lista(Lista_Medicamentos<T> unalista)
{
	this->unalista = unalista;
}

template<class T>
void Caja<T>::registrarVenta() {

	gotoxy(getXCenter(86), Console::WindowTop + 1); cout << R"(    ____  _______________________________  ___    ____     _    _________   ___________ )";
	gotoxy(getXCenter(86), Console::WindowTop + 2); cout << R"(   / __ \/ ____/ ____/  _/ ___/_  __/ __ \/   |  / __ \   | |  / / ____/ | / /_  __/   |)";
	gotoxy(getXCenter(86), Console::WindowTop + 3); cout << R"(  / /_/ / __/ / / __ / / \__ \ / / / /_/ / /| | / /_/ /   | | / / __/ /  |/ / / / / /| |)";
	gotoxy(getXCenter(86), Console::WindowTop + 4); cout << R"( / _, _/ /___/ /_/ // / ___/ // / / _, _/ ___ |/ _, _/    | |/ / /___/ /|  / / / / ___ |)";
	gotoxy(getXCenter(86), Console::WindowTop + 5); cout << R"(/_/ |_/_____/\____/___//____//_/ /_/ |_/_/  |_/_/ |_|     |___/_____/_/ |_/ /_/ /_/  |_|)";

	bool medicamentoEnInventario = false;
	int cantidadDisponible = 0, indexMedicamento = -1;
	string nombreMedicamento;
	int cantidadVenta;

	string mensaje = "Productos disponibles";

	gotoxy(getXCenter(mensaje.size()), 7); cout << mensaje;

	unalista.coutLista();
	gotoxy(3, 20);
	cout << "Ingrese el nombre del medicamento: "; cin >> nombreMedicamento;
	gotoxy(3, 23);
	cout << "Ingrese la cantidad: "; cin >> cantidadVenta;

	Medicamento<string, int, float> venta;

	for (int i = 0; i < unalista.get_lon(); ++i)
	{
		if (unalista.obtenerPos(i).getNombre() == nombreMedicamento) {
			medicamentoEnInventario = true;
			cantidadDisponible = unalista.obtenerPos(i).getCantidad();
			venta = unalista.obtenerPos(i);
			indexMedicamento = i;
			break;
		}
	}

	if (!medicamentoEnInventario)
	{
		cout << "El medicamento '" << nombreMedicamento << "' no esta disponible en el inventario" << endl;
	}
	else	if (cantidadDisponible >= cantidadVenta) {
		//Logica de la venta...

		cout << "Venta realizada: " << cantidadVenta << " unidades de " << nombreMedicamento << endl;
		historialVentas.push(venta);

		//Actualizar la cantidad de medicamentos en el inventario
		unalista.eliminarPos(indexMedicamento);
		unalista.actualizarArchivo();
	}
	else {
		cout << "Error: No hay suficientes unidades de '" << nombreMedicamento << "' en el inventario." << endl;
	}
	system("pause");
}

template<class T>
void Caja<T>::mostrarHistorialVentas() {

	gotoxy(getXCenter(105), Console::WindowTop + 1);  cout << R"(	__  _____________________  ____  _______    __       ____  ______   _    _________   ___________   _____)";
	gotoxy(getXCenter(105), Console::WindowTop + 2); cout << R"(   / / / /  _/ ___/_  __/ __ \/ __ \/  _/   |  / /      / __ \/ ____/  | |  / / ____/ | / /_  __/   | / ___/)";
	gotoxy(getXCenter(105), Console::WindowTop + 3); cout << R"(  / /_/ // / \__ \ / / / / / / /_/ // // /| | / /      / / / / __/     | | / / __/ /  |/ / / / / /| | \__ \)";
	gotoxy(getXCenter(105), Console::WindowTop + 4); cout << R"( / __  // / ___/ // / / /_/ / _, _// // ___ |/ /___   / /_/ / /___     | |/ / /___/ /|  / / / / ___ |___/ / )";
	gotoxy(getXCenter(105), Console::WindowTop + 5); cout << R"(/_/ /_/___//____//_/  \____/_/ |_/___/_/  |_/_____/  /_____/_____/     |___/_____/_/ |_/ /_/ /_/  |_/____/  )";


	int pos = 0;

	historialVentas.forEach([pos](T venta)mutable {
		venta.mostrar(7, ConsoleColor::Cyan, ++pos);
		});

	gotoxy(getXCenter(39), Console::WindowHeight - 5);
	system("pause");
}

template<class T>
inline void Caja<T>::menu_caja()
{
	Console::Clear();

	gotoxy(getXCenter(24), Console::WindowTop + 1); cout << R"(   ______        _      )";
	gotoxy(getXCenter(24), Console::WindowTop + 2); cout << R"(  / ____/___ _  (_)___ _)";
	gotoxy(getXCenter(24), Console::WindowTop + 3); cout << R"( / /   / __ `/ / / __ `/)";
	gotoxy(getXCenter(24), Console::WindowTop + 4); cout << R"(/ /___/ /_/ / / / /_/ / )";
	gotoxy(getXCenter(24), Console::WindowTop + 5); cout << R"(\____/\__,_/_/ /\__,_/  )";
	gotoxy(getXCenter(24), Console::WindowTop + 6); cout << R"(          /___/         )";
	gotoxy(getXCenter(24), Console::WindowTop + 7); cout << R"(------------------------)";

	gotoxy(55, 9);  cout << R"(Venta)";
	gotoxy(55, 11); cout << R"(Historial)";
	gotoxy(55, 13); cout << R"(Volver al Menu)";

	short opcion = logica_menu(9, 3, 45, 9);

	if (opcion == 1) {
		Console::Clear();
		registrarVenta();
		menu_caja();
	}
	if (opcion == 2) {
		Console::Clear();
		mostrarHistorialVentas();
		menu_caja();
	}
	if (opcion == 3) {
		Console::Clear();
	}
}


