#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
// Variáveis globais para compartilhar entre as threads
#define BUFFER_SIZE 10
int buffer[BUFFER_SIZE];
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *thread11(void *arg) {
    int count = 0;
    int index = 0;

    while (count < 20)
    {
        sleep(1);
        int temperature = rand() % 25;  // Gerar valor de temperatura

        pthread_mutex_lock(&mutex);

        // Se o buffer estiver cheio, shift para a esquerda
        if (count >= 10)
        {
            printf("-----------------------------\n");
            for (int i = 0; i < BUFFER_SIZE - 1; i++)
            {
                buffer[i] = buffer[i + 1];
            }
            index = BUFFER_SIZE - 1;  // Posicionar no último elemento
        } else {
            index = count;  // Usar o índice atual
        }

        buffer[index] = temperature;
        printf("%s: Valor %d armazenado no buffer.\n", __func__, temperature);

        ++count;

        pthread_mutex_unlock(&mutex);
    }
    printf("|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d| -> Depois\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7], buffer[8], buffer[9]);
    pthread_exit(NULL);
}

void *thread12(void *arg) {
    int count = 0;
    int index = 0;

    while (count < 30)
    {
        sleep(1);
        int temperature = rand() % 40;  // Gerar valor de temperatura

        pthread_mutex_lock(&mutex);

        // Se o buffer estiver cheio, shift para a esquerda
        if (count >= 10)
        {
            printf("-----------------------------\n");
            for (int i = 0; i < BUFFER_SIZE - 1; i++)
            {
                buffer[i] = buffer[i + 1];
            }
            index = BUFFER_SIZE - 1;  // Posicionar no último elemento
        } else {
            index = count;  // Usar o índice atual
        }

        buffer[index] = temperature;
        printf("%s: Valor %d armazenado no buffer.\n", __func__, temperature);

        ++count;

        pthread_mutex_unlock(&mutex);
    }
    printf("|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d| -> Depois\n", buffer[0], buffer[1], buffer[2], buffer[3], buffer[4], buffer[5], buffer[6], buffer[7], buffer[8], buffer[9]);
    pthread_exit(NULL);
}


void *thread13(void *arg)
{

}

int main()
{
    pthread_t thread;



    pid_t pid1, pid2;

    printf("Processo pai (PID=%d)\n", getpid());
    pid1 = fork();
    if (pid1 == 0) // Processo filho
    {
        pthread_create(&thread, NULL, thread11, NULL);
        pthread_create(&thread, NULL, thread12, NULL);
        pthread_create(&thread, NULL, thread13, NULL);
        pthread_join(thread, NULL);
        printf("Processo filho 1 (PID=%d) do pai (PID=%d)\n", getpid(), getppid());
    }
    else if (pid1 > 0)// Processo pai
    {
        pid2 = fork(); // Processo 2
        if (pid2 == 0) // Processo filho do primeiro filho
        {
            printf("Processo filho 2 (PID=%d) do filho 1 (PID=%d)\n", getpid(), getppid());
        }
        else if (pid2 > 0) // Pai do segundo filho
        {
            wait(NULL);
            printf("Processo pai do segundo filho (PID=%d)\n", getpid());
        }
        wait(NULL);
    }

    return 0;
}
