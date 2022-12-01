#include <stdio.h>
#include <stdlib.h>
#include "list.h"

int main(){
	LIST* lista1;
	lista1 = (LIST*)malloc(sizeof(LIST));
	LIST* lista2;
	lista2 = (LIST*)malloc(sizeof(LIST));
	init(lista1,"lista1");
	init(lista2,"lista2");

	printList(lista1);
	printList(lista2);

	pushBack(lista1,2);
	pushBack(lista2,10);
	pushBack(lista2,13);
	pushBack(lista1,3);
	pushBack(lista1,4);
	pushBack(lista2,8);
	printList(lista1);
	printList(lista2);

}
