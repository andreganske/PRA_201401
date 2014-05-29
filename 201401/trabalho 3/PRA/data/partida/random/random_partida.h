/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske and Wesklei Migliorini
 */

#ifndef _random_partida_h
#define _random_partida_h

// Including some library
#include "../../../main.h"


typedef struct STACK *pSTACK;
typedef struct STACK **ppSTACK;

typedef struct STACK{
	pDATA data;
	pSTACK next;
}STACK;

typedef struct QUEUE *pQUEUE;
typedef struct QUEUE **ppQUEUE;

typedef struct QUEUE{
	pDATA data;
	pQUEUE next;
}QUEUE;

//Function definition
void pop(ppSTACK stack, ppDATA elem);
void push(ppSTACK stack, ppSTACK newStack, pDATA elem);
void insertQueue(ppQUEUE queue, pDATA elem);
void sortStack(pSTACK first , pSTACK second, ppQUEUE queue,int(* cmp)(void *p1, void *p2, void *typeCmp), int cmpKey1, int cmpKey2);
void randomPartida(ppPARTIDA ppPartida);
void randomDate(pDATE date);
void randomTimeName(char* timeName);
void randomScore(int* score);
void randomqtdPayer(int* qtdPayer);
void randomPlace(char* place);

#endif
