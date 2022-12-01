#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getprocinfo.h"

static void filter(char* value){
    int i = 0;
    do i++; while(value[i]!=':');
    do i++; while(value[i]==' ');
    
    for(int j=0; value[j]!='\n';j++)
       value[j] = value[j+i];
    value[strcspn(value,"\n")] = '\0';
}

void getCpuInfo(char* description, char* value){
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

static void mbConverter(int* value){
    *value /= 1024;
}


int getMemoryInfo(char* description){
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

