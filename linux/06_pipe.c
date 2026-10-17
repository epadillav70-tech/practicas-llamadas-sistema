/* Práctica 6: comunicación padre-hijo con pipe().
 * El padre escribe un mensaje; el hijo lo lee y lo muestra.
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void) {
    int fd[2]; /* fd[0] = lectura, fd[1] = escritura */
    if (pipe(fd) < 0) {
        perror("pipe");
        return 1;
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        close(fd[1]);
        char buf[128];
        ssize_t n = read(fd[0], buf, sizeof buf - 1);
        if (n > 0) {
            buf[n] = '\0';
            printf("[hijo ] recibí: \"%s\"\n", buf);
        }
        close(fd[0]);
        _exit(0);
    }

    close(fd[0]);
    const char *msg = "hola desde el padre";
    write(fd[1], msg, strlen(msg));
    close(fd[1]);
    waitpid(pid, NULL, 0);
    return 0;
}
