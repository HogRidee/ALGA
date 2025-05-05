/* 
 * File:   main.cpp
 * Author: cueva.r
 *
 * Created on 25 de marzo de 2025, 03:32 PM
 */

#include <iostream>
#define N 10
#define M 10

int mov[8][2];

using namespace std;

void cargamovimientos(){
    mov[0][0]=-1; mov[0][1]=0;
    mov[1][0]=-1; mov[1][1]=1;
    mov[2][0]=0; mov[2][1]=1;
    mov[3][0]=1; mov[3][1]=1;
    mov[4][0]=1; mov[4][1]=0;
    mov[5][0]=1; mov[5][1]=-1;
    mov[6][0]=0; mov[6][1]=-1;
    mov[7][0]=-1;mov[7][1]=-1;
}

void cargaminas(char **a){
    a[0][4]='*';
    a[2][2]='*';
    a[4][1]='*';
    a[4][2]='*';
    a[4][4]='*';
    a[5][1]='*';
    a[5][2]='*';
    a[5][4]='*';
    a[6][1]='*';    
    a[6][3]='*';
    a[7][0]='*';
    a[7][1]='*';
    a[7][2]='*';    
    a[7][3]='*';
}
int main(int argc, char** argv) {
    char mapa[N][M];
    
    cargaminas(mapa);
    
    return 0;
}

