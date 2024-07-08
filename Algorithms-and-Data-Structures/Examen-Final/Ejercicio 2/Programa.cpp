#include <iostream>
#include "MiArbolBinario.h"

using namespace std;

void menu() {
    MiArbolBinario arbol;
    int opcion, numero;
    do {
        cout << "=====================================================================================" << endl;
        cout << "            M  E  N  U        D  E       O  P  C  I  O  N  E  S:" << endl;
        cout << "1. Insertar numero" << endl;
        cout << "2. Promedio en rango" << endl;
        cout << "3. Mostrar elementos en orden" << endl;
        cout << "4. Producto de digitos del mayor valor" <<endl;
        cout << "5. Salir" << endl; 
        cout << "=====================================================================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cout << endl;

        switch (opcion) {
        case 1:
            cout << "Ingrese un numero: ";
            cin >> numero;
            arbol.insertar(numero);
            break;

        case 2:
            if (arbol.cantidad() == 0) {
                cout << "El arbol esta vacio. No se puede calcular el promedio.\n";
            }
            else {
                cout << "Ingrese un valor para calcular el promedio en rango: ";
                cin >> numero;
                double promedio = arbol.promedio_rango(numero);
                cout << "El promedio de los elementos en el rango es: " << promedio << endl;
            }
            break;

        case 3:
            cout << "Elementos en orden: ";
            arbol.enOrden();
            cout << endl;
            break;

        case 4:
            if (arbol.cantidad() == 0) {
                cout << "El arbol esta vacio. No se puede calcular el producto de digitos.\n";
            }
            else {
                int producto = arbol.producto_digitos();
                cout << "El producto de los digitos del mayor valor es: " << producto << endl;
            }
            break;

        case 5:
            cout << "ADIOOOS...\n";
            break;

        default:
            cout << "Opcion no valida. Intente denuevo..." << endl;
            break;
        }
    } while (opcion != 5);
}

int main() {
    menu();
    cin.get();
    cin.ignore();
    return 0;
}
