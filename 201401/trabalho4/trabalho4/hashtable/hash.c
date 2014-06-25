/* 
 * File:   hash.c
 * Author: deivid
 *
 * Created on 4 de Junho de 2014, 19:28
 */

#include "../main.h"

/**
 * 
 * @param 
 * @return 
 */
unsigned int shortHash(unsigned int x) {
    char stringNum[SIZE_DIGITOS_UNSIGNED_INT * 2];
    char stringShort[SIZE_DIGITOS_HASH + 1];

    //converte para string
    sprintf(stringNum, "%u", x);

    memcpy(stringShort, stringNum, SIZE_DIGITOS_HASH);
    stringShort[SIZE_DIGITOS_HASH] = '\0';

    return atoi(stringShort);
}

/**
 * 
 * @param
 * @return
 */
unsigned int functionHashInt(unsigned int x) {
    x = ((x >> 16) ^ x) * 0x3335b369;
    x = ((x >> 16) ^ x) * 0x3335b369;
    x = ((x >> 16) ^ x);
    return shortHash(x);
}

/**
 * Insere o valor na tabela
 * @param tabela
 * @param valor
 * @return void
 */
void insert_hash(HashTable* table, unsigned int value) {
    unsigned int values[1];
    values[0] = value;
    insert (1, table, values);
}

void insert (int size, HashTable* table, unsigned int* values) {
    unsigned int count = 0, hashId = 0, i;

    int count_colisao = 0;
    int count_insercao = 0;

    Table **moreHashes;
    unsigned int *moreHashesColisoes;
    moreHashes = malloc(sizeof (Table*));

    do {
        hashId = functionHashInt(values[count]);

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
                table->hashTable[hashId]->hashTableColisoes = moreHashesColisoes;
                table->hashTable[hashId]->hashTableColisoes[numElements - 1] = values[count];
                table->hashTable[hashId]->numElements =  numElements + 1;// numElements;
                table->numElements += 1;
            } else {
                free(table->hashTable);
                free(table);
                puts("Error (re)allocating memory in collision");
                exit(1);
            }
            count_colisao++;
        } else { //insere sem colisao
            table->hashTable[hashId]->key = values[count];
            table->hashTable[hashId]->numElements += 1;
            table->hashTable[hashId]->deleted = 0;
            table->numElements += 1;
        }
        count_insercao++;
        count++;

    } while (count < size);
    
    printf("\nTotal de insercao: %d\n", count_insercao);
    printf("Total de colisao: %d\n", count_colisao);
    printf("Total indices alocados: %d\n", table->sizeOfTable);    
}

/**
 * Busca o hash pelo valor
 * @param key
 * @param table
 * @return void
 */
Table* busca_hash(unsigned int key, HashTable* table) {
    unsigned int hashId = functionHashInt(key);
    
    if (table->hashTable[hashId]->key == key) {
        if (table->hashTable[hashId]->deleted == 0) {
            return table->hashTable[hashId];
        }
    }
    return NULL;
}

/**
 * Remove o item da tabela e do arquivo 
 * @param key
 * @param table
 * @return void
 */
void remove_hash (unsigned int key, HashTable* table) {
    Table* hash = busca_hash(key, table);
    hash->deleted = 1;
}
   
/**
 * Exibe os itens da tabela na tela 
 * @param table
 * @return void
 */
void show_hashlist (HashTable* table) {
    int i = 0, j = 0;
    for (i = 0; i < table->sizeOfTable; i++) {

        if (table->hashTable[i]->numElements != 0 && table->hashTable[i]->deleted != 1) {
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
}

void create_hashtable(HashTable* table, int blockSize) {
    // load block from file
    insert(blockSize, table, NULL);
}

void create_hashfile (HashTable* table) {
    FILE** ppFile;
    ppFile = (FILE**) malloc(sizeof (FILE*));

    unsigned i = 0, j = 0, index = 0, size = table->sizeOfTable;
    openHashFile(ppFile, "wb");
    
    ppHASH_TABLE ppHash = (ppHASH_TABLE) malloc(sizeof (pHASH_TABLE) * size);
    
    for (i = 0; i < size; i++) {
        if (table->hashTable[i]->numElements != 0 && table->hashTable[i]->deleted != 1) {
            ppHash[index] = (pHASH_TABLE) malloc(sizeof (HASH_TABLE));
            ppHash[index]->index = index;
            ppHash[index]->byteIndex = table->hashTable[i]->key;
            index++;
        
            if (table->hashTable[i]->numElements > 0) {
                for (j = 0; j < table->hashTable[i]->numElements -1; j++) {
                    ppHash[index] = (pHASH_TABLE) malloc(sizeof (HASH_TABLE));
                    ppHash[index]->index = index;
                    ppHash[index]->byteIndex = table->hashTable[i]->hashTableColisoes[j];
                    index ++;
                }
            }   
        }
    }
    
    fDataWriteHash(ppFile, ppHash, size);
    
    for (i = 0; i < size; i++) {
        free(ppHash[i]);
    }
    
    free(ppHash);
    closeFile(ppFile);
}

/**
 * Exibe o registro selecionado 
 * @param key
 * @param table
 * @return void
 */
void show_hash(unsigned int key, HashTable* table) {
     unsigned int hashId = functionHashInt(key), i;

     if (table->hashTable[hashId]->key == key) {
        printf("\ntable->hashTable[hashId]->key %d", table->hashTable[hashId]->key);
        printf("\ntable->hashTable[hashId]->numElements %d", table->hashTable[hashId]->numElements);
        printf("\ntable->hashTable[hashId]->deleted %d", table->hashTable[hashId]->deleted);
        printf("\n");
     }
}
