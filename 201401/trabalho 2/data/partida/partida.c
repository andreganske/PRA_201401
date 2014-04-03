#include "../../main.h"

typedef struct STACK *pSTACK;
typedef struct STACK **ppSTACK;

typedef struct STACK{
	pPARTIDA partida;
}STACK;

typedef struct QUEUE *pQUEUE;
typedef struct QUEUE **ppQUEUE;

typedef struct QUEUE{
	pPARTIDA partida;
}QUEUE;

sortStack(Stack first , Stack second){
	queue result = NULL;
	while ( first && second ) {
		if ( first.topo == second.topo )
		{
			elem = pop( first);
			//TODO tratar os dois pops iguais
			//pop( second );
		}
		else if ( first.topo < second.topo ) 
		{
			elem = pop( first);
		}
		else
		{
			elem = pop( second );
		}
		result = insere na fila ( elem );
	}
}


//TODO cmp function
