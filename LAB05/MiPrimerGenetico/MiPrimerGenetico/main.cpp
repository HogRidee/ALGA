// Archivo: mochila_ga.cpp
// Autor: Refactorizado para claridad
// Propósito: Resolver la mochila 0/1 con un Algoritmo Genético

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>    // srand, rand
#include <ctime>      // time
#include <map>        // para eliminar duplicados

using namespace std;

// —— Parámetros del GA ——
static const int N_ITERACIONES = 1000;  // Generaciones
static const int POBLACION_MAX = 10;     // Tamaño máximo de población
static const double P_SELECCION = 0.3;   // Fracción de padres
static const double P_CRUCE    = 0.5;   // Punto de cruce (50%)
static const double P_MUTACION = 0.5;   // Fracción de genes a mutar

// —— Helpers globales ——
static int* GLOBAL_ITEMS;  // apunta al vector de pesos/beneficios

// Calcula el valor (fitness) de un cromosoma (vector de 0/1)
int fitness(const vector<int> &cromo) {
    int suma = 0;
    for(int i = 0; i < (int)cromo.size(); ++i)
        suma += cromo[i] * GLOBAL_ITEMS[i];
    return suma;
}

// Comprueba si un cromosoma no excede la capacidad (peso)
bool esFactible(const vector<int> &cromo, int capacidadMax) {
    return fitness(cromo) <= capacidadMax;
}

// Imprime la población con su fitness
void mostrarPoblacion(const vector<vector<int>> &pob, int capacidadMax) {
    cout << "Población actual:\n";
    for(auto &c : pob) {
        cout << "[ ";
        for(int bit : c) cout << bit << ' ';
        cout << "]  f=" << fitness(c)
             << (esFactible(c, capacidadMax) ? "" : " (inválido)")
             << '\n';
    }
    cout << '\n';
}

// Genera población inicial aleatoria y factible
void inicializarPoblacion(vector<vector<int>> &pob, int nItems, int capacidadMax) {
    pob.clear();
    while((int)pob.size() < POBLACION_MAX) {
        vector<int> crom(nItems);
        for(int i = 0; i < nItems; ++i)
            crom[i] = rand() % 2;
        if (esFactible(crom, capacidadMax))
            pob.push_back(move(crom));
    }
}

// Selección por ruleta proporcional al fitness
vector<vector<int>> seleccionarPadres(const vector<vector<int>> &pob) {
    int n = pob.size();
    int nPadres = max(1, int(n * P_SELECCION));
    vector<int> fitnesses(n);
    int totalFit = 0;
    for(int i = 0; i < n; ++i) {
        fitnesses[i] = fitness(pob[i]);
        totalFit += fitnesses[i];
    }
    // Rueda: vector con índices repetidos según porcentaje
    vector<int> rueda;
    for(int i = 0; i < n; ++i) {
        int quota = totalFit > 0 
            ? int(100.0 * fitnesses[i] / totalFit)
            : 0;
        rueda.insert(rueda.end(), quota, i);
    }
    // Extraer padres
    vector<vector<int>> padres;
    for(int k = 0; k < nPadres; ++k) {
        int idx = rueda.empty() 
                ? rand() % n 
                : rueda[rand() % rueda.size()];
        padres.push_back(pob[idx]);
    }
    return padres;
}

// Cruce de un padre y una madre (single-point)
vector<int> cruzar(const vector<int> &padre, const vector<int> &madre) {
    int n = padre.size();
    int punto = int(n * P_CRUCE);
    vector<int> hijo(n);
    for(int i = 0; i < punto; ++i)      hijo[i] = padre[i];
    for(int i = punto; i < n; ++i)      hijo[i] = madre[i];
    return hijo;
}

// Genera todos los hijos factibles de la lista de padres
void reproducir(vector<vector<int>> &pob, 
               const vector<vector<int>> &padres, 
               int capacidadMax) {
    int p = padres.size();
    for(int i = 0; i < p; ++i)
        for(int j = i+1; j < p; ++j) {
            auto hijo1 = cruzar(padres[i], padres[j]);
            auto hijo2 = cruzar(padres[j], padres[i]);
            if (esFactible(hijo1, capacidadMax)) pob.push_back(move(hijo1));
            if (esFactible(hijo2, capacidadMax)) pob.push_back(move(hijo2));
        }
}

// Invierte todos los bits de cada padre para crear variantes
void invertirPadres(vector<vector<int>> &pob, 
                    const vector<vector<int>> &padres, 
                    int capacidadMax) {
    for(auto &crom : padres) {
        vector<int> inv = crom;
        for(int &bit : inv) bit = 1 - bit;
        if (esFactible(inv, capacidadMax))
            pob.push_back(move(inv));
    }
}

// Mutación: cambia P_MUTACION·nItems bits al azar en cada padre
void mutarPadres(vector<vector<int>> &pob, 
                 const vector<vector<int>> &padres, 
                 int capacidadMax) {
    int nItems = padres[0].size();
    int nmuts   = int(nItems * P_MUTACION);
    for(auto &crom : padres) {
        vector<int> mut = crom;
        for(int k = 0; k < nmuts; ++k) {
            int pos = rand() % nItems;
            mut[pos] = 1 - mut[pos];
        }
        if (esFactible(mut, capacidadMax))
            pob.push_back(move(mut));
    }
}

// Elimina cromos duplicados en la población usando un map
void eliminarDuplicados(vector<vector<int>> &pob) {
    map<string, vector<int>> unicos;
    for(auto &c : pob) {
        string key;
        for(int bit : c) key += char('0'+bit);
        unicos[key] = c;
    }
    pob.clear();
    for(auto &p : unicos)
        pob.push_back(move(p.second));
}

// Trima la población al tamaño máximo, manteniendo los mejores
void recortarPoblacion(vector<vector<int>> &pob) {
    sort(pob.begin(), pob.end(),
        [](auto &A, auto &B){
            return fitness(A) > fitness(B);
        });
    if ((int)pob.size() > POBLACION_MAX)
        pob.resize(POBLACION_MAX);
}

// —— Función principal del GA para la mochila ——
void resolverMochilaGA(int *items, int nItems, int capacidadMax) {
    GLOBAL_ITEMS = items;
    srand(time(NULL));

    vector<vector<int>> poblacion;
    inicializarPoblacion(poblacion, nItems, capacidadMax);
    mostrarPoblacion(poblacion, capacidadMax);

    for(int gen = 1; gen <= N_ITERACIONES; ++gen) {
        // 1) Selección
        auto padres = seleccionarPadres(poblacion);

        // 2) Cruce
        reproducir(poblacion, padres, capacidadMax);

        // 3) Inversión
        invertirPadres(poblacion, padres, capacidadMax);

        // 4) Mutación
        mutarPadres(poblacion, padres, capacidadMax);

        // 5) Limpieza y recorte
        eliminarDuplicados(poblacion);
        recortarPoblacion(poblacion);

        // 6) Mostrar y conservar mejor
        cout << "=== Generación " << gen << " ===\n";
        mostrarPoblacion(poblacion, capacidadMax);
    }

    // Mostrar MEJOR al final
    auto mejorIt = max_element(poblacion.begin(), poblacion.end(),
        [&](auto &A, auto &B){ return fitness(A) < fitness(B); });
    cout << "\nMejor solución encontrada: valor "
         << fitness(*mejorIt)
         << ", peso libre "
         << capacidadMax - fitness(*mejorIt)
         << "\n[ ";
    for(int bit : *mejorIt) cout << bit << ' ';
    cout << "]\n";
}

int main() {
    // Cada ítem vale "peso" igual a beneficio
    int items[] = {1,2,4,12,1,3,5,10,7};
    int nItems   = sizeof(items)/sizeof(items[0]);
    int capacidadMax = 35;

    resolverMochilaGA(items, nItems, capacidadMax);
    return 0;
}
