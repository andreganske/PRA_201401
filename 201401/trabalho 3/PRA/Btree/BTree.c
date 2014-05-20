/* 
 * File:   BTree.c
 * Author: udesc
 *
 * Created on May 9, 2014, 7:25 PM
 */

#include "BTree.h"

int busca_binaria(arvoreB *no, int info) {
    int meio, i, f;
    i = 0;
    f = no->num_chaves - 1;

    while (i <= f) {
        meio = (i + f) / 2;
        if (no->chaves[meio] == info)
            return (meio); //Encontrou. Retorna a posíção em que a chave está.
        else if (no->chaves[meio] > info) {
            f = meio - 1;

        } else i = meio + 1;
    }
    return (i); //Não encontrou. Retorna a posição do ponteiro para o filho.
}

void em_ordem(arvoreB *raiz) {
    int i;
    if (raiz != NULL) {
        for (i = 0; i < raiz->num_chaves; i++) {
            em_ordem(raiz->filhos[i]);

            printf(" %d", raiz->chaves[i]);
        }
        em_ordem(raiz->filhos[i]);
    }
}

bool busca(arvoreB *raiz, int info) {
    arvoreB *no;
    int pos; //posição retornada pelo busca binária.

    no = raiz;
    while (no != NULL) {
        pos = busca_binaria(no, info);
        if (pos < no->num_chaves && no->chaves[pos] == info)
            return (true);

        else no = no->filhos[pos];
    }
    return (false);
}

//Insere uma chave e o ponteiro para o filho da direita em um nó

void insere_chave(arvoreB *raiz, int info, arvoreB *filhodir) {
    int k, pos;

    //busca para obter a posição ideal para inserir a nova chave
    pos = busca_binaria(raiz, info);
    k = raiz->num_chaves;

    //realiza o remanejamento para manter as chaves ordenadas
    while (k > pos && info < raiz->chaves[k - 1]) {

        raiz->chaves[k] = raiz->chaves[k - 1];
        raiz->filhos[k + 1] = raiz->filhos[k];
        k--;
    }
    //insere a chave na posição ideal
    raiz->chaves[pos] = info;
    raiz->filhos[pos + 1] = filhodir;
    raiz->num_chaves++;
}

/**
 * Realiza a busca do nó para inserir a chave e faz as subdivisões quando necessárias
 * @param raiz
 * @param info
 * @param h
 * @param info_retorno
 * @return 
 */
arvoreB *insere(arvoreB *raiz, int info, bool *h, int *info_retorno) {
    int i, j, pos,
            info_mediano; //auxiliar para armazenar a chave que irá subir para o pai
    arvoreB *temp, *filho_dir; //ponteiro para o filho à direita da chave 

    if (raiz == NULL) {
        //O nó anterior é o ideal para inserir a nova chave (chegou em um nó folha)
        *h = true;
        *info_retorno = info;
        return (NULL);
    } else {
        pos = busca_binaria(raiz, info);
        if (raiz->num_chaves > pos && raiz->chaves[pos] == info) {
            printf("Chave já contida na Árvore");
            *h = false;
        } else {
            //desce na árvore até encontrar o nó folha para inserir a chave.
            filho_dir = insere(raiz->filhos[pos], info, h, info_retorno);
            if (*h) //Se true deve inserir a info_retorno no nó.
            {
                if (raiz->num_chaves < MAX_CHAVES) //Tem espaço na página
                {
                    insere_chave(raiz, *info_retorno, filho_dir);
                    *h = false;
                } else { //Overflow. Precisa subdividir
                    temp = (arvoreB *) malloc(sizeof (arvoreB));
                    temp->num_chaves = 0;

                    //inicializa filhos com NULL
                    for (i = 0; i < MAX_FILHOS; i++)
                        temp->filhos[i] = NULL;

                    //elemento mediano que vai subir para o pai
                    info_mediano = raiz->chaves[MIN_OCUP];

                    //insere metade do nó raiz no temp (efetua subdivisão)
                    temp->filhos[0] = raiz->filhos[MIN_OCUP + 1];
                    for (i = MIN_OCUP + 1; i < MAX_CHAVES; i++)
                        insere_chave(temp, raiz->chaves[i], raiz->filhos[i + 1]);

                    //atualiza nó raiz. 
                    for (i = MIN_OCUP; i < MAX_CHAVES; i++) {
                        raiz->chaves[i] = 0;
                        raiz->filhos[i + 1] = NULL;
                    }
                    raiz->num_chaves = MIN_OCUP;

                    //Verifica em qual nó será inserida a nova chave
                    if (pos <= MIN_OCUP)
                        insere_chave(raiz, *info_retorno, filho_dir);
                    else insere_chave(temp, *info_retorno, filho_dir);

                    //retorna o mediano para inserí-lo no nó pai e o temp como filho direito do mediano.
                    *info_retorno = info_mediano;

                    return (temp);
                }
            }
        }
    }
}

/**
 * chamada principal da insercao
 * @param raiz
 * @param info
 * @return 
 */
arvoreB *insere_arvoreB(arvoreB *raiz, int info) {
    bool h;
    int info_retorno, i;
    arvoreB *filho_dir, *nova_raiz;

    filho_dir = insere(raiz, info, &h, &info_retorno);
    if (h) { //Aumetará a altura da árvore
        nova_raiz = (arvoreB *) malloc(sizeof (arvoreB));
        nova_raiz->num_chaves = 1;
        nova_raiz->chaves[0] = info_retorno;
        nova_raiz->filhos[0] = raiz;
        nova_raiz->filhos[1] = filho_dir;
        for (i = 2; i <= MAX_CHAVES; i++)
            nova_raiz->filhos[i] = NULL;
        return (nova_raiz);
    } else
        return (raiz);
}

/**
 * remove item do vetor
 * @param leaf
 * @param chave
 */
void removeLeafItem(arvoreB *leaf, int chave) {
    int i, pos = busca_binaria(leaf, chave);

    for (i = pos; i < leaf->num_chaves; i++) {
        leaf->chaves[i] = leaf->chaves[i + 1];
        leaf->filhos[i] = leaf->filhos[i + 1];
    }

    leaf->filhos[i + 1] = leaf->filhos[i + 2];
    leaf->num_chaves--;
}

/**
 * usado para rotacionar na hora da remocao
 * @param ptrRef
 * @param pos
 * @param bEsq
 */
void rotate(arvoreB *ptrRef, int pos, int bEsq) {

    if (!bEsq) {
        insere_chave(ptrRef->filhos[pos + 1], ptrRef->chaves[pos], NULL);
        int size = ptrRef->filhos[pos]->num_chaves - 1;
        insere_chave(ptrRef, ptrRef->filhos[pos]->chaves[size], ptrRef->filhos[pos]->filhos[size + 1]);
        removeLeafItem(ptrRef->filhos[pos], ptrRef->filhos[pos]->chaves[size]);
    } else {
        insere_chave(ptrRef->filhos[pos - 1], ptrRef->chaves[pos], NULL);
        int size = 0;
        insere_chave(ptrRef, ptrRef->filhos[pos]->chaves[size], ptrRef->filhos[pos]->filhos[size - 1]);
        removeLeafItem(ptrRef->filhos[pos], ptrRef->filhos[pos]->chaves[size]);
    }
}

void testBTree(void) {

    arvoreB **raiz;

    int i, j;
    raiz = malloc(sizeof (arvoreB*));
    *raiz = malloc(sizeof (arvoreB));
    if (*raiz) {
        printf("Arvore criada com sucesso!\n");
    } else {
        printf("Problema ao alocar arvore!\n");
    }

    printf("Inserindo elementos do slide (pg 163) ...\n");
    *raiz = insere_arvoreB(*raiz, 100);
    *raiz = insere_arvoreB(*raiz, 10);
    *raiz = insere_arvoreB(*raiz, 83);
    *raiz = insere_arvoreB(*raiz, 18);
    *raiz = insere_arvoreB(*raiz, 90);
    *raiz = insere_arvoreB(*raiz, 1);
    *raiz = insere_arvoreB(*raiz, 5);
    *raiz = insere_arvoreB(*raiz, 29);
    *raiz = insere_arvoreB(*raiz, 95);
    *raiz = insere_arvoreB(*raiz, 42);
    *raiz = insere_arvoreB(*raiz, 139);
    *raiz = insere_arvoreB(*raiz, 35);
    *raiz = insere_arvoreB(*raiz, 116);
    *raiz = insere_arvoreB(*raiz, 34);
    *raiz = insere_arvoreB(*raiz, 38);
    *raiz = insere_arvoreB(*raiz, 50);
    *raiz = insere_arvoreB(*raiz, 60);

    printf("Mostrando em-ordem...\n");
    em_ordem(*raiz);
    printf("\n");

    
    /*arvoreB raiz;

    int i = 0;

    raiz.chaves[MAX_CHAVES];
    raiz.num_chaves = 0;

    printf("\n testando a remocao na pagina");



    while (i <= 3) {
        raiz.chaves[i] = 29 + i;
        raiz.num_chaves += 1;
        i++;
    }

    for (i = 0; i < raiz.num_chaves; i++) {
        printf("%d ", raiz.chaves[i]);
    }
    printf("\n");
    removeLeafItem(&raiz, 30);

    for (i = 0; i < raiz.num_chaves; i++) {
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

     */
}
