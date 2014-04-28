#include "../../main.h"


void sortStack(pSTACK first , pSTACK second, ppQUEUE queue,int(* cmp)(void *p1, void *p2, void *typeCmp), int cmpKey1, int cmpKey2){

	pDATA elem;

	int cont = 0;
	/* while ( first && second ) { */
	while ( cont < (4096/sizeof(DATA))) {
		elem = malloc(sizeof(DATA));

		if ( (*cmp)(first->data,second->data,&cmpKey1) == 0 )
		{
			pop(&first,&elem);
			//se o primeiro criterio eh igual, tenta com o segundo
			if ( (*cmp)(first->data,second->data,&cmpKey2) == 0 )
			{
				//se o segundo eh igual, insere o first, na proxima vai o second
				 pop(&first,&elem);
			}
			else if ( (*cmp)(first->data,second->data,&cmpKey2) < 0 )
			{
				pop(&first,&elem);
			}
			else //se eh maior
			{
				pop(&second,&elem);
			}
 
		}
		else if ( (*cmp)(first->data,second->data,&cmpKey1) < 0 ) 
		{
			pop(&first,&elem);
		}
		else //se nao eh maior
		{
			pop(&second,&elem);
		}

		insertQueue(queue, elem);
		/* printf("elem id eh ======>>>>>> %d\n",elem->id); */
		cont++;
	}
	/* printf("tam do cont!!!! %d\n",cont); */
}

//insere no final
void insertQueue(ppQUEUE queue, pDATA elem)
{
	int i=0;
	if(queue)
	{
		ppQUEUE iterator = malloc(sizeof(ppQUEUE));
		iterator = queue;

		while(*iterator)
		{
			i++;
			/* printf("qtd %d\n",i); */

			iterator = &(*iterator)->next;
		}

		//if is the first
		/* if(!iterator) */
		/* { */
		/* 	iterator = malloc(sizeof(pQUEUE)); */
		/* 	iterator->data = malloc(sizeof(pDATA)); */
		/* 	iterator->data = elem; */
		/* 	iterator->next = NULL; */
		/* } */
		/* else */
		/* { */
			*iterator = malloc(sizeof(QUEUE));
			((*iterator))->data = malloc(sizeof(DATA));
			memcpy((*iterator)->data,elem,sizeof(DATA));
			(*iterator)->next = NULL;

			/* printf("id na insertQueue eh %d\n",elem->id); */
		/* } */
	}
}

//The first element put in the stack must be allocated before call this function
/* void push(ppSTACK stack, ppSTACK newStack, pDATA elem) */
/* { */
/* 	if(stack) */
/* 	{ */
/* 		(*newStack)->next = malloc(sizeof(pSTACK)); */
/* 		(*newStack)->next = *stack; */
/* 		(*newStack)->data = malloc(sizeof(DATA)); */
/*        		memcpy((*newStack)->data,elem,sizeof(DATA)); */
/* 		stack = newStack; */
/* 	} */
/* } */


void pop(ppSTACK ppStack, ppDATA elem)
{
	//get head element
	/* if(stack->data) */
	/* { */
       		memcpy(*elem,(*ppStack)->data,sizeof(DATA));
		/* printf("elem para o pop eh %d",(*ppStack)->data->id); */
	/* } */

	//chose new head
	/* if(stack->next ) */
	/* { */
		/* (stack)->data = &(*stack)->next->data; */
		*ppStack = (*ppStack)->next;
		/* printf("elem para o pop no next eh %d",(*ppStack)->data->id); */
	/* } */
	/* else //no more elements */
	/* { */
	/* 	free(stack->data); */
	/* 	free(stack->next); */
	/* 	free(stack); */
	/* } */

		/* printf("elem id22222 eh ======>>>>>> %d\n",(*elem)->id); */
}

