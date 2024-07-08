#include <iostream>

using namespace::std;

// Funcion usando recursividad para verificar si un numero es capicua
bool esCapicua(string numero, int inicio, int fin) {
    if (inicio >= fin) {
        return true;
    }
    if (numero[inicio] != numero[fin]) {
        return false;
    }
    return esCapicua(numero, inicio + 1, fin - 1);
}

// Función usando recursividad para calcular la sumatoria de los digitos de un numero
int sumatoriaDigitos(string numero, int index) {
    if (index < 0) {
        return 0;
    }
    return (numero[index] - '0') + sumatoriaDigitos(numero, index - 1);
}

// Función usando recursividad para calcular la multiplicacion de los digitos de un numero
int multiplicacionDigitos(string numero, int index) {
    if (index < 0) {
        return 1;
    }
    return (numero[index] - '0') * multiplicacionDigitos(numero, index - 1);
}

int main() {
    //Hacemos que numero sea de tipo string para que su manipulacion sea mas sencilla
    string numero;
    bool valido = false;
    do {
        cout << "======================================================" << endl;
        cout << "Ingrese un numero mayor a tres digitos: ";
        cin >> numero;

        // Hacemos la validacion para que el numero ingresado sea mayor a 3 digitos
        if (numero.length() >= 4) {
            valido = true;
        }else{
            cout << "======================================================" << endl;
            cout << "El numero ingresado no es mayor a tres digitos. Intentalo denuevo..." << endl;
        }
	} while (!valido);

    if (esCapicua(numero, 0, numero.length() - 1)) {
        cout << "======================================================" << endl;
        cout << "El numero es capicua." << endl;
        cout << "La sumatoria de sus digitos es: " << sumatoriaDigitos(numero, numero.length() - 1) << endl;
        cout << "======================================================" << endl;
    }
    else {
        cout << "======================================================" << endl;
        cout << "El numero no es capicua." << endl;
        cout << "La multiplicacion de sus digitos es: " << multiplicacionDigitos(numero, numero.length() - 1) << endl;
        cout << "======================================================" << endl;
    }
    cin.get();
    cin.ignore();
    return 0;
}
