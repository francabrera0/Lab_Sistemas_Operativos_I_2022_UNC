#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getversioninfo.h"


int main(){
	
	FILE* file = fopen("/proc/version","r");
	int size = getSizeFile(file);

	char* version = (char*)malloc(sizeof(char)*size);

	fgets(version,size,file);

	toUppercase(version, size);
	
	printList(version,size);
	
	free(version);
}

