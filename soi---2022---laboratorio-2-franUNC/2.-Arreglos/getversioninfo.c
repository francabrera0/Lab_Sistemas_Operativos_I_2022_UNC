#include <stdio.h>
#include <string.h>

int getSizeFile(FILE* file){
	char c;
	int size = 0;

	for(c=getc(file); c!=EOF; c=getc(file))
		size++;
	rewind(file);

	return size;
}

void toUppercase(char* str, int size){
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


void printList(char* str, int size){
	char strToPrint[size];
	strcpy(strToPrint,str);

	removeChar(strToPrint);

	char* token = strtok(strToPrint, " ");
	
	while(token!=NULL){
		printf("%s\n", token);
		token = strtok(NULL, " ");
	}
}