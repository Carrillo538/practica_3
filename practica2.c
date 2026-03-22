#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct {
    int *E;
    int n;
    long inicio;
    long fin;
    int contador;
} DatosHilo;

void* resolver_suma(void* arg) {
    DatosHilo* d = (DatosHilo*)arg;
    d->contador = 0;
    for (long i = d->inicio; i < d->fin; i++) {
        long suma = 0;
        int tiene_elementos = 0;
        for (int j = 0; j < d->n; j++) {
            if ((i >> j) & 1) {
                suma += d->E[j];
                tiene_elementos = 1;
            }
        }
        if (tiene_elementos && suma == 0) d->contador++;
    }
    pthread_exit(NULL);
}

int main(int argc, char* argv[]) {
    int num_hilos = (argc > 1) ? atoi(argv[1]) : 1;
    
    int n = 28; 

    int E[] = {
        1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 
        6, -6, 7, -7, 8, -8, 9, -9, 10, -10, 
        11, -11, 12, -12, 13, -13, 14, -14  // total: 28 elementos
    };
    
    pthread_t hilos[num_hilos];
    DatosHilo datos[num_hilos];
    
    // 1L << n calcula 2 elevado a la n
    long total_comb = 1L << n;
    long por_hilo = total_comb / num_hilos;

    for (int i = 0; i < num_hilos; i++) {
        datos[i].E = E; 
        datos[i].n = n;
        datos[i].inicio = i * por_hilo;
        datos[i].fin = (i == num_hilos - 1) ? total_comb : (i + 1) * por_hilo;
        pthread_create(&hilos[i], NULL, resolver_suma, &datos[i]);
    }

    int total_global = 0;
    for (int i = 0; i < num_hilos; i++) {
        pthread_join(hilos[i], NULL);
        total_global += datos[i].contador;
    }
    
    printf("Tamaño del conjunto (n): %d\n", n);
    printf("Subconjuntos que suman cero: %d\n", total_global);
    return 0;
}
