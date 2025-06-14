// Archivo: codigo_LAB4_P1.cpp
// GRASP sencillo para asignar tablas a discos y maximizar la velocidad mínima residual

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <cstdlib>  // srand, rand

using namespace std;

struct Tabla { int capGB, iops; };
struct Disco { int capMaxGB, iopsInit; };

// Comprueba si cabe la tabla t en el disco d según asign
bool factible(int t, int d, const vector<int>& asign,
              const vector<Tabla>& tablas,
              const vector<Disco>& discos) {
    int uso = tablas[t].capGB;
    for (int i = 0; i < (int)asign.size(); ++i)
        if (i != t && asign[i] == d)
            uso += tablas[i].capGB;
    return uso <= discos[d].capMaxGB;
}

// Calcula el peor IOPS residual entre todos los discos
int evalResidual(const vector<int>& asign,
                 const vector<Tabla>& tablas,
                 const vector<Disco>& discos) {
    int m = discos.size();
    vector<int> usoIOPS(m, 0);
    for (int i = 0; i < (int)asign.size(); ++i)
        usoIOPS[asign[i]] += tablas[i].iops;
    int peor = INT_MAX;
    for (int d = 0; d < m; ++d)
        peor = min(peor, discos[d].iopsInit - usoIOPS[d]);
    return peor;
}

int main() {
    // Semilla fija
    srand(17);

    // Datos "en duro"
    vector<Tabla> tablas = {
        {20,150}, {10,100}, {15,80},
        {100,50}, {50,120}, {100,10}
    };
    vector<Disco> discos = {
        {800,250}, {750,200}, {850,200}
    };
    double alpha = 0.3;
    int iterMax = 100000;

    int n = tablas.size(), m = discos.size();
    vector<int> bestAsig(n), asig(n);
    int bestVal = INT_MIN;

    // GRASP: many repeats of build + local improvement
    for (int it = 0; it < iterMax; ++it) {
        // Construcción semi-voraz
        fill(asig.begin(), asig.end(), 0);
        for (int t = 0; t < n; ++t) {
            vector<pair<int,int>> cand;
            for (int d = 0; d < m; ++d) {
                if (!factible(t,d,asig,tablas,discos)) continue;
                int usoIOPS = tablas[t].iops;
                for (int i = 0; i < n; ++i)
                    if (asig[i] == d) usoIOPS += tablas[i].iops;
                cand.emplace_back(discos[d].iopsInit - usoIOPS, d);
            }
            if (cand.empty()) continue;
            sort(cand.begin(), cand.end(), greater<>());
            int mejor = cand.front().first;
            int peor  = cand.back().first;
            double umbral = mejor - alpha * (mejor - peor);
            vector<int> RCL;
            for (auto &p : cand)
                if (p.first >= umbral)
                    RCL.push_back(p.second);
            asig[t] = RCL[rand() % RCL.size()];
        }

        // Mejora local (hill-climbing)
        bool mejoro = true;
        while (mejoro) {
            mejoro = false;
            int base = evalResidual(asig, tablas, discos);
            for (int t = 0; t < n && !mejoro; ++t) {
                int orig = asig[t];
                for (int d = 0; d < m; ++d) {
                    if (d == orig) continue;
                    auto prueba = asig;
                    prueba[t] = d;
                    if (!factible(t,d,prueba,tablas,discos)) continue;
                    int val = evalResidual(prueba, tablas, discos);
                    if (val > base) {
                        asig = move(prueba);
                        mejoro = true;
                        break;
                    }
                }
            }
        }

        // Guardar mejor
        int val = evalResidual(asig, tablas, discos);
        if (val > bestVal) {
            bestVal = val;
            bestAsig = asig;
        }
    }

    // Mostrar resultado
    cout << "Velocidad mínima residual óptima: " << bestVal << "\n";
    for (int d = 0; d < m; ++d) {
        cout << "Disco " << d+1 << ":";
        bool primero = true;
        for (int t = 0; t < n; ++t) {
            if (bestAsig[t] == d) {
                cout << (primero ? " " : ", ") << t+1;
                primero = false;
            }
        }
        cout << "\n";
    }

    return 0;
}
