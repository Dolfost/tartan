IF [%1] == [] ECHO "No operation specified!" & EXIT 1

SET "needdoxygen=0"
IF [%1] EQU "docs" SET "needdoxygen=1"
IF [%1] EQU "pack" SET "needdoxygen=1"
IF %needdoxygen% EQU 1 SET "wingetdeps= doxygen graphviz texlive perl"

:: this should ressemble MinGW
SET "CC=gcc"
SET "CXX=g++"

SET "SCRIPT_DIR=%~dp0"
SET "REPO=%SCRIPT_DIR%.."

cmake -P "%SCRIPT_DIR%cmake\%1.cmake"
