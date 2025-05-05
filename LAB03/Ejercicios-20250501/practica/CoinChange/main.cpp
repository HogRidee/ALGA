#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

// -------------------------------------------
// FUNCION 1: Programación dinámica
// -------------------------------------------
int cambio_minimo_dp(const vector<int>& monedas, int total) {
    int m = monedas.size();
    vector<int> dp(total + 1, INT_MAX); // dp[i] = mínimo de monedas para total i
    vector<int> eleccion(total + 1, -1); // para reconstruir solución
    dp[0] = 0; // base: para total 0 se necesitan 0 monedas

    for (int i = 1; i <= total; i++) {
        for (int j = 0; j < m; j++) {
            int coin = monedas[j];
            if (coin <= i && dp[i - coin] != INT_MAX) {
                if (dp[i - coin] + 1 < dp[i]) {
                    dp[i] = dp[i - coin] + 1;
                    eleccion[i] = j;
                }
            }
        }
    }

    cout << "Solución usando Programación Dinámica para " << total << ":\n";

    if (dp[total] == INT_MAX) {
        cout << "No se puede dar cambio exacto\n";
        return 0;
    }

    // Reconstruir la solución
    int valor_restante = total;
    while (valor_restante > 0) {
        int idx = eleccion[valor_restante];
        cout << "Moneda: " << monedas[idx] << "\n";
        valor_restante -= monedas[idx];
    }

    cout << "Total de monedas usadas: " << dp[total] << endl;
    return dp[total];
}

// -------------------------------------------
// FUNCION 2: Enfoque Greedy (Avaro)
// -------------------------------------------
int cambio_minimo_greedy(vector<int> monedas, int total) {
    sort(monedas.rbegin(), monedas.rend()); // orden descendente
    int monedas_usadas = 0;
    int restante = total;

    cout << "Solución usando Greedy para " << total << ":\n";

    for (int i = 0; i < monedas.size(); i++) {
        while (monedas[i] <= restante) {
            cout << "Moneda: " << monedas[i] << "\n";
            restante -= monedas[i];
            monedas_usadas++;
        }
    }

    if (restante > 0) {
        cout << "No se pudo completar el cambio exacto.\n";
        return 0;
    }

    cout << "Total de monedas usadas: " << monedas_usadas << endl;
    return monedas_usadas;
}

// -------------------------------------------
// FUNCION PRINCIPAL
// -------------------------------------------
int main() {
    vector<int> denominaciones = {1, 3, 4};
    int cambio = 6;

    cambio_minimo_dp(denominaciones, cambio);
    cout << "-----------------------------\n";
    cambio_minimo_greedy(denominaciones, cambio);

    return 0;
}
