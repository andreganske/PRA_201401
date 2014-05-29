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
#include "data/partida/partida.h"
#include "data/data.h"
#include "data/partida/random/random_partida.h"
#include "data/file/file_manager.h"
#include "utils/utils.h"
#include "Btree/BTree.h"


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


void insere_chave(arvoreB *raiz, int info, arvoreB *filhodir);
arvoreB *insere(arvoreB *raiz, int info, bool *h, int *info_retorno);
arvoreB *insere_arvoreB(arvoreB *raiz, int info);
int busca_binaria(arvoreB *no, int info);
void em_ordem(arvoreB *raiz);


#endif