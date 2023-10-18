
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>

#define FILAS 3
#define COLUMNAS 9
#define PERMISOS 0644

// Función para crear un semáforo basada en el ejemplo
int Crea_semaforo(key_t llave, int valor_inicial) {
    int semid = semget(llave, 1, IPC_CREAT | PERMISOS);
    if (semid == -1) {
        return -1;
    }
    semctl(semid, 0, SETVAL, valor_inicial);
    return semid;
}

// Función para realizar operación P basada en el ejemplo
void down(int semid) {
    struct sembuf op_p[] = {0, -1, 0};
    semop(semid, op_p, 1);
}

// Función para realizar operación V basada en el ejemplo
void up(int semid) {
    struct sembuf op_v[] = {0, +1, 0};
    semop(semid, op_v, 1);
}

int main() {
    int shmid, semid, i, j, suma;
    int *memoria;
    key_t clave = ftok(".", 'a');
    pid_t pid;

    // Crear memoria compartida basada en el ejemplo
    shmid = shmget(clave, FILAS * COLUMNAS * sizeof(int), IPC_CREAT | PERMISOS);
    if (shmid == -1) {
        perror("shmget");
        exit(1);
    }

    // Adjuntar a memoria compartida
    memoria = (int *)shmat(shmid, NULL, 0);
    if (memoria == (int *)-1) {
        perror("shmat");
        exit(1);
    }

    // Inicializar matriz
    int matriz[FILAS][COLUMNAS] = {
        {1, 2, 3, 4, 5, 6, 7, 8, 9},
        {1, 3, 5, 7, 9, 11, 13, 15, 17},
        {2, 4, 6, 8, 10, 12, 14, 16, 18}
    };

    // Mostrar matriz y guardar en memoria compartida
    printf("Matriz en proceso padre:\n");
    for (i = 0; i < FILAS; i++) {
        for (j = 0; j < COLUMNAS; j++) {
            memoria[i * COLUMNAS + j] = matriz[i][j];
            printf("%d ", matriz[i][j]);
        }
        printf("\n");
    }

    // Crear semáforo
    semid = Crea_semaforo(clave, 1);
    if (semid == -1) {
        perror("Crea_semaforo");
        exit(1);
    }

    for (i = 0; i < FILAS; i++) {
        pid = fork();
        if (pid == 0) {  // Proceso hijo
            down(semid);

            // Sumar elementos de la fila
            suma = 0;
            printf("Hijo con PID %d y PID del padre %d\n", getpid(), getppid());
            for (j = 0; j < COLUMNAS; j++) {
                printf("%d ", memoria[i * COLUMNAS + j]);
                suma += memoria[i * COLUMNAS + j];
            }
            printf("\nSuma de fila: %d\n", suma);

            up(semid);

            exit(0);
        } else if (pid == -1) {
            perror("fork");
            exit(1);
        }
    }

    // Esperar a que los hijos terminen
    for (i = 0; i < FILAS; i++) {
        wait(NULL);
    }

    // Desadjuntar de la memoria compartida
    if (shmdt(memoria) == -1) {
        perror("shmdt");
        exit(1);
    }

    // Eliminar memoria compartida y semáforo
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID, NULL);

    return 0;
}
