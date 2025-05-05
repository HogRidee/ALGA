

#include <iostream>

using namespace std;

// Función para imprimir el tablero a partir del vector solucion reinas
void imprimir_tablero(int* reinas, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (reinas[i] == j) {
                cout << "* ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void imprimir_posiciones(int* T, int N) {
    for (int i = 0; i < N; i++)
        cout << T[i] << " ";
    cout << endl;
}



// Función para verificar si la posición de la reina es valida
bool torres_ok(int* T, int fila, int columna) {
    return false;
}

bool reinas_ok(int* T, int fila, int col) {

    return false;
}

// Función recursiva para resolver el problema de las N reinas
bool ntorres(int* T, int N, int fila) {
    return false;
}

bool nreinas(int* T, int N, int fila) {
    return false;
}


int main() {
    int N=4; // Tamaño del tablero y número de fichas a colocar

    int* T = new int[N]; 
    for(int i = 0; i < N; i++) {
        T[i] = -1; // Inicializa todas las posiciones a -1
    }
    
    if (!ntorres(T, N, 0)) {
        cout << "No existe solución" << endl;
    } else {
        imprimir_tablero(T, N);
    }
    
    delete[] T; 
    return 0;
}
