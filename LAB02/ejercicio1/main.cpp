#include <iostream>
using namespace std;

const int MAX = 100;

bool dp[MAX][MAX]; // dp[i][j] = true si puedo hacer suma j con los primeros i elementos

// Función para imprimir un subconjunto que forma 'sum'
void printSubset(int arr[], int i, int sum) {
    if (i == 0 || sum == 0)
        return;

    // Si se puede formar sin el elemento arr[i-1], seguimos sin él
    if (dp[i-1][sum]) {
        printSubset(arr, i-1, sum);
    }
    else if (sum >= arr[i-1] && dp[i-1][sum - arr[i-1]]) {
        printSubset(arr, i-1, sum - arr[i-1]);
        cout << arr[i-1] << " "; // Este elemento está en el subconjunto
    }
}

bool canPartition(int arr[], int n) {
    int total = 0;
    for (int i = 0; i < n; i++)
        total += arr[i];

    if (total % 2 != 0)
        return false;

    int target = total / 2;

    // Inicialización
    for (int i = 0; i <= n; i++)
        dp[i][0] = true;
    for (int j = 1; j <= target; j++)
        dp[0][j] = false;

    // Llenar la tabla dp
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= target; j++) {
            if (j < arr[i - 1])
                dp[i][j] = dp[i - 1][j];
            else
                dp[i][j] = dp[i - 1][j] || dp[i - 1][j - arr[i - 1]];
        }
    }

    if (!dp[n][target])
        return false;

    cout << "Subconjunto que suma " << target << ": ";
    printSubset(arr, n, target);
    cout << endl;
    return true;
}

int main() {
    int arr[] = {1, 5, 11, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    if (canPartition(arr, n)) {
        cout << "Sí se puede dividir en dos subconjuntos iguales." << endl;
    } else {
        cout << "No se puede dividir en dos subconjuntos iguales." << endl;
    }

    return 0;
}
