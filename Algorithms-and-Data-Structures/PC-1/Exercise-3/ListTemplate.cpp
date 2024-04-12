#include <iostream>
#include <functional>
using namespace::std;

/*
Escribir un programa que utilice una función recursiva, que
calcule la suma de las cifras pares de un numero menos la suma
de cifras impares.La función debe ser ejecutada mediante una
función lambda y ser probada con por lo menos 3 diferentes
números.
Ejemplo:
Entrada A = 7452
Salida = 6 // suma de pares 6, suma de impares 12, 6-12 =-6
*/

//Declaramos la funcion lambda
function<int(int)> calcularEcuacion;

int main() {

    calcularEcuacion = [&](int numero) -> int {
        if (numero == 0) {
            return 0;
        }
        int ultimoDigito = numero % 10;
        if (ultimoDigito % 2 == 0) {
            return ultimoDigito + calcularEcuacion(numero / 10);
        }
        else {
            //Le colocamos un - al comienzo para que se reste al aplicar la recursividad
            return -ultimoDigito + calcularEcuacion(numero / 10);
        }
        };

    // Probamos la función lambda con estos numeros
    int num1 = 7452;      // numero aleatorio
    int num2 = 123454321; // numero capicua
    int num3 = 123456789; // sucesion de numeros

    cout << "Para el numero " << num1 << " la respuesta es : " << calcularEcuacion(num1) << endl;
    cout << "Para el numero " << num2 << " la respuesta es : " << calcularEcuacion(num2) << endl;
    cout << "Para el numero " << num3 << " la respuesta es : " << calcularEcuacion(num3) << endl;

    cin.get();
    cin.ignore();
    return 0;
}
