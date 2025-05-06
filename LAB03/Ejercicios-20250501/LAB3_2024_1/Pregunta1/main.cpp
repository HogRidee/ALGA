/* 
 * File:   main.cpp
 * Author: iarao
 *
 * Created on 6 de mayo de 2025, 14:17
 */

#include <iostream>

using namespace std;

// Matriz de distancias entre puntosa
int W[8][8] = {
    {0, 4, 5, 6, 0, 0, 0, 0}, // A 0
    {0, 0, 0, 0, 2, 0, 0, 0}, // B
    {0, 0, 0, 0, 0, 0, 0, 3}, // C
    {0, 0, 0, 0, 0, 3, 0, 0}, // D
    {0, 0, 0, 0, 0, 0, 10, 0}, // E
    {0, 0, 0, 0, 0, 0, 2, 0}, // F
    {0, 0, 0, 0, 0, 0, 0, 0}, // G 6
    {0, 0, 0, 0, 0, 0, 0, 0}  // H
};

void calcularViaje(int inicio, int fin){
    int tiempoTotal = 0;
    while(true){
        int menorTiempo = 1000;
        int indiceMenor = -1;
        for(int i = 0; i < 8; i++){
            if(W[inicio][i] < menorTiempo and W[inicio][i] != 0){
                menorTiempo = W[inicio][i];
                indiceMenor = i;
            }
        }
        tiempoTotal += menorTiempo;
        if (fin == indiceMenor){
            cout << "TIEMPO TOTAL: " << tiempoTotal << endl;
            break;
        }
        if (menorTiempo == 1000){
            cout << "NO SE ENCONTRÓ SOLUCIÓN " << endl;
            break;
        }
        inicio = indiceMenor;
    }
    
    
    
}

int main(int argc, char** argv) {

    calcularViaje(3, 6);
    
    return 0;
}

