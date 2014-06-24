/* 
 * File:   testeHash.c
 * Author: Wesklei M
 *
 * Created on June 19, 2014, 5:15 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DESATIVADO 0
#define SIZE_DIGITOS_HASH 6
#define SIZE_DIGITOS_UNSIGNED_INT 10

typedef struct Table {
    unsigned int numElements;
    unsigned int key;
    unsigned int *hashTableColisoes;
} Table;

typedef struct HashTable {
    unsigned int numElements;
    unsigned int sizeOfTable;
    Table **hashTable;
} HashTable;

unsigned int shortHash(unsigned int x) {
    char stringNum[SIZE_DIGITOS_UNSIGNED_INT * 2];
    char stringShort[SIZE_DIGITOS_HASH + 1];
    int i;

    //converte para string
    sprintf(stringNum, "%u", x);

    memcpy(stringShort, stringNum, SIZE_DIGITOS_HASH);
    stringShort[SIZE_DIGITOS_HASH] = '\0';

    return atoi(stringShort);
}

unsigned int functionHashInt(unsigned int x) {
    x = ((x >> 16) ^ x) * 0x3335b369;
    x = ((x >> 16) ^ x) * 0x3335b369;
    x = ((x >> 16) ^ x);
    return shortHash(x);
}

/*
 * 
 */
void testes_hash() {
    printf("testes_hash()\n");

    unsigned int count = 1000, hashId = 0, i, j = 0;
    Table **moreHashes;
    unsigned int *moreHashesColisoes;
    moreHashes = malloc(sizeof (Table*));

    int count_colisao = 0;
    int count_insercao = 0;

    HashTable *table;
    table = malloc(sizeof (HashTable));
    table->numElements = 0;
    table->sizeOfTable = 0;
    table->hashTable = malloc(sizeof (Table*));
    *(table)->hashTable = malloc(sizeof (Table));


    printf("Entering an integer value \n");
    do {
        count++;

        hashId = functionHashInt(count);

        if (hashId > table->sizeOfTable) {
            moreHashes = realloc(table->hashTable, (hashId + 1) * sizeof (Table*));


            if (moreHashes != NULL) {

                for (i = table->sizeOfTable; i < hashId + 1; i++) {
                    moreHashes[i] = malloc(sizeof (Table));
                    moreHashes[i]->hashTableColisoes = malloc(sizeof (unsigned int));
                    moreHashes[i]->numElements = 0;
                }

                table->sizeOfTable = hashId + 1;
                (table)->hashTable = moreHashes;

                //                if (memcpy(table->hashTable, moreHashes, (hashId + 1) * sizeof (Table*)) == NULL) {
                //                    printf("Erro na copia de dados!\n");
                //                    exit(1);
                //                }

            } else {
                free(table->hashTable);
                free(table);
                puts("Error (re)allocating memory");
                exit(1);
            }
        }

        //detecta colisao
        if (table->hashTable[hashId]->numElements != 0) {

            int numElements = table->hashTable[hashId]->numElements;
            moreHashesColisoes = (unsigned int *) realloc(table->hashTable[hashId]->hashTableColisoes, numElements * sizeof (unsigned int));

            if (moreHashesColisoes != NULL) {
                //  memccpy(table->hashTable[hashId]->hashTableColisoes,moreHashesColisoes,sizeof());

                table->hashTable[hashId]->hashTableColisoes = moreHashesColisoes;

                table->hashTable[hashId]->hashTableColisoes[numElements - 1] = count;
                table->hashTable[hashId]->numElements =  numElements + 1;// numElements;

                table->numElements += 1;
            } else {
                free(table->hashTable);
                free(table);
                puts("Error (re)allocating memory in collision");
                exit(1);
            }

            //printf("Colisao!!\n");
            count_colisao++;
        } else { //insere sem colisao
            table->hashTable[hashId]->key = count;
            table->hashTable[hashId]->numElements += 1;
            table->numElements += 1;
        }
        count_insercao++;

    } while (count  < 3500);

    printf("Numbers entered: \n");
    for (i = 0; i < table->sizeOfTable; i++) {

        if (table->hashTable[i]->numElements != 0) {
            printf("%d=> %d ",i, table->hashTable[i]->key);

            if (table->hashTable[i]->numElements > 0) {
                printf(" [ ");

                for (j = 0; j < table->hashTable[i]->numElements -1; j++) {
                    printf("%d ", table->hashTable[i]->hashTableColisoes[j]);
                }
                printf("]\n");
            }
        }
    }

    printf("\nTotal de insercao: %d\n", count_insercao);
    printf("Total de colisao: %d\n", count_colisao);
    printf("Total indices alocados: %d\n", table->sizeOfTable);

    for (i = 0; i < table->sizeOfTable; i++) {
        free(table->hashTable[i]->hashTableColisoes);
    }
    free(table);
    free(moreHashes);
}


