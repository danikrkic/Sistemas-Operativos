#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

#define SHARED_MEMORY_KEY 12345
#define SHARED_MEMORY_SIZE 1024

sem_t* server_sem;
sem_t* client_sem;
char* shared_memory;

int main() {
    int client_id = 0;  // Change this to the desired client ID.
    
    // Attach to the existing semaphores and shared memory
    server_sem = (sem_t*)malloc(sizeof(sem_t));
    client_sem = (sem_t*)malloc(sizeof(sem_t));
    
    sem_init(server_sem, 0, 0);
    sem_init(client_sem, 0, 1);
    
    int shmid = shmget(SHARED_MEMORY_KEY, SHARED_MEMORY_SIZE, 0666);
    shared_memory = shmat(shmid, NULL, 0);
    
    // Prepare the message to send
    char message[11];
    sprintf(message, "Client %d", client_id);
    
    while (1) {
        sem_wait(server_sem);
        strcpy(shared_memory, message);
        sem_post(client_sem);
    }
    
    // Cleanup and cleanup code as needed.
    
    return 0;
}

