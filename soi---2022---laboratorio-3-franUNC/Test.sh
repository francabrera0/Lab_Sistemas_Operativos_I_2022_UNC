#!/bin/bash
cd bin/

echo ""
echo "$(tput setaf 0)$(tput setab 7)Comando de ayuda$(tput sgr 0)"
./Main -h

echo ""
echo "$(tput setaf 0)$(tput setab 7)Ejecución del primer ejercicio$(tput sgr 0)"
./Main -s

echo ""
echo "$(tput setaf 0)$(tput setab 7)Ejecución del primer ejercicio formato JSON$(tput sgr 0)"
./Main -s -j

echo ""
echo "$(tput setaf 0)$(tput setab 7)Ejecución del segundo ejercicio$(tput sgr 0)"
./Main -a

echo ""
echo "$(tput setaf 0)$(tput setab 7)Ejecución del segundo ejercicio formato JSON$(tput sgr 0)"
./Main -a -j

echo ""
echo "$(tput setaf 0)$(tput setab 7)Información de archivos de sistema$(tput sgr 0)"
./Main -d