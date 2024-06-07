#pragma once
#include <string>
#include <sstream>

using namespace std;

class Producto {
public:
    string id;
    string nombre;
    int precio;
    int categoria;
    int stock;
    int fecha_caducidad;

    Producto();
    ~Producto();
    string ToString();

    
};

Producto::Producto() {
    this->id = "";
    this->nombre = "";
    this->precio = 0;
    this->categoria = 0;
    this->stock = 0;
    this->fecha_caducidad = 0;
}

string Producto::ToString() {
    stringstream ss;
    ss << "ID: \t" << this->id << endl;
    ss << "Nombre: \t" << this->nombre << endl;
    ss << "Precio: \t" << this->precio << endl;
    ss << "Categoria: \t" << this->categoria << endl;
    ss << "Stock: \t" << this->stock << endl;
    ss << "Fecha de caducidad: \t" << this->fecha_caducidad << endl;
    return ss.str();
}

Producto::~Producto() {}
