
/* 
 * File:   seleccion_actividades.cpp
 * Author: Igor Siveroni
 *
 * Problema: Seleccion de Actividades
 * Dadas n actividades que necesitan utlilizar un recurso
 *    a1, a2, ..., an
 * Cada una con un tiempo de inicio si y fin fi:  si<fi
 * Si la actividad i se selecciona, se llevara a cabo en [si,fi)
 * Decimos que 2 actividades ai, aj son compatibles (mutuamente excluyenyes)
 * si la intercession de [si,fi) y (sj,fj) es nula.
 * Problema: Seleccionar el mayor numero de actividades compatibles
 */

#include <iostream>
#include <vector>
#include <stack>
#include <list>
#include <limits>

#include <algorithm>
#include <random>

using namespace std;

struct actividad {
  int id, inicio, fin;
};

bool gt_act(const actividad& l, const actividad& r) {
  return l.fin <= r.fin;
}

void ordenar_actividades(vector<actividad>& a) {
  if (!is_sorted(a.begin(), a.end(), gt_act))
    sort(a.begin(), a.end(), gt_act);
  return;
}

/*
 * slot[i] inicio: i,  fin:i+1
 * act toma slots act.ini, act>ini+1,...,act.fin-1
 */
bool puedo_seleccionar(const actividad& act, const vector<bool>& slots) {
  for(int i=act.inicio; i < act.fin; i++)
    if (slots[i]) return false;  
  return true;
}

void seleccionar(const actividad& act, vector<bool>& slots) {
  for(int i=act.inicio; i < act.fin; i++)
    slots[i]=true;
  return;
}

void desseleccionar(const actividad& act, vector<bool>& slots) {
  for(int i=act.inicio; i < act.fin; i++)
    slots[i]=false;
  return;
}

/*
 * slots: indica que slots de tiempo han sido utlizados
 * n: seleccionar actividades 1..n
*/
void pa_bt(vector<actividad>& a, vector<actividad>& p, vector<bool>& slots, int n, int& max, vector<vector<actividad> >& l_max) {
  if (n<0) {
    int num = p.size();
    if (num == max) {
      l_max.push_back(p);
    } else if (num > max) {
      max=num;
      l_max.clear();
      l_max.push_back(p);
    }
    return;
  }

  // Similar a la estrategia de Knapsack.
  // Tratar de seleccionar actividad n, y seguir con actividades 1,...,n-1
 
  // Puedo seleccionar n?
  if (puedo_seleccionar(a[n], slots)) {
    seleccionar(a[n],slots); p.push_back(a[n]);
    pa_bt(a,p,slots,n-1,max,l_max);
    desseleccionar(a[n],slots); p.pop_back();
  }
  pa_bt(a,p,slots,n-1,max,l_max);
  return;
}

/*
 * Retorna el numero de actividades maximas
 * l_max: lista las programaciones validas con maximo numero de actividades
*/
int seleccionar_actividades_bt(vector<actividad>& a, vector<vector<actividad> >& l_max) {
  l_max.clear();
  int max_fin =-1;
  
  for(int i=0; i < a.size(); i++)
    if (max_fin < a[i].fin) max_fin = a[i].fin;
  vector<bool> slots(max_fin); // slots de tiempos usados para seleccionar actividades
  vector<actividad> programa;

  int max=-1;
  pa_bt(a,programa,slots,a.size()-1, max, l_max);

  return max;
}

/*
 * Algoritmo goloso/greedy
 * Ordenar actividades en orden ascendente a tiempos finales
 *    a1, a2, ..., an,  fi <= f(i+1)
 * Dados los arreglos s[1...n], f[1...n]
 * n <- len(s)
 * A <- {1} // seleccionar primera actividad
 * j <- 1   //fj, tiempo de fin (maximo) de ultima actividad en A
 * for i <- 2...n
 *   if si >> fj
 *     A <- A U {i}
 *     j <- i  // ultima actividad seleccionada
 */

int seleccionar_actividades_greedy(vector<actividad>& a, vector<actividad>& p) {
  ordenar_actividades(a);
  p.clear();
  int j,num_actividades=0;

  // agregar codigo
  
  return num_actividades;
}

// g++ -std=c++11 seleccion_actividades.cpp

int main(int argc, char** argv) {

  vector<actividad> a;  // puede ser a = {   }
  a.push_back({1,1,4});
  a.push_back({2,3,5});
  a.push_back({3,0,6});
  a.push_back({4,5,7});
  a.push_back({5,3,8});
  a.push_back({6,5,9});
  a.push_back({7,6,10});
  a.push_back({8,8,11});
  a.push_back({9,8,12});
  a.push_back({10,2,13});
  a.push_back({11,12,14});

  // normalmente el input vendra en cualquier orden
  // shuffle
  auto rng = std::default_random_engine {};
  std::shuffle(std::begin(a), std::end(a), rng);

  for(int i=0; i < a.size(); i++)
    cout << a[i].id << " ";
  cout << endl;

  vector<vector<actividad> > l_max;  // lista de programacion de actividades maximas

  int max_bt = seleccionar_actividades_bt(a,l_max);

  cout << "Solucion Backtracing:" << endl;
  cout << "Max numero actividades: " << max_bt << endl;
  for(int i=0; i<l_max.size(); i++) {
    cout << "{ ";
    for (int j=0; j<l_max[i].size(); j++) {
      cout << l_max[i][j].id << " ";
    }
    cout << "}" << endl;
  }

  cout << "---------------" << endl;
  vector<actividad> p;  // programa  
  int max_greedy = seleccionar_actividades_greedy(a,p);
  cout << "Solucion Greedy" << endl;
  cout << "Max numero actividades " << max_greedy << endl;
  for(int i=0; i<p.size(); i++)
    cout << "actividad: " << p[i].id << " [" << p[i].inicio << "," << p[i].fin << "]" << endl;
  
  
  return 0;
}

