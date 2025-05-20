#include <iostream>
#include <vector>
using namespace std;

// Función para contar cuántos elementos nuevos cubre un subconjunto
int contarNuevos(const vector<int>& subconjunto, const vector<int>& cubiertos) {
    int cuenta = 0;
    for (int i = 0; i < cubiertos.size(); i++) {
        if (subconjunto[i] == 1 && cubiertos[i] == 0)
            cuenta++;
    }
    return cuenta;
}

// Función principal del algoritmo voraz
vector<int> setCover(const vector<vector<int>>& subconjuntos, vector<int> universo) {
    int n = universo.size(); // Tamaño del universo
    vector<int> cubiertos(n, 0); // Marcar elementos cubiertos
    vector<int> seleccionados;

    while (cubiertos != universo) {
        int mejorIndice = -1;
        int maxNuevos = 0;

        for (int i = 0; i < subconjuntos.size(); i++) {
            int nuevos = contarNuevos(subconjuntos[i], cubiertos);
            if (nuevos > maxNuevos) {
                maxNuevos = nuevos;
                mejorIndice = i;
            }
        }

        if (mejorIndice == -1) break; // No se puede cubrir más

        // Agregar subconjunto seleccionado
        seleccionados.push_back(mejorIndice);

        // Marcar nuevos cubiertos
        for (int i = 0; i < n; i++) {
            if (subconjuntos[mejorIndice][i] == 1)
                cubiertos[i] = 1;
        }
    }

    return seleccionados;
}

int main() {
    // Universo U = {1, 2, 3, 4, 5, 6, 7}
    vector<int> universo = {1, 1, 1, 1, 1, 1, 1};

    // Subconjuntos representados como vectores binarios
    vector<vector<int>> subconjuntos = {
        {1, 1, 1, 0, 0, 0, 0}, // S1: {1, 2, 3}
        {0, 1, 0, 1, 1, 0, 0}, // S2: {2, 4, 5}
        {0, 0, 1, 0, 1, 1, 0}, // S3: {3, 5, 6}
        {0, 0, 0, 0, 0, 1, 1}, // S4: {6, 7}
    };

    vector<int> resultado = setCover(subconjuntos, universo);

    cout << "Subconjuntos seleccionados: ";
    for (int idx : resultado) {
        cout << "S" << (idx + 1) << " ";
    }
    cout << endl;

    return 0;
}
