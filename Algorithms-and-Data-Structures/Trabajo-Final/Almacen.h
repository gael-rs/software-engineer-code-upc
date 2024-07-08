#pragma once
#include "Proveedor.h"
#include "Lista_Medicamentos.h"
#include "HashTabla.h"
#include "Grafo.h"

template <class T>
class Almacen
{
private:
	Proveedor<T>* proveedor;
	Lista_Medicamentos<T> unalista;
	ofstream* archivoEscritor;
	ifstream* archivoLector;
	HashTabla<string, T>* hashTabla;
	Grafo<string>* grafos;

public:
	Almacen();
	~Almacen();

	void registrarPedido();
	void mostrarPedidos();
	void elegirOpcion(bool pedirPedidoDesabilitado, function<void()>* adicional = nullptr);
	void mostrarBotones(bool pedirPedidoDesabilitado);
	void agregarInicioLista(T obj);
	void mostrarInventario();
	void abrirArchivo();
	void guardarMedicamentoPersistente(T obj);
	void obtenerMedicamentosInventario();
	void mostrarPorCategorias();
	void ordenamiento_menu();
	void Almacen_menu();
	void toGrafo();
	void rutaMasRapidaByMedicamento(T medicamento);
	void borrarRutaMasRapidaByMedicamento(T medicamento);
	void mostrarRutasDisponibles();
	void elegirMedicamentoLive();

	void toHashTable();
	T getElementoLista(int n);

	void mostrarOpcion(string* message, int x, bool seleccionado = false, bool desactivado = false);

	Lista_Medicamentos<T> getUnaLista();
};


template <class T>
Almacen<T>::Almacen()
{
	this->grafos = new Grafo<string>;
	this->proveedor = new Proveedor<T>;
	this->archivoEscritor = new ofstream();
	this->archivoLector = new ifstream();
	this->hashTabla = new HashTabla<string, T>(300);
	abrirArchivo();
}

template <class T>
inline void Almacen<T>::abrirArchivo()
{
	archivoEscritor->open("Medicamentos.dat", ios::binary | ios::app);
	archivoLector->open("Medicamentos.dat", ios::in | ios::binary);
}

template <class T>
Almacen<T>::~Almacen()
{
	delete proveedor;
	delete archivoEscritor;
	delete archivoLector;
	delete grafos;
	delete hashTabla;
}

template<class T>
inline Lista_Medicamentos<T> Almacen<T>::getUnaLista() {
	return unalista;
}

template<class T>
inline void Almacen<T>::agregarInicioLista(T obj) {
	unalista.agregaInicial(obj);
}

template<class T>
inline void Almacen<T>::mostrarRutasDisponibles() {
	toGrafo();

	gotoxy(getXCenter(34), Console::WindowTop + 1);	cout << R"(    ____  __  ___________   _____)";
	gotoxy(getXCenter(34), Console::WindowTop + 2);	cout << R"(   / __ \/ / / /_  __/   | / ___/)";
	gotoxy(getXCenter(34), Console::WindowTop + 3);	cout << R"(  / /_/ / / / / / / / /| | \__ \ )";
	gotoxy(getXCenter(34), Console::WindowTop + 4); cout << R"( / _, _/ /_/ / / / / ___ |___/ / )";
	gotoxy(getXCenter(34), Console::WindowTop + 5); cout << R"(/_/ |_|\____/ /_/ /_/  |_/____/ )";


	unalista.forEach([this](T medicamento, int pos) {
		medicamento.mostrar(6, getYCenter((unalista.get_lon() - 1) * 3), pos == 0 ? ConsoleColor::Magenta : ConsoleColor::DarkGray, pos);
		if (pos == 0) {
			rutaMasRapidaByMedicamento(medicamento);
		}
		});

	elegirMedicamentoLive();

	mostrarOpcion(new string("Dale ESC para salir"), getXCenter(18), false);
}

template<class T>
inline void Almacen<T>::toGrafo()
{
	grafos->adicionarVertice("Almacen");

	for (short i = 0; i < 10; i++) {
		grafos->adicionarVertice("Sucursal " + string(1, i + 65));
	}

	for (short i = 0; i < 11; i++) {
		for (int j = 1; j < 11; j++) {
			if (i != j) {
				if (j < i) {
					grafos->adicionarArco(i, j, grafos->obtenerArco(j, i - 2));
				}
				else {
					grafos->adicionarArco(i, j, rand() % 41 + 10);
				}
			}
		}
	}

	unalista.forEach([this](T medicamento, int pos) {
		medicamento.setSucursalIdx(rand() % 10 + 1);
		});

}

//----------------------
template<class T>
inline void Almacen<T>::Almacen_menu()
{

	Console::Clear();
	string indicador = "=>";
	gotoxy(getXCenter(44), 3); cout << R"(    ___    __                              )";
	gotoxy(getXCenter(44), 4); cout << R"(   /   |  / /___ ___  ____ _________  ____ )";
	gotoxy(getXCenter(44), 5); cout << R"(  / /| | / / __ `__ \/ __ `/ ___/ _ \/ __ \)";
	gotoxy(getXCenter(44), 6); cout << R"( / ___ |/ / / / / / / /_/ / /__/  __/ / / /)";
	gotoxy(getXCenter(44), 7); cout << R"(/_/  |_/_/_/ /_/ /_/\__,_/\___/\___/_/ /_/ )";
	gotoxy(getXCenter(44), 8); cout << R"(-------------------------------------------)";

	gotoxy(50, 10); cout << R"(Lista de Pedidos Pendientes)";
	gotoxy(50, 12); cout << R"(Realizar Pedidos)";
	gotoxy(50, 14); cout << R"(Inventario)";
	gotoxy(50, 16); cout << R"(Inventario por categorias)";
	gotoxy(50, 18); cout << R"(Ordenar)";
	gotoxy(50, 20); cout << R"(Ruta de pedidos)";
	gotoxy(50, 22); cout << R"(Volver al Menu)";


	short opcion = logica_menu(10, 7, 45, 10);

	if (opcion == 1) {
		Console::Clear();
		mostrarPedidos();
	}
	if (opcion == 2) {
		Console::Clear();
		registrarPedido();
		Almacen_menu();
	}
	if (opcion == 3) {
		mostrarInventario();
		Console::Clear();
	}

	if (opcion == 4) {
		mostrarPorCategorias();
		Console::Clear();
	}

	if (opcion == 5) {
		ordenamiento_menu();
		Console::Clear();
	}

	if (opcion == 6) {
		Console::Clear();
		mostrarRutasDisponibles();
	}

	if (opcion == 7) {
		Console::Clear();
	}
}

template<class T>
inline void Almacen<T>::ordenamiento_menu() {
	Console::Clear();
	string indicador = "<=";
	gotoxy(getXCenter(69), 3); cout << R"(   ____           __                           _            __      )";
	gotoxy(getXCenter(69), 4); cout << R"(  / __ \_________/ /__  ____  ____ _____ ___  (_)__  ____  / /_____ )";
	gotoxy(getXCenter(69), 5); cout << R"( / / / / ___/ __  / _ \/ __ \/ __ `/ __ `__ \/ / _ \/ __ \/ __/ __ \)";
	gotoxy(getXCenter(69), 6); cout << R"(/ /_/ / /  / /_/ /  __/ / / / /_/ / / / / / / /  __/ / / / /_/ /_/ /)";
	gotoxy(getXCenter(69), 7); cout << R"(\____/_/   \__,_/\___/_/ /_/\__,_/_/ /_/ /_/_/\___/_/ /_/\__/\____/ )";
	gotoxy(getXCenter(69), 8); cout << R"(--------------------------------------------------------------------)";

	gotoxy(50, 10); cout << R"(Ordenar por Nombre (A->Z))";
	gotoxy(50, 12); cout << R"(Ordenar por Nombre (Z->A))";
	gotoxy(50, 14); cout << R"(Ordenar por Cantidad (Mayor->Menor))";
	gotoxy(50, 16); cout << R"(Ordenar por Cantidad (Menor->Mayor))";
	gotoxy(50, 18); cout << R"(Ordenar por Precio (Mayor->Menor))";
	gotoxy(50, 20); cout << R"(Ordenar por Precio (Menor->Mayor))";
	gotoxy(50, 22); cout << R"(Volver al Menu)";

	short opcion = logica_menu(10, 7, 45, 10);


	if (opcion == 1) {
		Console::Clear();
		unalista.ordenarNombre(CriterioDeOrdenamiento::Descendente);
		mostrarInventario();
	}
	if (opcion == 2) {
		Console::Clear();
		unalista.ordenarNombre(CriterioDeOrdenamiento::Ascendente);
		mostrarInventario();
	}
	if (opcion == 3) {
		Console::Clear();
		unalista.ordenarCantidad(CriterioDeOrdenamiento::Descendente);
		mostrarInventario();
	}
	if (opcion == 4) {
		Console::Clear();
		unalista.ordenarCantidad(CriterioDeOrdenamiento::Ascendente);
		mostrarInventario();
	}

	if (opcion == 5) {
		Console::Clear();
		unalista.ordenarPrecio(CriterioDeOrdenamiento::Descendente);
		mostrarInventario();
	}

	if (opcion == 6) {
		Console::Clear();
		unalista.ordenarPrecio(CriterioDeOrdenamiento::Ascendente);
		mostrarInventario();
	}

	if (opcion == 7) {
		Console::Clear();
		Almacen_menu();
	}
}

template<class T>
inline T Almacen<T>::getElementoLista(int n)
{

	return unalista.obtenerPos(n);
}

/*

	KEVIN NO TE OLVIDES, ESTA AQUI, REVISA DOS VECES, YA POR FAVOR, SE QUE ESTAS CANSADO, SE QUE YA HICISTE 9 EJERCICIOS, PERO
*/
template<class T>
inline void Almacen<T>::mostrarPorCategorias()
{
	Console::Clear();
	toHashTable();
	
	gotoxy(getXCenter(60), Console::WindowTop + 1);  cout << R"(   _________  ______________________  ____  _______   _____)";
	gotoxy(getXCenter(60), Console::WindowTop + 2); cout << R"(  / ____/   |/_  __/ ____/ ____/ __ \/ __ \/  _/   | / ___/)";
	gotoxy(getXCenter(60), Console::WindowTop + 3); cout << R"( / /   / /| | / / / __/ / / __/ / / / /_/ // // /| | \__ \ )";
	gotoxy(getXCenter(60), Console::WindowTop + 4); cout << R"(/ /___/ ___ |/ / / /___/ /_/ / /_/ / _, _// // ___ |___/ / )";
	gotoxy(getXCenter(60), Console::WindowTop + 5); cout << R"(\____/_/  |_/_/ /_____/\____/\____/_/ |_/___/_/  |_/____/  )";
	cout << "\n\n"; //un \n para que no se vea tan pegado

	hashTabla->DispAll([](list<Entidad<string, T>> entidad) {
		for (auto it = entidad.begin(); it != entidad.end(); it++) {
			cout << " - " << it->getKey() << "\n\n";

		}
	});

	hashTabla->makeEmpty();

	mostrarOpcion(new string("Volver al men" + string(1, 163)), getXCenter(18), true);

	elegirOpcion(true);
}

template<class T>
inline void Almacen<T>::toHashTable()
{
	unalista.forEach([this](T t) {
		hashTabla->insert(Entidad<string, T>(t.getCategoria(), t));
		});
}


template<class T>
inline void Almacen<T>::mostrarPedidos()
{
	Console::Clear();

	gotoxy(getXCenter(105), Console::WindowTop + 1);  cout << R"(    ____  __________  ________  ____  _____    ____  _______   ______  ___________   ___________________)";
	gotoxy(getXCenter(105), Console::WindowTop + 2); cout << R"(   / __ \/ ____/ __ \/  _/ __ \/ __ \/ ___/   / __ \/ ____/ | / / __ \/  _/ ____/ | / /_  __/ ____/ ___/)";
	gotoxy(getXCenter(105), Console::WindowTop + 3); cout << R"(  / /_/ / __/ / / / // // / / / / / /\__ \   / /_/ / __/ /  |/ / / / // // __/ /  |/ / / / / __/  \__ \)";
	gotoxy(getXCenter(105), Console::WindowTop + 4); cout << R"( / ____/ /___/ /_/ // // /_/ / /_/ /___/ /  / ____/ /___/ /|  / /_/ // // /___/ /|  / / / / /___ ___/ /)";
	gotoxy(getXCenter(105), Console::WindowTop + 5); cout << R"(/_/   /_____/_____/___/_____/\____//____/  /_/   /_____/_/ |_/_____/___/_____/_/ |_/ /_/ /_____//____/)";

	if (!proveedor->size()) {
		string mensaje = string("Por el momento, no cuenta con pedidos, si gusta agregar, hagalo en realizar pedido.");


		gotoxy(getXCenter(mensaje.size()), getYCenter(1));

		cout << mensaje;
	}
	else {

		short* pos = new short(0);

		proveedor->forEach([pos](T t, bool esInicio) mutable {
			t.mostrar(9, esInicio, ++ * pos);
			});

		delete pos;
	}
	mostrarBotones(!proveedor->size());

	elegirOpcion(!proveedor->size(), new function<void()>([this]() {
		archivoEscritor->close();
		archivoEscritor->open("Medicamentos.dat", ios::binary | ios::app);
		}));
}

template<class T>
inline void Almacen<T>::registrarPedido()
{
	Console::Clear();
	string temp_Name = "";
	int temp_cantidad = 0;

	gotoxy(getXCenter(35), getYCenter(5)); cout << "Ingrese el nombre de la medicina: ";
	getline(cin >> ws, temp_Name);
	gotoxy(getXCenter(30), getYCenter(5) + 2);  cout << "Ingrese la cantidad a pedir: ";
	cin >> temp_cantidad;

	proveedor->agregarPedido(temp_Name, temp_cantidad);
}

template<class T>
inline void Almacen<T>::elegirOpcion(bool pedirPedidoDesabilitado, function<void()>* adicional)
{
	int opcion = 0;

	while (1) {
		if (_kbhit()) {
			char tecla = _getch();


			if (!pedirPedidoDesabilitado) {
				if (tecla == 75) {
					opcion--;
					if (opcion < 0) opcion = 1;
				}
				else if (tecla == 77) {
					opcion++;
					if (opcion > 1) opcion = 0;
				}

				if (tecla == 75 || tecla == 77) {
					mostrarOpcion(new string("Volver al men" + string(1, 163)),
						getXCenter(37), opcion == 0);

					mostrarOpcion(new string("Recibir pedido"),
						getXCenter(37) + 19, opcion == 1);
				}

			}
			if (tecla == 13) break;


		}
	}

	if (opcion == 0) {
		// Volver al menu
		Console::Clear();
		if (adicional != nullptr) (*adicional)();
		Almacen_menu();
	}
	else if (opcion == 1) {
		// Recibir el pedido
		Console::Clear();
		T pedido = proveedor->recibirPedido();
		unalista.agregaInicial(pedido);
		guardarMedicamentoPersistente(pedido);
		mostrarPedidos();

		Console::Clear();
	}

}

template<class T>
inline void Almacen<T>::mostrarBotones(bool pedirPedidoDesabilitado)
{
	int x = getXCenter(37);

	string* message = new string("Volver al men" + string(1, 163));

	mostrarOpcion(message, x, true);
	x += message->length() + 5;

	*message = "Recibir pedido";
	mostrarOpcion(message, x, false, pedirPedidoDesabilitado);

	delete message;
}

template<class T>
inline void Almacen<T>::mostrarOpcion(string* message, int x, bool activado = false, bool desactivado = false)
{
	if (activado) color(ConsoleColor::Cyan);
	else if (desactivado) color(ConsoleColor::DarkGray);
	else color(ConsoleColor::White);

	gotoxy<short>(x, Console::WindowHeight - 4);

	cout << char(201);
	for (short i = 0; i < message->length() + 2; i++) cout << char(205);
	cout << char(187);

	gotoxy<short>(x, Console::WindowHeight - 3);

	cout << char(186) << " " << *message << " " << char(186);

	gotoxy<short>(x, Console::WindowHeight - 2);

	cout << char(200);
	for (short i = 0; i < message->length() + 2; i++) cout << char(205);
	cout << char(188);

	if (activado || desactivado) color(ConsoleColor::White);
}


template<class T>
inline void Almacen<T>::mostrarInventario()
{
	Console::Clear();


	gotoxy(getXCenter(53), Console::WindowTop + 1); cout << R"(    ____                      __             _)";
	gotoxy(getXCenter(53), Console::WindowTop + 2); cout << R"(   /  _/___ _   _____  ____  / /_____ ______(_)___)";
	gotoxy(getXCenter(53), Console::WindowTop + 3); cout << R"(   / // __ \ | / / _ \/ __ \/ __/ __ `/ ___/ / __ \)";
	gotoxy(getXCenter(53), Console::WindowTop + 4); cout << R"( _/ // / / / |/ /  __/ / / / /_/ /_/ / /  / / /_/ /)";
	gotoxy(getXCenter(53), Console::WindowTop + 5); cout << R"(/___/_/ /_/|___/\___/_/ /_/\__/\__,_/_/  /_/\____/)";

	obtenerMedicamentosInventario();

	unalista.coutLista();

	mostrarOpcion(new string("Volver al men" + string(1, 163)), getXCenter(18), true);

	elegirOpcion(true);

}

template <class T>
inline void Almacen<T>::guardarMedicamentoPersistente(T nodo) {

	char envio[50];
	char categoria[17];

	strcpy(envio, nodo.getNombre().c_str());
	strcpy(categoria, nodo.getCategoria().c_str());

	Medicamento<const char*, int, float>::MedicamentoStruct medicamentoStruct(envio,
		int(nodo.getCantidad()), nodo.getPrecio(), categoria, nodo.getSucursalIdx(), nodo.getVecesVendido());


	if (archivoEscritor->is_open()) {
		archivoEscritor->write((char*)&medicamentoStruct,
			sizeof(Medicamento<string, int, float>::MedicamentoStruct));
	}

}

template <class T>
inline void Almacen<T>::obtenerMedicamentosInventario() {

	Medicamento<string, int, float>::MedicamentoStruct medicamento("", 0, 0.0, "");


	if (archivoLector->is_open()) {

		while (archivoLector->read((char*)&medicamento, sizeof(Medicamento<string, int, float>::MedicamentoStruct))) {
			// Procesar la estructura leída
			// Aquí puedes hacer lo que necesites con la estructura leída desde el archivo
			Medicamento<string, int, float> medicamentoGuardado(medicamento.nombre, medicamento.cantidad, medicamento.precio,
				medicamento.categoria, medicamento.vecesVendido, medicamento.sucursalIdx);

			unalista.agregaInicial(medicamentoGuardado);
		}

	}

}

template <class T>
inline void Almacen<T>::rutaMasRapidaByMedicamento(T medicamento)
{
	vector<int>* camino = grafos->dijkstra(0, medicamento.getSucursalIdx());

	if (camino != nullptr) {
		short baseX = (Console::WindowWidth / 6 - 11 / 2) + Console::WindowWidth * 2 / 3;
		short baseY = getYCenter(camino->size() * 2 - 1);

		for (short i = camino->size() - 1; i >= 0; i--) {
			string v = grafos->obtenerVertice(camino->at(i));
			gotoxy(short(baseX + (v == "Almacen" ? 1 : 0)), short(baseY + i * 2)); cout << v;
			if (i <= 0) {
				gotoxy(short(baseX + 11 / 2), short(baseY + i * 2 + 1)); cout << char(25);
			}
		}
	}
}

template <class T>
inline void Almacen<T>::borrarRutaMasRapidaByMedicamento(T medicamento)
{
	vector<int>* camino = grafos->dijkstra(0, medicamento.getSucursalIdx());

	if (camino != nullptr) {
		short baseX = (Console::WindowWidth / 6 - 11 / 2) + Console::WindowWidth * 2 / 3;
		short baseY = getYCenter(camino->size() * 2 - 1);

		for (short i = camino->size() - 1; i >= 0; i--) {
			string v = grafos->obtenerVertice(camino->at(i));
			gotoxy(short(baseX + (v == "Almacen" ? 1 : 0)), short(baseY + i * 2)); cout << "               ";
			if (i <= 0) {
				gotoxy(short(baseX + 11 / 2), short(baseY + i * 2 + 1)); cout << "  ";
			}
		}
	}
}

template <class T>
inline void Almacen<T>::elegirMedicamentoLive()
{
	short actualMedicamento = 0;

	while (1) {
		if (_kbhit()) {
			char tecla = _getch();

			if (tecla == 72 || tecla == 'w' || tecla == 80 || tecla == 's') {
				borrarRutaMasRapidaByMedicamento(unalista.obtenerPos(actualMedicamento));
				unalista.obtenerPos(actualMedicamento).mostrar(6, getYCenter((unalista.get_lon() - 1) * 3), ConsoleColor::DarkGray, actualMedicamento);
			}

			if (tecla == 72 || tecla == 'w') {
				actualMedicamento = (actualMedicamento - 1) + (actualMedicamento - 1 < 0) * (unalista.get_lon());
			}

			if (tecla == 80 || tecla == 's') {
				actualMedicamento = (actualMedicamento + 1) % unalista.get_lon();
			}

			if (tecla == 72 || tecla == 'w' || tecla == 80 || tecla == 's') {
				unalista.obtenerPos(actualMedicamento).mostrar(6, getYCenter((unalista.get_lon() - 1) * 3), ConsoleColor::Magenta, actualMedicamento);
				rutaMasRapidaByMedicamento(unalista.obtenerPos(actualMedicamento));
			}

			if (tecla == 27) {
				break;
			}
		}
	}

	Almacen_menu();
}