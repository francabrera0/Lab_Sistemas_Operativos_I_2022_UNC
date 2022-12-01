#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/getprocinfo.h"
#include "../include/cJSON.h"


static void mbConverter(int* value){
    *value /= 1024;
}

static int getMemoryInfo(char* description){
    FILE* memInfo;
    memInfo =  fopen("/proc/meminfo","r");
    char desc[20];
    int value;

    while(fscanf(memInfo, "%s %d %*s", desc, &value)){
        if(!strcmp(description,desc)){
            fclose(memInfo);
            mbConverter(&value);
            return value;
        }
    }
    fclose(memInfo);
    return -1;
}

static void filter(char* value){
    int i = 0;
    do i++; while(value[i]!=':');
    do i++; while(value[i]==' ');
    
    for(int j=0; value[j]!='\n';j++)
       value[j] = value[j+i];
    value[strcspn(value,"\n")] = '\0';
}

static void getCpuInfo(char* description, char* value){
    FILE* information;
    information = fopen("/proc/cpuinfo","r");
    char valueTemp[64];

    while(fgets(valueTemp,64,information)){
        if(strstr(valueTemp,description)){
            fclose(information);
            filter(valueTemp);
            strcpy(value, valueTemp);
            break;
        }
    }
}


void getInfo(int jsonFlag){

    char* identifiers[5] = {"MemTotal:", "MemFree:", "MemAvailable:", "SwapTotal:", "SwapFree:"};
    int values[5];
    for(int i=0; i<5; i++)
        values[i]=getMemoryInfo(identifiers[i]);

    int value = getMemoryInfo(identifiers[3])-getMemoryInfo(identifiers[4]);

    char* cpuModel = (char*)malloc(sizeof(char)*64);
    char* cpuCores = (char*)malloc(sizeof(char)*2);
    char* siblings = (char*)malloc(sizeof(char)*2);

    char* identifiersCPU[3] = {"model name", "cpu cores", "siblings"};
    char* valuesCPU[3] = {cpuModel, cpuCores, siblings};

    for(int i=0; i<3; i++)
        getCpuInfo(identifiersCPU[i], valuesCPU[i]);

    if(!jsonFlag){
        printf("Información de memoria RAM solicitada en el punto i: \n");
        for(int i=0; i<3; i++)
            printf("%s %d MB\n", identifiers[i], values[i]);

        printf("Información de memoria SWAP solicitada en el punto ii: \n");
        
        printf("Swap Busy: %d MB \n", value);

        printf("Información de CPU solicitada en el punto iii: \n");

        for(int i=0; i<3; i++){
            printf("%s : %s\n", identifiersCPU[i], valuesCPU[i]);
            free(valuesCPU[i]);
        }

        printf("\n");
    }

    else{
        cJSON* root = cJSON_CreateObject();
        cJSON* ramMemory = cJSON_CreateObject();
        cJSON* swapMemory = cJSON_CreateObject();
        cJSON* cpu = cJSON_CreateObject();

        cJSON_AddItemToObject(root,"Información de memoria RAM",ramMemory);
        cJSON_AddNumberToObject(ramMemory, "Memoria Total",values[0]);
        cJSON_AddNumberToObject(ramMemory, "Memoria Libre",values[1]);
        cJSON_AddNumberToObject(ramMemory, "Memoria Disponible",values[2]);

        cJSON_AddItemToObject(root,"Información de memoria SWAP",swapMemory);
        cJSON_AddNumberToObject(swapMemory, "Swap Ocupada",value);

        cJSON_AddItemToObject(root,"Información de CPU",cpu);
        cJSON_AddStringToObject(cpu, "Modelo",valuesCPU[0]);
        cJSON_AddStringToObject(cpu, "Nucleos",valuesCPU[1]);
        cJSON_AddStringToObject(cpu, "Hilos",valuesCPU[2]);

        puts(cJSON_Print(root));

        for (int i=0; i<3; ++i)
            free(valuesCPU[i]);
    }
    
}