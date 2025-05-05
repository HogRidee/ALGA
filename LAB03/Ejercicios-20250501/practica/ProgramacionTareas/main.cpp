#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

// Estructura para representar cada trabajo
struct Job {
    int id;        // Identificador único del trabajo
    int deadline;  // Fecha límite (en unidades de tiempo) para completar
    int profit;    // Ganancia obtenida al completar el trabajo
};

// Función comparadora para ordenar trabajos por ganancia descendente
bool byProfitDesc(const Job &a, const Job &b) {
    return a.profit > b.profit;
}

// Obtiene la fecha límite máxima entre todos los trabajos
int findMaxDeadline(const vector<Job> &jobs) {
    int maxD = 0;
    for (const auto &job : jobs) {
        maxD = max(maxD, job.deadline);
    }
    return maxD;
}

// Algoritmo goloso para programar trabajos con deadlines y ganancias
// jobs: lista de trabajos
// slots: vector de tamaño maxDeadline, donde slot[t] = id del trabajo programado en t (o -1 si está libre)
// Retorna la ganancia total máxima
int scheduleJobsGreedy(const vector<Job> &jobs, vector<int> &slots) {
    // 1) Ordenar trabajos por ganancia descendente
    vector<Job> sorted = jobs;
    sort(sorted.begin(), sorted.end(), byProfitDesc);

    // 2) Determinar cuántos slots de tiempo necesitamos
    int maxD = findMaxDeadline(sorted);
    slots.assign(maxD, -1);  // Inicializa todos los slots a "vacío"

    int totalProfit = 0;

    // 3) Para cada trabajo en orden de ganancia
    for (const auto &job : sorted) {
        // Intentar ubicarlo en el slot más tarde posible antes de su deadline
        // Slot índice = tiempo - 1 (0-based)
        for (int t = min(job.deadline, maxD) - 1; t >= 0; --t) {
            if (slots[t] == -1) {
                // Slot libre: programamos el trabajo aquí
                slots[t] = job.id;
                totalProfit += job.profit;
                break;  // Pasar al siguiente trabajo
            }
        }
    }

    return totalProfit;
}

int main() {
    // Ejemplo de trabajos: {id, deadline, profit}
    vector<Job> jobs = {
        {0, 2, 100},
        {1, 1, 19},
        {2, 2, 27},
        {3, 1, 25},
        {4, 3, 15}
    };

    vector<int> slots;  // Donde guardaremos la programación final
    int maxProfit = scheduleJobsGreedy(jobs, slots);

    // Mostrar resultados
    cout << "Ganancia total: " << maxProfit << endl;
    cout << "Programación de trabajos (slot: job_id):" << endl;
    for (int t = 0; t < slots.size(); ++t) {
        if (slots[t] != -1)
            cout << "  " << t + 1 << ": trabajo " << slots[t] << endl;
        else
            cout << "  " << t + 1 << ": (vacío)" << endl;
    }

    return 0;
}