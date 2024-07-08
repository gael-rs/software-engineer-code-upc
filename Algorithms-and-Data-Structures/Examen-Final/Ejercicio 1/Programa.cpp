#include <iostream>
#include "CGenerador.h"
#include "ListaIteradores.h"
#include "CVehiculo.h"
#include "Quicksort.h"
#include "Arbol BB.h"


using namespace std;


void imprimir(Data e) {
    cout << e.ToString() << endl;
}

void ordenarPorColor(Lista<Data>& lista) {
    int n = lista.longitud();
    if (n <= 1) return;

    Data* arreglo = new Data[n];
    int index = 0;
    for (auto it = lista.begin(); it != lista.end(); ++it) {
        arreglo[index++] = *it;
    }

    quicksort(arreglo, 0, n - 1);

    lista.borrarTodo();

    for (int i = 0; i < n; ++i) {
        lista.agregaFinal(arreglo[i]);
    }

    delete[] arreglo;
}




void menu() {
    Lista<Data> listaDatos;
    ArbolBB<Data> arbol([](Data e) { imprimir(e); }, [](Data a, Data b) { return a.marca < b.marca ? -1 : a.marca > b.marca ? 1 : 0; });

    int opcion;
    do {
        cout << "=====================================================================================" << endl;
        cout << "            M  E  N  U        D  E       O  P  C  I  O  N  E  S:" << endl;
        cout << "1. Generar datos" << endl;
        cout << "2. Ordenar datos por color (QUICKSORT)" << endl;
        cout << "3. Mostrar Datos" << endl;
        cout << "4. Busqueda Binaria por Marca" << endl;
        cout << "=====================================================================================" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cout << endl;
        switch (opcion) {
        case 1: {
            Generador generador;
            int numDatos;
            cout << "Ingrese el numero de datos a generar: ";
            cin >> numDatos;
            generador.generar_datos(numDatos);
            cout << numDatos << " datos generados correctamente." << endl;

            for (int i = 0; i < generador.obtenerNumDatos(); ++i) {
                listaDatos.agregaFinal(generador.obtenerDato(i));
            }

            for (int i = 0; i < generador.obtenerNumDatos(); ++i) {
                Data dato = generador.obtenerDato(i);
                listaDatos.agregaFinal(dato);
                arbol.insertar(dato);  // Inserta los datos en el árbol
            }
            break;
        }
        case 2: {
            ordenarPorColor(listaDatos);
            cout << "Datos ordenados por color." << endl;
            break;
        }
        case 3: {
            cout << "Datos almacenados en la lista:" << endl;
            for (auto it = listaDatos.begin(); it != listaDatos.end(); ++it) {
                imprimir(*it);
            }
            break;
        }
        case 4: {
            string marca;
            cout << "Ingrese la marca a buscar: ";
            cin >> marca;
            Data resultado;
            if (arbol.buscarPorMarca(marca, resultado)) {
                cout << "Primer IDVehiculo encontrado para la marca " << marca << ": " << resultado.IDVehiculo << endl;
            }
            else {
                cout << "Marca " << marca << " no encontrada." << endl;
            }
            break;
        }
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