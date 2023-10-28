#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ROWS 3
#define COLS 9

// Matriz de entrada
int matrix[ROWS][COLS] = {
    {1, 2, 3, 1, 3, 5, 2, 4, 6},
    {4, 5, 6, 7, 9, 11, 8, 10, 12},
    {7, 8, 9, 13, 15, 17, 14, 16, 18}
};

long int results[ROWS];  // Almacenar resultados de los hilos

// Función que realiza la multiplicación de una fila de la matriz
void* multiply_row(void* arg) {
    long int row_number = *((int*)arg);
    long int result = 1;

    // Multiplicación de los elementos de la fila
    for (int j = 0; j < COLS; j++) {
        result *= matrix[row_number][j];
    }

    // Mostrar el resultado en pantalla
    printf("Hilo: Multiplicación de la fila %ld: %ld\n", row_number, result);

    // Almacenar el resultado en el array de resultados
    results[row_number] = result;
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[ROWS];
    int thread_args[ROWS];

    // Crear y ejecutar los hilos secundarios
    for (int i = 0; i < ROWS; i++) {
        thread_args[i] = i;
        pthread_create(&threads[i], NULL, multiply_row, &thread_args[i]);
    }

    // Esperar a que los hilos secundarios terminen
    for (int i = 0; i < ROWS; i++) {
        pthread_join(threads[i], NULL);
    }

    // Mostrar los resultados
    printf("Resultados:\n");
    for (int i = 0; i < ROWS; i++) {
        printf("Hilo %d: %ld\n", i, results[i]);
    }

    return 0;
}

