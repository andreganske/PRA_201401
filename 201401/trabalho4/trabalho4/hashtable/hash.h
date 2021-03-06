/* 
 * File:   hash.h
 * Author: deivid
 *
 * Created on 4 de Junho de 2014, 19:29
 */

#ifndef HASH_H
#define	HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../main.h"
 
#define DESATIVADO 0
#define SIZE_DIGITOS_HASH 6
#define SIZE_DIGITOS_UNSIGNED_INT 10

typedef struct Table {
    unsigned int numElements;
    unsigned int key;
    unsigned int *hashTableColisoes;
    int deleted;
} Table;

typedef struct HashTable {
    unsigned int numElements;
    unsigned int sizeOfTable;
    Table **hashTable;
} HashTable;
unsigned int shortHash(unsigned int x) ;
unsigned int functionHashInt(unsigned int x);

void insert_hash(HashTable* table, unsigned int value);
void insert (int size, HashTable* table, unsigned int* values);
Table* busca_hash(unsigned int key, HashTable* table);
void remove_hash (unsigned int key, HashTable *table);

// funcoes de exibicao 
void show_hash(unsigned int key, HashTable* table);
void show_hashlist (HashTable* table);
 
#endif	/* HASH_H */

