#include <iostream>
#include <vector>
using namespace std;

int contarFormas(int n) {
    // Arreglo para almacenar los resultados de la programación dinámica
    vector<int> dp(n + 1, 0);

    // Condiciones base
    dp[0] = 1;  // Una forma de llenar una tabla de 0x4 (no colocar bloques)
    dp[1] = 1;  // Una forma de llenar una tabla de 1x4
    dp[2] = 1;  // Una forma de llenar una tabla de 2x4
    dp[3] = 1;  // Una forma de llenar una tabla de 3x4

    // Llenamos la tabla usando la recurrencia
    for (int i = 4; i <= n; i++) {
        dp[i] = dp[i - 1] + dp[i - 4];
    }

    return dp[n];
}

int main() {
    int n;
    cout << "Introduce el valor de n: ";
    cin >> n;

    cout << "El número de formas de llenar una tabla de " << n << "x4 es: " << contarFormas(n) << endl;

    return 0;
}
