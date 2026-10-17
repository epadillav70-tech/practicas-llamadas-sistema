/* Práctica 2: fork() + exec(). El hijo reemplaza su imagen por otro programa (ls -l). */
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        printf("[hijo ] PID=%d ejecutará ls -l\n", getpid());
        execlp("ls", "ls", "-l", (char *)NULL);
        perror("execlp"); /* solo se llega aquí si exec falla */
        _exit(127);
    }

    wait(NULL);
    printf("[padre] ls terminó\n");
    return 0;
}
