#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int filho = 0;
void atualizaSinalFilho(int sig);

int main(void) {
    signal(SIGUSR1, atualizaSinalFilho);
    signal(SIGUSR2, atualizaSinalFilho);

    pause();

    pid_t child_pid = fork();
    if (child_pid == 0) {
        exit(0);
    }

    pause();
    wait(NULL);
    pause();
}

void atualizaSinalFilho(int sig) {
    filho = sig;
}
