#include "../main.h"

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

		cont++;
	}

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

			iterator = &(*iterator)->next;
		}

			*iterator = malloc(sizeof(QUEUE));
			((*iterator))->data = malloc(sizeof(DATA));
			memcpy((*iterator)->data,elem,sizeof(DATA));
			(*iterator)->next = NULL;

	}
}



void pop(ppSTACK ppStack, ppDATA elem)
{

       		memcpy(*elem,(*ppStack)->data,sizeof(DATA));

		*ppStack = (*ppStack)->next;

}

