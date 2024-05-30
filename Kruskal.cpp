#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

class Arista {
public:
    int costo;
    char nodos[2];

    Arista(char a, char b, int c) {
        costo = c;
        nodos[0] = a;
        nodos[1] = b;
    }

    bool operator<(const Arista& other) const {
        return costo < other.costo;
    }
};

class Grafo {
public:
    vector<Arista> aristas;
    vector<char> nodos;

    Grafo() {}

    void agregarArista(char a, char b, int costo) {
        Arista tmp(a, b, costo);
        aristas.push_back(tmp);
    }

    void agregarNodo(char nodo) {
        nodos.push_back(nodo);
    }
};

char encontrarRepresentante(map<char, char>& padre, char i) {
    if (padre[i] == i)
        return i;
    return encontrarRepresentante(padre, padre[i]);
}

void unirConjuntos(map<char, char>& padre, map<char, int>& rango, char x, char y) {
    char raizX = encontrarRepresentante(padre, x);
    char raizY = encontrarRepresentante(padre, y);

    if (rango[raizX] < rango[raizY])
        padre[raizX] = raizY;
    else if (rango[raizX] > rango[raizY])
        padre[raizY] = raizX;
    else {
        padre[raizY] = raizX;
        rango[raizX]++;
    }
}

set<Arista> Kruskal(Grafo& G) {
    set<Arista> conjuntoAristas(G.aristas.begin(), G.aristas.end());
    set<Arista> solucion;

    map<char, char> padre;
    map<char, int> rango;

    for (char nodo : G.nodos) {
        padre[nodo] = nodo;
        rango[nodo] = 0;
    }

    while (!conjuntoAristas.empty() && solucion.size() != G.nodos.size() - 1) {
        Arista aristaActual = *conjuntoAristas.begin();
        conjuntoAristas.erase(conjuntoAristas.begin());

        char u = aristaActual.nodos[0];
        char v = aristaActual.nodos[1];

        char conjuntoU = encontrarRepresentante(padre, u);
        char conjuntoV = encontrarRepresentante(padre, v);

        if (conjuntoU != conjuntoV) {
            solucion.insert(aristaActual);
            unirConjuntos(padre, rango, conjuntoU, conjuntoV);
        }
    }

    if (solucion.size() == G.nodos.size() - 1)
        return solucion;
    else
        return {};
}

int main() {
    Grafo G;
    G.agregarNodo('A');
    G.agregarNodo('B');
    G.agregarNodo('C');
    G.agregarNodo('D');
    G.agregarNodo('E');

    G.agregarArista('A', 'B', 1);
    G.agregarArista('A', 'C', 3);
    G.agregarArista('B', 'C', 1);
    G.agregarArista('B', 'D', 4);
    G.agregarArista('C', 'D', 2);
    G.agregarArista('D', 'E', 5);
    G.agregarArista('C', 'E', 3);

    set<Arista> mst = Kruskal(G);
    if (!mst.empty()) {
        cout << "Aristas en el T:" << endl;
        for (const Arista& a : mst) {
            cout << a.nodos[0] << " - " << a.nodos[1] << " : " << a.costo << endl;
        }
    }
    else {
        cout << "No hay solución" << endl;
    }

    return 0;
}
