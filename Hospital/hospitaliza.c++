#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;


struct Nodo {
    int valor; 
    vector<Nodo*> hijos; 
};


int valorTotal(Nodo* nodo) {
    int total = nodo->valor;
    for (Nodo* hijo : nodo->hijos) {
        total += valorTotal(hijo);
    }
    return total;
}



void agregarPaciente(Nodo* raiz, int anioNacimiento, int copago) {
    Nodo* nodo = new Nodo;
    nodo->valor = copago;
    
    for (Nodo* hijo : raiz->hijos) {
        if (hijo->valor == anioNacimiento) {
            hijo->hijos.push_back(nodo);
            return;
        }
    }
    
    Nodo* anioNode = new Nodo;
    anioNode->valor = anioNacimiento;
    anioNode->hijos.push_back(nodo);
    raiz->hijos.push_back(anioNode);
}



void promedioPorAnio(Nodo* raiz) {
    unordered_map<int, vector<int>> copagosPorAnio; 
    for (Nodo* anioNode : raiz->hijos) {
        int anio = anioNode->valor;
        for (Nodo* paciente : anioNode->hijos) {
            int copago = valorTotal(paciente);
            copagosPorAnio[anio].push_back(copago);
        }
    }


    for (auto& p : copagosPorAnio) {
        int anio = p.first;
        vector<int>& copagos = p.second;
        double promedio = 0;
        for (int copago : copagos) {
            promedio += (double) copago / copagos.size();
        }
        cout << "Promedio de copago para el año " << anio << ": " << promedio << endl;
    }
}





int main() {
   
    Nodo* raiz = new Nodo;
    raiz->valor = -1; 
    agregarPaciente(raiz, 1990, 50);
    agregarPaciente(raiz, 1990, 70);
    agregarPaciente(raiz, 1995, 80);
    agregarPaciente(raiz, 1995, 90);
    agregarPaciente(raiz, 2000, 100);
    
  promedioPorAnio(raiz);
    return 0;
}