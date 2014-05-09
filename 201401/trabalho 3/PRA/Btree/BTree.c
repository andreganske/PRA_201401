/* 
 * File:   BTree.c
 * Author: udesc
 *
 * Created on May 9, 2014, 7:25 PM
 */

#include "BTree.h"

// remove item do vetor
void removeLeafItem(arvoreB *leaf, int chave) {
    int i, pos = busca_binaria(leaf, chave);
    
    for (i=pos; i < leaf->num_chaves; i++) {
        leaf->chaves[i] = leaf->chaves[i+1];    
        leaf->filhos[i] = leaf->filhos[i+1];
    }
    
    leaf->filhos[i+1] = leaf->filhos[i+2];
    leaf->num_chaves--;
}

void rotate(arvoreB *ptrRef, int pos, int bEsq){
    
    if(!bEsq){
        insere_chave(ptrRef->filhos[pos+1],ptrRef->chaves[pos],NULL);
        int size = ptrRef->filhos[pos]->num_chaves-1;
        insere_chave(ptrRef,ptrRef->filhos[pos]->chaves[size],ptrRef->filhos[pos]->filhos[size+1]);
        removeLeafItem(ptrRef->filhos[pos],ptrRef->filhos[pos]->chaves[size]);
    } else {
        insere_chave(ptrRef->filhos[pos-1],ptrRef->chaves[pos],NULL);
        int size = 0;
        insere_chave(ptrRef,ptrRef->filhos[pos]->chaves[size],ptrRef->filhos[pos]->filhos[size-1]);
        removeLeafItem(ptrRef->filhos[pos],ptrRef->filhos[pos]->chaves[size]);
    }
}

void testBTree(void) {
    arvoreB raiz;
    
    int i = 0;
    
    raiz.chaves[MAX_CHAVES];
    raiz.num_chaves = 0;
    
    printf("\n testando a remocao na pagina");
    
    while (i <= 3) {
        raiz.chaves[i] = 29 + i;
        raiz.num_chaves += 1;
        i++;
    }
    
    for (i = 0 ; i < raiz.num_chaves; i++) {
        printf("%d ", raiz.chaves[i]);
    }
    printf("\n");
    removeLeafItem(&raiz, 30);
            
    for (i = 0 ; i < raiz.num_chaves; i++) {
        printf("%d ", raiz.chaves[i]);
    }
    
    printf("\n testando os rotates!");
    
    arvoreB raiz2, raiz3;
    
    raiz.filhos[0] = raiz2;
    raiz.filhos[1] = raiz3;
    
    i = 0;
    
    while (i <= 3) {
        raiz.chaves[i] = 19 + i;
        raiz.num_chaves += 1;
        i++;
    }
    
    i = 0;
    
    while (i <= 3) {
        raiz.chaves[i] = 19 + i;
        raiz.num_chaves += 1;
        i++;
    }

    
}
