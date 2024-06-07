#include <iostream>
#include "ArbolBB.h"
#include "CGenerador.h"
#include "mergeSort.h" // Incluir el archivo de mergeSort
#include "ListaIteradores.h"
#include "CProducto.h" // Incluir el archivo de definición de Diagnostico

using namespace std;

void imprimir(Producto e) {
    cout << e.ToString() << endl;
}

bool esPrimo(int num) {
    if (num <= 1) {
        return false;
    }
    for (int i = 2; i * i <= num; ++i) {
        if (num % i == 0) {
            return false;
        }
    }
    return true;
}

void menu() {
    Generador* geng = new Generador();
	Lista<Producto>* listaProductos = new Lista<Producto>();    
    ArbolBB<Producto>* arbol = nullptr;
    int opcion;
    do {
        cout << "=====================================================================================" << endl;
        cout << "            M  E  N  U        D  E       O  P  C  I  O  N  E  S:" << endl;
        cout << "1. Generar datos" << endl;
        cout << "2. Insertar datos en el árbol" << endl;
        cout << "3. Mostrar productos" << endl;
        cout << "4. Ordenar productos por precio" << endl;
        cout << "5. Busqueda Binaria del Producto por ID" << endl;
        cout << "6. Operacion con Arbol (STOCK)" << endl;
        cout << "7. Verificar si el elemento del nodo mayor es múltiplo de 5 (Para verificar seguir estas opciones: 1 - 6 - 7)" << endl;
		cout << "8. Eliminar nodo por stock" << endl;
        cout << "9. Salir" << endl;
        cout << "=====================================================================================" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        cout << endl;
        switch (opcion) {
        case 1:
            int num;
            cout << "Ingrese la cantidad de registros a generar: ";
            cin >> num;
            geng->generar_datos(num);
            cout << num << " registros generados" << endl;
            // Agregar los productos generados a la lista
            for (int i = 0; i < geng->obtenerNumProductos(); ++i) {
                listaProductos->agregaFinal(geng->obtenerProducto(i));
            }
            break;
        case 2:
            break;
        case 3:
            for (auto it = listaProductos->begin(); it != listaProductos->end(); ++it) {
                imprimir(*it);
            }
            break;
        case 4:
            mergeSort<Lista<Producto>, Producto>(listaProductos, compararPorPrecio);
            cout << "Productos ordenados por precio" << endl;
            break;
        case 5: {
            string idBuscado;
            cout << "Ingrese el id del producto a buscar (AAA - EEE - III - OOO - UUU): ";
            cin >> idBuscado;

            // Búsqueda binaria
            int inicio = 0;
            int fin = listaProductos->longitud() - 1;
            int indiceEncontrado = -1;

            while (inicio <= fin) {
                int medio = (inicio + fin) / 2;
                Producto productoMedio = listaProductos->obtenerPos(medio);

                if (productoMedio.id == idBuscado) {
                    indiceEncontrado = medio;
                    break;
                }
                else if (productoMedio.id < idBuscado) {
                    inicio = medio + 1;
                }
                else {
                    fin = medio - 1;
                }
            }

            // Mostrar resultados
            if (indiceEncontrado != -1) {
                cout << "Producto encontrado en el índice: " << indiceEncontrado << endl;
            }
            else {
                cout << "Producto no encontrado." << endl;
            }
            break;
        }
        case 6: {
            // Crear el árbol binario de búsqueda basado en el stock
            arbol = new ArbolBB<Producto>(imprimir);

            // Insertar los productos en el árbol
            for (auto it = listaProductos->begin(); it != listaProductos->end(); ++it) {
                arbol->insertar(*it);
            }

            // Mostrar los productos en orden según el stock
            cout << "Productos ordenados por stock:" << endl;
            arbol->enOrden();
            
            break;
        }
        case 7:
            if (arbol != nullptr) {
                // Obtener la raíz del árbol
                Nodo<Producto>* raizArbol = arbol->obtenerRaiz();

                // Verificar si el árbol está vacío
                if (raizArbol != nullptr) {
                    // Encontrar el nodo más grande en el árbol
                    while (raizArbol->der != nullptr) {
                        raizArbol = raizArbol->der;
                    }

                    // Verificar si el elemento del nodo mayor es múltiplo de 5
                    if (raizArbol->elemento.stock % 5 == 0) {
                        cout << "El elemento del nodo mayor es múltiplo de 5." << endl;
                    }
                    else {
                        cout << "El elemento del nodo mayor no es múltiplo de 5." << endl;
                    }
                }
                else {
                    cout << "El árbol está vacío." << endl;
                }
            }
            else {
                cout << "El árbol está vacío. Inserta elementos primero." << endl;
            }
            break;
        case 8:
            /*
            if (arbol != nullptr) {
                // Solicitar al usuario que ingrese el stock del producto a eliminar
                int stockAEliminar;
                cout << "Ingrese el stock del producto que desea eliminar del árbol binario: ";
                cin >> stockAEliminar;

                // Eliminar el nodo que contiene el elemento ingresado
                if (arbol->eliminarPorStock(stockAEliminar)) {
                    cout << "Producto con stock " << stockAEliminar << " eliminado correctamente." << endl;

                    // Mostrar los elementos del árbol binario actual
                    cout << "Elementos del árbol binario actual:" << endl;
                    arbol->enOrden();

                    // Verificar si el stock eliminado es un número primo
                    if (esPrimo(stockAEliminar)) {
                        cout << "El stock eliminado (" << stockAEliminar << ") es un número primo." << endl;
                    }
                }
                else {
                    cout << "No se encontró ningún producto con el stock especificado en el árbol binario." << endl;
                }
            }
            else {
                cout << "El árbol está vacío. Inserta elementos primero." << endl;
            }
            break;
            */
        case 9:
            cout << "Saliendo..." << endl;
            break;
        default:
            cout << "Opción no válida. Intente denuevo..." << endl;
            break;

        }
        } while (opcion != 5);
        if (arbol != nullptr) {
            delete arbol;
        }
        delete geng;
    
}

int main() {
    menu();
    cin.get();
    return 0;
}
