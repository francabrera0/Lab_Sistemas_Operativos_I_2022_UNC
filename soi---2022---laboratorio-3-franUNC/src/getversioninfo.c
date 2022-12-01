#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "../include/getversioninfo.h"
#include "../include/cJSON.h"

static int getSizeFile(FILE* file){
	char c;
	int size = 0;

	for(c=getc(file); c!=EOF; c=getc(file))
		size++;
	rewind(file);

	return size;
}

static void toUppercase(char* str, int size){
	for(int i=0; i<size; i++)
		if(str[i]>='a' && str[i]<='z')
			str[i] -= 32;
}

static void removeChar(char* str){
    int place = strcspn(str,"(),");

    if(place != strlen(str)){
        while(str[place]!='\0'){
            str[place] = str[place+1];
            place++;
        }
    removeChar(str);
    }
}

static void printList(char* str, int size){
	char strToPrint[size];
	strcpy(strToPrint,str);

	removeChar(strToPrint);

	char* token = strtok(strToPrint, " ");
	
	while(token!=NULL){
		printf("%s\n", token);
		token = strtok(NULL, " ");
	}
	printf("\n");
}

void getVersion(int jsonFlag){
	
	FILE* file = fopen("/proc/version","r");
	int size = getSizeFile(file);

	char* version = (char*)malloc(sizeof(char)*size);

	fgets(version,size,file);

	toUppercase(version, size);

	if(!jsonFlag){
		printList(version,size);
	}
	else{
		cJSON* ver = cJSON_CreateObject();
		cJSON_AddStringToObject(ver,"version del SO",version);

		puts(cJSON_Print(ver));
	}
	
	free(version);
}