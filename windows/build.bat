@echo off
rem Compila las prácticas con MinGW (gcc) o, si no hay gcc, con MSVC (cl) desde "Developer Command Prompt".
where gcc >nul 2>nul
if %errorlevel%==0 (
  for %%f in (*.c) do gcc -Wall -O2 %%f -o %%~nf.exe
) else (
  for %%f in (*.c) do cl /nologo /W3 %%f
)
echo Listo.
