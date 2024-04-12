#include <iostream>
using namespace::std;

/*
Realizar la clase calculadora que utilice templates y permita
realizar las operaciones de suma, resta, multiplicación, división y
potencia, la aplicación debe permitir escoger el tipo de datos con
el que se desea trabajar, y tener una función calcular que
controle que realice todo la operación correspondiente.
*/

template<typename T>
class Calculadora {
public:
    Calculadora() {}

    T suma(T a, T b) {
        return a + b;
    }

    T resta(T a, T b) {
        return a - b;
    }

    T multiplicacion(T a, T b) {
        return a * b;
    }

    T division(T a, T b) {
        // Validamos que el segundo termino (b) si es 0 mande un mensaje al usuario.
        if (b == 0) {
            cerr << "No se puede una division por 0" << endl;
            return 0;
        }
        return a / b;
    }
    //Simulamos una potencia con un for donde las veces que se multiplicara consecutivamentes sera el valor que le demos al int exponente
    T potencia(T n, int exponente) {
        T resultado = 1;
        for (int i = 0; i < exponente; ++i) {
            resultado *= n;
        }
        return resultado;
    }

    void calcular(char signo, T a, T b) {
        switch (signo) {
        case '+':
            cout << "Suma: " << suma(a, b) << endl;
            break;
        case '-':
            cout << "Resta: " << resta(a, b) << endl;
            break;
        case '*':
            cout << "Multiplicacion: " << multiplicacion(a, b) << endl;
            break;
        case '/':
            cout << "Division: " << division(a, b) << endl;
            break;
        case '^':
            cout << "Potencia: " << potencia(a, b) << endl;
            break;
        default:
            cout << "Coloque uno de los signos que aparece en pantalla..." << endl;
        }
    }
};

int main() {
    //Creamos dos (uno de tipo int y otro de tipo double)ya que uno nos servira para la pontencia
    Calculadora<double> calculadoraDouble;
    Calculadora<int> calculadoraInt;

    char signo;
    cout << "========= C A L C U L A D O R A =========" << endl;
    cout << "Ingrese el signo de la operación que deseas realizar (+, -, *, /, ^): ";
    cin >> signo;
    
    if (signo == '^') {
        int num1, num2;
        cout << "Ingrese el primer numero: ";
        cin >> num1;
        cout << "Ingrese el segundo numero: ";
        cin >> num2;
        calculadoraInt.calcular(signo, num1, num2);
    }
    else {
        double num1, num2;
        cout << "Ingrese el primer numero: ";
        cin >> num1;
        cout << "Ingrese el segundo numero: ";
        cin >> num2;
        calculadoraDouble.calcular(signo, num1, num2);
    }

    cin.get();
    cin.ignore();
    return 0;

}
