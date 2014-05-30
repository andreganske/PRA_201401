/* 
 * File:   BTree.c
 * Author: udesc
 *
 * Created on May 9, 2014, 7:25 PM
 */

#include "../main.h"

void createBTree(arvoreB **raiz, int blockSize) {
    int position, i;
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
    if (raiz) {
        //for(i=0;i<blockSize;i++){

        while (!feof(pFileData)) {
            position++;
            fDataReadBlock((pFileData), ppData, blockSize / (sizeof (DATA)), position);

            for (i = 0; i < blockSize; i++) {

                *raiz = insere_arvoreB(*raiz, ppData[i]);
            }
        }
        //}
    }
    closeFile(&pFileData);
}

int busca_binaria(arvoreB *no, pDATA info) {
    int meio, i, f;
    i = 0;

    f = no->num_chaves - 1;
    while (i <= f) {
        meio = (i + f) / 2;
        //if (no->chaves[meio] == info)
        if (cmpEncapsulate(no->chaves[meio], info, cmpKey1) == 0)
            return meio; //Encontrou. Retorna a posíção em que a chave está.
            //else if (no->chaves[meio] > info) {
        else if (cmpEncapsulate(no->chaves[meio], info, cmpKey1) > 0) {
            f = meio - 1;

        } else i = meio + 1; //ele eh menor
    }
    return (i); //Não encontrou. Retorna a posição do ponteiro para o filho.
}

void em_ordem(arvoreB *raiz) {
    int i;
    if (raiz != NULL) {
        for (i = 0; i < raiz->num_chaves; i++) {

            em_ordem(raiz->filhos[i]);

            //printf(" %d", raiz->chaves[i]);
            if (raiz->chaves[i] != NULL && raiz->chaves[i]->id != 0 && raiz->chaves[i]->id > 0)
                printEntries(raiz->chaves[i]);
        }
        em_ordem(raiz->filhos[i]);
    }
}

void em_ordem_paginado(arvoreB *raiz, int *pos_atual, int *inicio, int *limit) {
    int i;
    if (raiz != NULL && *limit >= 0) {


        for (i = 0; i < raiz->num_chaves; i++) {

            em_ordem_paginado(raiz->filhos[i], pos_atual, inicio, limit);

            //printf(" %d", raiz->chaves[i]);
            if (raiz->chaves[i] != NULL && raiz->chaves[i]->id != 0) {//mostra so quando chegou no ponto que quer

                if (*pos_atual >= *inicio)
                    printEntries(raiz->chaves[i]);
                *limit -= 1;
                *pos_atual += 1;
            } else {
                *pos_atual += 1;
            }
        }
        em_ordem_paginado(raiz->filhos[i], pos_atual, inicio, limit);
    }
}

arvoreB *busca(arvoreB *raiz, pDATA info) {
    arvoreB *no;
    int pos; //posição retornada pelo busca binária.

    no = raiz;
    while (no != NULL) {
        pos = busca_binaria(no, info);
        if (pos < no->num_chaves && (cmpEncapsulate(no->chaves[pos], info, cmpKey1) == 0))
            return no;

        else no = no->filhos[pos];
    }
    return no;
}

//Insere uma chave e o ponteiro para o filho da direita em um nó

void insere_chave(arvoreB *raiz, pDATA info, arvoreB *filhodir) {
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
arvoreB *insere(arvoreB *raiz, pDATA info, bool *h, pDATA *info_retorno) {
    int i, j, pos;
    pDATA info_mediano; //auxiliar para armazenar a chave que irá subir para o pai
    arvoreB *temp, *filho_dir; //ponteiro para o filho à direita da chave 

    if (raiz == NULL) {
        //O nó anterior é o ideal para inserir a nova chave (chegou em um nó folha)
        *h = true;
        *info_retorno = info;
        return (NULL);
    } else {
        pos = busca_binaria(raiz, info);
        if (raiz->num_chaves > pos && raiz->chaves[pos] == info) {
            //printf("Chave já contida na Árvore");
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

                    //Verifica em qual nó será inserida a nova chave
                    if (pos <= MIN_OCUP)
                        insere_chave(raiz, *info_retorno, filho_dir);
                    else
                        insere_chave(temp, info, filho_dir);

                    //elemento mediano que vai subir para o pai
                    info_mediano = raiz->chaves[MIN_OCUP];

                    //insere metade do nó raiz no temp (efetua subdivisão)
                    temp->filhos[0] = raiz->filhos[MIN_OCUP + 1];
                    for (i = MIN_OCUP + 1; i < MAX_CHAVES; i++)
                        insere_chave(temp, raiz->chaves[i], raiz->filhos[i + 1]);

                    if (pos <= MIN_OCUP)
                        insere_chave(temp, raiz->chaves[MAX_CHAVES], raiz->filhos[MAX_CHAVES + 1]);

                    //atualiza nó raiz. 
                    for (i = MIN_OCUP; i < MAX_CHAVES; i++) {
                        raiz->chaves[i] = 0;
                        raiz->filhos[i + 1] = NULL;
                    }
                    if (pos <= MIN_OCUP) {
                        raiz->chaves[MAX_CHAVES] = 0;
                        raiz->filhos[MAX_CHAVES + 1] = NULL;
                    }

                    raiz->num_chaves = MIN_OCUP;

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
arvoreB *insere_arvoreB(arvoreB *raiz, pDATA info) {
    bool h;
    pDATA info_retorno;
    int i;
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
void removeLeafItem(arvoreB *leaf, int pos) {
    int i;

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
        removeLeafItem(ptrRef->filhos[pos], size);
    } else {

        insere_chave(ptrRef->filhos[pos - 1], ptrRef->chaves[pos], NULL);
        int size = 0;
        insere_chave(ptrRef, ptrRef->filhos[pos]->chaves[size], ptrRef->filhos[pos]->filhos[size - 1]);
        removeLeafItem(ptrRef->filhos[pos], size);
    }
}

bool isLeaf(arvoreB *leaf) {

    if (leaf != NULL)
        return leaf->filhos[0] == NULL; //testa so no indice 0, nao precisa o resto

    else
        return false;
}

/**
 * Acha a chave sucessora
 * @param pTree
 * @param chave
 * @return 
 */
pDATA sucessorKeyInNode(arvoreB *pTree, pDATA chave) {

    arvoreB *pNo;
    pNo = busca(pTree, chave);

    //acha sucessor,pos a direita
    int pos_interna = busca_binaria(pNo, chave);

    if (pos_interna < MAX_FILHOS) {
        int pos_sucessor = busca_binaria(pNo->filhos[pos_interna + 1], chave);
        return pNo->filhos[pos_sucessor]->chaves[0];
    } else {

        return NULL;
    }
}

/**
 * Acha no sucessor
 * @param pTree
 * @param chave
 * @return 
 */
arvoreB *sucessorChild(arvoreB *pTree, pDATA chave) {

    if (pTree == NULL)
        return NULL;

    arvoreB * pNo;
    pNo = busca(pTree, chave);

    //acha sucessor,pos a direita
    int pos_interna = busca_binaria(pNo, chave);

    if (pos_interna < MAX_FILHOS) {
        int pos_sucessor = busca_binaria(pNo->filhos[pos_interna + 1], chave);
        return pNo->filhos[pos_sucessor];
    } else {

        return NULL;
    }
}

/**
 * Acha a chave predecessora apartir de pTree
 * @param pTree
 * @param chave
 * @return 
 */
pDATA precedecinfKey(arvoreB *pTree, pDATA chave) {

    arvoreB *pNo;
    pNo = busca(pTree, chave);

    //acha predecessor, pos a esquerda
    int pos_interna = busca_binaria(pNo, chave);
    if (pos_interna > 0) {
        int pos_predecessor = busca_binaria(pNo->filhos[pos_interna - 1], chave);
        return pNo->filhos[pos_predecessor]->chaves[pNo->filhos[pos_predecessor]->num_chaves];
    } else {

        return NULL;
    }
}

/**
 * Acha no predecessor apartir de pTree
 * @param pTree
 * @param chave
 * @return 
 */
arvoreB *predecindChild(arvoreB *pTree, pDATA chave) {

    if (pTree == NULL)
        return NULL;

    arvoreB * pNo;
    pNo = busca(pTree, chave);

    //acha predecessor, pos a esquerda
    int pos_interna = busca_binaria(pNo, chave);
    if (pos_interna > 0 && pNo->filhos[pos_interna - 1] != NULL) {
        int pos_predecessor = busca_binaria(pNo->filhos[pos_interna - 1], chave);
        return pNo->filhos[pos_predecessor];
    } else if (pos_interna > 0 && pNo->filhos[pos_interna + 1] != NULL) {
        int pos_predecessor = busca_binaria(pNo->filhos[pos_interna - 1], chave);
        return pNo->filhos[pos_predecessor];
    } else {

        return NULL;
    }
}

/**
 * Move infoKey de node1 para node2
 * @param infoKey
 * @param node1
 * @param node2
 */
void moveKey(pDATA infoKey, arvoreB *node1, arvoreB *node2) {

    int pos;

    pos = busca_binaria(node1, infoKey);

    //insere no node2
    insere_chave(node2, infoKey, node1->filhos[pos + 1]);

    //remove do node1
    node1->chaves[pos] = 0;
    node1->filhos[pos + 1] = NULL;
    //realiza o remanejamento para manter as chaves ordenadas
    int k = pos;
    while (k < node1->num_chaves) {

        node1->chaves[k] = node1->chaves[k + 1];
        node1->filhos[k] = node1->filhos[k + 2];
        k++;
    }
}

/**
 * Concatena dois nos
 * Node destino recebe a concatenacao e origem fica NULL
 * @param destino
 * @param origem
 */
void mergeNodes(arvoreB *origem, arvoreB *destino) {

    int i, total;
    total = destino->num_chaves + origem->num_chaves;
    for (i = 0; i < total; i++) {

        insere_chave(destino, origem->chaves[i], origem->filhos[i + 1]);
        origem->chaves[i] = 0;
        origem->filhos[i + 1] = NULL;
    }
    origem->num_chaves = 0;
    origem = NULL;

}

/**
 * Acha o root de um node por uma chave
 * @param raiz
 * @param key
 * @return 
 */
arvoreB *rootOfNodeByKey(arvoreB *raiz, pDATA key) {
    arvoreB *no, *predecessor;
    int pos; //posição retornada pelo busca binária.

    no = raiz;
    predecessor = raiz;
    while (no != NULL) {
        pos = busca_binaria(no, key);
        if (pos < no->num_chaves && no->chaves[pos] == key) {
            return predecessor;
        } else {

            predecessor = no;
            no = no->filhos[pos];
        }
    }

    return predecessor;
}

/**
 * Acha a chave do root que liga neste node
 * @param raiz
 * @param key
 * @return 
 */
pDATA rootKeyOfNode(arvoreB *raiz, pDATA key) {

    arvoreB *predecessor;
    int pos; //posição retornada pelo busca binária.

    predecessor = rootOfNodeByKey(raiz, key);
    pos = busca_binaria(predecessor, key);

    return predecessor->chaves[pos];
}

/**
 * Acha o irmao de um node
 * @param raiz
 * @param irmao
 * @return 
 */
arvoreB *findSibling(arvoreB *raiz, arvoreB *irmao) {
    arvoreB *no, *predecessor;
    int pos; //posição retornada pelo busca binária.
    pDATA key;

    //usa alguma chave para buscar
    key = irmao->chaves[0];

    no = raiz;
    predecessor = raiz;
    while (no != NULL) {
        pos = busca_binaria(no, key);
        if (pos < no->num_chaves && cmpEncapsulate(no->chaves[pos], key, cmpKey1) == 0) {
            break;
        } else {
            predecessor = no;
            no = no->filhos[pos];
        }
    }

    //quando sair do while vai ter o predecessor
    //e em 'pos' vai estar a posicao do 'irmao' no pai (predecessor)
    //pega outro irmao para 'irmao'

    if (pos == 0) {
        return predecessor->filhos[pos + 1];
    } else {

        return predecessor->filhos[0];
    }
}

/**pNode eh o no com a infoKey
 * Dois casos (1) se nao eh folha e (2) se eh folha
 * Cada caso possui subcasos
 * @param pTree
 * @param infoKey
 */
void removeBTree(arvoreB *pRoot, arvoreB *pNode, pDATA infoKey) {

    int i, k, pos_interna, pos_sucessor;
    int num_chaves;
    pDATA predecingKey, sucessorKey, rootKey;

    arvoreB *pPreceding, *pSuccessor, *pRootNode, *pRootRootNode;
    arvoreB *pIrmao;
    //pNode = busca(pNode, infoKey);

    //acha predecessor e sucessor
    pPreceding = predecindChild(pNode, infoKey);
    pSuccessor = sucessorChild(pNode, infoKey);

    //Dois casos principais

    //(1)-Se nao eh Folha
    if (!isLeaf(pNode)) {

        //se o que predecedor tem mais q o minimo de chaves
        if (pPreceding->num_chaves > MIN_OCUP) {

            //move a chave que precede para o pNode
            //a chave que precede infoKey eh a ultima do NO predecessor      
            num_chaves = pPreceding->num_chaves;

            //move chave do predecessor para pNode
            moveKey(pPreceding->chaves[num_chaves - 1], pPreceding, pNode);

            //move infoket do pNode para o sucessor
            moveKey(infoKey, pNode, pSuccessor);

            //chamada recursiva para continuar a remocao
            removeBTree(pRoot, pSuccessor, infoKey);

            //se o sucessor tem mais q o minimo de chaves
        } else if (pSuccessor->num_chaves > MIN_OCUP) {

            //move a chave que sucede para o pNode
            //a chave que sucede infoKey eh a primeira (zero) NO sucessor  

            //move chave do sucessor  para pNode
            moveKey(pSuccessor->chaves[0], pSuccessor, pNode);

            //move infoKey do pNode para o predecessor
            moveKey(infoKey, pNode, pPreceding);

            //chamada recursiva para continuar a remocao
            removeBTree(pRoot, pPreceding, infoKey);

        } else {//se tem o minimo, faz merge

            //move chave para o predecessor
            moveKey(infoKey, pNode, pPreceding);

            //faz merge dos nodes (concatena))
            mergeNodes(pSuccessor, pPreceding);

            //chamada recursiva para continuar a remocao
            removeBTree(pRoot, pPreceding, infoKey);
        }
    } else {//quando eh uma folha

        pRootNode = rootOfNodeByKey(pRoot, infoKey);
        rootKey = rootKeyOfNode(pRoot, infoKey);

        //apenas remove se eh uma folha com mais do que o minimo
        if (pNode->num_chaves > MIN_OCUP) {

            //pega pos dentro do no
            pos_interna = busca_binaria(pNode, infoKey);

            //remove da folha
            removeLeafItem(pNode, pos_interna);

        } else if (pPreceding->num_chaves > MIN_OCUP) {

            //acha o predecessor do root para mover
            predecingKey = precedecinfKey(pRootNode, rootKey);
            moveKey(predecingKey, pPreceding, pRootNode);

            //acha o sucessor do root para mover
            sucessorKey = sucessorKeyInNode(pRootNode, rootKey);
            moveKey(sucessorKey, pRootNode, pNode);

            //chamada recursiva para continuar a remocao
            removeBTree(pRoot, pNode, infoKey);

        } else if (pRootNode->num_chaves > MIN_OCUP) {

            sucessorKey = sucessorKeyInNode(pRootNode, rootKey);
            moveKey(sucessorKey, pSuccessor, pRootNode);

            //acha o predecessor do root para mover
            predecingKey = precedecinfKey(pRootNode, rootKey);
            moveKey(predecingKey, pRootNode, pNode);

            //chamada recursiva para continuar a remocao
            removeBTree(pRoot, pNode, infoKey);

        } else {

            //algum irmao do rootNode
            pIrmao = findSibling(pRoot, pRootNode);
            //o root desta raiz
            pRootRootNode = rootOfNodeByKey(pRootNode, infoKey);

            if (pRootRootNode->num_chaves > MIN_OCUP) {

                //concatena eles
                mergeNodes(pRootRootNode, pRootNode);
                mergeNodes(pRootNode, pIrmao);

                //chamada recursiva para continuar a remocao
                removeBTree(pRoot, pNode, infoKey);

            } else {

                //move para do root para o node

                moveKey(rootKey, pRootNode, pNode);

                //chamada recursiva para continuar a remocao
                removeBTree(pRoot, pNode, infoKey);
            }
        }

    }
}

void testBTreeInsercaoConsulta(void) {
    /*
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

void testBTreeInsercaoRemocaoConsulta(void) {

    /*  arvoreB **raiz;

      int i, j;
      raiz = malloc(sizeof (arvoreB*));
     *raiz = malloc(sizeof (arvoreB));
      if (*raiz) {
          printf("Arvore criada com sucesso!\n");
      } else {
          printf("Problema ao alocar arvore!\n");
      }

      printf("Inserindo elementos do slide ED2_03_Arvore_B.pdf (pg 36) ...\n");
     *raiz = insere_arvoreB(*raiz, 85);
     *raiz = insere_arvoreB(*raiz, 60);
     *raiz = insere_arvoreB(*raiz, 52);
     *raiz = insere_arvoreB(*raiz, 70);
     *raiz = insere_arvoreB(*raiz, 58);
     *raiz = insere_arvoreB(*raiz, 37);
     *raiz = insere_arvoreB(*raiz, 111);
     *raiz = insere_arvoreB(*raiz, 23);
     *raiz = insere_arvoreB(*raiz, 205);
     *raiz = insere_arvoreB(*raiz, 5);
     *raiz = insere_arvoreB(*raiz, 97);
     *raiz = insere_arvoreB(*raiz, 64);
     *raiz = insere_arvoreB(*raiz, 14);
     *raiz = insere_arvoreB(*raiz, 90);
     *raiz = insere_arvoreB(*raiz, 30);
     *raiz = insere_arvoreB(*raiz, 75);
     *raiz = insere_arvoreB(*raiz, 25);
     *raiz = insere_arvoreB(*raiz, 54);
     *raiz = insere_arvoreB(*raiz, 56);

      printf("Mostrando em-ordem...\n");
      em_ordem(*raiz);
      printf("\n");

      printf("\nRemovendo elemento 37\n");
      arvoreB *node;
      node = busca(*raiz, 37);

      removeBTree((*raiz), node, 37);
      printf("Mostrando em-ordem...\n");
      em_ordem(*raiz);
      printf("\n");

      printf("\nRemovendo elemento 58\n");
      //removeBTree(*raiz,*raiz, 58);
      printf("Mostrando em-ordem...\n");
      em_ordem(*raiz);
      printf("\n");*/
}

void testIsLeaf() {
    arvoreB **raiz;

    int i, j;
    raiz = malloc(sizeof (arvoreB*));
    *raiz = malloc(sizeof (arvoreB));
    if (*raiz) {
        printf("Arvore criada com sucesso!\n");
    } else {

        printf("Problema ao alocar arvore!\n");
    }

    printf("Inserindo elementos do slide ED2_03_Arvore_B.pdf (pg 36) ...\n");
    /*   *raiz = insere_arvoreB(*raiz, 85);
     *raiz = insere_arvoreB(*raiz, 60);
     *raiz = insere_arvoreB(*raiz, 52);
     *raiz = insere_arvoreB(*raiz, 70);
     *raiz = insere_arvoreB(*raiz, 58);
     *raiz = insere_arvoreB(*raiz, 37);
     *raiz = insere_arvoreB(*raiz, 111);
     *raiz = insere_arvoreB(*raiz, 23);
     *raiz = insere_arvoreB(*raiz, 205);
     *raiz = insere_arvoreB(*raiz, 5);
     *raiz = insere_arvoreB(*raiz, 97);
     *raiz = insere_arvoreB(*raiz, 64);
     *raiz = insere_arvoreB(*raiz, 14);
     *raiz = insere_arvoreB(*raiz, 90);
     *raiz = insere_arvoreB(*raiz, 30);
     *raiz = insere_arvoreB(*raiz, 75);
     *raiz = insere_arvoreB(*raiz, 25);
     *raiz = insere_arvoreB(*raiz, 54);
     *raiz = insere_arvoreB(*raiz, 56);

       printf("Mostrando em-ordem...\n");
       em_ordem(*raiz);
       printf("\n");

       arvoreB *leaf;
       leaf = malloc(sizeof (arvoreB));

       leaf = busca(*raiz, 54);
       if (isLeaf(leaf)) {
           printf("54 eh Leaf\n");
       } else {
           printf("54 nao eh Leaf\n");
       }

       leaf = busca(*raiz, 37);
       if (isLeaf(leaf)) {
           printf("37 eh Leaf\n");
       } else {
           printf("37 nao eh Leaf\n");
       }*/
}

void testBTreeAll(void) {
    // printf("testBTreeInsercaoConsulta()\n");
    //testBTreeInsercaoConsulta();
    //printf("testIsLeaf()\n");
    //testIsLeaf();
    printf("testBTreeInsercaoRemocaoConsulta()\n");
    testBTreeInsercaoRemocaoConsulta();

}