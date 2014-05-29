/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske, Deivid Sartori and Wesklei Migliorini
 */

// Calling some librarys
#include "../main.h"

#define APPENDB 	"a+b"
#define READB		"r"

void openFile(FILE **ppFile, char* param) {
    (*ppFile) = fopen(FULLFILEPATH, param);
    if ((*ppFile) == NULL) {
        fileGenericProblemError();
    }
}

void closeFile(FILE **ppFile) {
    fclose((*ppFile));
}

void openFileIndexTable(FILE **ppFile, char* param) {
    (*ppFile) = fopen(FULLFILEPATH_INDEX_TABLE, param);
    if ((*ppFile) == NULL) {
        fileGenericProblemError();
    }
}

long currentSizeInFile(FILE** ppFile) {
    long retValue = -1;
    retValue = ftell(*ppFile);
    return retValue;
}

/**
 * Set in second parameter a string representative of DataType
 */
void getStringOfType(DataType type, char *typeofData) {
    switch (type) {

        case TYPE_PARTIDA:
            strcpy(typeofData, "PARTIDA");
            break;

        default:
            strcpy(typeofData, "NULL");
    }
}

void printEntries(pDATA pData) {
    printf("ID: %d\n", pData->id);
    /* printf("Show PARTIDA data sieze: %d must be %d  \n",sizeof(pData->partida), sizeof(PARTIDA)); */
    DATA data;
    memcpy(&data, pData, sizeof (DATA));

    /* printf("###1  id,%d\n",data2.id); */
    /* printf("###1.2 %d\n",data2.partida.score); */
    printf("Date: %d/%d/%d\n", data.partida.Date.dia, data.partida.Date.mes, data.partida.Date.ano);
    printf("TimeA name: %s\n", data.partida.nameTimeA);
    printf("TimeB name: %s\n", data.partida.nameTimeB);
    printf("Score: %d\n", data.partida.score);
    printf("Qtd Payer: %d\n", data.partida.qtdPayer);
    printf("Place name: %s\n", data.partida.place);
}

void intercalateSort(int blockSize, int k_vias, int cmpKey1, int cmpKey2) {
    ppPARTIDA ppPartida;

    FILE** ppFile;
    ppFile = (FILE**) malloc(sizeof (FILE*));
    ppDATA ppData;
    int i = 0;

    //cmp function pointer
    void *cmp;
    cmp = &cmpEncapsulate;

    int count = 0;
    int id = -1;
    int position, idData, j, stackIndex = 0;

    int lenght = blockSize;
    ppData = (ppDATA) malloc(sizeof (pDATA) * lenght);
    for (i = 0; i < lenght; i++) {
        ppData[i] = (pDATA) malloc(sizeof (DATA));
        /* ppData[i]->data = (pPARTIDA) malloc(sizeof(PARTIDA)); */
    }

    ppPartida = (ppPARTIDA) malloc(sizeof (pPARTIDA));
    (*ppPartida) = (pPARTIDA) malloc(sizeof (PARTIDA));

    //Allocate all the stacks
    ppSTACK ppStack, ppStackNew;
    ppStack = malloc(sizeof (pSTACK) * (k_vias + 1));
    ppStackNew = malloc(sizeof (pSTACK));
    for (i = 0; i < k_vias + 1; i++) {
        ppStack[i] = malloc(sizeof (STACK));

        //initialize the first elem in the stack with null
        ppStack[i]->data = NULL;
        ppStack[i]->next = NULL;
    }

    //Allocate the queue
    ppQUEUE ppQueue;
    ppQUEUE iterator;
    ppQueue = malloc(sizeof (pQUEUE));
    *ppQueue = malloc(sizeof (QUEUE));
    (*ppQueue)->data = NULL;
    (*ppQueue)->next = NULL;

    position = -1;
    stackIndex = 0;
    do {
        position++;

        //read 1 block for each stack
        openFile(ppFile, "r+b");
        fDataReadBlock((*ppFile), ppData, blockSize / (sizeof (DATA)), position);

        //put in the stack
        i = 0;
        while (i < blockSize / sizeof (DATA)) {
            if (ppData[i] != NULL) {
                *ppStackNew = malloc(sizeof (STACK));

                (*ppStackNew)->next = malloc(sizeof (pSTACK));
                (*ppStackNew)->next = ppStack[stackIndex];
                (*ppStackNew)->data = malloc(sizeof (DATA));
                memcpy((*ppStackNew)->data, ppData[i], sizeof (DATA));
                ppStack[stackIndex] = *ppStackNew;

                i++;
            }
        }
        stackIndex++;
        closeFile(ppFile);
    } while (stackIndex < k_vias);

    //test print all ids in stack
    ppSTACK iterators = malloc(sizeof (pSTACK));

    //sort all k_vias and put in the queue
    stackIndex = 0;
    do {
        sortStack(ppStack[stackIndex], ppStack[stackIndex + 1], ppQueue, cmpEncapsulate, cmpKey1, cmpKey2);
        stackIndex += 2;
    } while (stackIndex < k_vias - 2);

    //at her, the queue has all the references to ppDATA already sort
    //just write this references in an external file
    ppINDEX_TABLE ppIndexTable;
    ppIndexTable = malloc(sizeof (INDEX_TABLE));

    //the block size
    for (i = 0; i < lenght; i++) {
        ppIndexTable[i] = malloc(sizeof (INDEX_TABLE));
    }

    i = 0;
    openFileIndexTable(ppFile, "a+b");
    if (ppQueue) {
        iterator = malloc(sizeof (pQUEUE));
        iterator = ppQueue;

        //write the first out
        while (*iterator) {
            //get next and write
            if (*iterator && (*iterator)->data) {
                i++;
                pDATA data = malloc(sizeof (DATA));
                data = (*iterator)->data;
                ppIndexTable[i]->byteIndex = data->id * sizeof (DATA); //use in byte	

                //when get the limit size of block, write in file
                if (i == k_vias - 1) {
                    for (j = 0; j < k_vias; j++) {
                    }
                    fIndexTableWriteBlock(*ppFile, ppIndexTable, k_vias);
                    i = 0;
                }
            } else {
                iterator = &(*iterator)->next;
            }
        }
    }
    printf("at end\n");
    closeFile(ppFile);
}

void creteBTree(arvoreB raiz, int cmpKey1, int cmpKey2) {

    ppPARTIDA ppPartida;   

    FILE** ppFile;
    ppFile = (FILE**) malloc(sizeof (FILE*));
    ppDATA ppData;
    int i = 0;

    //cmp function pointer
    void *cmp;
    cmp = &cmpEncapsulate;

    int lenght = 4096;
    ppData = (ppDATA) malloc(sizeof (pDATA) * lenght);
    for (i = 0; i < lenght; i++) {
        ppData[i] = (pDATA) malloc(sizeof (DATA));
    }

    ppPartida = (ppPARTIDA) malloc(sizeof (pPARTIDA));
    (*ppPartida) = (pPARTIDA) malloc(sizeof (PARTIDA));

    // create BTree
    for (i = 0; i < lenght; i++) {
        *raiz = insere_arvoreB(*raiz, ppData[i], cmpKey1, cmpKey2);        
    }
    
    // gera e salva o index
}

void createIndexFile(em_ordem) {
    
}

void removeFromBTree(int info, int cmpKey1, int cmpKey2) {
    
}