#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void init(LIST* list, char* name){
	list -> root = NULL;
	list -> final = NULL;
	list -> size = 0;
	list -> listname = name;
}

int isEmpty(LIST* list){
	if(list->root==NULL)
		return 1;
	return 0;
}

static NODE* createNode(int dataToSave){
	NODE* newNode = (NODE*)malloc(sizeof(NODE));
	newNode -> data = dataToSave;
	newNode -> next = NULL;
	return newNode;
}

void pushBack(LIST* list, int dataToSave){

	NODE *newNode = createNode(dataToSave);

	if(isEmpty(list)){
		list -> root = newNode;
		list -> final = newNode;
	}
	else{
		list -> final -> next = newNode;
		list -> final = newNode;
	}
	list -> size++;
}

void printList(LIST* list){
	printf("------------------------\n");
	printf("%s\n",list -> listname);
	if(!isEmpty(list)){

		NODE* aux = list -> root;

		for(int i=0; i < list ->size; i++){
			printf("%d\n", aux -> data);
			aux = aux -> next;
		}
		printf("------------------------\n");
	}	
	else{ 
		printf("Lista vacia\n");
		printf("------------------------\n");
	}
}