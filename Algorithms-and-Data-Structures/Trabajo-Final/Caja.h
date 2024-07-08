#pragma once
#include "Proveedor.h"
#include "Lista_Medicamentos.h"
#include "Pila.h"
#include "Medicamento.h"
#include "Arbol.h"
#include "Cupon_Generator.h"

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
	void toArbol();
	void mostrarTop3Vendidos();
	void mostrarCuponesDisponibles();
	void buscarMedicamento();

private:
	Lista_Medicamentos<T> unalista;
	Pila<T> historialVentas;
	Arbol<T>* arbol;
	CuponGenerator* cuponGenerator;
	T vacio;
	float ganancias;

};

template <class T>
Caja<T>::Caja(Lista_Medicamentos<T> unalista) {

	this->cuponGenerator = new CuponGenerator;
	this->unalista = unalista;

	int pos = 0;

	this->arbol = new Arbol<T>([&pos](T medicamento) {
		medicamento.mostrar(7, ConsoleColor::Cyan, ++pos);
		});
}

template <class T>
Caja<T>::~Caja()
{
	delete cuponGenerator;
	delete arbol;
}

template<class T>
inline void Caja<T>::actualizar_lista(Lista_Medicamentos<T> unalista)
{
	this->unalista = unalista;
}

template<class T>
inline void Caja<T>::toArbol()
{
	unalista.forEach([this](T medicamento) {
		arbol->insertar(medicamento);
		});
}

template<class T>
inline void Caja<T>::mostrarTop3Vendidos()
{
	toArbol();
	gotoxy(getXCenter(84), Console::WindowTop + 1); cout << R"(  __________  ____     _____             _    __               ___     __          )";
	gotoxy(getXCenter(84), Console::WindowTop + 2); cout << R"( /_  __/ __ \/ __ \   |__  /            | |  / /__  ____  ____/ (_)___/ /___  _____)";
	gotoxy(getXCenter(84), Console::WindowTop + 3); cout << R"(  / / / / / / /_/ /    /_ <   ______    | | / / _ \/ __ \/ __  / / __  / __ \/ ___/)";
	gotoxy(getXCenter(84), Console::WindowTop + 4); cout << R"( / / / /_/ / ____/   ___/ /  /_____/    | |/ /  __/ / / / /_/ / / /_/ / /_/ (__  ) )";
	gotoxy(getXCenter(84), Console::WindowTop + 5); cout << R"(/_/  \____/_/       /____/              |___/\___/_/ /_/\__,_/_/\__,_/\____/____/  )";
	gotoxy(getXCenter(84), Console::WindowTop + 6); cout << R"(                                                                                   )";


	for (short i = 0; i < 3; i++) {

		if (!arbol->esVacio()) {
			T med = arbol->Maximo();
			med.mostrarVenta(Console::WindowTop + 10, ConsoleColor::Magenta, i);
			arbol->Eliminar(med);
		}

	}

	arbol->raiz = nullptr;
	cout << "\n\t";

	system("pause");
}

template<class T>
inline void Caja<T>::mostrarCuponesDisponibles()
{
	gotoxy(getXCenter(43), Console::WindowTop + 1);	cout << R"(   ______                                 )";
	gotoxy(getXCenter(43), Console::WindowTop + 2);	cout << R"(  / ____/_  ______  ____  ____  ___  _____)";
	gotoxy(getXCenter(43), Console::WindowTop + 3);	cout << R"( / /   / / / / __ \/ __ \/ __ \/ _ \/ ___/)";
	gotoxy(getXCenter(43), Console::WindowTop + 4); cout << R"(/ /___/ /_/ / /_/ / /_/ / / / /  __(__  ) )";
	gotoxy(getXCenter(43), Console::WindowTop + 5); cout << R"(\____/\__,_/ .___/\____/_/ /_/\___/____/  )";
	gotoxy(getXCenter(43), Console::WindowTop + 6); cout << R"(          /_/                             )";


	this->cuponGenerator->mostrarCupones();

	cout << "\n";

	system("pause");
}

template<class T>
inline void Caja<T>::buscarMedicamento()
{
	gotoxy(getXCenter(49), Console::WindowTop + 1); cout << R"(    ____)";
	gotoxy(getXCenter(49), Console::WindowTop + 2); cout << R"(   / __ )__  ________________ _____/ /___  _____)";
	gotoxy(getXCenter(49), Console::WindowTop + 3); cout << R"(  / __  / / / / ___/ ___/ __ `/ __  / __ \/ ___/)";
	gotoxy(getXCenter(49), Console::WindowTop + 4); cout << R"( / /_/ / /_/ (__  ) /__/ /_/ / /_/ / /_/ / /)";
	gotoxy(getXCenter(49), Console::WindowTop + 5); cout << R"(/_____/\__,_/____/\___/\__,_/\__,_/\____/_/  )";

	string nombreMedicamento = "";

	gotoxy(getXCenter(26), 7);
	cout << "Nombre de medicamento a buscar: ";

	getline(cin >> ws, nombreMedicamento);

	bool medicamentoEnInventario = false;


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

		string cuponCode = "";

		cout << "Cup" << char(162) << "n para descuento: ";
		getline(cin >> ws, cuponCode);

		if (cuponCode.length() > 0) {
			float descuento = cuponGenerator->getDescuentoByCodigo(cuponCode);

			if (descuento == 0.0) {
				cout << "Cup" << char(162) << "n inv" << char(160) << "lido" << endl;
			}
			else {
				cout << "Descuento aplicado: " << descuento << "%" << endl;
				float nuevoPrecio = venta.getPrecio() - (venta.getPrecio() * descuento / 100);
				venta.setPrecio(nuevoPrecio);
			}
		}

		cout << "Venta realizada: " << cantidadVenta << " unidades de " << nombreMedicamento << endl;
		int cantidad = int(venta.getCantidad() - cantidadVenta);

		unalista.eliminarPos(indexMedicamento);

		venta.setVecesVendido(venta.getVecesVendido() + cantidadVenta);
		venta.setCantidad(cantidad);

		historialVentas.push(venta);

		unalista.agregarPos(venta, indexMedicamento);
		//Actualizar la cantidad de medicamentos en el inventario
		// unalista.eliminarPos(indexMedicamento);
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
	gotoxy(55, 13); cout << R"(TOP 3. Vendidos)";
	gotoxy(55, 15); cout << R"(Cupones disponibles)";
	gotoxy(55, 17); cout << R"(Volver al Menu)";

	short opcion = logica_menu(9, 5, 45, 9);

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
		mostrarTop3Vendidos();
		menu_caja();
	}
	if (opcion == 4) {
		Console::Clear();
		mostrarCuponesDisponibles();
		menu_caja();
	}
	if (opcion == 5) {
		Console::Clear();
	}
}


