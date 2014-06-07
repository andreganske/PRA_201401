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

void printEntries(pDATA pData) {
    
    if(pData == NULL) return;
    
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
