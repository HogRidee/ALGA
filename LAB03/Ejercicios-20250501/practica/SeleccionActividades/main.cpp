// Seleccion de Actividades - Algoritmo Backtracking y Goloso
// Autor original: Igor Siveroni
// Reescrito con comentarios y estructura clara

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

// Estructura para representar una actividad con ID, inicio y fin
typedef struct {
    int id;
    int inicio;
    int fin;
} Actividad;

// Ordena las actividades por tiempo de finalización (creciente)
bool compararPorFin(const Actividad& a, const Actividad& b) {
    return a.fin < b.fin;
}

// Ordena las actividades si no están ya ordenadas
void ordenarActividades(vector<Actividad>& actividades) {
    if (!is_sorted(actividades.begin(), actividades.end(), compararPorFin)) {
        sort(actividades.begin(), actividades.end(), compararPorFin);
    }
}

// Verifica si una actividad puede ser seleccionada dado un arreglo de tiempo ocupado
bool puedoSeleccionar(const Actividad& act, const vector<bool>& tiempoOcupado) {
    for (int i = act.inicio; i < act.fin; ++i) {
        if (tiempoOcupado[i]) return false;
    }
    return true;
}

// Marca el tiempo de una actividad como ocupado
void seleccionarActividad(const Actividad& act, vector<bool>& tiempoOcupado) {
    for (int i = act.inicio; i < act.fin; ++i) {
        tiempoOcupado[i] = true;
    }
}

// Desmarca el tiempo de una actividad (para backtracking)
void deseleccionarActividad(const Actividad& act, vector<bool>& tiempoOcupado) {
    for (int i = act.inicio; i < act.fin; ++i) {
        tiempoOcupado[i] = false;
    }
}

// Algoritmo Backtracking para seleccionar el máximo número de actividades compatibles
void backtrackingSeleccion(vector<Actividad>& actividades, vector<Actividad>& seleccionActual, vector<bool>& tiempoOcupado, int n, int& maxActividades, vector<vector<Actividad>>& solucionesMaximas) {
    if (n < 0) {
        int totalSeleccionadas = seleccionActual.size();
        if (totalSeleccionadas == maxActividades) {
            solucionesMaximas.push_back(seleccionActual);
        } else if (totalSeleccionadas > maxActividades) {
            maxActividades = totalSeleccionadas;
            solucionesMaximas.clear();
            solucionesMaximas.push_back(seleccionActual);
        }
        return;
    }

    // Intentar seleccionar la actividad n-ésima
    if (puedoSeleccionar(actividades[n], tiempoOcupado)) {
        seleccionarActividad(actividades[n], tiempoOcupado);
        seleccionActual.push_back(actividades[n]);
        backtrackingSeleccion(actividades, seleccionActual, tiempoOcupado, n - 1, maxActividades, solucionesMaximas);
        deseleccionarActividad(actividades[n], tiempoOcupado);
        seleccionActual.pop_back();
    }

    // O no seleccionarla
    backtrackingSeleccion(actividades, seleccionActual, tiempoOcupado, n - 1, maxActividades, solucionesMaximas);
}

// Ejecuta el algoritmo Backtracking
int seleccionarActividadesBacktracking(vector<Actividad>& actividades, vector<vector<Actividad>>& solucionesMaximas) {
    solucionesMaximas.clear();

    int maxTiempo = 0;
    for (const auto& act : actividades) {
        if (act.fin > maxTiempo) maxTiempo = act.fin;
    }

    vector<bool> tiempoOcupado(maxTiempo, false);
    vector<Actividad> seleccionActual;
    int maxActividades = 0;

    backtrackingSeleccion(actividades, seleccionActual, tiempoOcupado, actividades.size() - 1, maxActividades, solucionesMaximas);

    return maxActividades;
}

// Algoritmo Goloso para seleccionar actividades
int seleccionarActividadesGreedy(vector<Actividad>& actividades, vector<Actividad>& seleccionadas) {
    ordenarActividades(actividades);
    seleccionadas.clear();

    if (actividades.empty()) return 0;

    // Siempre se selecciona la primera actividad ordenada por fin
    seleccionadas.push_back(actividades[0]);
    int finUltima = actividades[0].fin;

    // Seleccionar la siguiente actividad compatible más próxima
    for (size_t i = 1; i < actividades.size(); ++i) {
        if (actividades[i].inicio >= finUltima) {
            seleccionadas.push_back(actividades[i]);
            finUltima = actividades[i].fin;
        }
    }

    return seleccionadas.size();
}

int main() {
    vector<Actividad> actividades = {
        {1,1,4}, {2,3,5}, {3,0,6}, {4,5,7}, {5,3,8},
        {6,5,9}, {7,6,10}, {8,8,11}, {9,8,12}, {10,2,13}, {11,12,14}
    };

    // Mezclar el orden de entrada
    shuffle(actividades.begin(), actividades.end(), default_random_engine{});

    cout << "Actividades desordenadas (ID): ";
    for (const auto& act : actividades) cout << act.id << " ";
    cout << endl;

    // Backtracking
    vector<vector<Actividad>> solucionesBT;
    int maxBT = seleccionarActividadesBacktracking(actividades, solucionesBT);
    cout << "\nSolución por Backtracking:" << endl;
    cout << "Máximo número de actividades: " << maxBT << endl;
    for (const auto& solucion : solucionesBT) {
        cout << "{ ";
        for (const auto& act : solucion) cout << act.id << " ";
        cout << "}" << endl;
    }

    // Greedy
    cout << "\n-----------------------\n";
    vector<Actividad> seleccionGreedy;
    int maxGreedy = seleccionarActividadesGreedy(actividades, seleccionGreedy);

    cout << "Solución Golosa:" << endl;
    cout << "Máximo número de actividades: " << maxGreedy << endl;
    for (const auto& act : seleccionGreedy) {
        cout << "Actividad: " << act.id << " [" << act.inicio << "," << act.fin << "]" << endl;
    }

    return 0;
}
