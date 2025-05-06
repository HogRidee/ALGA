/* 
 * File:   main.cpp
 * Author: iarao
 *
 * Created on 6 de mayo de 2025, 14:56
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Pedido{
    int id;
    int dimension;
    int cantidad;
    int ganancia;
};

bool ordenarPorBeneficio(const Pedido &a, const Pedido &b){
    //TRUE SI A DEBE IR ADELANTE
    double beneficioA = a.ganancia/(a.dimension*a.cantidad);
    double beneficioB = b.ganancia/(b.dimension*b.cantidad);
    return beneficioA > beneficioB;
}

int calcularPedidos(vector<Pedido> pedidos, int *desperdicio){
    vector<Pedido> pedidosOrdenados;
    sort(pedidosOrdenados.begin(), pedidosOrdenados.end(), ordenarPorBeneficio);
}

int main(int argc, char** argv) {

    vector<Pedido> pedidos{
        {1, 10, 5, 10},
        {2, 20, 10, 20},
        {3, 1, 18, 15},
        {4, 3, 1, 5},
        {5, 1, 1, 2}
    };
    
    int desperdicio[20];
    int ganancia = calcularPedidos(pedidos, desperdicio);
    
    cout << "Ganancia: $" << ganancia << " k" << endl;
    
    return 0;
}

