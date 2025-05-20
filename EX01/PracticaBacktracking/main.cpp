// Programa: Ruta más rápida en DAG por Backtracking
#include <iostream>
#include <vector>
#include <climits>   // Para INT_MAX

using namespace std;

// Número total de nodos en la red (0 a NODOS-1)
static const int NODOS = 6;

// Matriz de tiempos: TIEMPOS[u][v] = tiempo de ir de u a v, 0 si no hay conexión
auto TIEMPOS = vector<vector<int>>{
    {0, 3, 5, 0, 0, 0},  // desde nodo 0
    {0, 0, 3, 2, 1, 0},  // desde nodo 1
    {0, 0, 0, 2, 3, 0},  // desde nodo 2
    {0, 0, 0, 0, 1, 6},  // desde nodo 3
    {0, 0, 0, 0, 0, 2},  // desde nodo 4
    {0, 0, 0, 0, 0, 0}   // desde nodo 5
};

// Mejor tiempo encontrado (distancia mínima)
int mejorTiempo;

// Ruta que produce mejorTiempo
vector<int> mejorRuta;

/**
 * busquedaBacktracking: Explora recursivamente todas las rutas desde 'actual'
 * hasta 'destino', acumulando tiempo y guardando la mejor solución.
 *
 * @param actual       Nodo actual en la ruta.
 * @param destino      Nodo destino buscado.
 * @param tiempoAcum   Tiempo acumulado desde el origen hasta 'actual'.
 * @param rutaParcial  Vector con la ruta actual.
 */
void busquedaBacktracking(int actual, int destino, int tiempoAcum, vector<int>& rutaParcial) {
    // Poda: si ya superamos el mejor tiempo, abortar búsqueda
    if (tiempoAcum >= mejorTiempo) return;

    // Si llegamos al destino, actualizar mejor solución
    if (actual == destino) {
        mejorTiempo = tiempoAcum;
        mejorRuta = rutaParcial;
        return;
    }

    // Explorar aristas desde 'actual' hacia nodos mayores
    for (int siguiente = actual + 1; siguiente < NODOS; ++siguiente) {
        int tiempoPaso = TIEMPOS[actual][siguiente];
        if (tiempoPaso > 0) {
            rutaParcial.push_back(siguiente);
            busquedaBacktracking(siguiente, destino, tiempoAcum + tiempoPaso, rutaParcial);
            rutaParcial.pop_back();  // retroceder para seguir explorando
        }
    }
}

/**
 * resolverPara: Inicializa variables y lanza el backtracking para un destino dado.
 * Imprime la distancia mínima y la ruta encontrada.
 *
 * @param destino  Nodo destino (0..NODOS-1).
 */
void resolverPara(int destino) {
    mejorTiempo = INT_MAX;
    mejorRuta.clear();

    vector<int> rutaInicial = {0};  // empezamos en el origen 0
    busquedaBacktracking(0, destino, 0, rutaInicial);

    if (mejorTiempo == INT_MAX) {
        cout << "ruta de 0 a " << destino << ": inexistente\n";
    } else {
        cout << "Distancia mínima de 0 a " << destino << ": " << mejorTiempo << "\n";
        cout << "ruta mínima de 0 a " << destino << ": ";
        for (int nodo : mejorRuta) cout << nodo << " ";
        cout << "\n";
    }
}

int main() {
    cout << "=== Rutas desde 0 ===\n";
    resolverPara(5);  // ejemplo destino = 5
    cout << "\n";
    resolverPara(3);  // ejemplo destino = 3
    return 0;
}
