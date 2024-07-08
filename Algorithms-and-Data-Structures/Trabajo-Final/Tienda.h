#pragma once
#include "Almacen.h"
#include "Caja.h"
#include "Medicamento.h"
#include "Encabezados.h"


class Tienda
{
private:
	Almacen<Medicamento<string, int, float>>* objAlmacen;
	Caja<Medicamento<string, int, float>>* objCaja;

public:
	Tienda();
	~Tienda();
	void menu();
};

Tienda::Tienda()
{
	objAlmacen = new Almacen<Medicamento<string, int, float>>();
	objAlmacen->obtenerMedicamentosInventario();
	objCaja = new Caja<Medicamento<string, int, float>>(objAlmacen->getUnaLista());
}

Tienda::~Tienda()
{
	delete objAlmacen;
	delete objCaja;
}


inline void Tienda::menu()
{
	Console::SetWindowSize(130, 40);
	Console::Clear();
	string indicador = "<=";
	gotoxy(3, getYCenter(11) - 7); cout <<  R"(    ______                                _                   __  ___           __             __  ___            _      )";
	gotoxy(3, getYCenter(11) - 6); cout <<  R"(   / ____/___ __________ ___  ____ ______(_)___ _     __     /  |/  /_  _______/ /_  ____ _   /  |/  /___ _____ _(_)___ _)";
	gotoxy(3, getYCenter(11) - 5); cout <<  R"(  / /_  / __ `/ ___/ __ `__ \/ __ `/ ___/ / __ `/  __/ /_   / /|_/ / / / / ___/ __ \/ __ `/  / /|_/ / __ `/ __ `/ / __ `/)";
	gotoxy(3, getYCenter(11) - 4); cout <<  R"( / __/ / /_/ / /  / / / / / / /_/ / /__/ / /_/ /  /_  __/  / /  / / /_/ / /__/ / / / /_/ /  / /  / / /_/ / /_/ / / /_/ /)";
	gotoxy(3, getYCenter(11) - 3); cout << R"(/_/    \__,_/_/  /_/ /_/ /_/\__,_/\___/_/\__,_/    /_/    /_/  /_/\__,_/\___/_/ /_/\__,_/  /_/  /_/\__,_/\__, /_/\__,_/ )";
	gotoxy(3, getYCenter(11) - 2); cout <<  R"(                                                                                                        /____/)";
	gotoxy(3, getYCenter(11) - 1); cout << R"(-----------------------------------------------------------------------------------------------------------------------------)";

	gotoxy(55, getYCenter(11) + 1); cout << R"(Caja)";
	gotoxy(55, getYCenter(11) + 3); cout << R"(Almacen)";
	gotoxy(55, getYCenter(11) + 5); cout << R"(Integrantes)";
	gotoxy(55, getYCenter(11) + 7); cout << R"(Salir)";


	//parametros para escoger en el menu
	int x = 50;  //un poco m�s a la derecha de donde estan las opciones
	int y_inicial = getYCenter(11) + 1;
	int y = 12;
	short opcion = 1;


	gotoxy(x, y_inicial); cout << indicador;

	opcion = logica_menu(y_inicial, 4, x, y_inicial);

	if (opcion == 1) {
		//Caja_menu();   //mostrar el menu de caja
		objCaja->actualizar_lista(objAlmacen->getUnaLista());
		objCaja->menu_caja();
		menu();
	}
	if (opcion == 2) {
		//almacen_menu();    //mostrar el menu de almacen
		objAlmacen->Almacen_menu();
		menu();
	}
	if (opcion == 3) {
		//pantalla_integrantes();
		mostrar_creditos();
		Console::Clear();
		menu();
	}
	if (opcion == 4) {
		exit(0);
	}
}