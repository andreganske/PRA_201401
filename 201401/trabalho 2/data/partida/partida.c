#include "../../main.h"

typedef struct STACK *pSTACK;
typedef struct STACK **ppSTACK;

typedef struct STACK{
	pDATA topo;
	pSTACK next;
}STACK;

typedef struct QUEUE *pQUEUE;
typedef struct QUEUE **ppQUEUE;

typedef struct QUEUE{
	pDATA data;
	pQUEUE next;
}QUEUE;

pDATA pop(pSTACK stack);
void insertQueue(ppQUEUE queue, pDATA elem);

void sortStack(pSTACK first , pSTACK second, ppQUEUE queue,int(* cmp1)(void *p1, void *p2),int(* cmp2)(void *p1, void *p2)){

	pDATA elem;

	while ( first && second ) {
		if ( (*cmp1)(first->topo,second->topo) == 0 )
		{
			elem = pop(first);
			//se o primeiro criterio eh igual, tenta com o segundo
			if ( (*cmp2)(first->topo,second->topo) == 0 )
			{
				//se o segundo eh igual, insere o first, na proxima vai o second
				elem = pop(first);
			}
			else if ( (*cmp2)(first->topo,second->topo) < 0 )
			{
				elem = pop(first);
			}
			else //se eh maior
			{
				elem = pop(second);
			}
 
		}
		else if ( (*cmp1)(first->topo,second->topo) < 0 ) 
		{
			elem = pop(first);
		}
		else //se nao eh maior
		{
			elem = pop(second);
		}
		insertQueue(queue, elem);
	}
}

//insere no final
void insertQueue(ppQUEUE queue, pDATA elem)
{
	if(queue)
	{
		pQUEUE iterator = (*queue)->next;

		while(iterator && iterator->next)
		{
			iterator = iterator->next;
		}

		iterator->next = malloc(sizeof(QUEUE));
		iterator->next->data = elem;
		iterator->next->next = NULL;
	}
}


pDATA pop(pSTACK stack)
{
	pDATA elem = malloc(sizeof(DATA));;

	//get head element
	if(stack->topo)
	{
       		memcpy(elem,stack->topo,sizeof(DATA));
	}

	//chose new head
	if(stack->next && stack->next->next)
	{
		stack->topo = stack->next->topo;
		stack->next = stack->next->next;
	}

	return elem;
}

