#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;

const int n = 4;  // Número total de ciudades
const int k = 2;  // Número de centros (almacenes/ATMs) a seleccionar

// Matriz de distancias entre ciudades
int W[n][n] = {
    {0, 4, 8, 5},
    {4, 0, 10, 7},
    {8, 10, 0, 9},
    {5, 7, 9, 0}
};

// ------------------------
// Algoritmo Greedy (Goloso)
// ------------------------
void algoritmo_goloso() {
    bool seleccionadas[n] = {false};     // Marcar las ciudades seleccionadas como centros
    int mejor_distancia = INT_MAX;       // Mantiene la menor distancia máxima encontrada

    for (int i = 0; i < k; i++) {
        int mejor_ciudad = -1;
        int menor_distancia_max = INT_MAX;

        // Evaluar cada ciudad que no haya sido seleccionada aún
        for (int ciudad = 0; ciudad < n; ciudad++) {
            if (!seleccionadas[ciudad]) {
                int max_distancia = 0;

                // Comparar esta ciudad con las otras no seleccionadas
                for (int otra = 0; otra < n; otra++) {
                    if (!seleccionadas[otra] && ciudad != otra) {
                        max_distancia = max(max_distancia, W[ciudad][otra]);
                    }
                }

                // Si esta ciudad tiene una mejor distancia máxima, guardarla
                if (max_distancia < menor_distancia_max) {
                    menor_distancia_max = max_distancia;
                    mejor_ciudad = ciudad;
                }
            }
        }

        // Marcar la mejor ciudad encontrada como seleccionada
        if (mejor_ciudad != -1) {
            seleccionadas[mejor_ciudad] = true;
            mejor_distancia = min(mejor_distancia, menor_distancia_max);
            cout << "Ciudad seleccionada: " << mejor_ciudad
                 << " con distancia máxima: " << menor_distancia_max << endl;
        }
    }

    // Mostrar resultado final
    cout << "Mejor distancia máxima obtenida: " << mejor_distancia << endl;
}

// ---------------------------------------
// Evaluar una combinación de k centros
// ---------------------------------------
int evaluar_centros(int centros[]) {
    bool es_centro[n] = {false};  // Marcar ciudades que son centros

    // Marcar los centros seleccionados
    for (int i = 0; i < k; i++)
        es_centro[centros[i]] = true;

    int peor_distancia = 0;

    // Para cada ciudad que NO es centro
    for (int ciudad = 0; ciudad < n; ciudad++) {
        if (!es_centro[ciudad]) {
            int min_a_centro = INT_MAX;

            // Buscar el centro más cercano a esta ciudad
            for (int i = 0; i < k; i++) {
                min_a_centro = min(min_a_centro, W[ciudad][centros[i]]);
            }

            // Guardar la peor distancia (más lejana) de entre todas las ciudades
            peor_distancia = max(peor_distancia, min_a_centro);
        }
    }

    return peor_distancia;  // Esta es la métrica que estamos minimizando
}

// -----------------------------
// Función principal (main)
// -----------------------------
int main() {
    cout << "--- Solución Golosa ---" << endl;
    algoritmo_goloso();

    cout << "\n--- Evaluando todas las combinaciones posibles ---" << endl;

    // Generar todas las combinaciones posibles de k centros entre n ciudades
    vector<bool> v(n);
    fill(v.end() - k, v.end(), true);  // Últimos k elementos en true (centros)
    int centros[k];

    // Iterar sobre todas las combinaciones de ciudades
    do {
        int idx = 0;

        // Almacenar la combinación actual en el arreglo centros[]
        for (int i = 0; i < n; i++)
            if (v[i]) centros[idx++] = i;

        // Mostrar la combinación actual
        cout << "Centros: ";
        for (int i = 0; i < k; i++) cout << centros[i] << " ";

        // Evaluar la combinación
        int dist = evaluar_centros(centros);
        cout << "-> Distancia máxima: " << dist << endl;

    } while (next_permutation(v.begin(), v.end()));  // Genera siguiente combinación

    return 0;
}
