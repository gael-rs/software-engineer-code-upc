#pragma once
#include <vector>
#include "Cupon.h"
using namespace std;

class CuponGenerator
{
public:
	CuponGenerator();
	~CuponGenerator();
	void crearValores();
	void crearCupon();
    void mostrarCupones();  
    float getDescuentoByCodigo(string codigo);

private:
	int elSuperNumero = 1;  //para que no se repitan los numeros
	vector<Cupon>* cupones;
};

CuponGenerator::CuponGenerator()
{
    cupones = new vector<Cupon>;
    crearValores();
}

CuponGenerator::~CuponGenerator()
{
    delete cupones;
}

inline void CuponGenerator::crearValores()
{
    int cantidad = rand() % 12 + 10;

    for (int i = 0; i < cantidad; i++)
    {
        Cupon* cupon = new Cupon(elSuperNumero);
        elSuperNumero++;
		cupones->push_back(*cupon);

        delete cupon;
    }
}

inline void CuponGenerator::crearCupon()
{
    Console::Clear();
    cout << "\nIngrese el nombre del cup" << char(162) << "n: ";
    string nombre;
    cin >> nombre;

    cout << "\nIngrese el porcentaje de descuento: ";
    int descuento;
    cin >> descuento;
    Cupon* cupon = new Cupon(nombre, descuento);
    cupones->push_back(*cupon);

	delete cupon;
}

inline void CuponGenerator::mostrarCupones()
{
    int baseX = 0;
    int xActual = 0;

    for each (Cupon cupon in *cupones)
    {
        cupon.mostrar(baseX, xActual);
    }
}

inline float CuponGenerator::getDescuentoByCodigo(string codigo)
{
    auto cupon = find_if(cupones->begin(), cupones->end(), [codigo](Cupon c) {
        return c.getCode() == codigo;
        });

    if(cupon != cupones->end()) return (*cupon).getPorcentaje();

    return 0.0;
}
