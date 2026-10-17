/* Práctica 1: fork() + wait(). Crea un proceso hijo y espera a que termine. */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    printf("[padre] PID=%d antes del fork\n", getpid());
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        printf("[hijo ] PID=%d, PPID=%d\n", getpid(), getppid());
        _exit(7);
    }

    int estado;
    waitpid(pid, &estado, 0);
    if (WIFEXITED(estado))
        printf("[padre] el hijo %d terminó con código %d\n", pid, WEXITSTATUS(estado));
    return 0;
}
