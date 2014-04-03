/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske, Deivid Sartori and Weskley Migliorini
 *
 * How to compile: gcc main.c main.h data/partida/partida.c  data/file/file_manager.c  data/data.c data/partida/random/random_partida.c utils/utils.c
 */
#include "main.h"
void generateRandomEntriesBlock(int size, int blockSize);
void readRandomEntriesBlock(int blockSize);
void executionTime(clock_t time_start, clock_t time_end);
void readEntryPosition(int position);
void generateOneEntry();

// main menu
int main() {
	printf("\nWelcome!");
	printf("\nWhat you want to do?");
	
	menu();
}

void menu() {
	//to use random values
	srand(time(NULL));

	int menu,submenu, status = 0, position, quantity;
	int size,blockSize;
	// execution time control
	clock_t time_start, time_end;

	do {

		printf("\n[0] Generate multiple randon entries in file using block");
		printf("\n[1] Read entry in position using block");
		printf("\n[2] Create and insert one random entry");
		printf("\n[3] Read entry in position");
		/* printf("\n[2] Create and insert multiple entries"); */
		/* printf("\n[3] Find and print one entry"); */
		/* printf("\n[4] Find and print multiple entries"); */

		printf("\n");
		scanf("%d", &menu);

		switch (menu) {
			case 0:
				printf("\n Chose size:");
				printf("\n[0] MB");
				printf("\n[1] GB (default)");
				printf("\n");

				scanf("%d",&submenu);
				
				printf("What size?\n");
				switch (submenu){
					case 0:
						scanf("%d",&size);
						size *= 1024*1024;
						break;
					default:
						scanf("%d",&size);
						size *= 1024*1024*1024;
						break;
				}

				printf("What is the block size?\n");
				scanf("%d",&blockSize);
				
				time_start = time(NULL);	
				generateRandomEntriesBlock(size,blockSize);
				time_end = time(NULL);

				executionTime(time_start,time_end);
				status = 1;
			break;

			case 1:
				printf("What is the block size?\n");
				scanf("%d",&blockSize);
				
				time_start = time(NULL);	
				readRandomEntriesBlock(blockSize);
				time_end = time(NULL);

				executionTime(time_start,time_end);
			break;

			case 2:
				time_start = time(NULL);	
				generateOneEntry(size,blockSize);
				time_end = time(NULL);

				executionTime(time_start,time_end);
			break;

			case 3:
				printf("What position?\n");
				scanf("%d",&position);
				
				time_start = time(NULL);	
				readEntryPosition(position);
				time_end = time(NULL);

				executionTime(time_start,time_end);
			break;


			
			case 4:
				/* status = 0; */
				/* position = getInsertPosition(); */
				/* quantity = getInsertQuantity(); */
				/* printEntries(getMultipleEntries(position, quantity), quantity); */
			break;

			default: 
				status = 1;
				printf("\nPlease, select a valid option!!!");
			break;
		}

	} while (status == 1);
}

void generateOneEntry()
{
	FILE** ppFile;
	ppFile = (FILE**) malloc(sizeof(FILE*));
	pDATA pData;
	pData = (pDATA) malloc(sizeof(DATA));

	ppPARTIDA ppPartida;
	ppPartida = (ppPARTIDA) malloc(sizeof(pPARTIDA));
	(*ppPartida) = (pPARTIDA) malloc(sizeof(PARTIDA));

	randomPartida(ppPartida);

	//TODO get next ID and set her
	//Generate Data
	pData->id = 1;

	//copy the random PARTIDA generated before
	/* pData->partida = (pPARTIDA) malloc(sizeof(PARTIDA)); */
	memcpy(&pData->partida,(*ppPartida),sizeof(PARTIDA));

	openFile(ppFile,"wb");
	fDataWrite((*ppFile),pData);
	fflush(*ppFile);
	closeFile(ppFile);

	free((*ppPartida));
	free((ppPartida));
	free((pData));
	free(ppFile);
}

void executionTime(clock_t time_start, clock_t time_end)
{
	double duration;
	// calc time elapsed
	duration = (double) (time_end - time_start) ;/// CLOCKS_PER_SEC;

	// print elapsed time
	printf("\n=> This function was running for %.2lf seconds\n", duration);
}

void readEntryPosition(int position)
{

	pDATA pData;
	pData = (pDATA) malloc(sizeof(DATA));
	/* (pData)->data = (pPARTIDA) malloc(sizeof(PARTIDA)); */

	FILE** ppFile;
	ppFile = (FILE**) malloc(sizeof(FILE*));

	DATA data;
	/* testeD.data = (pPARTIDA) malloc(sizeof(PARTIDA)); */
	/* printEntries((&testeD)); */
	openFile(ppFile,"r+b");
	fDataReadPosition((*ppFile),&data,position);
	printEntries((&data));
	closeFile(ppFile);


	/* free((pData)->data); */
	free((pData));
	free(ppFile);
}

void generateRandomEntriesBlock(int size, int blockSize)
{
	ppPARTIDA ppPartida;
	
	FILE** ppFile;
	ppFile = (FILE**) malloc(sizeof(FILE*));
	ppDATA ppData;
	int i=0;
	printf("Generating random entries ....\n");
	/* long maxSizeFile = 1073741824;//1GygaByte */
	long maxSizeFile = size;
	/* int currSizeFile = 0; */
	int currSizeBlock = 0;
	int maxSizeBlock = blockSize;//4096;//1024;//2048;//4096;

	int count = 0;
	int id = -1;

	//* multiply by 2 just to ensure enougth space
	int lenght = maxSizeBlock;
	ppData = (ppDATA) malloc(sizeof(pDATA) * lenght);
	for(i=0;i<lenght;i++)
	{
		ppData[i] = (pDATA) malloc(sizeof(DATA));
		/* ppData[i]->data = (pPARTIDA) malloc(sizeof(PARTIDA)); */
	}

	ppPartida = (ppPARTIDA) malloc(sizeof(pPARTIDA));
	(*ppPartida) = (pPARTIDA) malloc(sizeof(PARTIDA));
	long currSizeFile = 0.0f;
	
	openFile(ppFile,"a+b");
	while(currSizeFile <= maxSizeFile){ 

		currSizeBlock = 0;
		count = 0;
		i=0;
		while((currSizeBlock + sizeof(DATA)) <= maxSizeBlock){ 	
			count++;//keep count

			//Generete PARTIDA
			randomPartida(ppPartida);
		
			//Generate Data
			id++;
			ppData[i]->id = id;

			//copy the random PARTIDA generated before
			memcpy(&(ppData[i]->partida),(*ppPartida),sizeof(PARTIDA));

			i++;
			currSizeBlock += sizeof(DATA);
		}
		/* printf("cound => %d and %d \n",count,maxSizeBlock/sizeof(DATA)); */
		fDataWriteBlock((*ppFile),ppData,maxSizeBlock/sizeof(DATA));
		currSizeFile += currSizeBlock;//update current size of file
		/* currSizeFile = currentSizeInFile(ppFile); */
		/* printf("currSizeFile %d and maxSizeFile %d\n",currSizeFile,maxSizeFile); */
	}
	closeFile(ppFile);


	for(i=0;i<lenght;i++)
	{
		free(ppData[i]);
		/* ppData[i]->data = (pPARTIDA) malloc(sizeof(PARTIDA)); */
	}
	free(ppData);
	free((*ppPartida));
	free(ppPartida);
}

void readRandomEntriesBlock(int blockSize)
{
	ppPARTIDA ppPartida;
	
	FILE** ppFile;
	ppFile = (FILE**) malloc(sizeof(FILE*));
	ppDATA ppData;
	int i=0;

	int count = 0;
	int id = -1;
	int ask;
	int position;

	//* multiply by 2 just to ensure enougth space
	int lenght = blockSize;
	ppData = (ppDATA) malloc(sizeof(pDATA) * lenght);
	for(i=0;i<lenght;i++)
	{
		ppData[i] = (pDATA) malloc(sizeof(DATA));
		/* ppData[i]->data = (pPARTIDA) malloc(sizeof(PARTIDA)); */
	}

	ppPartida = (ppPARTIDA) malloc(sizeof(pPARTIDA));
	(*ppPartida) = (pPARTIDA) malloc(sizeof(PARTIDA));
	


	printf("Reading the first block ...\n");
	position = -1;
	do{
		position++;

		openFile(ppFile,"r+b");
		fDataReadBlock((*ppFile),ppData,blockSize/(sizeof(DATA)), position);
		
		i=0;
		while(i<blockSize/sizeof(DATA))
		{
			/* memcpy((*ppPartida),ppData[i].partida); */
			printEntries(ppData[i]);
			i++;
		}
		closeFile(ppFile);

		printf("What now?\n");
		printf("[0] Next Block\n");
		printf("[1] Stop reading ...\n");
		scanf("%d",&ask);
	}while(ask == 0);
		



	for(i=0;i<lenght;i++)
	{
		free(ppData[i]);
		/* ppData[i]->data = (pPARTIDA) malloc(sizeof(PARTIDA)); */
	}
	free(ppData);
	free((*ppPartida));
	free(ppPartida);
}
