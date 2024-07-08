#include "Encabezados.h"

template <typename T>
inline void gotoxy(T x, T y = Console::CursorTop) {
	Console::SetCursorPosition(x, y);
}

template <typename T>
inline void color(T color) {
	Console::ForegroundColor = ConsoleColor(color);
};

inline int getXCenter(string* s) {
	return ((Console::WindowWidth - s->length()) / 2);
}

template <typename T>
inline int getXCenter(T lengthX) {
	return ((Console::WindowWidth - lengthX) / 2);
}

template <typename T>
inline T getYCenter(T lengthY) {
	return ((Console::WindowHeight - lengthY) / 2);
}



inline void mostrar_creditos() {
	Console::Clear();
	gotoxy(getXCenter(17), 2); cout << "+-+-+-+-+-+-+-+-+";
	gotoxy(getXCenter(17), 3); cout << "|C|R|E|D|I|T|O|S|";
	gotoxy(getXCenter(17), 4); cout << "+-+-+-+-+-+-+-+-+";
	gotoxy(getXCenter(74), 6); cout << "Integrantes:             Carrera:                       Secci" << char(162) << "n:";
	gotoxy(getXCenter(74), 7); cout << "- Kevin Chi              Ingenier" << char(161) << "a de Software         SX34";
	gotoxy(getXCenter(74), 8); cout << "- Gael Rivera            Curso:";
	gotoxy(getXCenter(74), 9); cout << "- Alejandro Oroncoy      Algoritmos y estructura de datos\n\n";

	system("pause");
}


string* categorias = new string[25]{
				"Analgésicos",
				"Antibióticos",
				"Antifúngicos",
				"Antivirales",
				"Antipiréticos",
				"Antiinflamatorios",
				"Antihistamínicos",
				"Antidepresivos",
				"Antipsicóticos",
				"Antiepilépticos",
				"Ansiolíticos",
				"Broncodilatadores",
				"Cardiovasculares",
				"Diuréticos",
				"Hipoglucemiantes",
				"Anticoagulantes",
				"Antihipertensivos",
				"Laxantes",
				"Antieméticos",
				"Esteroides",
				"Inmunosupresores",
				"Antidiarreicos",
				"Antiespasmódicos",
				"Hormonas",
				"Sedantes"
};



inline short logica_menu(int pos_y_inicial, int cantidad_opciones, int x, int y) {
	short opcion = 1;
	string indicador = "=>";
	Console::ForegroundColor = ConsoleColor::Cyan;
	gotoxy(x, pos_y_inicial); cout << indicador;
	Console::ForegroundColor = ConsoleColor::White;

	while (1) {
		if (_kbhit()) {
			char caracter = _getch();
			if (caracter == 72 || caracter == 'w') {
				gotoxy(x, y);
				cout << "   ";
				opcion--;
				y -= 2;
				if (opcion < 1) {
					y = pos_y_inicial + (cantidad_opciones*2)-2;
					opcion = cantidad_opciones;
				};
				gotoxy(x, y);
				Console::ForegroundColor = ConsoleColor::Cyan;
				cout << indicador;
			}
			if (caracter == 80 || caracter == 's') {
				gotoxy(x, y);
				cout << "   ";
				opcion++;
				y += 2;
				if (opcion > cantidad_opciones) {
					y = pos_y_inicial;
					opcion = 1;
				};
				gotoxy(x, y);
				Console::ForegroundColor = ConsoleColor::Cyan;
				cout << indicador;
			}
			else if (caracter == 13) {
				Console::ForegroundColor = ConsoleColor::White;
				break;
			};
		}
	}

	return opcion;
}