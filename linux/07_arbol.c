/* Práctica 7: árbol de procesos. ¿Cuántos procesos crean estos fork() consecutivos?
 * Predice la respuesta (2^n) antes de ejecutar y compárala con el simulador (index.html).
 */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    fork();
    fork();
    fork();
    printf("PID=%d PPID=%d\n", getpid(), getppid());
    while (wait(NULL) > 0)
        ;
    return 0;
}
