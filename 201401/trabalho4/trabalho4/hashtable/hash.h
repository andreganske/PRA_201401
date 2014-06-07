/* 
 * File:   hash.h
 * Author: deivid
 *
 * Created on 4 de Junho de 2014, 19:29
 */

#ifndef HASH_H
#define	HASH_H

#include "../main.h"

typedef  struct hashpo{
    struct hashbu *bu;
}hashpo;

typedef struct hashbu{
    DATA partida;
    struct hashbu *next;    
}hashbu;

//Function definition
int funcaohash (DATA *info);
void iniciarhash (hashpo *table);
void criarhash (hashpo *table, int blockSize);


 
#endif	/* HASH_H */

