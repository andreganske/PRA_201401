/**
 * This code is under GNU License Version 3.
 * 
 * Create by Andre Ganske and Weskley Migliorini
 */

/**************************************************************************************/
// Including some library
#include <string.h>
#include <stdio.h>
#include <time.h>

/**************************************************************************************/
// Define struct
typedef struct {
	
	unsigned int id;
	int data;

} DAO;

DAO dao;

DAO* block;

/**************************************************************************************/
// Externalise functions

 // persiste entries
void saveOneEntry();
void saveMultipleEntries();

// findind entries
DAO getOneEntry();
DAO getMultipleEntries();

// generic functions
int getInsertPosition();
int getInsertQuantity();
void countFileLines();

void printEntries(DAO* block, int quantity);
