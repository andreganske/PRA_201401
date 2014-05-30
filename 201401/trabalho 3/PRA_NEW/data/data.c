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
//void fDataOverWrite(FILE* pFile, pDATA pData, int position)

/**
 * Comecar com quanty = 0
 * ira incrementar e salvar a posicao no arquivo
 * Tambem passar o arquivo aberto e a raiz da arvore
 * @param node
 * @param ppFILE
 * @param quanty
 */
void em_ordemWrite(arvoreB *node, FILE **ppFILE, int *quanty) {
    int i;
    DATA data;
    INDEX_TABLE indexTable;

    if (node != NULL) {
        for (i = 0; i < node->num_chaves; i++) {
            em_ordem(node->filhos[i]);

            //printf(" %d", node->chaves[i]);

            //TODO alterar aki
            //data = node->chaves[i];
            //indexTable.byteIndex = data.id * sizeof (DATA); //use in byte	
            fIndexTableOverWrite(ppFILE, indexTable, quanty);

        }
        em_ordem(node->filhos[i]);
    }
}

void writeIndex(arvoreB *raiz) {

    int i;
    FILE **ppFile;

    /* //this way will try on-be-one, Using block is more fast */
    /* //iterate untill it is finished */
    i = 0;
    openFileIndexTable(ppFile, "a+b");
    if (raiz) {

        //call write in ordem
        em_ordemWrite(raiz, ppFile, &i);
    }
    closeFile(ppFile);

}

void readIndex(arvoreB **raiz, int blockSize) {
    int i;
    FILE **ppFile;
    FILE **ppFileData;

    /* //this way will try on-be-one, Using block is more fast */
    /* //iterate untill it is finished */
    INDEX_TABLE *indexTable;
    indexTable = malloc(sizeof(INDEX_TABLE));
    
    pDATA pData;
    pData = malloc(sizeof(DATA));
    
    openFileIndexTable(ppFile, "a+b");
    openFile(ppFileData,"rb");
    if (raiz) {
        for(i=0;i<blockSize;i++){
            fIndexTableReadPosition(ppFile,&indexTable,i);
            
            fDataReadPosition(*ppFileData,pData,indexTable->byteIndex);
            *raiz = insere_arvoreB(*raiz,pData);
        }
    }
    closeFile(ppFile);

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
