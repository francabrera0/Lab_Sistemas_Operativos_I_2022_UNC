#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>

#include "../include/getprocinfo.h"
#include "../include/getversioninfo.h"

#define OPTION_NUMBER 5

enum FLAGS{s, a, j, d, h};

void fileSystemsInfo(void);
void invalidOpt(void);
void printHelp(void);

int main(int argc, char* argv[]){

	if(argc<2)
		invalidOpt();

	int flags[OPTION_NUMBER];
	
	for(int i=0; i<OPTION_NUMBER; i++)
		flags[i] = 0;

	char option;
	while((option = getopt(argc, argv, "sajdh")) != -1){
		int flag = -1;
		switch(option){

			case 's': 	flag = s;
						break;
			case 'a':	flag = a;
						break;
			case 'j':	flag = j;
						break;
			case 'd':	flag = d;
						break;
			case 'h':	flag = h;
						break;
			default:	invalidOpt();
		}
		
		if(flags[flag]==1)
			invalidOpt();
		flags[flag] = 1;
	}

	if(flags[j]&&!flags[a]&!flags[s])
		invalidOpt();
	if(flags[s])
		getInfo(flags[j]);	
	if(flags[a])
		getVersion(flags[j]);
	if(flags[d])
		fileSystemsInfo();
	if(flags[h])
		printHelp();
}

void fileSystemsInfo(void){
	void* handle = dlopen("../lib/libfilesystems.so",RTLD_LAZY);
	void(*filesystems)();

	if(!handle){
		printf("FALLO DE LIBRERIA");
		exit(EXIT_FAILURE);
	}
	dlerror();

	*(void **)(&filesystems) = dlsym(handle,"getFileSystems");
	(*filesystems)();
	dlclose(handle);
}

void invalidOpt(void){
	printf("Verifique el ingreso de argumentos. Ingrese -h para obtener ayuda\n");
	exit(EXIT_FAILURE);
}

void printHelp(void){
	printf("--------------------------------Laboratorio N°3-----------------------------------\n");
	printf("Comandos permitidos:\n");
	printf("-s	ejecuta el ejercicio n° 1 del laboratorio 2\n");
	printf("-a	ejecuta el ejercicio n° 2 del laboratorio 2\n");
	printf("-j	modifica el formato de salida de las ejecuciones anteriores (formato JSON)\n");
	printf("-d	muestra información sobre los archivos de sistema (formato JSON)\n");
	printf("-h	obtener ayuda sobre los comandos\n");
	printf("----------------------------------------------------------------------------------\n");
}