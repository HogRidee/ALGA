/* 
 * File:   main.cpp
 * Author: iarao
 *
 * Created on 5 de mayo de 2025, 12:31
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Paquete{
    int id;
    int ganancia;
    int peso;
};

bool compararPorPeso(const Paquete &a, const Paquete &b){
    return a.peso < b.peso; //primer elemento debe ir antes? (true)
}

void ordenarPaquetes(vector<Paquete> &paquetes){
    sort(paquetes.begin(), paquetes.end(), compararPorPeso);
}

int seleccionarPaquetes(vector<Paquete> &paquetes, vector<Paquete> &solucion, 
        int pesoMax){
    ordenarPaquetes(paquetes);
    if(paquetes.empty()) return 0;
    solucion.push_back(paquetes[0]);
    int ganancia = paquetes[0].ganancia;
    int peso = paquetes[0].peso;
    for(int i = 1; i < paquetes.size(); i++){
        if(peso + paquetes[i].peso <= pesoMax){
            solucion.push_back(paquetes[i]);
            ganancia += paquetes[i].ganancia;
            peso += paquetes[i].peso;
        }
    }
    return ganancia;
}

int main(int argc, char** argv) {

    vector<Paquete> paquetes = {
        {1,10,2},
        {2,15,3},
        {3,10,5},
        {4,24,12},
        {5,8,2}
    };
    
    vector<Paquete> paquetes2 = {
        {1,10,2},
        {2,15,3},
        {3,10,5},
        {4,14,12},
        {5,8,2},
        {6,5,5}
    };
    
    int pesoMax = 20;
    vector<Paquete> solucion;
    int maxGanancia = seleccionarPaquetes(paquetes2, solucion, pesoMax);
    int pesoSolucion = 0;
    
    for (auto paq : solucion){
        pesoSolucion += paq.peso;
    }
    
    cout << "Peso sobrante en el contenedor: " << pesoMax - pesoSolucion << " Tn" << endl;
    cout << "Ganancia de la exportación: " << maxGanancia << " en miles de dólares" << endl;
    
    return 0;
}

