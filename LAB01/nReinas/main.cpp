#include <iostream>
#include <cmath> // para abs()
using namespace std;

// Muestra el tablero con '*' para la reina
void imprimir_tablero(int* T, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (T[i] == j)
                cout << "* ";
            else
                cout << ". ";
        }
        cout << endl;
    }
    cout << endl;
}

// Verifica que no haya conflictos con reinas anteriores
bool reinas_ok(int* T, int fila, int col) {
    for (int i = 0; i < fila; i++) {
        // misma columna
        if (T[i] == col)
            return false;
        // misma diagonal ↘ o ↙
        if (abs(T[i] - col) == abs(i - fila))
            return false;
    }
    return true;
}

// Backtracking para colocar reinas
bool nreinas(int* T, int N, int fila) {
    if (fila == N)
        return true; // ¡solución completa!

    for (int col = 0; col < N; col++) {
        if (reinas_ok(T, fila, col)) {
            T[fila] = col;
            if (nreinas(T, N, fila + 1))
                return true;
            // Backtrack
            T[fila] = -1;
        }
    }
    return false;
}

int main() {
    int N = 4;
    int* T = new int[N];
    for (int i = 0; i < N; i++)
        T[i] = -1;

    if (!nreinas(T, N, 0))
        cout << "No existe solución" << endl;
    else
        imprimir_tablero(T, N);

    delete[] T;
    return 0;
}
