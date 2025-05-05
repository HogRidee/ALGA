#include <iostream>
#include <cstring>
using namespace std;

int memo[51][51][51][4];

int dp(int p, int q, int r, int last) {
    if (p == 0 && q == 0 && r == 0) return 1;
    if (memo[p][q][r][last] != -1) return memo[p][q][r][last];

    int total = 0;
    if (p > 0 && last != 1) total += dp(p - 1, q, r, 1); // usar una de 1 sol
    if (q > 0 && last != 2) total += dp(p, q - 1, r, 2); // usar una de 2 soles
    if (r > 0 && last != 3) total += dp(p, q, r - 1, 3); // usar una de 5 soles

    return memo[p][q][r][last] = total;
}

int main() {
    int p, q, r;
    cout << "Monedas de 1 sol: "; cin >> p;
    cout << "Monedas de 2 soles: "; cin >> q;
    cout << "Monedas de 5 soles: "; cin >> r;

    memset(memo, -1, sizeof(memo));

    int resultado = dp(p, q, r, 0); // iniciamos sin haber colocado ninguna moneda
    cout << "Número de formas válidas: " << resultado << endl;

    return 0;
}
