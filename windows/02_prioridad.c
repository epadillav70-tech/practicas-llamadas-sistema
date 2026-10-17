/* Práctica W2: prioridades. Crea dos hijos que consumen CPU, uno con prioridad BELOW_NORMAL
 * y otro con ABOVE_NORMAL, y mide el tiempo de CPU de cada uno.
 * Para que la diferencia se vea, fija ambos a un solo núcleo (afinidad = 1).
 * Uso: 02_prioridad.exe            (padre)
 *      02_prioridad.exe hijo        (trabajo; lo lanza el padre)
 */
#include <windows.h>
#include <stdio.h>
#include <string.h>

static ULONGLONG ft_ms(FILETIME f) {
    ULARGE_INTEGER u;
    u.LowPart = f.dwLowDateTime;
    u.HighPart = f.dwHighDateTime;
    return u.QuadPart / 10000ULL;
}

static int hijo(void) {
    ULONGLONG fin = GetTickCount64() + 5000;
    while (GetTickCount64() < fin)
        ;
    return 0;
}

static void lanzar(const char *exe, DWORD prioridad, PROCESS_INFORMATION *pi) {
    char cmd[MAX_PATH + 16];
    snprintf(cmd, sizeof cmd, "\"%s\" hijo", exe);
    STARTUPINFOA si;
    ZeroMemory(&si, sizeof si);
    si.cb = sizeof si;
    CreateProcessA(NULL, cmd, NULL, NULL, FALSE, CREATE_SUSPENDED | prioridad, NULL, NULL, &si, pi);
    SetProcessAffinityMask(pi->hProcess, 1);
    ResumeThread(pi->hThread);
}

int main(int argc, char **argv) {
    if (argc > 1 && strcmp(argv[1], "hijo") == 0)
        return hijo();

    PROCESS_INFORMATION a, b;
    lanzar(argv[0], BELOW_NORMAL_PRIORITY_CLASS, &a);
    lanzar(argv[0], ABOVE_NORMAL_PRIORITY_CLASS, &b);
    WaitForSingleObject(a.hProcess, INFINITE);
    WaitForSingleObject(b.hProcess, INFINITE);

    FILETIME c, e, k, u;
    GetProcessTimes(a.hProcess, &c, &e, &k, &u);
    printf("BELOW_NORMAL (PID %lu): CPU = %llu ms\n", a.dwProcessId, ft_ms(u));
    GetProcessTimes(b.hProcess, &c, &e, &k, &u);
    printf("ABOVE_NORMAL (PID %lu): CPU = %llu ms\n", b.dwProcessId, ft_ms(u));

    CloseHandle(a.hProcess); CloseHandle(a.hThread);
    CloseHandle(b.hProcess); CloseHandle(b.hThread);
    return 0;
}
