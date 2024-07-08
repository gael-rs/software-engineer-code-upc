#pragma once
#include "Proveedor.h"
#include "Lista_Medicamentos.h"

template <class T>
class Almacen
{
private:
	Proveedor<T>* proveedor;
	Lista_Medicamentos<T> unalista;
	ofstream* archivoEscritor;
	ifstream* archivoLector;

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

	void Almacen_menu();

	T getElementoLista(int n);

	void mostrarOpcion(string* message, int x, bool seleccionado = false, bool desactivado = false);

	Lista_Medicamentos<T> getUnaLista();
};


template <class T>
Almacen<T>::Almacen()
{
	this->proveedor = new Proveedor<T>;
	this->archivoEscritor = new ofstream();
	this->archivoLector = new ifstream();
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
}

template<class T>
inline Lista_Medicamentos<T> Almacen<T>::getUnaLista() {
	return unalista;
}

template<class T>
inline void Almacen<T>::agregarInicioLista(T obj) {
	unalista.agregaInicial(obj);
}

//----------------------
template<class T>
inline void Almacen<T>::Almacen_menu()
{

	Console::Clear();
	string indicador = "<=";
	gotoxy(getXCenter(44), 3); cout << R"(    ___    __                              )";
	gotoxy(getXCenter(44), 4); cout << R"(   /   |  / /___ ___  ____ _________  ____ )";
	gotoxy(getXCenter(44), 5); cout << R"(  / /| | / / __ `__ \/ __ `/ ___/ _ \/ __ \)";
	gotoxy(getXCenter(44), 6); cout << R"( / ___ |/ / / / / / / /_/ / /__/  __/ / / /)";
	gotoxy(getXCenter(44), 7); cout << R"(/_/  |_/_/_/ /_/ /_/\__,_/\___/\___/_/ /_/ )";
	gotoxy(getXCenter(44), 8); cout << R"(-------------------------------------------)";

	gotoxy(50, 10); cout << R"(Lista de Pedidos Pendientes)";
	gotoxy(50, 12); cout << R"(Realizar Pedidos)";
	gotoxy(50, 14); cout << R"(Inventario)";
	gotoxy(50, 16); cout << R"(Volver al Menu)";


	short opcion = logica_menu(10, 4, 45, 10);

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
		Console::Clear();
	}
}

template<class T>
inline T Almacen<T>::getElementoLista(int n)
{

	return unalista.obtenerPos(n);
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
			t.mostrar(9, esInicio, ++* pos);
		});

		delete pos;
	}
	mostrarBotones(!proveedor->size());

	elegirOpcion(!proveedor->size(), new function<void ()>([this]() {
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
	cin.ignore(); getline(cin, temp_Name);
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
		if(adicional != nullptr) (*adicional)();
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

	strcpy(envio, nodo.getNombre().c_str());

	Medicamento<const char*, int, float>::MedicamentoStruct medicamentoStruct(envio,
		int(nodo.getCantidad()), nodo.getPrecio());


	if (archivoEscritor->is_open()) {
		archivoEscritor->write((char*)&medicamentoStruct,
			sizeof(Medicamento<string, int, float>::MedicamentoStruct));
	}

}

template <class T>
inline void Almacen<T>::obtenerMedicamentosInventario() {

	Medicamento<string, int, float>::MedicamentoStruct medicamento("", 0, 0.0);


	if (archivoLector->is_open()) {

		while (archivoLector->read((char* )&medicamento, sizeof(Medicamento<string, int, float>::MedicamentoStruct))) {
			// Procesar la estructura leída
			// Aquí puedes hacer lo que necesites con la estructura leída desde el archivo
			Medicamento<string, int, float> medicamentoGuardado(medicamento.nombre, medicamento.cantidad, medicamento.precio);

			unalista.agregaInicial(medicamentoGuardado);
		}

	}

}