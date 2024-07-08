#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>

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

    int obtenerVerticeLlegada(int v, int apos) {
        Vertice* ver = vertices->at(v);
        return (ver->ady->at(apos))->v;
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
    vector<int>* dijkstra(int inicio, int fin) {
        int n = vertices->size();
        vector<int> dist(n, numeric_limits<int>::max());
        vector<int> previo(n, -1);
        vector<bool> visitado(n, false);

        dist[inicio] = 0;

        for (int i = 0; i < n - 1; ++i) {
            int u = -1;

            // Encontrar el vértice no visitado con la menor distancia
            for (int j = 0; j < n; ++j) {
                if (!visitado[j] && (u == -1 || dist[j] < dist[u])) {
                    u = j;
                }
            }

            if (dist[u] == numeric_limits<int>::max()) {
                break;
            }

            visitado[u] = true;

            for (auto& arco : *(vertices->at(u)->ady)) {
                int v = arco->v;
                int peso = arco->peso;

                if (dist[u] + peso < dist[v]) {
                    dist[v] = dist[u] + peso;
                    previo[v] = u;
                }
            }
        }

        if (dist[fin] == numeric_limits<int>::max()) {
            cout << "No hay camino desde el inicio hasta el fin" << endl;
            return nullptr;
        }

        vector<int>* camino = new vector<int>;
        for (int at = fin; at != -1; at = previo[at])
            camino->push_back(at);
        reverse(camino->begin(), camino->end());

        return camino;
    }
};