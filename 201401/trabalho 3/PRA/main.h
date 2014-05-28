/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske, Deivid Sartori and Wesklei Migliorini
 */

#ifndef _MAIN_H_
#define _MAIN_H_

/*INCLUDES*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <sys/time.h>
#include <dirent.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>

/* Include local files */
#include "DAO/data.h"
#include "DAO/partida.h"

/*DEFINICOES*/
#define SUCESSO         1
#define FRACASSO        0
#define TRUE            1
#define FALSE           0
#define MAIOR           1
#define IGUAL           0
#define MENOR           -1
#define DIREITA         1
#define ESQUERDA        0
#define AMBOS           2
#define arq1 "file1.dat"
#define arq2 "file2.dat"
#define LIMPA "clear || cls"

#define T 2
#define MAX_CHAVES  2*T // começa de zero!
#define MAX_FILHOS  2*T+2
#define MIN_OCUP  T



typedef struct no_arvoreB arvoreB;

typedef struct no_arvoreB {
    int num_chaves; //Quantidades de chaves contida no nó
    int chaves[MAX_CHAVES+1]; //Chaves armazenadas no nó
    arvoreB *filhos[MAX_FILHOS]; //Ponteiro para os filhos
} No_arvoreB;

void insere_chave(arvoreB *raiz, int info, arvoreB *filhodir);
arvoreB *insere(arvoreB *raiz, int info, bool *h, int *info_retorno);
arvoreB *insere_arvoreB(arvoreB *raiz, int info);
int busca_binaria(arvoreB *no, int info);
void em_ordem(arvoreB *raiz);


#endif