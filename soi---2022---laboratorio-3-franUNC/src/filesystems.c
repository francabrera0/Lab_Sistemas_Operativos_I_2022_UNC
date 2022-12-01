#include <stdio.h>
#include <stdlib.h>
#include "../include/filesystems.h"
#include "../include/cJSON.h"

void getFileSystems(void){

	FILE* file;
	file = fopen("/proc/filesystems","r");

	cJSON* root;
	root = cJSON_CreateObject();
	cJSON* fs;
	fs = cJSON_CreateObject();
	cJSON_AddItemToObject(root,"filesystems",fs);

	char valueTemp[40];
    char number[5];
    int counter = 1;
    
    while(fgets(valueTemp,40,file)){
        sprintf(number, "%d", counter);
        cJSON_AddItemToObject(fs,  number, cJSON_CreateString(valueTemp));
        counter++;
    }

	puts(cJSON_Print(root));
	free(root);
	fclose(file);

}