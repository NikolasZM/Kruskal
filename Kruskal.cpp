#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class arista {
public:
	int v;
	char nodos[2];

	arista(char a, char b, int va) {
		v = va;
		nodos[0] = a;
		nodos[1] = b;
	}

};


class Grafo {
public:
	vector<arista> aristas;
	vector<char> nodos;
	Grafo() {}
	void setAristas(char a, char b, int val) {
		arista tmp(a, b, val);
		aristas.push_back(tmp);
	}

	void setNodo(char val) {
		nodos.push_back(val);
	}
};

void kruskal(Grafo GG) {
	vector<arista> G;
	vector<arista> S;
	vector<int> valores;
	vector<int> indices;
	for (int i{ 0 }; i < GG.aristas.size(); i++) {
		valores.push_back(GG.aristas[i].v);
		indices.push_back(i);
	}
	
	for (int i{ 0 }; i < valores.size(); i++) {
		cout << valores[i] << " ";
	}
	cout << endl;
	
	sort(indices.begin(), indices.end(), [&](int a, int b) {
		return valores[a] < valores[b];
		});

	vector<int> valoresOrd(valores.size());

	for (int i{ 0 }; i < GG.aristas.size(); i++) {
		valoresOrd[i] = valores[indices[i]];
	}

	for (int i{ 0 }; i < valores.size(); i++) {
		cout << valoresOrd[i] << " ";
	}
}


int main() {
	int val[15] = { 4,5,7,6,8,12,3,9,7,4,5,5,11,10,6 };
	Grafo G;
	
	for (int i{ 97 }; i < 106; i++) {
		char tmp = i;
		G.setNodo(tmp);
	}
	G.setAristas('a','b',5);
	G.setAristas('b', 'c', 4);
	G.setAristas('b', 'd', 6);
	G.setAristas('a', 'd', 7);
	G.setAristas('c', 'd', 8);
	G.setAristas('d', 'e', 3);
	G.setAristas('d', 'g', 4);
	G.setAristas('c', 'f', 9);
	G.setAristas('a', 'h', 12);
	G.setAristas('f', 'g', 7);
	G.setAristas('f', 'i', 10);
	G.setAristas('g', 'i', 6);
	G.setAristas('g', 'h', 5);
	G.setAristas('i', 'h', 11);
	G.setAristas('e', 'h', 5);


	kruskal(G);
	cout << endl;


	
}