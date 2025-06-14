// Archivo: main.cpp
// Autor: cueva.r (refactorizado con comentarios y nombres descriptivos)

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <climits>

#define ITERACIONES 1000000   // Número de veces que ejecutamos GRASP
#define ALFA 0.30             // Equilibrio voraz vs. aleatorio

using namespace std;

// ----------------------------
// Estructuras de datos
// ----------------------------

// Representa tanto una tabla (demanda IOPs) como un disco (IOPs disponibles)
struct Item {
    int id;            // Identificador (1,2,3…)
    int rendimiento;   // Para tablas = demanda; para discos = IOPs libres
};

// Guarda una asignación tabla→disco
struct Asignacion {
    int discoId;
    int tablaId;
};

// Ordena de mayor a menor rendimiento
bool compareByPerformance(const Item &a, const Item &b) {
    return a.rendimiento > b.rendimiento;
}

// Cuenta cuántos elementos de 'items' tienen rendimiento ≥ umbral
int countCandidates(const vector<Item> &items, int umbral) {
    int count = 0;
    for (auto &it : items)
        if (it.rendimiento >= umbral)
            ++count;
    return count;
}

// ----------------------------
// Función principal de GRASP
// ----------------------------
void assignTablesToDisks(const vector<Item> &tabla, 
                         const vector<Item> &disco) {
    vector<Asignacion> bestSolution;  // Mejor conjunto de asignaciones global
    int bestResidual = INT_MIN;       // Mejor IOPs residual mínimo

    // Inicializamos la semilla UNA vez para toda la ejecución
    srand(17);

    // Bucle de iteraciones GRASP
    for (int iter = 0; iter < ITERACIONES; ++iter) {
        // Copias locales de tablas y discos para cada iteración
        vector<Item> tables = tabla;
        vector<Item> disks  = disco;
        vector<Asignacion> currentAssign;  // Asignaciones de esta iteración

        // Fase de construcción
        // Mientras queden tablas por asignar:
        sort(tables.begin(), tables.end(), compareByPerformance);

        while (!tables.empty()) {
            // 1) Selección de tabla desde su RCL
            int mejorTab = tables.front().rendimiento;
            int peorTab  = tables.back().rendimiento;
            int umbralT  = round(mejorTab - ALFA * (mejorTab - peorTab));
            int candidatosT = countCandidates(tables, umbralT);
            int idxTab = rand() % candidatosT;
            Item chosenTable = tables[idxTab];

            // 2) Selección de disco desde su RCL
            sort(disks.begin(), disks.end(), compareByPerformance);
            int mejorDis = disks.front().rendimiento;
            int peorDis  = disks.back().rendimiento;
            int umbralD  = round(mejorDis - ALFA * (mejorDis - peorDis));
            int candidatosD = countCandidates(disks, umbralD);
            int idxDis = rand() % candidatosD;
            Item &chosenDisk = disks[idxDis];

            // 3) Si el disco tiene IOPs suficientes, asignamos la tabla
            if (chosenDisk.rendimiento >= chosenTable.rendimiento) {
                chosenDisk.rendimiento -= chosenTable.rendimiento;
                currentAssign.push_back({ chosenDisk.id, chosenTable.id });
            }

            // 4) Eliminamos la tabla (asignada o no) para pasar a la siguiente
            tables.erase(tables.begin() + idxTab);
        }

        // Fase de evaluación: el peor disco tras asignar todas las tablas
        sort(disks.begin(), disks.end(), compareByPerformance);
        int residualMin = disks.back().rendimiento;

        // Guardamos la mejor solución si mejora el residual mínimo
        if (residualMin > bestResidual) {
            bestResidual   = residualMin;
            bestSolution   = currentAssign;
        }
    }

    // ----------------------------
    // Imprimimos el resultado
    // ----------------------------
    cout << "Mejor velocidad residual mínima: " << bestResidual << "\n";
    cout << "Asignaciones (Disco <- Tabla):\n";
    for (auto &asig : bestSolution) {
        cout << "  Disco " << asig.discoId
             << "  ←  Tabla " << asig.tablaId << "\n";
    }
}

int main() {
    // Definición de tablas (ID, demanda IOPs)
    vector<Item> tabla = {
        {1,150}, 
        {2,100}, 
        {3,80},
        {4,50},  
        {5,120}, 
        {6,10}
    };
    // Definición de discos (ID, IOPs iniciales)
    vector<Item> disco = {
        {1,250}, 
        {2,200}, 
        {3,200}
    };

    assignTablesToDisks(tabla, disco);
    
    return 0;
}
