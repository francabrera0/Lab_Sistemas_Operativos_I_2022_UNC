#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getprocinfo.h"

#define NUMDATA 3
#define NUMDATASWAP 2

void RamMemoryInformation(void);
void SwapMemoryInformation(void);
void CpuInformation(void);

int main(void){
    printf("Información de memoria RAM solicitada en el punto i: \n");
    RamMemoryInformation();
    printf("Información de memoria SWAP solicitada en el punto ii: \n");
    SwapMemoryInformation();
    printf("Información de CPU solicitada en el punto iii: \n");
    CpuInformation();
}


void RamMemoryInformation(void){

    char* identifiers[NUMDATA] = {"MemTotal:", "MemFree:", "MemAvailable:"};
    int values[NUMDATA];

    for(int i=0; i<NUMDATA; i++)
        values[i]=getMemoryInfo(identifiers[i]);

    for(int i=0; i<NUMDATA; i++)
        printf("%s %d MB\n", identifiers[i], values[i]);
}


void SwapMemoryInformation(void){

    char* identifiers[NUMDATASWAP] = {"SwapTotal:", "SwapFree:"};
    int value = getMemoryInfo(identifiers[0])-getMemoryInfo(identifiers[1]);
    printf("Swap Busy: %d MB \n", value);
}


void CpuInformation(void){

    char* cpuModel = (char*)malloc(sizeof(char)*64);
    char* cpuCores = (char*)malloc(sizeof(char)*2);
    char* siblings = (char*)malloc(sizeof(char)*2);

    char* identifiers[NUMDATA] = {"model name", "cpu cores", "siblings"};
    char* values[NUMDATA] = {cpuModel, cpuCores, siblings};

    for(int i=0; i<NUMDATA; i++)
        getCpuInfo(identifiers[i], values[i]);

    for(int i=0; i<NUMDATA; i++){
        printf("%s : %s\n", identifiers[i], values[i]);
        free(values[i]);
    }
}

