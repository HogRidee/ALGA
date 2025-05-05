
/* 
 * File:   main.cpp
 * Author: cueva.r
 *
 * Created on 25 de marzo de 2025, 02:48 PM
 */

#include <iostream>

using namespace std;

int knapsack(int *w, int n, int i, int peso){
    if(peso<0 || i==n)
        return 0;
    if(peso==w[i])
        return 1;
    if(knapsack(w, n, i+1, peso-w[i]))
        return 1;
    else
        return(knapsack(w, n, i+1, peso));
}


int main(int argc, char** argv) {
    int w[]={1,2,4,12,1};
    int W=15;
    int n=sizeof(w)/sizeof(w[0]);
    
    if(knapsack(w,n, 0, W))
        cout <<"Encontro el peso"<< endl;
    else
        cout <<"No encontro el peso"<< endl;
    
    return 0;
}

