#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

void imprimirSubconjuntos(int arr[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++)
        total += arr[i];

    bool dp[n+1][total/2 + 1];
    memset(dp, false, sizeof(dp));

    // Inicialización
    for (int i = 0; i <= n; i++)
        dp[i][0] = true;

    // Llenar tabla
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= total/2; j++) {
            if (arr[i-1] <= j)
                dp[i][j] = dp[i-1][j] || dp[i-1][j - arr[i-1]];
            else
                dp[i][j] = dp[i-1][j];
        }
    }

    // Encontrar la suma más cercana a la mitad
    int s1;
    for (s1 = total/2; s1 >= 0; s1--) {
        if (dp[n][s1]) break;
    }

    std::vector<int> subset1, subset2;

    // Reconstruir subconjuntos
    int i = n, j = s1;
    while (i > 0 && j >= 0) {
        if (dp[i-1][j]) {
            // El elemento arr[i-1] NO fue incluido en subset1
            subset2.push_back(arr[i-1]);
            i--;
        } else {
            // El elemento arr[i-1] fue incluido en subset1
            subset1.push_back(arr[i-1]);
            j -= arr[i-1];
            i--;
        }
    }

    // Imprimir resultado
    std::cout << "Subconjunto 1: ";
    for (int num : subset1) std::cout << num << " ";
    std::cout << "\nSubconjunto 2: ";
    for (int k = 0; k < i; k++) std::cout << arr[k] << " "; // Lo que quedó sin revisar
    for (int num : subset2) std::cout << num << " ";

    std::cout << "\nDiferencia mínima: " << total - 2 * s1 << std::endl;
}

int main() {
    int A[] = {1, 6, 11, 5};
    int n = sizeof(A)/sizeof(A[0]);
    imprimirSubconjuntos(A, n);
    return 0;
}
