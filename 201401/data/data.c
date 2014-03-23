/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske and Weskley Migliorini
 */

// Calling some librarys
#include "../main.h"

#define APPENDB 	"a+b"
#define READB		"r"

void openFile(FILE **ppFile, char* param)
{
	(*ppFile) = fopen(FULLFILEPATH,param);
	if((*ppFile) == NULL)
	{
		fileGenericProblemError();
	}
}

void closeFile(FILE **ppFile)
{
	fclose((*ppFile));
}

long currentSizeInFile(FILE** ppFile)
{
	long retValue = -1;
		retValue = ftell(*ppFile);
	return retValue;
}

/**
 * Set in second parameter a string representative of DataType
 */
void getStringOfType(DataType type, char *typeofData){
	switch(type){

		case TYPE_PARTIDA:
			strcpy(typeofData,"PARTIDA");
			break;

		default:
			strcpy(typeofData,"NULL");
	}
}

void printEntries(pDATA pData)
{
	printf("ID: %d\n",pData->id);
	printf("Show PARTIDA data\n");
	if(pData == NULL)
	{
		printf("the pData is NULL\n");
	}
	pPARTIDA pPartida;
        pPartida =  malloc(sizeof(PARTIDA));
	printf("###\n");
	
	memcpy(pPartida,pData->data,sizeof(PARTIDA));
	printf("###\n");
	printf("Date: %d/%d/%d\n",pPartida->Date.dia,pPartida->Date.mes,pPartida->Date.ano);
	printf("TimeA name: %s\n",pPartida->nameTimeA);
	printf("TimeB name: %s\n",pPartida->nameTimeB);
	printf("Score: %d\n",pPartida->score);
	printf("Qtd Payer: %d\n",pPartida->qtdPayer);
	printf("Place name: %s\n",pPartida->place);
}
