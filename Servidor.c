#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <pthread.h>

#define SHARED_MEMORY_KEY 12345
#define SHARED_MEMORY_SIZE 1024

sem_t* server_sem;
sem_t* client_sem;
char* shared_memory;

void* client_handler(void* arg) {
    int client_id = *((int*)arg);
    
    while (1) {
        sem_wait(&client_sem[client_id]);
        printf("Server received from Client %d: %s\n", client_id, shared_memory);
        sem_post(&server_sem[client_id]);
    }
    
    pthread_exit(NULL);
}

int main() {
    int num_clients = 3;  // Change this to the desired number of clients.
    
    // Initialize semaphores and shared memory
    server_sem = (sem_t*)malloc(num_clients * sizeof(sem_t));
    client_sem = (sem_t*)malloc(num_clients * sizeof(sem_t));
    
    for (int i = 0; i < num_clients; i++) {
        sem_init(&server_sem[i], 0, 0);
        sem_init(&client_sem[i], 0, 1);
    }
    
    int shmid = shmget(SHARED_MEMORY_KEY, SHARED_MEMORY_SIZE, IPC_CREAT | 0666);
    shared_memory = shmat(shmid, NULL, 0);
    
    pthread_t client_threads[num_clients];
    int client_ids[num_clients];
    
    for (int i = 0; i < num_clients; i++) {
        client_ids[i] = i;
        pthread_create(&client_threads[i], NULL, client_handler, &client_ids[i]);
    }
    
    while (1) {
        // Server main loop - continue running to handle client messages.
        // You can add your logic here for processing client messages.
    }
    
    // Cleanup and cleanup code as needed.
    
    return 0;
}

