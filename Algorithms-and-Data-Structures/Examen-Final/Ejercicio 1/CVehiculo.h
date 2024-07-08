#pragma once
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

class Data {
public:

    int IDVehiculo;
    string marca;
    int modelo;
    int color;
    int asiento;

    Data();
    ~Data();
    string ToString();

    int getColor() {
        return color;
    }

    
    int getIDVehiculo() {
        return IDVehiculo;
    }
    
    string getMarca() {
        return marca;
    }

};

Data::Data() {
    this->IDVehiculo = 0;
    this->marca = " ";
    this->modelo = 0;
    this->color = 0;
    this->asiento = 0;
}

string Data::ToString() {
    stringstream ss;
    ss << "=================================" << endl;
    ss << "ID Vehiculo: \t" << this->IDVehiculo << endl;
    ss << "Marca: \t" << this->marca << endl;
    ss << "Modelo: \t" << this->modelo << endl;
    ss << "Color: \t" << this->color << endl;
    ss << "Asiento: \t" << this->asiento << endl;
    return ss.str();
}

Data::~Data() {}