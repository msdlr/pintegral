#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>

#define f(x) (float)(4.0/(1.0 + x*x))

struct tread_args{
    int arg1;
    int arg2;

}

/*
    VARIABLES GLOBALES
*/

float anchura_intervalo;
unsigned short n_rectangulos;
unsigned short n_threads;

float *areas_rectangulos;

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

// Función que ejecuta cada hilo hasta morir
void threads(int nt, int nr){
    int i = 0;

    // nt-1 hilos calcularán nr/(nt-1) áreas
    for(i=0;i<(nt/(nr-1));i++){
    	// Para cada i, calcular rectángulo pasándole el punto medio
        calcula_area(0.5*(1/nr)*i);
    }
    // El último hilo hace la tarea de sumar
    if(nt == (n_threads-1)){

    }
}


void main(int argc, char *argv[]){

    int nt; // Número de threads
    int nr; // Número de rectángulos

    int ir; // errorlevel al crear un hilo



    pthread_t mtid;

    if(argc != 3){
        printf("Uso: pintegral <nº de rectangulos> <nº de hilos>");
        exit(1);
    }

    nr = (unsigned short)atoi(argv[1]);
    nt = (unsigned short)atoi(argv[2]);

    // Calcular la anchura de los rectángulos
    anchura_intervalo = 1.0/nr;

    //Reparto de rectángulos entre hilos

    tread_args =

    // Crear el array de áreas que componen toda el área completa
    areas_rectangulos = malloc(nr*sizeof(float));

    // Si el número de rectángulos es mayor que el número de threads, toca al menos un rectángulo a cada thread
    if(nr > nt){
        // Dividimos entre el número de hilos -1, y el ultimo tiene algo menos de carga pero hará otras tareas
    }

    //lanzamiento de threads
    if (ir = pthread_create(&mtid, NULL, threads, (void *)tread_args))


    printf("Integrando...\n");

}
