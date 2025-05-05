/**
 * Implementacion de algoritmo Goloso para resolver el Problema de Programación Secuencial de tareas con deadlines: 
 * Se tiene una serie de n tareas a ser ejecutadas en una sola maquina de forma secuencial.
 * Cada tarea tiene:
 * - una fecha límite para ser finalizado y una ganancia asociada si el trabajo 
 * se finaliza antes de la fecha límite. Cada trabajo toma una sola unidad de tiempo para su ejecución.
 * Escoger una programación secuencial de trabajos tal que se obtenga la máxima ganancia total. 
 * 
 * 
 * Autor: Dr. Edwin Villanueva
 * Modificado: Igor Siveroni
 *
 */

#include <iostream>
#include <algorithm> // Para std::sort
#include <vector> 

using namespace std;

struct Job {
  int id;       // ID del trabajo
  int deadline; // Fecha límite del trabajo
  int profit;   // Ganancia del trabajo
  int slot;     // time-slot donde fue programado
};

// Función comparadora para ordenar trabajos por ganancia de forma decreciente
bool compareJobs(const Job &a, const Job &b) {
    return a.profit > b.profit;
}

int maxDeadline(const Job jobs[], int n) {
    int max_d = 0;
    for (int i = 0; i < n; i++) {
        if (jobs[i].deadline > max_d) {
            max_d = jobs[i].deadline;
        }
    }
    return max_d;
}

/*
 * Algoritmo greedy/goloso
 * Tenemos las tareas en orden descendente a ganancia
 *     a1,...,an
 * y un arrego d1,...,dn con las fechas limites de fin (deadlines)
 * for i < 1...n:
 *   Si es posible programar i lo mas tarde posible:
 *     S = S U {i}
 *
 * "programar i lo mas tarde posible"
 * Dado un arreglo de tiempo slots indicando las unidades de tiempo ya programadas,
 * buscar el primer slot libre, de derecha a izquierda,  empezando por di.
*/

int schedule_jobs(const Job jobs[], int n, vector<int>& slots) {
  slots.clear();
  // Ordenar los trabajos por ganancia de forma decreciente
  Job sortedJobs[n];
  copy(jobs, jobs + n, sortedJobs);
  sort(sortedJobs, sortedJobs + n, compareJobs);

  int max_d = maxDeadline(sortedJobs, n); // Fecha límite máxima
  
  slots = vector<int>(max_d,-1);
  
   int total_profit = 0; // Ganancia total obtenida
  
   //cout << "max deadline: " << max_d << endl;
  
  int num_jobs=0;
  for (int i = 0; i < n; i++) {
    const Job &j = sortedJobs[i];
    
    // Intentar insertar el sgte trabajo mas valioso en la ranura
    // más tardía posible dentro de su límite

    // editar
 
  }
  
  return total_profit;
}


int main() {
    Job jobs[] = {
      {0, 2, 100}, // ID = 0, Deadline = 2, Profit = 100
      {1, 1, 19},  
      {2, 2, 27},  
      {3, 1, 25},  
      {4, 3, 15}   
    };
    Job jobs2[] = {
      {1, 2, 30}, 
      {2, 1, 35},  
      {3, 2, 25},  
      {4, 1, 40},  
     };
    
    int n = sizeof(jobs) / sizeof(jobs[0]);

    vector<int> slots;
    int profit = schedule_jobs(jobs, n, slots);
    cout << "\nGanancia total: " << profit << endl;
    cout << "Secuencia de trabajos seleccionados para la máxima ganancia: " << endl;  
    for(int i=0; i < slots.size(); i++)
      if (slots[i]!=-1)
	cout << "Slot: " << i << " tarea " << slots[i] << endl;
	

    return 0;
}
