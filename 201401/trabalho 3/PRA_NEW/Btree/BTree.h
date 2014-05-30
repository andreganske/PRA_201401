/* 
 * File:   BTree.h
 * Author: udesc
 *
 * Created on May 9, 2014, 7:25 PM
 */

#ifndef BTREE_H
#define	BTREE_H


#define T 2
#define MAX_CHAVES  2*T // começa de zero!
#define MAX_FILHOS  2*T+2
#define MIN_OCUP  T

typedef struct arvoreB arvoreB;

/**Estrutura correspondente a cada nó da Arvore B.
 */
typedef struct arvoreB {
    /**@var num_chaves
	 * Numero de chaves contidas em um nó.
         */
    int num_chaves; //Quantidades de chaves contida no nó
    /**@var chaves
    	 * Vetor com as chaves armazenadas nesse no.
    	 */
    pDATA chaves[MAX_CHAVES+1]; //Chaves armazenadas no nó
    /**@var filhos
    	 * Ponteiro para os filhos desse no.
    	 */
    arvoreB *filhos[MAX_FILHOS]; //Ponteiro para os filhos
} arvoreB;

#endif	/* BTREE_H */

