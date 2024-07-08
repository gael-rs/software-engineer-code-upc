#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> // Para rand()
#include <ctime>   // Para time()

using namespace std;

template<class T>
class Grafo {
private:
    class Arco {
    public:
        int v; // Índice del vértice de llegada
        int peso; // Peso del arco (tiempo de viaje)
        Arco(int vLlegada, int pesoArco) {
            v = vLlegada;
            peso = pesoArco;
        }
    };

    class Vertice {
    public:
        T info;
        vector<Arco*>* ady; // Lista de adyacencia
        Vertice(T infoVertice) {
            info = infoVertice;
            ady = new vector<Arco*>();
        }
        ~Vertice() {
            for (auto arco : *ady) {
                delete arco;
            }
            delete ady;
        }
    };

    vector<Vertice*>* vertices;

public:
    Grafo() {
        vertices = new vector<Vertice*>();
        srand(time(0)); // Inicializar semilla para generación aleatoria
    }

    ~Grafo() {
        for (auto vertice : *vertices) {
            delete vertice;
        }
        delete vertices;
    }

    int adicionarVertice(string info) {
        Vertice* vert = new Vertice(info);
        vertices->push_back(vert);
        return vertices->size() - 1;
    }

    int cantidadVertices() {
        return vertices->size();
    }

    T obtenerVertice(int v) {
        return (vertices->at(v))->info;
    }

    void modificarVertice(int v, T info) {
        (vertices->at(v))->info = info;
    }

    void eliminarVertice(int v) {
        Vertice* ver = vertices->at(v);
        for (auto arco : *(ver->ady)) {
            delete arco;
        }
        delete ver->ady;
        delete ver;
        vertices->erase(vertices->begin() + v);
    }

    int adicionarArco(int v, int vLlegada, int peso) {
        Vertice* ver = vertices->at(v);
        Arco* arc = new Arco(vLlegada, peso);
        ver->ady->push_back(arc);
        return ver->ady->size() - 1;
    }

    int cantidadArcos(int v) {
        return (vertices->at(v))->ady->size();
    }

    int obtenerArco(int v, int apos) {
        Vertice* ver = vertices->at(v);
        return (ver->ady->at(apos))->peso;
    }

    void modificarArco(int v, int apos, T peso) {
        Vertice* ver = vertices->at(v);
        (ver->ady->at(apos))->peso = peso;
    }

    void eliminarArco(int v, int apos) {
        Vertice* ver = vertices->at(v);
        Arco* arc = ver->ady->at(apos);
        ver->ady->erase(ver->ady->begin() + apos);
        delete arc;
    }

    void imprimirGrafo() {
        for (int i = 0; i < vertices->size(); ++i) {
            cout << "Vertice " << i << " (" << vertices->at(i)->info << "): ";
            for (auto arco : *(vertices->at(i)->ady)) {
                cout << " -> " << arco->v << " (" << arco->peso << ")";
            }
            cout << endl;
        }
    }

    void registro_aleatorio() {
        int n_vertices;
        cout << "Ingrese el numero de vertices: ";
        cin >> n_vertices;
        cout << endl;

        // Generar vértices aleatorios
        for (int i = 0; i < n_vertices; ++i) {
            int valor_vertice = rand() % 1000 + 1; // Valor aleatorio entre 1 y 1000
            adicionarVertice(to_string(valor_vertice));
        }

        int n_arcos_total = 0;
        cout << "Ingrese el numero total de arcos: ";
        cin >> n_arcos_total;
        cout << endl;

        // Generar arcos aleatorios
        for (int i = 0; i < n_vertices; ++i) {
            int n_arcos = rand() % 4; // Entre 0 y 3 arcos por vértice
            for (int j = 0; j < n_arcos; ++j) {
                int vLlegada = rand() % n_vertices; // Vértice de llegada aleatorio
                int peso_arco = rand() % 91 + 10; // Peso del arco entre 10 y 100
                adicionarArco(i, vLlegada, peso_arco);
                n_arcos_total--;
                if (n_arcos_total <= 0)
                    break;
            }
            if (n_arcos_total <= 0)
                break;
        }

        cout << "Grafo generado aleatoriamente:" << endl;
        imprimirGrafo();
    }

    void vertices_cantidad() {
        int max_arcos = -1;
        int vertice_max = -1;

        // Encontrar el vértice con más arcos
        for (int i = 0; i < vertices->size(); ++i) {
            int num_arcos = cantidadArcos(i);
            if (num_arcos > max_arcos) {
                max_arcos = num_arcos;
                vertice_max = i;
            }
        }

        if (vertice_max != -1) {
            cout << "El vertice con mas arcos es el vertice " << vertice_max << " con " << max_arcos << " arcos:" << endl;
            cout << "Arcos:";
            for (auto arco : *(vertices->at(vertice_max)->ady)) {
                cout << " -> " << arco->v << " (" << arco->peso << ")";
            }
            cout << endl;
        }
        else {
            cout << "No se encontraron vertices en el grafo." << endl;
        }
    }
};
