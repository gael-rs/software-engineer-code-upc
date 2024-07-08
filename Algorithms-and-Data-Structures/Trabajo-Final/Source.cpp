#include "string"
#include "Tienda.h"


using namespace std;

int main() {
    srand(time(nullptr));

    
    Tienda* objTienda = new Tienda();

    objTienda->menu();
 

    delete objTienda;

    cin.get();
    cin.ignore();
    return 0;
}