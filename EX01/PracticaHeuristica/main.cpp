/* 
 * File:   main.cpp
 * Author: alulab14
 *
 * Created on 10 de mayo de 2025, 09:05 AM
 */

#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Pedido{
    int id;
    char accion; // 'L': lavar 'S': secar 'C': Centrifugar
    int peso;
};

struct Lavadora{
    int id;
    double tiempoAcumulado;
    vector<int> pedidos;
};

bool comparaLavadoras(const Lavadora &a, const Lavadora &b){
    return a.tiempoAcumulado < b.tiempoAcumulado;
}

bool comparaPorId(const Lavadora &a, const Lavadora &b){
    return a.id < b.id;
}

/*
 * Recorre cada pedido y asigna a la lavadora con menor tiempoAcumulado
 */

int encontrarLavadora(vector<Lavadora> lavadoras, char tipo){
    if(tipo == 'L'){
        return 0;
    }
    for(int i = 0; i < 3; i++){
        if(tipo == 'S' and (lavadoras[i].id == 2 or lavadoras[i].id == 3)){
            return i;
        }
        if(tipo == 'C' and (lavadoras[i].id == 3)){
            return i;
        } 
    }
}

void algoritmo(const vector<Pedido> &pedidos, vector<Lavadora> &lavadoras){
    for(int i = 0; i < pedidos.size(); i++){
        int lavadora = -1;
        double tiempo = 0;
        if (pedidos[i].accion == 'L'){
            tiempo = (pedidos[i].peso/(double)5) * 20; 
        }
        if (pedidos[i].accion == 'S'){
            tiempo = (pedidos[i].peso/(double)5) * 10; 
        }
        if (pedidos[i].accion == 'C'){
            tiempo = (pedidos[i].peso/(double)5) * 5; 
        }
        sort(lavadoras.begin(), lavadoras.end(), comparaLavadoras);
        lavadora = encontrarLavadora(lavadoras, pedidos[i].accion);
        lavadoras[lavadora].tiempoAcumulado += tiempo;
        lavadoras[lavadora].pedidos.push_back(pedidos[i].id);
    }
}

int main(int argc, char** argv) {

    vector<Pedido> pedidos{
        {1,  'L', 10},
        {2,  'L', 15},
        {3,  'S', 8},
        {4,  'C', 5},
        {5,  'L', 12},
        {6,  'S', 9},
        {7,  'C', 6},
        {8,  'L', 11},
        {9,  'S', 7},
        {10, 'C', 10},
        {11, 'L', 13}, 
        {12, 'S', 15},
        {13, 'L', 14},
        {14, 'C', 8},
        {15, 'S', 6},
        {16, 'C', 12},
        {17, 'L', 6},
        {18, 'S', 5},
        {19, 'C', 7},
        {20, 'L', 9}
    };

    vector<Lavadora> lavadoras{
        {1,0},
        {2,0},
        {3,0}
    };
    
    algoritmo(pedidos, lavadoras);
    sort(lavadoras.begin(), lavadoras.end(), comparaPorId);

    cout << "Asignacion de ordenes por lavadora" << endl;
    cout << left << setw(10) << "Lavadora" << setw(10) << "Tiempo total (min) " 
            << setw(10) << "Ordenes asignadas " << endl;
    
    for(auto l: lavadoras){
        cout << setw(13) << l.id;
        cout << setw(20) << l.tiempoAcumulado;
        for(auto p: l.pedidos){
            cout << p << ",";
        }
        cout << endl;
    }
    
    return 0;
}

