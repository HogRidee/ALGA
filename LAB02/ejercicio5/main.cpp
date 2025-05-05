#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int m, n, k;
int grid[50][50];
int memo[50][50][501]; // i, j, monedas restantes

int dfs(int i, int j, int coinsLeft) {
    if (i >= m || j >= n) return 0;
    coinsLeft -= grid[i][j];
    if (coinsLeft < 0) return 0;

    if (i == m - 1 && j == n - 1)
        return (coinsLeft == 0) ? 1 : 0;

    if (memo[i][j][coinsLeft] != -1)
        return memo[i][j][coinsLeft];

    int right = dfs(i, j + 1, coinsLeft);
    int down = dfs(i + 1, j, coinsLeft);

    return memo[i][j][coinsLeft] = right + down;
}

int main() {
    cout << "Filas y columnas: ";
    cin >> m >> n;
    cout << "Monedas exactas que quieres recoger (k): ";
    cin >> k;

    cout << "Ingresa la matriz de monedas:\n";
    for (int i = 0; i < m; i++)
        for (int j = 0; j < n; j++)
            cin >> grid[i][j];

    memset(memo, -1, sizeof(memo));

    int formas = dfs(0, 0, k);
    cout << "Número de caminos válidos: " << formas << endl;

    return 0;
}
