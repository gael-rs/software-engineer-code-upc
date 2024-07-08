#pragma once
#include <string>
#include <sstream>

using namespace::std;

class CCliente
{
public:
	string nombre;
	int dni;
	int numeroCelular;
	int numeroDestino;
	double monto;
	CCliente();
	~CCliente();
	string ToString();
};

CCliente::CCliente(){
	this->nombre = "";
	this->dni = 0;
	this->numeroCelular = 0;
	this->numeroDestino = 0;
	this->monto = 0.0;
}

string CCliente::ToString() {
	stringstream ss;
	ss << "Nombre: \t" << this->nombre << endl;
	ss << "DNI: \t" << this->dni << endl;
	ss << "Numero de Celular: \t" << this->numeroCelular << endl;
	ss << "Numero de Destino: \t" << this->numeroDestino << endl;
	ss << "Monto: \t" << this->monto << endl;
	return ss.str();
}

CCliente::~CCliente(){}