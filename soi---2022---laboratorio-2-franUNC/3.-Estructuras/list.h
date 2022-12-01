#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct NODE{
	int data;
	struct NODE* next;
} NODE;

typedef struct LIST{
	NODE* root;
	NODE* final;
	int size;
	char* listname;
} LIST;

void init(LIST* list, char* name);
int isEmpty(LIST* list);
void pushBack(LIST* list, int dataToSave);
void printList(LIST* list);

#endif