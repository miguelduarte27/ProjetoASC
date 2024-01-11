#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <pthread.h>

int main() {
    pthread_t thread = NULL;
    if (thread == NULL)
        printf("thread não criado!\n");
    return 0;
}

/*int main() {
    pid_t pid1, pid2;

    printf("Processo pai (PID=%d)\n", getpid());

    pid1 = fork();
    if (pid1 == 0) // Processo filho
    {
        
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
}*/
