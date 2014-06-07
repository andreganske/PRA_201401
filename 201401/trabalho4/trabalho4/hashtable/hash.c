/* 
 * File:   hash.c
 * Author: deivid
 *
 * Created on 4 de Junho de 2014, 19:28
 */

#include "../main.h"

/**
 * Função para iniciar vetor com todas as posições recebendo null.
 * @param table Tabela hash a ser utilizada.
 */
void iniciarhash (hashpo *table){
    int i;
    for (i=0;i<tam;i++){
        table[i].bu->next=NULL;
        table[i].bu->partida=NULL;
    }
}
    

void criarhash (hashpo *table, int blockSize){
    int position, i,chave1;
    FILE *pFileData;

    /* //this way will try on-be-one, Using block is more fast */
    /* //iterate untill it is finished */

    ppDATA ppData;
    ppData = malloc(sizeof (pDATA));
    ppData = (ppDATA) malloc(sizeof (pDATA) * blockSize);
        for (i = 0; i < blockSize; i++) {
                ppData[i] = (pDATA) malloc(sizeof (DATA));
                /* ppData[i]->data = (pPARTIDA) malloc(sizeof(PARTIDA)); */
        }

    pFileData = malloc(sizeof (FILE));
    openFile(&pFileData, "rb");
    position = -1;
    if (table) {
        //for(i=0;i<blockSize;i++){

        while (!feof(pFileData)) {
            position++;
            fDataReadBlock((pFileData), ppData, blockSize / (sizeof (DATA)), position);

            for (i = 0; i < blockSize; i++) {
                chave1 = funcaohash(ppData[i]);
                if (table[chave1].bu->partida==NULL){
                    table[chave1]->bu->partida = ppData[i];
                }else
                    if (table[chave1]->bu->next == NULL){
                        table->bu->next = 
                    }
                    
            }
        }
        //}
    }
    closeFile(&pFileData);
}
}
