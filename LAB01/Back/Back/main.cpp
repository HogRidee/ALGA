
/* 
 * File:   main.cpp
 * Author: cueva.r
 *
 * Created on 25 de marzo de 2025, 02:48 PM
 */

#include <iostream>

using namespace std;

int cargamochila(int i,int n,int peso,int *paq){
    if(peso<0 || i==n) 
        return 0;
    if(peso==paq[i])   
        return 1;
    if(cargamochila(i+1,n,peso-paq[i],paq))
        return 1;
    else
        return(cargamochila(i+1,n,peso,paq));
}



int main(int argc, char** argv) {
    int paq[]={1,2,4,12,1};
    int peso=15;
    int n=sizeof(paq)/sizeof(paq[0]);
    
    if(cargamochila(0,n,peso,paq))
        cout <<"Encontro el peso"<< endl;
    else
        cout <<"No encontro el peso"<< endl;
    
    return 0;
}

