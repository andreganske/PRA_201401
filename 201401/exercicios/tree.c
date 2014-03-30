#include <stdio.h>
#include "stdlib.h"
#include <string.h>

typedef struct TREE *pTREE,**ppTREE;

typedef struct TREE{
	char data;
	pTREE pLeft;
	pTREE pRight;
}TREE;

void printDataAsChar(pTREE pTree);
pTREE searchTree(pTREE pRoot, int k);
void insertTree(pTREE pRoot, pTREE pNew);
void printTree(pTREE pRoot);
void preOrderTree(pTREE pRoot);
void inOrderTree(pTREE pRoot);
void posOrderTree(pTREE pRoot);


int main(int argc, char **argv)
{
	TREE rootTree;

	rootTree.data = '4';
	rootTree.pLeft = NULL;
	rootTree.pRight = NULL;

	pTREE pNewTree;

	pNewTree = malloc(sizeof(TREE));
	pNewTree->pLeft = NULL;
	pNewTree->pRight = NULL;
	pNewTree->data ='2';    
	insertTree(&rootTree,pNewTree);

	pNewTree = malloc(sizeof(TREE));
	pNewTree->pLeft = NULL;
	pNewTree->pRight = NULL;
	pNewTree->data ='3';
	insertTree(&rootTree,pNewTree);

	pNewTree = malloc(sizeof(TREE));
	pNewTree->pLeft = NULL;
	pNewTree->pRight = NULL;
	pNewTree->data ='5';
	insertTree(&rootTree,pNewTree);

	pNewTree = malloc(sizeof(TREE));
	pNewTree->pLeft = NULL;
	pNewTree->pRight = NULL;
	pNewTree->data ='1';
	insertTree(&rootTree,pNewTree);

	printf("\npreOrderTree()\n");
	preOrderTree(&rootTree);
	printf("\ninOrderTree()\n");
	inOrderTree(&rootTree);
	printf("\nposOrderTree()\n");
	posOrderTree(&rootTree);


	return 0;
}
pTREE searchTree(pTREE pRoot, int k)
{
	if(pRoot != NULL || pRoot->data == k)
	{
		return pRoot;
	}

	if(pRoot->data > k)
	{
		return searchTree(pRoot->pLeft,k);
	}
	else
	{
		return searchTree(pRoot->pRight,k);
	}
}

void printDataAsChar(pTREE pTree)
{
	printf(" %c ",pTree->data);
}


void insertTree(pTREE pRoot, pTREE pNew)
{
	pTREE pCurr, pPrev;

	if(!pRoot)
	{
		pRoot = pNew;
	}
	else
	{
		pCurr = pRoot;        
		while(pCurr)
		{
			pPrev = pCurr;

			if(pCurr->data > pNew->data)
			{
				pCurr = pCurr->pLeft;
			}
			else
			{
				pCurr = pCurr->pRight;
			}
		}
		if(pPrev->data > pNew->data)
		{
			pPrev->pLeft = pNew;
		}
		else
		{
			pPrev->pRight = pNew;
		}
	}    
}


void printTree(pTREE pRoot){
	pTREE pCurr;

	printf("Mostrando a BTree\n");
	if(pRoot != NULL)
	{
		printf(" %c ",pRoot->data);

		pCurr = pRoot->pLeft;        
		while(pCurr)
		{
			printf(" %c ",pCurr->data);
			pCurr = pCurr->pLeft;            
		}

		pCurr = pRoot->pRight;
		while(pCurr)
		{
			printf(" %c ",pCurr->data);
			pCurr = pCurr->pRight;            
		}
	}
}

void preOrderTree(pTREE pRoot)
{
	if(pRoot)
	{
		printDataAsChar(pRoot);
		preOrderTree(pRoot->pLeft);
		preOrderTree(pRoot->pRight);
	}
}

void inOrderTree(pTREE pRoot)
{
	if(pRoot)
	{
		inOrderTree(pRoot->pLeft);
		printDataAsChar(pRoot);        
		inOrderTree(pRoot->pRight);
	}
}

void posOrderTree(pTREE pRoot)
{
	if(pRoot)
	{
		posOrderTree(pRoot->pLeft);                
		posOrderTree(pRoot->pRight);
		printDataAsChar(pRoot);
	}
}
