ECHO OFF

IF [%1] == [] ECHO "No operation specified!" & EXIT 1

SET "needdoxygen=0"
IF [%1] EQU "docs" SET "needdoxygen=1"
IF [%1] EQU "pack" SET "needdoxygen=1"
IF %needdoxygen% EQU 1 SET "wingetdeps= doxygen graphviz texlive perl"

REM install chocolatey
@"%SystemRoot%\System32\WindowsPowerShell\v1.0\powershell.exe" -NoProfile -InputFormat None -ExecutionPolicy Bypass -Command "[System.Net.ServicePointManager]::SecurityProtocol = 3072; iex ((New-Object System.Net.WebClient).DownloadString('https://community.chocolatey.org/install.ps1'))" && SET "PATH=%PATH%;%ALLUSERSPROFILE%\chocolatey\bin"

REM install dependencies
choco install mingw

:: this should ressemble MinGW
SET "CC=gcc"
SET "CXX=g++"

SET "SCRIPT_DIR=%~dp0"
SET "REPO=%SCRIPT_DIR%.."

where gcc 

EXIT 1
cmake -P "%SCRIPT_DIR%cmake\%1.cmake"
