/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske and Weskley Migliorini
 */

// Including some library
#ifndef _partida_h
#define _partida_h

// Define struct


typedef struct DATE{
   int dia;
   int mes;
   int ano;
}DATE;

typedef struct DATE *pDATE;
typedef struct DATE *ppDATE;

typedef struct PARTIDA *pPARTIDA;
typedef struct PARTIDA **ppPARTIDA;

typedef struct PARTIDA{
	char	nameTimeA[150];
	char	nameTimeB[150];
	int	score;
	DATE	Date;
	int	qtdPayer;
	char	place[150];
}PARTIDA;



#endif
