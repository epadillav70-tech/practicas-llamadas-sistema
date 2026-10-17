/* Práctica 3: proceso zombi y huérfano.
 *   ./03_zombi zombi    -> el hijo termina y el padre NO hace wait(): estado Z en `ps`.
 *   ./03_zombi huerfano -> el padre termina primero: el hijo pasa a ser adoptado por init/systemd.
 * Mientras duerme, observa en otra terminal:  ps -o pid,ppid,stat,cmd --ppid <PID> o  ps aux | grep 03_zombi
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int huerfano = (argc > 1 && strcmp(argv[1], "huerfano") == 0);
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    }
    if (pid == 0) {
        if (huerfano) {
            sleep(1);
            printf("[hijo ] PID=%d, mi PPID ahora es %d (adoptado)\n", getpid(), getppid());
            sleep(10);
        } else {
            printf("[hijo ] PID=%d termina ya (quedará zombi)\n", getpid());
        }
        _exit(0);
    }

    printf("[padre] PID=%d, hijo=%d\n", getpid(), pid);
    if (huerfano) {
        printf("[padre] termino sin esperar al hijo\n");
        return 0;
    }
    printf("[padre] duermo 30 s sin llamar a wait(); revisa `ps` (estado Z)\n");
    sleep(30);
    return 0;
}
