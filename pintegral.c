#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>

#define f(x) (float)(4.0/(1.0 + x*x))



/*
    VARIABLES GLOBALES
*/
unsigned short nr;
unsigned short nt;
unsigned short n_areas_parciales;
short *rectangulos_por_hilo;
float area_total = 0;
float *areas_parciales;
float anchura_intervalo;

/*
    FUNTIONES
*/

// Calcula f(x) en el punto medio de dos valores de X pasados por parámetro
void *calcula_area(void* _id){
    int inicial=0;
    int final=0;
    unsigned short i;
    unsigned short id = *((unsigned short*)_id);

    //Rectangulo inicial del hilo
    for(i = 0; i < id; i++){
        inicial+=rectangulos_por_hilo[i];
    }
    printf("Hilo %d, rectangulo inicial: %d", id, inicial+1);
    final=inicial+rectangulos_por_hilo[id];
    //Calculo de los rectangulos
    for(i=inicial; i<final; i++){
        areas_parciales[id] += f(anchura_intervalo*(i+0.5));
    }

}


void main(int argc, char *argv[]){

    int ir; // errorlevel al crear un hilo

    pthread_t *mtid = malloc(sizeof(pthread_t)*nt);

    if(argc != 3){
        printf("Uso: pintegral <nº de rectangulos> <nº de hilos>\n");
        exit(1);
    }

    nr = (unsigned short)atoi(argv[1]);
    nt = (unsigned short)atoi(argv[2]);
    anchura_intervalo=1.0/nr;
    printf("Anchura de intervalo: %f\n", anchura_intervalo);

    /* Reparto de rectángulos entre hilos (calcular número de rectángulos que tiene que calcular cada hilo) */
    // Cada posición del vector tiene el número de rectángulos por hilo
    rectangulos_por_hilo = malloc(nt*sizeof(short));
    for(int i = 0;i < nt; i++){
        // Calculamos el número mínimo de áreas que debe calcular cada hilo
        rectangulos_por_hilo[i] = nr/nt;
        // A los (nr%nt) primeros hilos les toca otro área para calcular
        if(i < (nr%nt)) rectangulos_por_hilo[i]++;
        
        printf("Hilo: %d, %d rectangulos\n", i, rectangulos_por_hilo[i]);

    } // Si el número de rectángulos es múltiplo del de hilos todos hacen las mismas áreas


    // Creamos el array para guardar las áreas parciales
    areas_parciales = malloc(nt*sizeof(float));

    // Dejamos todas las posiciones con valor -1, lo que significa que el área parcial aún no está calculada
    for(int i = 0; i<nt; i++) areas_parciales[i] = -1;


    /* Lanzamiento de los hilos */
    for(int i = 0 ; i<nt ; i++){
        if(ir=pthread_create(&mtid[i],NULL, calcula_area, (void*) &i)){
            fprintf(stderr, "error al crear hilo: pthread_create() %d", ir);
            exit(1);
        }
    }
    /* Espera a los hilos */
    for(int i = 0 ; i<nt ; i++){
        if(ir=pthread_join(mtid[i],NULL)){
            fprintf(stderr, "error al esperar hilo: pthread_join() %d", ir);
            exit(1);
        }
    }

    // Hilo principal: Sumar las áreas parciales que se han terminado de calcular para conseguir la total
    for(int i=0;i<nt;i++){
        while(areas_parciales[i] == -1); // No hacer nada hasta que no esté el área parcial calculada
        area_total += areas_parciales[i];
    }
    area_total=area_total*anchura_intervalo;

    //lanzamiento de threads
    //if (ir = pthread_create(&mtid, NULL, threads, (void *)tread_args))

    printf("Pi=%f",area_total);
    exit(EXIT_SUCCESS);

}
