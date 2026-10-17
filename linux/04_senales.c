/* Práctica 4: señales. El proceso atrapa SIGINT y SIGTERM; el hijo recibe SIGUSR1 del padre.
 * Prueba: ./04_senales   y desde otra terminal:  kill -TERM <PID>  o  Ctrl+C
 */
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

static volatile sig_atomic_t recibida = 0;

static void manejador(int sig) {
    recibida = sig;
}

int main(void) {
    struct sigaction sa;
    memset(&sa, 0, sizeof sa);
    sa.sa_handler = manejador;
    sigaction(SIGINT, &sa, NULL);
    sigaction(SIGTERM, &sa, NULL);
    sigaction(SIGUSR1, &sa, NULL);

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        while (!recibida)
            pause();
        printf("[hijo ] recibí la señal %d (%s)\n", (int)recibida, strsignal(recibida));
        _exit(0);
    }

    sleep(1);
    printf("[padre] envío SIGUSR1 al hijo %d\n", pid);
    kill(pid, SIGUSR1);
    waitpid(pid, NULL, 0);

    printf("[padre] PID=%d esperando SIGINT/SIGTERM (10 s)...\n", getpid());
    sleep(10);
    if (recibida)
        printf("[padre] recibí la señal %d (%s)\n", (int)recibida, strsignal(recibida));
    return 0;
}
