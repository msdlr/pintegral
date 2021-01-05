#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>

#define f(x) (float)(4.0/(1.0 + x*x))

struct tread_args{
    int arg1;
    int arg2;

};

/*
    VARIABLES GLOBALES
*/
unsigned short n_rectangulos;
unsigned short n_threads;
unsigned short n_areas_parciales;
float area_total = 0;
float *areas_parciales;
float anchura_intervalo;

/*
    FUNTIONES
*/

// Calcula f(x) en el punto medio de dos valores de X pasados por parámetro
float calcula_area(float pto_medio){
    return f((pto_medio)*(anchura_intervalo));
}

int suma_total(){
    //funcion para sumar los resultados parciales al total
    //No tiene parametros, utiliza el vector de areas parciales y lo va sumando

    return 0;
}




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

    //Reparto de rectángulos entre hilos

    //tread_args =


    // Distinción entre el caso en el que el número de hilos sea múltiplo o no del de rectángulos, o viceversa
    if(nr%nt == 0){
        // Si uno es múltiplo de otro, repartimos en rectángulos iguales la función.
        // Cada hilo calcula sus rectángulos y va calculando sus áreas en el vector
        n_areas_parciales = nr/nt;
        areas_parciales = malloc(n_areas_parciales*sizeof(float));
        // Dejamos todas las posiciones con valor -1, lo que significa que el área parcial aún no está calculada
        for(int i = 0; i<n_areas_parciales; i++) areas_parciales[i] = -1;
        // Lanzamiento de los hilos

        // Hilo principal: Sumar las áreas parciales que se han terminado de calcular para conseguir la total
        for(int i=0;i<n_areas_parciales;i++){
            while(areas_parciales[i] == -1); // No hacer nada hasta que no esté el área parcial calculada
            area_total += n_areas_parciales;
        }
    } else {
        // Si no, calcular el número de sumas parciales


        areas_parciales = malloc(n_areas_parciales*sizeof(float));
        // Dejamos todas las posiciones con valor -1, lo que significa que el área parcial aún no está calculada
        for(int i = 0; i<n_areas_parciales; i++) areas_parciales[i] = -1;
        // Lanzamiento de hilos

    }

    //lanzamiento de threads
    //if (ir = pthread_create(&mtid, NULL, threads, (void *)tread_args))

    printf("Pi=%f",area_total);
    exit(EXIT_SUCCESS);

}
