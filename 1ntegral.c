#include<stdio.h>

#define f(x) (float)(4.0/(1.0 + x*x))

/*
    VARIABLES GLOBALES
*/

float anchura_intervalo;
unsigned short n_rectangulos;
unsigned short n_hilos;

/*
    FUNTIONES
*/

// Calcula f(x) en el punto medio de dos valores de X pasados por parámetro
float calcula_area(float pto_medio){
    return f(pto_medio)*(anchura_intervalo));
}





/*
    nt : number of threads
    nr : number of rectangles
*/
void threads(int nt, int nr){
    
}


void main(int argc, char *argv[]){
    printf("Integrando...\n");
}
