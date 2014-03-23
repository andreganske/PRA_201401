 
// Calling some librarys
#include "../main.h"


void test_randomDate();
void test_randomTimeName();
void test_randomScore();
void test_randomqtdPayer();
void test_randomPlace();
void test_randomPartida(ppPARTIDA ppPartida);
void test_generateDATAInFile();
void test_generateDATAInFileInBlock(FILE** ppFile,ppDATA ppData, int quanty);
void test_DATAWFileInBlock();
void test_DATARFile();
void test_readDataInFile(FILE** ppFile,pDATA pData);

int main()
{
	//to use random values
	srand(time(NULL));
	printf("Testing metods ...\n");
	/* test_randomDate();	 */
	/* test_randomTimeName(); */
	/* test_randomScore(); */
	/* test_randomqtdPayer(); */
	/* test_randomPlace(); */
	/* test_DATAWFileInBlock();	 */
	test_generateDATAInFile();
	test_DATARFile();
}

void test_DATARFile()
{

	ppDATA ppData;
	ppData = (ppDATA) malloc(sizeof(pDATA));
	(*ppData) = (pDATA) malloc(sizeof(DATA));
	(*ppData)->data = (void*) malloc(sizeof(PARTIDA));

	FILE** ppFile;
	ppFile = (FILE**) malloc(sizeof(FILE*));

	test_readDataInFile(ppFile,(*ppData));
	printEntries((*ppData));


	free((*ppData)->data);
	free((*ppData));
	free(ppFile);
}

void test_readDataInFile(FILE** ppFile,pDATA pData)
{
	openFile(ppFile,"rb");
	fDataRead((*ppFile),pData);
	closeFile(ppFile);
}

void test_DATAWFileInBlock()
{

	ppPARTIDA ppPartida;
	
	FILE** ppFile;
	ppFile = (FILE**) malloc(sizeof(FILE*));
	ppDATA ppData;
	int i=0;
	printf("Generate 1GB of random files ....\n");
	/* long maxSizeFile = 1073741824;//1GygaByte */
	long maxSizeFile = sizeof(char)*1024*1024;
	/* int currSizeFile = 0; */
	int currSizeBlock = 0;
	int maxSizeBlock = 4096;//1024;//2048;//4096;

	int count = 0;
	int id = -1;

	//* multiply by 2 just to ensure enougth space
	int lenght = (maxSizeBlock * 2);
	ppData = (ppDATA) malloc(sizeof(pDATA) * lenght);
	for(i=0;i<lenght;i++)
	{
		ppData[i] = (pDATA) malloc(sizeof(DATA));
		ppData[i]->data = (pPARTIDA) malloc(sizeof(PARTIDA));
	}

	ppPartida = (ppPARTIDA) malloc(sizeof(pPARTIDA));
	(*ppPartida) = (pPARTIDA) malloc(sizeof(PARTIDA));
	long currSizeFile = 0;
	while(currSizeFile <= maxSizeFile){ 

		currSizeBlock = 0;
		count = 0;
		i=0;
		while((currSizeBlock + sizeof(DATA)) <= maxSizeBlock){ 	
			count++;//keep count

			//Generete PARTIDA
			test_randomPartida(ppPartida);
		
			//Generate Data
			id++;
			ppData[i]->id = id;

			//copy the random PARTIDA generated before
			memcpy(ppData[i]->data,(*ppPartida),sizeof(PARTIDA));

			i++;
			currSizeBlock += sizeof(DATA);

		}
		test_generateDATAInFileInBlock(ppFile,ppData,count);
		currSizeFile += currSizeBlock;//update current size of file
		/* currSizeFile = currentSizeInFile(ppFile); */
		printf("currSizeFile %d and maxSizeFile %d\n",currSizeFile,maxSizeFile);
	}
}

void test_generateDATAInFileInBlock(FILE** ppFile,ppDATA ppData, int quanty)
{
	openFile(ppFile,"a+b");
	fDataWriteBlock((*ppFile),ppData,quanty);
	closeFile(ppFile);
}

void test_generateDATAInFile()
{
	FILE** ppFile;
	ppFile = (FILE**) malloc(sizeof(FILE*));
	pDATA pData;
	pData = (pDATA) malloc(sizeof(DATA));

	ppPARTIDA ppPartida;
	ppPartida = (ppPARTIDA) malloc(sizeof(pPARTIDA));
	(*ppPartida) = (pPARTIDA) malloc(sizeof(PARTIDA));

	test_randomPartida(ppPartida);

	printf("###id\n");
	//Generate Data
	pData->id = 10;

	printf("###id %d\n",pData->id);
	//copy the random PARTIDA generated before
	pData->data = (pPARTIDA) malloc(sizeof(PARTIDA));
	memcpy(pData->data,(*ppPartida),sizeof(PARTIDA));

	openFile(ppFile,"a+b");
	fDataWrite((*ppFile),pData);
	closeFile(ppFile);

	free((*ppPartida));
	free((ppPartida));
	free((pData->data));
	free((pData));
	free(ppFile);
}

void test_randomDate()
{
	printf("Teste of randomDate()...\n");
	pDATE date = (pDATE) malloc(sizeof(DATE));

	randomDate(date);
	printf("Found: %d/%d/%d\n",date->dia,date->mes,date->ano);
}

void test_randomTimeName()
{
	printf("Teste of randomTimeName()...\n");
	char timeName[150];

	randomTimeName(timeName);
	printf("Found: %s\n",timeName);
}

void test_randomScore()
{
	printf("Teste of randomScore()...\n");
	int score = 0;

	randomScore(&score);
	printf("Found: %d\n",score);
}

void test_randomqtdPayer()
{
	printf("Teste of randomqtdPayer()...\n");
	int qtd = 0;

	randomqtdPayer(&qtd);
	printf("Found: %d\n",qtd);
}

void test_randomPlace()
{
	printf("Teste of randomPlace()...\n");
	char place[150];

	randomPlace(place);	
	printf("Found: %s\n",place);
}

void test_randomPartida(ppPARTIDA ppPartida)
{
	/* printf("Teste of randomPartida()...\n"); */
	randomPartida(ppPartida);

	/* printf("Show PARTIDA data\n"); */
	/* printf("Date: %d/%d/%d\n",(*ppPartida)->Date.dia,(*ppPartida)->Date.mes,(*ppPartida)->Date.ano); */
	/* printf("TimeA name: %s\n",(*ppPartida)->nameTimeA); */
	/* printf("TimeB name: %s\n",(*ppPartida)->nameTimeB); */
	/* printf("Score: %d\n",(*ppPartida)->score); */
	/* printf("Qtd Payer: %d\n",(*ppPartida)->qtdPayer); */
	/* printf("Place name: %s\n",(*ppPartida)->place); */

}
