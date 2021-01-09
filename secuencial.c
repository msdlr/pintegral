#include <stdio.h>
#include <sys/time.h>

unsigned long inicio, fin;

unsigned long get_time() {
        struct timeval tv;
        gettimeofday(&tv, NULL);
        unsigned long ret = tv.tv_usec;
        ret += (tv.tv_sec * 1000000);
        return ret;
}

main (int argc, char *argv[]) 
{
   int    nrect;                /* Numero de rectangulos */
   double x, pi, suma = 0.0;
   double arect;                /* Anchura de los rectangulos */

  /* TIEMPO EN EPOCH DE INICIO */
  inicio = get_time();

   if (argc == 2)get_time(
    nrect  = atoi(argv[1]);
   else 
    {
      printf ("Sintaxis: <ejecutable> <numero de rectangulos>\n");
      printf ("Por ejemplo, pi 10000000\n");
      exit(0);
    }

   arect = 1.0 / nrect;

   /* Para cada rectangulo calcula f(punto_medio) y lo acumula */
   for (x = 0.5 * arect; x < 1.0; x += arect)
    suma += 4.0 / (1.0 + x * x);

  /* TIEMPO EN EPOCH DE FIN */
  fin = get_time();

   /* Resultado = suma * arect */
   pi = suma * arect;
   printf("pi = %2.10f con %d rectangulos (%lu us) \n", pi, nrect,fin - inicio);

   return(0);
}
