/* Práctica W3: comunicación padre-hijo con una tubería anónima (CreatePipe).
 * El padre lanza "cmd /c echo ..." y lee su salida estándar por la tubería.
 */
#include <windows.h>
#include <stdio.h>

int main(void) {
    SECURITY_ATTRIBUTES sa = {sizeof sa, NULL, TRUE}; /* handles heredables */
    HANDLE rd, wr;
    if (!CreatePipe(&rd, &wr, &sa, 0)) {
        fprintf(stderr, "CreatePipe falló (%lu)\n", GetLastError());
        return 1;
    }
    SetHandleInformation(rd, HANDLE_FLAG_INHERIT, 0); /* el hijo no hereda el extremo de lectura */

    STARTUPINFOA si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof si);
    si.cb = sizeof si;
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdOutput = wr;
    si.hStdError = wr;
    si.hStdInput = GetStdHandle(STD_INPUT_HANDLE);

    char cmd[] = "cmd.exe /c echo hola desde el hijo";
    if (!CreateProcessA(NULL, cmd, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi)) {
        fprintf(stderr, "CreateProcess falló (%lu)\n", GetLastError());
        return 1;
    }
    CloseHandle(wr); /* el padre cierra su copia de escritura para ver el fin de datos */

    char buf[256];
    DWORD n;
    while (ReadFile(rd, buf, sizeof buf - 1, &n, NULL) && n > 0) {
        buf[n] = '\0';
        printf("[padre] recibí: %s", buf);
    }

    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    CloseHandle(rd);
    return 0;
}
