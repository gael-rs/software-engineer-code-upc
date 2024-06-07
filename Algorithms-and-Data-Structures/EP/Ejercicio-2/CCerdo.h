#pragma once
#include <string>
#include <sstream>

using namespace std;

class CCRegistro
{
public:
	string codigoCerdo;
	int edad;
	float peso; //Mejor float que double ya que ocupa menos memoria
	float altura; //Mejor float que double ya que ocupa menos memoria
	float temperatura; //Mejor float que double ya que ocupa menos memoria
	CCRegistro();
	~CCRegistro();
	string ToString();
};

CCRegistro::CCRegistro() {
	this->codigoCerdo = "";
	this->edad = 0;
	this->peso = 0.0;
	this->altura = 0.0;
	this->temperatura = 0.0;
}

string CCRegistro::ToString() {
	stringstream ss;
	ss << "Codigo del cerdo: \t" << this->codigoCerdo << endl;
	ss << "Edad del cerdo: \t" << this->edad << endl;
	ss << "Peso del cerdo: \t" << this->peso << endl;
	ss << "Altura del cerdo: \t" << this->altura << endl;
	ss << "Temperatura del cerdo: \t" << this->temperatura << endl;
	return ss.str();
}

CCRegistro::~CCRegistro() {}