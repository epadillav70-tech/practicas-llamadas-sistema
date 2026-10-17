/* Práctica 5: prioridades con nice()/setpriority().
 * Dos hijos hacen el mismo cálculo; uno con nice 0 y otro con nice 15. Mide cuánto CPU
 * consigue cada uno en un tiempo fijo. Para que la diferencia se note, fija ambos a un solo núcleo:
 *     taskset -c 0 ./05_prioridad       (en Linux)
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <sys/resource.h>
#include <sys/wait.h>

static void trabajar(int nice_val, int segundos) {
    setpriority(PRIO_PROCESS, 0, nice_val);
    time_t fin = time(NULL) + segundos;
    while (time(NULL) < fin)
        for (volatile int i = 0; i < 100000; i++)
            ;
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);
    printf("[PID %d nice %2d] CPU usada: %ld.%06ld s\n", getpid(),
           getpriority(PRIO_PROCESS, 0), (long)ru.ru_utime.tv_sec, (long)ru.ru_utime.tv_usec);
    _exit(0);
}

int main(void) {
    int niveles[2] = {0, 15};
    for (int i = 0; i < 2; i++) {
        pid_t pid = fork();
        if (pid < 0) {
            perror("fork");
            return 1;
        }
        if (pid == 0)
            trabajar(niveles[i], 5);
    }
    wait(NULL);
    wait(NULL);
    return 0;
}
