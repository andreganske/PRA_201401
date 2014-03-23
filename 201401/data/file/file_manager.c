
#include "../../main.h"

void fDataWrite(FILE* pFile, pDATA pData)
{
	if(pFile == NULL)
	{
		fileGenericProblemError();	
	}
	else
	{
		fwrite(pData,1,sizeof(DATA),pFile);
	}
}

void fDataOverWrite(FILE* pFile, pDATA pData, int position)
{
	if(pFile == NULL)
	{
		fileGenericProblemError();	
	}
	else
	{
		fseek(pFile,sizeof(DATA) * position, SEEK_SET);
		fDataWrite(pFile,pData);
	}
}

void fDataRead(FILE* pFile, pDATA pData)
{
	if(pFile == NULL)
	{
		fileGenericProblemError();	
	}
	else
	{
		printf("111###\n");
		fread(pData,1,sizeof(DATA),pFile);
		printf("222###\n");
	}
}

void fDataReadPosition(FILE* pFile, pDATA pData, int position)
{
	if(pFile == NULL)
	{
		fileGenericProblemError();	
	}
	else
	{
		fseek(pFile,sizeof(DATA) * position, SEEK_SET);
		fDataRead(pFile,pData);
	}
}

/**
 * Write in block. This way always append in file
 */
void fDataWriteBlock(FILE* pFile, ppDATA ppData, int quanty)
{
	int i;
	if(pFile == NULL)
	{
		fileGenericProblemError();	
	}
	else
	{
		fwrite((*ppData),quanty,sizeof(DATA) * quanty,pFile);
	}
}

void fDataReadBlock(FILE* pFile, ppDATA ppData, int quanty)
{
	if(pFile == NULL)
	{
		fileGenericProblemError();	
	}
	else
	{

	}
}

void fileGenericProblemError()
{
	perror("\nError operating file!\n");
	exit(1);
}
