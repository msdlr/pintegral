#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>

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
    return f((pto_medio)*(anchura_intervalo));
}





/*
    nt : number of threads
    nr : number of rectangles
*/
void threads(int nt, int nr){
    
}


void main(int argc, char *argv[]){

    int nt;
    int nr;

    if(argc != 3){
        printf("Uso: pintegral <nº de rectangulos> <nº de hilos>");
        exit(1);
    }    

    nr = (unsigned short)atoi(argv[1]);
    nt = (unsigned short)atoi(argv[2]);

    //Reparto de rectángulos entre hilos

    




    printf("Integrando...\n");

}
