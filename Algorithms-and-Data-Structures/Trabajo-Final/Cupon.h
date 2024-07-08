#pragma once

#include "sstream"
#include "iomanip"
#include <iostream>
using namespace System;
using namespace std;

class Cupon
{
public:
	Cupon(int intnombre);
	Cupon(string nombre, int porcentaje);
	~Cupon();
	void mostrar(int& baseX, int& xActual);
	string generateCode();
	string getCode();
	float getPorcentaje();

private:
	string nombre_str = "";
	int nombre_int = 0;
	float porcentajeDescuento;
	string code = "";
};


Cupon::Cupon(int intnombre)
{
	float porcentajeDescuento = (float(rand()) / RAND_MAX) * 50.0;

	this->nombre_int = intnombre;  //se le pone un numero para despues hacer un: cout << "Proceso" << random
	this->porcentajeDescuento = porcentajeDescuento;
	this->code = generateCode();
}

inline Cupon::Cupon(string nombre, int porcentaje)
{
	this->nombre_str = nombre;  //se le pone un numero para despues hacer un: cout << "Proceso" << random
	this->porcentajeDescuento = porcentaje;
	this->code = generateCode();
}


Cupon::~Cupon()
{
}



inline void Cupon::mostrar(int& baseX, int& xActual)
{
	stringstream* ss = new stringstream;

	*ss << "Descuento: " << setprecision(trunc(this->porcentajeDescuento) < 10 ? 3 : 4) << this->porcentajeDescuento << "%  | ";
	*ss << "C" << char(162) << "digo: " << this->code;

	string text = ss->str();

	Console::ForegroundColor = ConsoleColor(rand() % 15);

	gotoxy<short>(xActual, 7 + trunc((baseX + text.length() + 4 + 1) / Console::WindowWidth) * 3);

	cout << char(2);
	for (short i = 0; i < text.length() + 2; i++) cout << char(205);
	cout << char(2);

	gotoxy<short>(xActual, 7 + trunc((baseX + text.length() + 4 + 1) / Console::WindowWidth) * 3 + 1);

	cout << char(186) << " " << text << " " << char(186);

	gotoxy<short>(xActual, 7 +  trunc((baseX + text.length() + 4 + 1) / Console::WindowWidth) * 3 + 2);

	cout << char(2);
	for (short i = 0; i < text.length() + 1; i++) cout << char(205);
	cout << char(2);

	cout << char(2);

	Console::ForegroundColor = ConsoleColor::White;

	baseX += text.length() + 5;
	xActual = (xActual + (text.length() + 5)*2 > Console::WindowWidth ? 0 : xActual + text.length() + 5);

	delete ss;
}

inline string Cupon::generateCode()
{
	stringstream* ss = new stringstream;

	short* n = new short(rand() % 6 + 5);
	short* decision = new short;
	char* randoms = new char;

	for (short i = 0; i < *n; i++) {
		decision = new short(rand() % 3);

		randoms = new char[3] {
			char(rand() % 26 + 65),
				char(rand() % 26 + 97),
				char(rand() % 10 + 48)
			};

		*ss << randoms[*decision];
	}


	string result = ss->str();

	delete n;
	delete ss;
	delete decision;
	delete[] randoms;

	return result;
}

inline string Cupon::getCode()
{
	return code;
}

inline float Cupon::getPorcentaje()
{
	return  porcentajeDescuento;
}
