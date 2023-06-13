#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <string.h>
#include <errno.h>

float calculaTempo(struct timeval *inicio, struct timeval *fim)
{
    return (fim->tv_sec - inicio->tv_sec) + (fim->tv_usec - inicio->tv_usec) / 1000000.0;
}

int main(void) {
    struct timeval inicio, fim, inicioTotal, fimTotal;
    char caminhoExecutavel[50], argumento[75];

    gettimeofday(&inicioTotal, NULL);
    while (scanf("%s %s", caminhoExecutavel, argumento) == 2) {
        gettimeofday(&inicio, NULL);
        pid_t pid = fork();
        if (pid == 0) {
            fclose(stdin);
            execl(caminhoExecutavel, caminhoExecutavel, argumento, NULL);
            printf("> Erro: %s\n", strerror(errno));
            fflush(stdout);
            _exit(errno);
        } else {
            int status;
            pid_t childPid = wait(&status);
            gettimeofday(&fim, NULL);
            printf("> Demorou %.1f segundos, retornou %d\n", calculaTempo(&inicio, &fim), WEXITSTATUS(status));
        }
        fflush(stdout);
    }

    gettimeofday(&fimTotal, NULL);
    printf(">> O tempo total foi de %.1f segundos\n", calculaTempo(&inicioTotal, &fimTotal));

    exit(0);
}






