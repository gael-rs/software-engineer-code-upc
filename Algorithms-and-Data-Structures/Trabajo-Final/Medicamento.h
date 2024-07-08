#pragma once
#include "Utilidades.h"

template<typename T1, typename T2, typename T3>
class Medicamento
{
private:
	T1 nombre;
	T2 cantidad;
	T3 precio;
	short vecesVendido;
	string categoria;
	short sucursalIdx;


public:
	struct MedicamentoStruct;
	Medicamento();
	Medicamento(T1 nombre, T2 cantidad, T3 precio);
	Medicamento(T1 nombre, T2 cantidad, T3 precio, string categoria, short vecesVendido, short sucursalIdx);
	~Medicamento();

	T1 getNombre();
	void setNombre(T1& nombre);

	T2 getCantidad();
	void setCantidad(T2& cantidad);

	T3 getPrecio();
	void setPrecio(T3& Precio);

	short getVecesVendido();
	void setVecesVendido(short vecesVendido);

	string getCategoria();
	void setCategoria(string categoria);
	
	short getSucursalIdx();
	void setSucursalIdx(short sucursalIdx);

	void mostrar(short baseY, bool esInicio, int pos);
	void mostrar(short baseY, ConsoleColor cc, int pos);
	void mostrar(short baseX, short baseY, ConsoleColor cc, int pos);
	void mostrarVenta(short baseY, ConsoleColor cc, int pos);

	MedicamentoStruct toStruct();
};

template <typename T1, typename T2, typename T3>
struct Medicamento<T1, T2, T3>::MedicamentoStruct {
	char nombre[50];
	char categoria[17];
	short sucursalIdx;
	int cantidad;
	float precio;
	short vecesVendido;

	MedicamentoStruct(char* _nombre, int _cantidad, float _precio, char* categoria, short sucursalIdx = -1, short vecesVendido = 0) {
		strcpy(nombre, _nombre);
		strcpy(this->categoria, categoria);
		cantidad = _cantidad;
		precio = _precio;
		this->vecesVendido = vecesVendido;
		this->sucursalIdx = sucursalIdx;
	};
};


template<typename T1, typename T2, typename T3>
inline Medicamento<T1, T2, T3>::Medicamento()
{
	this->nombre = T1();
	this->cantidad = T2();
	this->precio = T3();
	this->vecesVendido = 0;
	this->categoria = categorias[rand() % 25];
	this->sucursalIdx = -1;
}

template<typename T1, typename T2, typename T3>
inline Medicamento<T1, T2, T3>::Medicamento(T1 nombre, T2 cantidad, T3 precio)
{ 	
	this->nombre = nombre;
	this->cantidad = cantidad;
	this->precio = precio;
	this->vecesVendido = 0;
	this->categoria = categorias[rand() % 25];
	this->sucursalIdx = rand() % 10 + 1;
}

template<typename T1, typename T2, typename T3>
inline Medicamento<T1, T2, T3>::Medicamento(T1 nombre, T2 cantidad, T3 precio, string categoria, short vecesVendido, short sucursalIdx)
{
	this->nombre = nombre;
	this->cantidad = cantidad;
	this->precio = precio;
	this->vecesVendido = vecesVendido;
	this->categoria = categoria;
	this->sucursalIdx = sucursalIdx;
}

template<typename T1, typename T2, typename T3>
inline Medicamento<T1, T2, T3>::~Medicamento()
{
}

template<typename T1, typename T2, typename T3>
inline T1 Medicamento<T1, T2, T3>::getNombre()
{
	return nombre;
}

template<typename T1, typename T2, typename T3>
inline void Medicamento<T1, T2, T3>::setNombre(T1& nombre)
{
	this->nombre = nombre;
}

template<typename T1, typename T2, typename T3>
inline T2 Medicamento<T1, T2, T3>::getCantidad()
{
	return cantidad;
}

template<typename T1, typename T2, typename T3>
inline void Medicamento<T1, T2, T3>::setCantidad(T2& cantidad)
{
	this->cantidad = cantidad;
}

template<typename T1, typename T2, typename T3>
inline T3 Medicamento<T1, T2, T3>::getPrecio()
{
	return this->precio;
}

template<typename T1, typename T2, typename T3>
inline void Medicamento<T1, T2, T3>::setPrecio(T3& precio)
{
	this->precio = precio;
}

template<typename T1, typename T2, typename T3>
inline short Medicamento<T1, T2, T3>::getVecesVendido()
{
	return vecesVendido;
}

template<typename T1, typename T2, typename T3>
inline void Medicamento<T1, T2, T3>::setVecesVendido(short vecesVendido)
{
	this->vecesVendido = vecesVendido;
}

template<typename T1, typename T2, typename T3>
inline string Medicamento<T1, T2, T3>::getCategoria()
{
	return categoria;
}

template<typename T1, typename T2, typename T3>
inline void Medicamento<T1, T2, T3>::setCategoria(string categoria)
{
	this->categoria = categoria;
}

template<typename T1, typename T2, typename T3>
inline short Medicamento<T1, T2, T3>::getSucursalIdx()
{
	return sucursalIdx;
}

template<typename T1, typename T2, typename T3>
inline void Medicamento<T1, T2, T3>::setSucursalIdx(short sucursalIdx)
{
	this->sucursalIdx = sucursalIdx;
}

template<typename T1, typename T2, typename T3>
inline void Medicamento<T1, T2, T3>::mostrar(short baseY, bool esInicio, int pos)
{
	stringstream* ss = new stringstream;

	*ss << "Nombre: " << this->nombre;
	*ss << "   Cantidad: " << this->cantidad;
	*ss << "   Precio: " << this->precio;

	string* message = new string;
	*message = ss->str();

	if (esInicio) color(ConsoleColor::Cyan);
	else color(ConsoleColor::DarkGray);

	short* x = new short(getXCenter<short>(message->length() + 4));
	short* y = new short(baseY + pos * 3);

	gotoxy<short>(*x - 2, *y - 1);
	
	cout << char(201);
	for (short i = 0; i < message->length() + 2; i++) cout << char(205);
	cout << char(187);

	gotoxy<short>(*x - 2, *y);

	cout << char(186) << " " << *message << " " << char(186);

	gotoxy<short>(*x - 2, *y + 1);

	cout << char(200);
	for (short i = 0; i < message->length() + 2; i++) cout << char(205);
	cout << char(188);

	color(ConsoleColor::White);

	delete ss;
	delete message;
	delete x;
	delete y;
}

template<typename T1, typename T2, typename T3>
inline void Medicamento<T1, T2, T3>::mostrar(short baseY, ConsoleColor cc, int pos)
{
	stringstream* ss = new stringstream;

	*ss << "Nombre: " << this->nombre;
	*ss << "   Cantidad: " << this->cantidad;
	*ss << "   Precio: " << this->precio;

	string* message = new string;
	*message = ss->str();

	color(cc);

	short* x = new short(getXCenter<short>(message->length() + 4));
	short* y = new short(baseY + pos * 3);

	gotoxy<short>(*x - 2, *y - 1);

	cout << char(201);
	for (short i = 0; i < message->length() + 2; i++) cout << char(205);
	cout << char(187);

	gotoxy<short>(*x - 2, *y);

	cout << char(186) << " " << *message << " " << char(186);

	gotoxy<short>(*x - 2, *y + 1);

	cout << char(200);
	for (short i = 0; i < message->length() + 2; i++) cout << char(205);
	cout << char(188);

	color(ConsoleColor::White);

	delete ss;
	delete message;
	delete x;
	delete y;
}

template<typename T1, typename T2, typename T3>
inline void Medicamento<T1, T2, T3>::mostrar(short baseX, short baseY, ConsoleColor cc, int pos)
{

	stringstream* ss = new stringstream;

	*ss << "Nombre: " << this->nombre;
	*ss << "   Cantidad: " << this->cantidad;
	*ss << "   Precio: " << this->precio;

	string* message = new string;
	*message = ss->str();

	color(cc);

	short* x = new short(baseX);
	short* y = new short(baseY + pos * 3);

	gotoxy<short>(*x - 2, *y - 1);

	cout << char(201);
	for (short i = 0; i < message->length() + 2; i++) cout << char(205);
	cout << char(187);

	gotoxy<short>(*x - 2, *y);

	cout << char(186) << " " << *message << " " << char(186);

	gotoxy<short>(*x - 2, *y + 1);

	cout << char(200);
	for (short i = 0; i < message->length() + 2; i++) cout << char(205);
	cout << char(188);

	color(ConsoleColor::White);

	delete ss;
	delete message;
	delete x;
	delete y;
}

template<typename T1, typename T2, typename T3>
inline void Medicamento<T1, T2, T3>::mostrarVenta(short baseY, ConsoleColor cc, int pos)
{
	stringstream* ss = new stringstream;

	*ss << "Nombre: " << this->nombre;
	*ss << "   Ventas: " << this->vecesVendido;

	string* message = new string;
	*message = ss->str();

	color(cc);

	short* x = new short(getXCenter<short>(message->length() + 4));
	short* y = new short(baseY + pos * 3);

	gotoxy<short>(*x - 2, *y - 1);

	cout << char(201);
	for (short i = 0; i < message->length() + 2; i++) cout << char(205);
	cout << char(187);

	gotoxy<short>(*x - 2, *y);

	cout << char(186) << " " << *message << " " << char(186);

	gotoxy<short>(*x - 2, *y + 1);

	cout << char(200);
	for (short i = 0; i < message->length() + 2; i++) cout << char(205);
	cout << char(188);

	color(ConsoleColor::White);

	delete ss;
	delete message;
	delete x;
	delete y;
}

template<typename T1, typename T2, typename T3>
inline struct Medicamento<T1, T2, T3>::MedicamentoStruct Medicamento<T1, T2, T3>::toStruct()
{
	return MedicamentoStruct(nombre, cantidad, precio, vecesVendido);
}
