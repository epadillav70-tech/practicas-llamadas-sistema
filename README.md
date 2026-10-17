# Prácticas: llamadas al sistema para administrar procesos

Material para practicar en **Linux, UNIX (macOS, FreeBSD, Solaris/illumos) y Windows**, más un simulador web interactivo.

**Simulador:** abre `index.html` (o la página publicada con GitHub Pages). Permite escribir un programa con `fork`, `exec`, `wait`, `sleep` y `exit`, ejecutarlo paso a paso y ver el árbol de procesos, zombis y huérfanos.

## Linux / UNIX (carpeta `linux/`)

Requiere `gcc` (en Windows, usar WSL2: `wsl --install`).

```bash
cd linux
make            # compila todo
./01_fork_wait
```

| Archivo | Tema | Llamadas |
|---|---|---|
| `01_fork_wait.c` | Crear hijo y esperarlo | `fork`, `waitpid`, `_exit` |
| `02_fork_exec.c` | Ejecutar otro programa | `fork`, `execlp`, `wait` |
| `03_zombi.c` | Zombis y huérfanos | `fork`, `sleep` (observar con `ps`) |
| `04_senales.c` | Señales | `sigaction`, `kill`, `pause` |
| `05_prioridad.c` | Prioridades | `setpriority`, `getrusage` |
| `06_pipe.c` | Comunicación padre-hijo | `pipe`, `read`, `write` |
| `07_arbol.c` | Árbol de procesos (2ⁿ) | `fork` consecutivos |

Herramientas de observación: `ps -ef --forest`, `pstree -p`, `top`, `strace -f ./programa` (en Solaris: `truss`).

## Windows (carpeta `windows/`)

Requiere MinGW (`gcc`) o Visual Studio (Developer Command Prompt).

```bat
cd windows
build.bat
01_createprocess.exe notepad.exe
```

| Archivo | Tema | Llamadas |
|---|---|---|
| `01_createprocess.c` | Crear y esperar proceso | `CreateProcess`, `WaitForSingleObject` |
| `02_prioridad.c` | Prioridades y afinidad | `SetPriorityClass` (vía flags), `SetProcessAffinityMask`, `GetProcessTimes` |
| `03_pipe.c` | Tubería anónima | `CreatePipe`, `ReadFile` |

Observación: Administrador de tareas, Process Explorer, `tasklist`.

## Equivalencias

| Operación | POSIX | Windows |
|---|---|---|
| Crear | `fork()` + `exec*()` | `CreateProcess()` |
| Esperar | `wait()`, `waitpid()` | `WaitForSingleObject()` |
| Terminar | `exit()`, `kill()` | `ExitProcess()`, `TerminateProcess()` |
| PID | `getpid()`, `getppid()` | `GetCurrentProcessId()` |
| Prioridad | `nice()`, `setpriority()` | `SetPriorityClass()` |
| Comunicación | `pipe()`, señales | `CreatePipe()`, eventos |

## Informe sugerido por práctica

Código, salida, diagrama del árbol de procesos, y conclusión (por ejemplo, comparar `fork` con `CreateProcess`).
