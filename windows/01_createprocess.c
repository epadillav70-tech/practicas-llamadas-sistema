/* Práctica W1: CreateProcess() + WaitForSingleObject().
 * Equivale a fork()+exec()+wait() de POSIX. Uso: 01_createprocess.exe [comando]
 */
#include <windows.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char **argv) {
    char cmd[MAX_PATH] = "notepad.exe";
    if (argc > 1) {
        cmd[0] = '\0';
        for (int i = 1; i < argc; i++) {
            strncat(cmd, argv[i], sizeof cmd - strlen(cmd) - 2);
            strncat(cmd, " ", sizeof cmd - strlen(cmd) - 1);
        }
    }

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof si);
    si.cb = sizeof si;
    ZeroMemory(&pi, sizeof pi);

    printf("[padre] PID=%lu crea: %s\n", GetCurrentProcessId(), cmd);
    if (!CreateProcessA(NULL, cmd, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi)) {
        fprintf(stderr, "CreateProcess falló (%lu)\n", GetLastError());
        return 1;
    }
    printf("[padre] hijo PID=%lu; espero a que termine...\n", pi.dwProcessId);

    WaitForSingleObject(pi.hProcess, INFINITE);

    DWORD codigo = 0;
    GetExitCodeProcess(pi.hProcess, &codigo);
    printf("[padre] el hijo terminó con código %lu\n", codigo);

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    return 0;
}
