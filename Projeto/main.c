#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>
#include <time.h>
#include <stdbool.h>

// Variáveis globais para compartilhar entre as threads
#define BUFFER_SIZE 10

//Macros ac
#define AC_ON_TEMP 15
#define AC_ON 1
#define AC_OFF 0

// Variáveis Temperatura
int bufferTemp[BUFFER_SIZE];
int idxTemp = 0;
int globalCountTemp = 0;
bool quitTemp = false;

// Variáveis Luminosidade
int bufferLum[BUFFER_SIZE];
int idxLum = 0;
int globalCountLum = 0;
bool quitLum = false;

// pthread
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void mysleep(unsigned int seconds)
{
    struct timespec tempo;
    tempo.tv_sec = seconds;
    tempo.tv_nsec = 0;

    if (nanosleep(&tempo, NULL) != 0) {
        perror("mysleep");
    }
}

void controla_ac(int estado)
{
    if(estado == 0)
        printf("AC [OFF]\n");
    else
        printf("AC [ON]\n");
}

void controla_focos(int luminosidade)
{
    if(luminosidade > 0 && luminosidade <= 25)
        printf("FOCOS LUM [ON] -> 100%%\n");
    else if(luminosidade > 25 && luminosidade <= 50)
        printf("FOCOS LUM [ON] -> 75%%\n");
    else if(luminosidade == 50 && luminosidade <= 75)
        printf("FOCOS LUM [ON] -> 50%%\n");
    else if(luminosidade == 75 && luminosidade <= 100)
        printf("FOCOS LUM [OFF] -> 0%%\n");
}

void *thread_temperatura(void *arg)
{
    int sensorTemp = (int)arg; // Valor do sensor
    int countMax = 0;
    int numThread = 0;
    if(sensorTemp == 1)
    {
        countMax = 20;
        numThread = 1;
    }
    else if(sensorTemp == 2)
    {
        countMax = 30;
        numThread = 2;
    }

    int count = 0; // numero de repetições
    printf("######################## Temperatura Thread: %d ########################\n", numThread);
    while (count < countMax )
    {
        mysleep(1);
        int temperature = rand() % 25;  // Gerar valor de temperatura
        pthread_mutex_lock(&mutex);

        // Se o buffer estiver cheio, shift para a esquerda
        if (globalCountTemp >= 10)
        {
            for (int i = 0; i < BUFFER_SIZE - 1; i++)
            {
                bufferTemp[i] = bufferTemp[i + 1];
            }
            idxTemp = BUFFER_SIZE - 1;  // Posicionar no último elemento
        }
        bufferTemp[idxTemp] = temperature;
        if(globalCountTemp >= 9)
        {
            printf("Chamei o thread 13 | %s\n", __func__);
            pthread_cond_signal(&cond);
        }

        printf("|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d| %s %i | Thread: %d\n", bufferTemp[0], bufferTemp[1], bufferTemp[2], bufferTemp[3], bufferTemp[4], bufferTemp[5], bufferTemp[6], bufferTemp[7], bufferTemp[8], bufferTemp[9], __func__, getpid(), numThread);

        idxTemp != 9 ? idxTemp++ : idxTemp;
        ++globalCountTemp;
        ++count;

        pthread_mutex_unlock(&mutex);
    }
    if(numThread == 2)
        quitTemp = true;
    printf("pthread_exit: %s\n", __func__);
    pthread_exit(NULL);
}
void *thread13(void *arg)
{
    int sum = 0;
    while(!quitTemp)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        sum = 0;
        // Calcula a média das temperaturas no buffer
        for (int i = 0; i < BUFFER_SIZE; ++i)
        {
            sum += bufferTemp[i];
        }
        printf("\n");
        int media = sum / BUFFER_SIZE;
        printf("-> %s: Média das temperaturas = %d\n", __func__, media);
        controla_ac( media > AC_ON_TEMP ? AC_ON : AC_OFF);
        printf("-------------------------------------\n");
        pthread_mutex_unlock(&mutex);
    }
    printf("pthread_exit: %s\n", __func__);
    pthread_exit(NULL);
}

void *thread_luminosidade(void *arg)
{
    int sensorLum = (int)arg; // Valor do sensor
    int countMax = 0;
    int numThread = 0;
    if(sensorLum == 1)
    {
        countMax = 20;
        numThread = 1;
    }
    else if(sensorLum == 2)
    {
        countMax = 30;
        numThread = 2;
    }

    int count = 0; // numero de repetições
    printf("######################## Luminosidade Thread: %d ########################\n", numThread);
    while (count < countMax )
    {
        mysleep(1);
        int luminosidade = rand() % 101;  // Gerar valor de temperatura
        pthread_mutex_lock(&mutex);

        // Se o buffer estiver cheio, shift para a esquerda
        if (globalCountLum >= 10)
        {
            for (int i = 0; i < BUFFER_SIZE - 1; i++)
            {
                bufferLum[i] = bufferLum[i + 1];
            }
            idxLum = BUFFER_SIZE - 1;  // Posicionar no último elemento
        }
        bufferLum[idxLum] = luminosidade;
        if(globalCountLum >= 9)
        {
            printf("Chamei o thread 23 | %s\n", __func__);
            pthread_cond_signal(&cond);
        }

        printf("|%d|%d|%d|%d|%d|%d|%d|%d|%d|%d| %s %i | Thread: %d\n", bufferLum[0], bufferLum[1], bufferLum[2], bufferLum[3], bufferLum[4], bufferLum[5], bufferLum[6], bufferLum[7], bufferLum[8], bufferLum[9], __func__, getpid(), numThread);

        idxLum != 9 ? idxLum++ : idxLum;
        ++globalCountLum;
        ++count;

        pthread_mutex_unlock(&mutex);
    }
    if(numThread == 2)
        quitLum = true;
    printf("pthread_exit: %s\n", __func__);
    pthread_exit(NULL);
}
void *thread23(void *arg)
{
    int sum = 0;
    while(!quitLum)
    {
        pthread_mutex_lock(&mutex);
        pthread_cond_wait(&cond, &mutex);
        sum = 0;
        // Calcula a média das temperaturas no buffer
        for (int i = 0; i < BUFFER_SIZE; ++i)
        {
            sum += bufferLum[i];
        }
        printf("\n");
        int media = sum / BUFFER_SIZE;
        printf("-> %s: Média das temperaturas = %d\n", __func__, media);
        controla_focos(media);
        printf("-------------------------------------\n");
        pthread_mutex_unlock(&mutex);
    }
    printf("pthread_exit: %s\n", __func__);
    pthread_exit(NULL);
}

int main()
{
    pthread_t pthread11, pthread12, pthread13, pthread21, pthread22, pthread23;
    pid_t pid1, pid2;


    // printf("Processo pai (PID=%d)\n", getpid());
    pid1 = fork();
    if (pid1 == 0) // Processo filho
    {
        pthread_create(&pthread11, NULL, thread_temperatura, (void*)1);
        pthread_create(&pthread12, NULL, thread_temperatura, (void*)2);
        pthread_create(&pthread13, NULL, thread13, NULL);

        pthread_join(pthread11, NULL);
        pthread_join(pthread12, NULL);
        pthread_join(pthread13, NULL);


        // printf("Processo filho 1 (PID=%d) do pai (PID=%d)\n", getpid(), getppid());
    }
    else if (pid1 > 0)// Processo pai
    {
        pid2 = fork(); // Processo 2
        if (pid2 == 0) // Processo filho do primeiro filho
        {
            pthread_create(&pthread21, NULL, thread_luminosidade, (void*)1);
            pthread_create(&pthread22, NULL, thread_luminosidade, (void*)2);
            pthread_create(&pthread23, NULL, thread23, NULL);

            pthread_join(pthread21, NULL);
            pthread_join(pthread22, NULL);
            pthread_join(pthread23, NULL);
            printf("Processo filho 2 (PID=%d) do filho 1 (PID=%d)\n", getpid(), getppid());
        }
        else if (pid2 > 0) // Pai do segundo filho
        {
            waitpid(pid1, NULL, 0);
            waitpid(pid2, NULL, 0);
            // printf("Processo pai do segundo filho (PID=%d)\n", getpid());
        }
    }
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);

    return 0;
}
