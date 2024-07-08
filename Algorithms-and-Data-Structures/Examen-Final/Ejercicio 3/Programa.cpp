#include <iostream>
#include "Grafos.h"

using namespace std;

void menu() {
    Grafo<string> grafo;
    int opcion;
    do {
        cout << "=====================================================================================" << endl;
        cout << "            M  E  N  U        D  E       O  P  C  I  O  N  E  S:" << endl;
        cout << "1. Generar grafo aleatorio" << endl;
        cout << "2. Mostrar vertice con mas arcos" << endl;
        cout << "3. Salir" << endl;
        cout << "=====================================================================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cout << endl;
        switch (opcion) {
        case 1: {
            grafo.registro_aleatorio();
            break;
        }
        case 2: {
            grafo.vertices_cantidad();
            break;
        }
        case 3: {
            cout << "ADIOOOS" << endl;
            break;
        }
        default:
            cout << "Opcion no valida. Intente denuevo..." << endl;
            break;
        }
    } while (opcion != 3);
}

int main() {
    menu();
    cin.get();
    cin.ignore();
    return 0;
}
