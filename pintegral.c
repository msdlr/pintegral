#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
#include <sys/time.h>

#define f(x) (double)(4.0/(1.0 + x*x))
//#define debug


/*
    VARIABLES GLOBALES
*/
unsigned long nr;
unsigned long nt;
unsigned long n_areas_parciales;
int *rectangulos_por_hilo;
long double area_total = 0;
long double *areas_parciales;
long double anchura_intervalo;
unsigned long inicio,fin;

/*
    FUNCIONES
*/

// Cálculo del instante de llamada en tiempo epoch
unsigned long get_time() {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        unsigned long ret = tv.tv_usec;
        ret += (tv.tv_sec * 1000000);
        return ret;
}

//suma de areas parciales
void *calcula_area(void *_id){
    unsigned long inicial=0;
    unsigned long final=0;
    unsigned long i;
    int id = *((int*)_id);



    //Rectangulo inicial del hilo
    for(i = 0; i < id; i++){
        inicial+=rectangulos_por_hilo[i];
    }
    
    final=inicial+rectangulos_por_hilo[id]-1;
    #ifdef debug 
    printf("Hilo %ld, rectangulo inicial: %ld, rectangulo final: %ld\n", id, inicial, final);
    #endif
    areas_parciales[id]=0.0;
    //Calculo de los rectangulos
    for(i=inicial; i<=final; i++){
        areas_parciales[id] = areas_parciales[id]+f(anchura_intervalo*(i+0.5));
    }
    
    #ifdef debug
    printf("Hilo %ld, area parcial: %Lf\n", id, areas_parciales[id]);
    #endif

    pthread_exit(0);
    return(0);
}


void main(int argc, char *argv[]){

    int ir; // errorlevel al crear un hilo
    unsigned long i=0;

    if(argc != 3){
        printf("Uso: pintegral <nº de rectangulos> <nº de hilos>\n");
        exit(1);
    }

    // Toma de tiempo al inicio del programa
    inicio = get_time();

    nr = atoi(argv[1]);
    nt = atoi(argv[2]);

    int *hilo_id = malloc(sizeof(int)*nt);
    pthread_t *mtid = malloc(sizeof(pthread_t)*(int)nt);

    anchura_intervalo=1.0/nr;
    #ifdef debug
    printf("Anchura de intervalo: %Lf\n", anchura_intervalo);
    #endif
    /* Reparto de rectángulos entre hilos (calcular número de rectángulos que tiene que calcular cada hilo) */
    // Cada posición del vector tiene el número de rectángulos por hilo
    rectangulos_por_hilo = malloc(nt*sizeof(int));
    for(i = 0;i < nt; i++){
        //inicializamos las IDS de los hilos
        hilo_id[i]=i;
        // Calculamos el número mínimo de áreas que debe calcular cada hilo
        rectangulos_por_hilo[i] = nr/nt;
        // A los (nr%nt) primeros hilos les toca otro área para calcular
        if(i < (nr%nt)) rectangulos_por_hilo[i]++;
        #ifdef debug
        printf("Hilo: %ld, %ld rectangulos\n", i, rectangulos_por_hilo[i]);
        #endif

    } // Si el número de rectángulos es múltiplo del de hilos todos hacen las mismas áreas


    // Creamos el array para guardar las áreas parciales
    areas_parciales = malloc(nt*sizeof(long double));

    // Dejamos todas las posiciones con valor -1, lo que significa que el área parcial aún no está calculada
    for(i = 0; i<nt; i++) areas_parciales[i] = -1;

    /* Lanzamiento de los hilos */
    for(i = 0 ; i<nt ; i++){

        if(ir=pthread_create(&mtid[i],NULL, calcula_area, (void*) &hilo_id[i])){
            fprintf(stderr, "error al crear hilo: pthread_create() %ld", ir);
            exit(1);
        }
    }

    // Espera a los hilos 
    for(i = 0 ; i<nt ; i++){
        if(ir=pthread_join(mtid[i],NULL)){
            fprintf(stderr, "error al esperar hilo: pthread_join() %ld", ir);
            exit(1);
        }
    }

    // Hilo principal: Sumar las áreas parciales que se han terminado de calcular para conseguir la total
    for(i=0;i<nt;i++){
        while(areas_parciales[i] == -1); // No hacer nada hasta que no esté el área parcial calculada
        area_total += areas_parciales[i];
    }
    #ifdef debug
    printf("Suma total de areas parciales: %lf\n", area_total);
    #endif

    area_total=area_total*anchura_intervalo;

    // Toma de tiempo al final del programa
    fin = get_time();

    printf("π=%Lf (%2.10lu us)\n",area_total,fin-inicio);
    exit(EXIT_SUCCESS);

}
