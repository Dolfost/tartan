IF [%1] == [] ECHO "No operation specified!" & EXIT 1

IF [%1] EQU "docs" SET "needdoxygen=1"
IF [%1] EQU "pack" SET "needdoxygen=1"
IF %needdoxygen% EQU 1 SET "wingetdeps= doxygen graphviz texlive perl"
powershell -noexit "& ""C:\my_path\yada_yada\run_import_script.ps1"""

:: installing dependencies
winget install cmake git %wingetdeps

SET "SCRIPT_DIR=%~dp0"

SET "REPO=%SCRIPT_DIR.."

cmake -P "%SCRIPT_DIR/cmake/$1.cmake"
